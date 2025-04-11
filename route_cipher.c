#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 1000

void cleanText(char* src, char* dest) {
    int j = 0;
    for (int i = 0; src[i]; i++) {
        if (isalpha(src[i])) {
            dest[j++] = toupper(src[i]);
        }
    }
    dest[j] = '\0';
}

void encryptRoute(char* msg, int rows, int cols, char* cipher) {
    int len = strlen(msg);
    int total = rows * cols;
    char mat[rows][cols];

    for (int i = 0; i < total; i++) {
        if (i < len)
            msg[i] = toupper(msg[i]);
        else
            msg[i] = 'X'; // padding
    }

    // Fill matrix row-wise
    int k = 0;
    for (int i = 0; i < rows && k < total; i++) {
        for (int j = 0; j < cols && k < total; j++) {
            mat[i][j] = msg[k++];
        }
    }

    // Spiral traversal
    int top = 0, bottom = rows - 1, left = 0, right = cols - 1;
    k = 0;
    while (top <= bottom && left <= right) {
        for (int i = top; i <= bottom; i++)
            cipher[k++] = mat[i][left];
        left++;

        for (int i = left; i <= right; i++)
            cipher[k++] = mat[bottom][i];
        bottom--;

        if (left <= right) {
            for (int i = bottom; i >= top; i--)
                cipher[k++] = mat[i][right];
            right--;
        }

        if (top <= bottom) {
            for (int i = right; i >= left; i--)
                cipher[k++] = mat[top][i];
            top++;
        }
    }
    cipher[k] = '\0';
}

void decryptRoute(char* cipher, int rows, int cols, char* plain) {
    int total = rows * cols;
    char mat[rows][cols];

    // Spiral fill
    int top = 0, bottom = rows - 1, left = 0, right = cols - 1;
    int k = 0;
    while (top <= bottom && left <= right && k < total) {
        for (int i = top; i <= bottom && k < total; i++)
            mat[i][left] = cipher[k++];
        left++;

        for (int i = left; i <= right && k < total; i++)
            mat[bottom][i] = cipher[k++];
        bottom--;

        if (left <= right) {
            for (int i = bottom; i >= top && k < total; i--)
                mat[i][right] = cipher[k++];
            right--;
        }

        if (top <= bottom) {
            for (int i = right; i >= left && k < total; i--)
                mat[top][i] = cipher[k++];
            top++;
        }
    }

    // Read matrix row-wise
    k = 0;
    for (int i = 0; i < rows && k < total; i++) {
        for (int j = 0; j < cols && k < total; j++) {
            plain[k++] = mat[i][j];
        }
    }
    plain[k] = '\0';
}

int main() {
    char input[MAX], cleaned[MAX], result[MAX];
    char choice;
    int rows, cols;

    printf("Encrypt or Decrypt? (E/D): ");
    scanf(" %c", &choice);
    getchar();

    printf("Enter the message: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    printf("Enter number of rows: ");
    scanf("%d", &rows);
    printf("Enter number of columns: ");
    scanf("%d", &cols);

    cleanText(input, cleaned);

    if (choice == 'E' || choice == 'e') {
        encryptRoute(cleaned, rows, cols, result);
        printf("Encrypted message: %s\n", result);
    } else {
        decryptRoute(cleaned, rows, cols, result);
        printf("Decrypted message: %s\n", result);
    }

    return 0;
}
