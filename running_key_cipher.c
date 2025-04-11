#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Encrypt the message using Running Key Cipher
void encrypt(char* plaintext, char* runningKey, char* ciphertext) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i++) {
        if (isalpha(plaintext[i]) && isalpha(runningKey[i])) {
            int p = toupper(plaintext[i]) - 'A';
            int k = toupper(runningKey[i]) - 'A';
            int c = (p + k) % 26;
            ciphertext[i] = isupper(plaintext[i]) ? ('A' + c) : ('a' + c);
        } else {
            ciphertext[i] = plaintext[i];  // keep spaces/punctuations
        }
    }
    ciphertext[len] = '\0';
}

// Decrypt the message using Running Key Cipher
void decrypt(char* ciphertext, char* runningKey, char* plaintext) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (isalpha(ciphertext[i]) && isalpha(runningKey[i])) {
            int c = toupper(ciphertext[i]) - 'A';
            int k = toupper(runningKey[i]) - 'A';
            int p = (c - k + 26) % 26;
            plaintext[i] = isupper(ciphertext[i]) ? ('A' + p) : ('a' + p);
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[len] = '\0';
}

int main() {
    char input[1000], runningKey[1000], output[1000];
    char choice;

    printf("=== Running Key Cipher ===\n");
    printf("Encrypt or Decrypt? (E/D): ");
    scanf(" %c", &choice);
    getchar(); // consume newline

    printf("Enter message: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    printf("Enter running key (must be at least as long as message): ");
    fgets(runningKey, sizeof(runningKey), stdin);
    runningKey[strcspn(runningKey, "\n")] = '\0';

    if (strlen(runningKey) < strlen(input)) {
        printf("Error: Running key must be at least as long as the message!\n");
        return 1;
    }

    if (choice == 'E' || choice == 'e') {
        encrypt(input, runningKey, output);
        printf("Encrypted: %s\n", output);
    } else if (choice == 'D' || choice == 'd') {
        decrypt(input, runningKey, output);
        printf("Decrypted: %s\n", output);
    } else {
        printf("Invalid choice. Use E or D.\n");
    }

    return 0;
}
