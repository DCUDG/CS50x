#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LN_KEY 26
#define LN_USR 50
#define LOWER_A 97
#define UPPER_A 65
#define UPPER_Z 90

void display_cipher(char *plain_text, char *key);

int main(int argc, char *argv)
{
    char plain_text[LN_USR];
    char cp_key[] = "VcHpRzGjNtLsKfBdQwAxEuYmOi";
    strcpy(argv, cp_key);

    // Validate key from argv
    if (strlen(argv) != LN_KEY)
    {
        printf("Key must contain 26 characters.");
        return 1;
    }
    else if (strlen(argv) == 0 || argc >= 3)
    {
        printf("Usage: ./substitution key");
        return 2;
    }
    else
    {
        // Get input from user
        printf("Plaintext: ");
        fgets(plain_text, LN_USR, stdin);

        // Generate ciphertext
        display_cipher(plain_text, argv);
    }
}

void display_cipher(char *plain_text, char *key)
{
    char cipher_text[LN_USR];
    int tmp;

    // Make substitutions with key
    for (int i = 0, n = strlen(plain_text); i < n; i++)
    {
        if (isalpha(plain_text[i]))
        {
            if (isupper(plain_text[i]))
            {
                tmp = (int)plain_text[i] - UPPER_A;
                cipher_text[i] = toupper(key[tmp]);
            }
            else
            {
                tmp = (int)plain_text[i] - LOWER_A;
                cipher_text[i] = tolower(key[tmp]);
            }
        }
        else
        {
            cipher_text[i] = plain_text[i];
        }
    }

    // Print output
    printf("Ciphertext: %s", cipher_text);
}