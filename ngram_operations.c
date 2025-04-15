#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 1000

void clean_input(char *input, char *output) {
    int j = 0;
    for (int i = 0; input[i]; i++) {
        if (isalpha(input[i])) {
            output[j++] = toupper(input[i]);
        }
    }
    output[j] = '\0';
}

void generate_ngrams(char *text, int n) {
    int len = strlen(text);
    if (n > len) {
        printf("N is larger than the message length.\n");
        return;
    }

    printf("Generated %d-grams:\n", n);
    for (int i = 0; i <= len - n; i++) {
        for (int j = 0; j < n; j++) {
            putchar(text[i + j]);
        }
        printf("\n");
    }
}

int main() {
    char message[MAX], cleaned[MAX];
    int n;

    printf("Enter message: ");
    fgets(message, MAX, stdin);

    clean_input(message, cleaned);

    printf("Enter value of N for N-gram analysis: ");
    scanf("%d", &n);

    generate_ngrams(cleaned, n);

    return 0;
}
