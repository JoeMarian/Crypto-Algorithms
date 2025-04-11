#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 1000

void cleanInput(char *input, char *output) {
    int j = 0;
    for (int i = 0; input[i]; i++) {
        if (isalpha(input[i])) {
            output[j++] = toupper(input[i]);
        }
    }
    output[j] = '\0';
}

void getColumnOrder(char *key, int *order) {
    int len = strlen(key);
    for (int i = 0; i < len; i++) {
        int rank = 1;
        for (int j = 0; j < len; j++) {
            if (key[j] < key[i])
                rank++;
        }
        order[i] = rank;
    }
}

void encryptAugust(char *plain, char *key, char *cipher) {
    int len = strlen(plain);
    int keyLen = strlen(key);
    int rows = (len + keyLen - 1) / keyLen;
    char matrix[rows][keyLen];
    int k = 0;

    // Fill matrix row-wise
    for (int i = 0; i < rows * keyLen; i++) {
        int r = i / keyLen;
        int c = i % keyLen;
        if (k < len)
            matrix[r][c] = plain[k++];
        else
            matrix[r][c] = 'X'; // Padding
    }

    int order[keyLen];
    getColumnOrder(key, order);

    // Read by column order
    k = 0;
    for (int rnk = 1; rnk <= keyLen; rnk++) {
        for (int col = 0; col < keyLen; col++) {
            if (order[col] == rnk) {
                for (int row = 0; row < rows; row++) {
                    cipher[k++] = matrix[row][col];
                }
            }
        }
    }
    cipher[k] = '\0';
}

int main() {
    char input[MAX], clean[MAX], key[] = "AUGUST", encrypted[MAX];

    printf("Enter your message: ");
    fgets(input, MAX, stdin);
    input[strcspn(input, "\n")] = '\0';

    cleanInput(input, clean);

    encryptAugust(clean, key, encrypted);

    printf("Encrypted (August Cipher): %s\n", encrypted);

    return 0;
}
