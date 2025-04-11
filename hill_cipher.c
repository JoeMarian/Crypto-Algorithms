#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int mod26(int x) {
    return (x % 26 + 26) % 26;
}

// Find mod inverse of determinant
int modInverse(int det) {
    det = mod26(det);
    for (int i = 1; i < 26; i++) {
        if ((det * i) % 26 == 1) return i;
    }
    return -1;
}

// Calculate determinant (only for 2x2 for simplicity here)
int determinant2x2(int** key) {
    return mod26(key[0][0]*key[1][1] - key[0][1]*key[1][0]);
}

// Invert a 2x2 matrix mod 26
void inverseMatrix2x2(int** key, int** invKey) {
    int det = determinant2x2(key);
    int invDet = modInverse(det);

    if (invDet == -1) {
        printf("Invalid key matrix! No modular inverse exists.\n");
        exit(1);
    }

    invKey[0][0] = mod26(invDet * key[1][1]);
    invKey[0][1] = mod26(-invDet * key[0][1]);
    invKey[1][0] = mod26(-invDet * key[1][0]);
    invKey[1][1] = mod26(key[0][0] * invDet);
}

// Encrypt block
void multiplyBlock(int* block, int** key, int size, char* result) {
    for (int i = 0; i < size; i++) {
        int val = 0;
        for (int j = 0; j < size; j++) {
            val += key[i][j] * block[j];
        }
        result[i] = mod26(val) + 'A';
    }
}

// Clean message and pad with X
void cleanMessage(char* input, char* output, int size) {
    int len = 0;
    for (int i = 0; input[i]; i++) {
        if (isalpha(input[i])) {
            output[len++] = toupper(input[i]);
        }
    }
    while (len % size != 0) {
        output[len++] = 'X';
    }
    output[len] = '\0';
}

int main() {
    int size;
    printf("Enter matrix size (only 2 supported): ");
    scanf("%d", &size);

    if (size != 2) {
        printf("Only 2x2 matrix is supported in this version.\n");
        return 1;
    }

    // Allocate key matrix
    int** key = malloc(size * sizeof(int*));
    int** invKey = malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        key[i] = malloc(size * sizeof(int));
        invKey[i] = malloc(size * sizeof(int));
    }

    printf("Enter %dx%d key matrix values (0-25):\n", size, size);
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            scanf("%d", &key[i][j]);

    getchar(); // consume newline
    char choice;
    printf("Encrypt or Decrypt? (E/D): ");
    scanf(" %c", &choice);
    getchar();

    char input[1000], cleaned[1000];
    printf("Enter message: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    cleanMessage(input, cleaned, size);

    printf("%s message:\n", (choice == 'E' || choice == 'e') ? "Encrypted" : "Decrypted");

    for (int i = 0; i < strlen(cleaned); i += size) {
        int block[10];
        for (int j = 0; j < size; j++)
            block[j] = cleaned[i + j] - 'A';

        char result[10];

        if (choice == 'E' || choice == 'e')
            multiplyBlock(block, key, size, result);
        else {
            inverseMatrix2x2(key, invKey);
            multiplyBlock(block, invKey, size, result);
        }

        for (int j = 0; j < size; j++)
            printf("%c", result[j]);
    }
    printf("\n");

    for (int i = 0; i < size; i++) {
        free(key[i]);
        free(invKey[i]);
    }
    free(key);
    free(invKey);

    return 0;
}
