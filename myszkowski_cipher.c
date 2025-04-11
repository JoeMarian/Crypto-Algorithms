#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXT 1000
#define MAX_KEY 100

void cleanText(char* src, char* dest) {
    int j = 0;
    for (int i = 0; src[i]; i++) {
        if (isalpha(src[i]))
            dest[j++] = toupper(src[i]);
    }
    dest[j] = '\0';
}

void assignRanks(char* key, int* ranks) {
    int len = strlen(key);
    for (int i = 0; i < len; i++) {
        int rank = 1;
        for (int j = 0; j < len; j++) {
            if (key[j] < key[i]) rank++;
        }
        ranks[i] = rank;
    }
}

void encryptMyszkowski(char* plaintext, char* key, char* ciphertext) {
    int ranks[MAX_KEY];
    assignRanks(key, ranks);

    int keyLen = strlen(key);
    int textLen = strlen(plaintext);
    int rows = (textLen + keyLen - 1) / keyLen;

    char matrix[rows][keyLen];
    int k = 0;

    for (int i = 0; i < rows * keyLen; i++) {
        int r = i / keyLen, c = i % keyLen;
        matrix[r][c] = (k < textLen) ? plaintext[k++] : 'X';
    }

    k = 0;
    for (int rank = 1; rank <= keyLen; rank++) {
        for (int col = 0; col < keyLen; col++) {
            if (ranks[col] == rank) {
                for (int row = 0; row < rows; row++) {
                    ciphertext[k++] = matrix[row][col];
                }
            }
        }
    }
    ciphertext[k] = '\0';
}

int main() {
    char input[MAX_TEXT], cleaned[MAX_TEXT], key[MAX_KEY], result[MAX_TEXT];

    printf("Enter the message: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    printf("Enter the keyword (can have repeated letters): ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';

    cleanText(input, cleaned);
    cleanText(key, key);  // Clean key too

    encryptMyszkowski(cleaned, key, result);
    printf("Encrypted message: %s\n", result);

    return 0;
}
