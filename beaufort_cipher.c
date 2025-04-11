#include <stdio.h>
#include <string.h>
#include <ctype.h>

void generateKey(char* input, char* key, char* repeatedKey) {
    int inputLen = strlen(input);
    int keyLen = strlen(key);
    for (int i = 0; i < inputLen; i++) {
        repeatedKey[i] = key[i % keyLen];
    }
    repeatedKey[inputLen] = '\0';
}

void beaufortCipher(char* input, char* key, char* output) {
    for (int i = 0; input[i] != '\0'; i++) {
        char ch = input[i];
        if (isalpha(ch)) {
            int keyVal = tolower(key[i]) - 'a';
            int chVal = tolower(ch) - 'a';
            int resultVal = (26 + keyVal - chVal) % 26;

            output[i] = isupper(ch) ? (resultVal + 'A') : (resultVal + 'a');
        } else {
            output[i] = ch; 
        }
    }
    output[strlen(input)] = '\0';
}

int main() {
    char input[1000], key[1000], repeatedKey[1000], output[1000];
    char choice;

    printf("=== Beaufort Cipher ===\n");
    printf("Encrypt or Decrypt? (E/D): ");
    scanf(" %c", &choice);
    getchar(); // to consume newline

    if (choice == 'E' || choice == 'e' || choice == 'D' || choice == 'd') {
        printf("Enter message: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        printf("Enter key: ");
        fgets(key, sizeof(key), stdin);
        key[strcspn(key, "\n")] = '\0';

        generateKey(input, key, repeatedKey);
        beaufortCipher(input, repeatedKey, output);

        printf("Result: %s\n", output);
    } else {
        printf("Invalid option. Please choose E or D.\n");
    }

    return 0;
}
