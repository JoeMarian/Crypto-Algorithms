#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to find modular inverse of a under modulo m
int modInverse(int a, int m) {
    for (int i = 1; i < m; i++) {
        if ((a * i) % m == 1)
            return i;
    }
    return -1;  // No inverse exists if a and m aren't coprime
}

void affineEncrypt(char* input, char* output, int a, int b) {
    for (int i = 0; input[i] != '\0'; ++i) {
        char ch = input[i];
        if (isalpha(ch)) {
            if (islower(ch))
                output[i] = ((a * (ch - 'a') + b) % 26) + 'a';
            else
                output[i] = ((a * (ch - 'A') + b) % 26) + 'A';
        } else {
            output[i] = ch;
        }
    }
    output[strlen(input)] = '\0';
}

void affineDecrypt(char* input, char* output, int a, int b) {
    int a_inv = modInverse(a, 26);
    if (a_inv == -1) {
        printf("Error: 'a' (%d) has no modular inverse under mod 26. Choose a value coprime to 26.\n", a);
        return;
    }

    for (int i = 0; input[i] != '\0'; ++i) {
        char ch = input[i];
        if (isalpha(ch)) {
            if (islower(ch))
                output[i] = (a_inv * ((ch - 'a' - b + 26)) % 26) + 'a';
            else
                output[i] = (a_inv * ((ch - 'A' - b + 26)) % 26) + 'A';
        } else {
            output[i] = ch;
        }
    }
    output[strlen(input)] = '\0';
}

int main() {
    char choice;
    char input[1000], output[1000];
    int a, b;

    printf("Choose an operation:\n");
    printf("E - Encrypt\n");
    printf("D - Decrypt\n");
    printf("Enter your choice: ");
    scanf(" %c", &choice);
    getchar();  // Flush newline

    if (choice == 'E' || choice == 'e' || choice == 'D' || choice == 'd') {
        printf("Enter your message: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        printf("Enter value of 'a' (must be coprime to 26): ");
        scanf("%d", &a);
        printf("Enter value of 'b': ");
        scanf("%d", &b);

        if (choice == 'E' || choice == 'e') {
            affineEncrypt(input, output, a, b);
            printf("Encrypted Message: %s\n", output);
        } else {
            affineDecrypt(input, output, a, b);
            printf("Decrypted Message: %s\n", output);
        }
    } else {
        printf("Invalid choice. Please enter E or D.\n");
    }

    return 0;
}
