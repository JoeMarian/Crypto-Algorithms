#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to encrypt/decrypt using Atbash Cipher
void atbashCipher(char* input, char* output) {
    for (int i = 0; input[i] != '\0'; ++i) {
        char ch = input[i];
        if (isalpha(ch)) {
            if (isupper(ch)) {
                output[i] = 'Z' - (ch - 'A');  
            } else {
                output[i] = 'z' - (ch - 'a');
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

        atbashCipher(input, output);

        if (choice == 'E' || choice == 'e')
            printf("Encrypted Message: %s\n", output);
        else
            printf("Decrypted Message: %s\n", output);  
    } else {
        printf("Invalid choice. Please enter E or D.\n");
    }

    return 0;
}
