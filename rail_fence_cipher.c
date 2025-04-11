#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void encryptRailFence(char* text, int key, char* result) {
    int len = strlen(text);
    char rail[key][len];
    for (int i = 0; i < key; i++)
        for (int j = 0; j < len; j++)
            rail[i][j] = '\n';

    int row = 0, dir_down = 0;

    for (int i = 0; i < len; i++) {
        rail[row][i] = text[i];

        if (row == 0 || row == key - 1)
            dir_down = !dir_down;

        row += dir_down ? 1 : -1;
    }

    int idx = 0;
    for (int i = 0; i < key; i++)
        for (int j = 0; j < len; j++)
            if (rail[i][j] != '\n')
                result[idx++] = rail[i][j];
    result[idx] = '\0';
}

void decryptRailFence(char* cipher, int key, char* result) {
    int len = strlen(cipher);
    char rail[key][len];
    for (int i = 0; i < key; i++)
        for (int j = 0; j < len; j++)
            rail[i][j] = '\n';

    int row = 0, dir_down = 0;

    // Mark the positions to fill
    for (int i = 0; i < len; i++) {
        rail[row][i] = '*';

        if (row == 0 || row == key - 1)
            dir_down = !dir_down;

        row += dir_down ? 1 : -1;
    }

    int index = 0;
    for (int i = 0; i < key; i++)
        for (int j = 0; j < len; j++)
            if (rail[i][j] == '*' && index < len)
                rail[i][j] = cipher[index++];

    row = 0, dir_down = 0;
    int idx = 0;
    for (int i = 0; i < len; i++) {
        result[idx++] = rail[row][i];

        if (row == 0 || row == key - 1)
            dir_down = !dir_down;

        row += dir_down ? 1 : -1;
    }
    result[idx] = '\0';
}

void cleanText(char* input, char* cleaned) {
    int j = 0;
    for (int i = 0; input[i]; i++) {
        if (isalpha(input[i])) {
            cleaned[j++] = toupper(input[i]);
        }
    }
    cleaned[j] = '\0';
}

int main() {
    char input[1000], cleaned[1000], result[1000];
    int key;
    char choice;

    printf("Encrypt or Decrypt? (E/D): ");
    scanf(" %c", &choice);
    getchar();

    printf("Enter the message: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    printf("Enter the number of rails: ");
    scanf("%d", &key);

    cleanText(input, cleaned);

    if (choice == 'E' || choice == 'e') {
        encryptRailFence(cleaned, key, result);
        printf("Encrypted message: %s\n", result);
    } else {
        decryptRailFence(cleaned, key, result);
        printf("Decrypted message: %s\n", result);
    }

    return 0;
}
