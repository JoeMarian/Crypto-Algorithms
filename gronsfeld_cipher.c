#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to repeat numeric key to match message length
void generateKey(char* input, char* numericKey, int keySequence[]) {
    int inputLen = strlen(input);
    int keyLen = strlen(numericKey);

    for (int i = 0; i < inputLen; i++) {
        if (isdigit(numericKey[i % keyLen])) {
            keySequence[i] = numericKey[i % keyLen] - '0';
        } else {
            keySequence[i] = 0; // default to 0 if not a digit
        }
    }
}

void gronsfeldEncrypt(char* input, char* numericKey, char* output) {
    int keySequence[1000];
    generateKey(input, numericKey, keySequence);

    for (int i = 0; input[i] != '\0'; i++) {
        char ch = input[i];
        if (isalpha(ch)) {
            int shift = keySequence[i];
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

void gronsfeldDecrypt(char* input, char* numericKey, char* output) {
    int keySequence[1000];
    generateKey(input, numericKey, keySequence);

    for (int i = 0; input[i] != '\0'; i++) {
        char ch = input[i];
        if (isalpha(ch)) {
            int shift = keySequence[i];
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
    char input[1000], key[100], output[1000];

    printf("Choose an operation:\n");
    printf("E - Encrypt\n");
    printf("D - Decrypt\n");
    printf("Enter your choice: ");
    scanf(" %c", &choice);
    getchar(); // flush newline

    if (choice == 'E' || choice == 'e' || choice == 'D' || choice == 'd') {
        printf("Enter your message: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        printf("Enter numeric key (digits only, like 31415): ");
        fgets(key, sizeof(key), stdin);
        key[strcspn(key, "\n")] = '\0';

        if (choice == 'E' || choice == 'e') {
            gronsfeldEncrypt(input, key, output);
            printf("Encrypted Message: %s\n", output);
        } else {
            gronsfeldDecrypt(input, key, output);
            printf("Decrypted Message: %s\n", output);
        }
    } else {
        printf("Invalid choice. Please enter E or D.\n");
    }

    return 0;
}
