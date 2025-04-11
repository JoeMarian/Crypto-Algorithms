#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Encrypt function
void caesarEncrypt(char *input, char *output, int key) {
    for (int i = 0; input[i] != '\0'; i++) {
        char ch = input[i];
        if (isalpha(ch)) {
            if (isupper(ch)) {
                output[i] = ((ch - 'A' + key) % 26) + 'A';
            } else {
                output[i] = ((ch - 'a' + key) % 26) + 'a';
            }
        } else {
            output[i] = ch;
        }
    }
    output[strlen(input)] = '\0';
}

// Decrypt function
void caesarDecrypt(char *input, char *output, int key) {
    for (int i = 0; input[i] != '\0'; i++) {
        char ch = input[i];
        if (isalpha(ch)) {
            if (isupper(ch)) {
                output[i] = ((ch - 'A' - key + 26) % 26) + 'A';
            } else {
                output[i] = ((ch - 'a' - key + 26) % 26) + 'a';
            }
        } else {
            output[i] = ch;
        }
    }
    output[strlen(input)] = '\0';
}

int main() {
    char choice;
    char input[1000], output[1000];
    int key;

    printf("Choose an operation:\n");
    printf("E - Encrypt\n");
    printf("D - Decrypt\n");
    printf("Enter your choice: ");
    scanf(" %c", &choice);
    getchar();  // Clear newline from buffer

    if (choice == 'E' || choice == 'e' || choice == 'D' || choice == 'd') {
        printf("Enter your message: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        printf("Enter the shift key (number): ");
        scanf("%d", &key);

        if (choice == 'E' || choice == 'e') {
            caesarEncrypt(input, output, key);
            printf("Encrypted Message: %s\n", output);
        } else {
            caesarDecrypt(input, output, key);
            printf("Decrypted Message: %s\n", output);
        }
    } else {
        printf("Invalid choice. Please enter E or D.\n");
    }

    return 0;
}
