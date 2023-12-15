#include <stdio.h>
#include <stdlib.h>

struct Car {
    char modelName[50];
    float price;
    char manufacturer[50];
    float engineCapacity;
    struct Car* prev;
    struct Car* next;
};

struct Car* createCarNode(char modelName[], float price, char manufacturer[], float engineCapacity) {
    struct Car* newCar = (struct Car*)malloc(sizeof(struct Car));
    strcpy(newCar->modelName, modelName);
    newCar->price = price;
    strcpy(newCar->manufacturer, manufacturer);
    newCar->engineCapacity = engineCapacity;
    newCar->prev = NULL;
    newCar->next = NULL;
    return newCar;
}

struct Car* insertCarNode(struct Car* head, char modelName[], float price, char manufacturer[], float engineCapacity) {
    struct Car* newCar = createCarNode(modelName, price, manufacturer, engineCapacity);
    if (head == NULL) {
        return newCar;
    }

    newCar->next = head;
    head->prev = newCar;
    return newCar;
}

struct Car* deleteCarNode(struct Car* head, char modelName[]) {
    struct Car* current = head;

    while (current != NULL) {
        if (strcmp(current->modelName, modelName) == 0) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                head = current->next;
            }

            if (current->next != NULL) {
                current->next->prev = current->prev;
            }

            free(current);
            printf("Car model %s deleted successfully.\n", modelName);
            return head;
        }

        current = current->next;
    }

    printf("Car model %s not found.\n", modelName);
    return head;
}

void updateCarPrice(struct Car* head, char modelName[], float newPrice) {
    struct Car* current = head;

    while (current != NULL) {
        if (strcmp(current->modelName, modelName) == 0) {
            current->price = newPrice;
            printf("Price for car model %s updated successfully.\n", modelName);
            return;
        }

        current = current->next;
    }

    printf("Car model %s not found.\n", modelName);
}

void listCarsInPriceRange(struct Car* head, float minPrice, float maxPrice) {
    struct Car* current = head;
    int found = 0;

    printf("Car models within the price range %.2f to %.2f:\n", minPrice, maxPrice);

    while (current != NULL) {
        if (current->price >= minPrice && current->price <= maxPrice) {
            printf("Model: %s, Price: %.2f, Manufacturer: %s, Engine Capacity: %.2f\n",
                   current->modelName, current->price, current->manufacturer, current->engineCapacity);
            found = 1;
        }
        current = current->next;
    }

    if (!found) {
        printf("No car models found in the specified price range.\n");
    }
}

void displayCarList(struct Car* head) {
    struct Car* current = head;

    printf("Car Model List:\n");

    while (current != NULL) {
        printf("Model: %s, Price: %.2f, Manufacturer: %s, Engine Capacity: %.2f\n",
               current->modelName, current->price, current->manufacturer, current->engineCapacity);
        current = current->next;
    }

    printf("\n");
}

void freeCarList(struct Car* head) {
    struct Car* temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    struct Car* carList = NULL;
    int choice;
    char modelName[50];
    float price, engineCapacity, minPrice, maxPrice;
    char manufacturer[50];

    do {
        printf("\nMenu:\n");
        printf("1. Insert New Car Model\n");
        printf("2. Delete Obsolete Car Model\n");
        printf("3. Update Car Price\n");
        printf("4. List Cars in Price Range\n");
        printf("5. Display Car Model List\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Car Model Name: ");
                scanf("%s", modelName);
                printf("Enter Price: ");
                scanf("%f", &price);
                printf("Enter Manufacturer: ");
                scanf("%s", manufacturer);
                printf("Enter Engine Capacity: ");
                scanf("%f", &engineCapacity);
                carList = insertCarNode(carList, modelName, price, manufacturer, engineCapacity);
                printf("Car model %s inserted successfully.\n", modelName);
                break;
            case 2:
                printf("Enter Car Model Name to Delete: ");
                scanf("%s", modelName);
                carList = deleteCarNode(carList, modelName);
                break;
            case 3:
                printf("Enter Car Model Name to Update Price: ");
                scanf("%s", modelName);
                printf("Enter New Price: ");
                scanf("%f", &price);
                updateCarPrice(carList, modelName, price);
                break;
            case 4:
                printf("Enter Minimum Price: ");
                scanf("%f", &minPrice);
                printf("Enter Maximum Price: ");
                scanf("%f", &maxPrice);
                listCarsInPriceRange(carList, minPrice, maxPrice);
                break;
            case 5:
                displayCarList(carList);
                break;
            case 6:
                freeCarList(carList);
                printf("Program terminated successfully.\n");
                exit(0);
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (1);

    return 0;
}

