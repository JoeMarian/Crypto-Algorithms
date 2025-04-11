#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to repeat the key to match input length
void generateKey(char* str, char* key) {
    int strLen = strlen(str);
    int keyLen = strlen(key);
    for (int i = 0; i < strLen; i++) {
        key[i] = key[i % keyLen];
    }
    key[strLen] = '\0';
}

// Encrypt using Vigenere Cipher
void vigenereEncrypt(char* input, char* key, char* output) {
    for (int i = 0; input[i] != '\0'; i++) {
        char ch = input[i];
        if (isalpha(ch)) {
            int shift = tolower(key[i]) - 'a';
            if (islower(ch))
                output[i] = ((ch - 'a' + shift) % 26) + 'a';
            else
                output[i] = ((ch - 'A' + shift) % 26) + 'A';
        } else {
            output[i] = ch;
        }
    }
    output[strlen(input)] = '\0';
}

// Decrypt using Vigenere Cipher
void vigenereDecrypt(char* input, char* key, char* output) {
    for (int i = 0; input[i] != '\0'; i++) {
        char ch = input[i];
        if (isalpha(ch)) {
            int shift = tolower(key[i]) - 'a';
            if (islower(ch))
                output[i] = ((ch - 'a' - shift + 26) % 26) + 'a';
            else
                output[i] = ((ch - 'A' - shift + 26) % 26) + 'A';
        } else {
            output[i] = ch;
        }
    }
    output[strlen(input)] = '\0';
}

int main() {
    char choice;
    char input[1000], key[1000], newKey[1000], output[1000];

    printf("Choose an operation:\n");
    printf("E - Encrypt\n");
    printf("D - Decrypt\n");
    printf("Enter your choice: ");
    scanf(" %c", &choice);
    getchar(); // Clear newline from buffer

    if (choice == 'E' || choice == 'e' || choice == 'D' || choice == 'd') {
        printf("Enter your message: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // remove newline

        printf("Enter keyword: ");
        fgets(key, sizeof(key), stdin);
        key[strcspn(key, "\n")] = '\0'; // remove newline

        generateKey(input, key);  // key gets stored in 'key' itself

        if (choice == 'E' || choice == 'e') {
            vigenereEncrypt(input, key, output);
            printf("Encrypted Message: %s\n", output);
        } else {
            vigenereDecrypt(input, key, output);
            printf("Decrypted Message: %s\n", output);
        }
    } else {
        printf("Invalid choice. Please enter E or D.\n");
    }

    return 0;
}
