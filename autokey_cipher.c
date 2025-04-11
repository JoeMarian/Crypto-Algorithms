#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Generate extended key for encryption using the plaintext
void generateKeyEncrypt(char* input, char* key, char* extendedKey) {
    int inputLen = strlen(input);
    int keyLen = strlen(key);
    int i;

    for (i = 0; i < keyLen && i < inputLen; i++) {
        extendedKey[i] = key[i];
    }

    for (int j = 0; i < inputLen; i++, j++) {
        extendedKey[i] = input[j];
    }
    extendedKey[inputLen] = '\0';
}

void generateKeyDecrypt(char* input, char* key, char* extendedKey) {
    int inputLen = strlen(input);
    int keyLen = strlen(key);
    strcpy(extendedKey, key);

    for (int i = keyLen; i < inputLen; i++) {
        extendedKey[i] = 'A'; 
    }
    extendedKey[inputLen] = '\0';
}

// Encryption function
void encrypt(char* input, char* key, char* output) {
    char extendedKey[1000];
    generateKeyEncrypt(input, key, extendedKey);

    for (int i = 0; input[i] != '\0'; i++) {
        if (isalpha(input[i])) {
            int val = ((toupper(input[i]) - 'A') + (toupper(extendedKey[i]) - 'A')) % 26;
            output[i] = (isupper(input[i]) ? 'A' : 'a') + val;
        } else {
            output[i] = input[i];
        }
    }
    output[strlen(input)] = '\0';
}

// Decryption function
void decrypt(char* input, char* key, char* output) {
    char extendedKey[1000];
    generateKeyDecrypt(input, key, extendedKey);

    for (int i = 0; input[i] != '\0'; i++) {
        if (isalpha(input[i])) {
            int val = ((toupper(input[i]) - 'A') - (toupper(extendedKey[i]) - 'A') + 26) % 26;
            output[i] = (isupper(input[i]) ? 'A' : 'a') + val;

            // Now extend the key using decrypted text
            extendedKey[i + strlen(key)] = toupper(output[i]);
        } else {
            output[i] = input[i];
        }
    }
    output[strlen(input)] = '\0';
}

int main() {
    char input[1000], key[1000], output[1000];
    char choice;

    printf("=== Auto Key Cipher ===\n");
    printf("Encrypt or Decrypt? (E/D): ");
    scanf(" %c", &choice);
    getchar(); // Consume newline

    printf("Enter message: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    printf("Enter key (only letters): ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';

    if (choice == 'E' || choice == 'e') {
        encrypt(input, key, output);
        printf("Encrypted Message: %s\n", output);
    } else if (choice == 'D' || choice == 'd') {
        decrypt(input, key, output);
        printf("Decrypted Message: %s\n", output);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}
