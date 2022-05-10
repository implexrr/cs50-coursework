#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(int argc, string argv[])
{
    // Check that number of arguments is 2 (exe and key)
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Extract key from CLI, make sure key length is exactly 26
    string key = argv[1];
    int key_len = strlen(key);
    if (key_len != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Check for invalid keys
    for (int i = 0; i < key_len; i++)
    {
        if ((key[i] > 'Z' || key[i] < 'A') && (key[i] > 'z' || key[i] < 'a'))
        {
            printf("Key must be alphabetic.\n");
            return 1;
        }
        else
        {
            for (int j = 0; j < i; j++)
            {
                if (key[j] == key[i])
                {
                    printf("Key cannot contain duplicate characters.\n");
                    return 1;
                }
            }
        }
    }

    // Prompt user for plaintext
    string plaintext = get_string("plaintext: ");
    int text_len = strlen(plaintext);

    // Initialize ciphertext
    char ciphertext[text_len];
    for (int i = 0; i < text_len; i++)
    {
        ciphertext[i] = plaintext[i];
    }
    ciphertext[text_len] = '\0';

    // Create ciphertext via substitution
    for (int i = 0; i < text_len; i++)
    {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z')
        {
            ciphertext[i] = toupper(key[((int) plaintext[i]) - 65]);
        }
        else if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
        {
            ciphertext[i] = tolower(key[((int) plaintext[i]) - 97]);
        }
    }

    // Print results
    printf("plaintext: %s\n", plaintext);
    printf("ciphertext: %s\n", ciphertext);
    return 0;

}