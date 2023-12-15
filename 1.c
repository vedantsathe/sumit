#include <stdio.h>

#define MAX 10

typedef struct {
    int row;
    int col;
    int value;
} Element;

typedef struct {
    Element data[MAX];
    int rows, cols, numTerms;
} SparseMatrix;

SparseMatrix transposeSimple(SparseMatrix matrix) {
    SparseMatrix result;
    int b, term, i;

    result.rows = matrix.cols;
    result.cols = matrix.rows;
    result.numTerms = matrix.numTerms;

    if (result.numTerms > 0) {
        b = 0;
        for (term = 0; term < matrix.numTerms; term++) {
            for (i = 0; i < matrix.cols; i++) {
                if (matrix.data[term].col == i) {
                    result.data[b].row = matrix.data[term].col;
                    result.data[b].col = matrix.data[term].row;
                    result.data[b].value = matrix.data[term].value;
                    b++;
                }
            }
        }
    }

    return result;
}

SparseMatrix transposeFast(SparseMatrix matrix) {
    SparseMatrix result;
    int rowTerms[MAX], startingPos[MAX], i, j;

    result.rows = matrix.cols;
    result.cols = matrix.rows;
    result.numTerms = matrix.numTerms;

    if (result.numTerms > 0) {
        for (i = 0; i < matrix.cols; i++) {
            rowTerms[i] = 0;
        }

        for (i = 0; i < matrix.numTerms; i++) {
            rowTerms[matrix.data[i].col]++;
        }

        startingPos[0] = 0;
        for (i = 1; i < matrix.cols; i++) {
            startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
        }

        for (i = 0; i < matrix.numTerms; i++) {
            j = startingPos[matrix.data[i].col]++;
            result.data[j].row = matrix.data[i].col;
            result.data[j].col = matrix.data[i].row;
            result.data[j].value = matrix.data[i].value;
        }
    }

    return result;
}

void displayMatrix(SparseMatrix matrix) {
    int i, j, k;

    k = 0;
    for (i = 0; i < matrix.rows; i++) {
        for (j = 0; j < matrix.cols; j++) {
            if (k < matrix.numTerms && i == matrix.data[k].row && j == matrix.data[k].col) {
                printf("%d\t", matrix.data[k].value);
                k++;
            } else {
                printf("0\t");
            }
        }
        printf("\n");
    }
}

int main() {
    SparseMatrix matrix, result;

    printf("Enter number of rows and columns: ");
    scanf("%d %d", &matrix.rows, &matrix.cols);

    printf("Enter number of non-zero elements: ");
    scanf("%d", &matrix.numTerms);

    printf("Enter matrix elements (row col value):\n");
    for (int i = 0; i < matrix.numTerms; i++) {
        scanf("%d %d %d", &matrix.data[i].row, &matrix.data[i].col, &matrix.data[i].value);
    }

    printf("\nOriginal Matrix:\n");
    displayMatrix(matrix);

    result = transposeSimple(matrix);

    printf("\nSimple Transpose:\n");
    displayMatrix(result);

    result = transposeFast(matrix);

    printf("\nFast Transpose:\n");
    displayMatrix(result);

    return 0;
}
