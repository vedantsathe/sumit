#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5

struct CircularQueue {
    int front, rear;
    int capacity;
    int* array;
};

struct CircularQueue* createCircularQueue(int capacity) {
    struct CircularQueue* queue = (struct CircularQueue*)malloc(sizeof(struct CircularQueue));
    queue->capacity = capacity;
    queue->front = queue->rear = -1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

int isFull(struct CircularQueue* queue) {
    return (queue->front == 0 && queue->rear == queue->capacity - 1) ||
           (queue->front == queue->rear + 1);
}

int isEmpty(struct CircularQueue* queue) {
    return queue->front == -1;
}

void enqueue(struct CircularQueue* queue, int item) {
    if (isFull(queue)) {
        printf("Queue is full. Cannot enqueue.\n");
        return;
    }

    if (isEmpty(queue)) {
        queue->front = queue->rear = 0;
    } else if (queue->rear == queue->capacity - 1) {
        queue->rear = 0;
    } else {
        queue->rear++;
    }

    queue->array[queue->rear] = item;
    printf("Enqueued %d to the queue.\n", item);
}

int dequeue(struct CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return -1;
    }

    int item = queue->array[queue->front];

    if (queue->front == queue->rear) {
        queue->front = queue->rear = -1;
    } else if (queue->front == queue->capacity - 1) {
        queue->front = 0;
    } else {
        queue->front++;
    }

    printf("Dequeued %d from the queue.\n", item);
    return item;
}

void display(struct CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Circular Queue: ");
    int i = queue->front;

    do {
        printf("%d ", queue->array[i]);

        if (i == queue->rear && queue->front != queue->rear) {
            break;
        }

        i = (i + 1) % queue->capacity;

    } while (i != (queue->rear + 1) % queue->capacity);

    printf("\n");
}

void freeQueue(struct CircularQueue* queue) {
    free(queue->array);
    free(queue);
}

int main() {
    struct CircularQueue* queue = createCircularQueue(MAX_SIZE);

    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    enqueue(queue, 40);
    enqueue(queue, 50);

    display(queue);

    dequeue(queue);
    dequeue(queue);

    display(queue);

    enqueue(queue, 60);
    enqueue(queue, 70);

    display(queue);

    freeQueue(queue);

    return 0;
}

