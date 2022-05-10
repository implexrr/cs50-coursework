#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    // Prompts user for input and validates height
    do
    {
        height = get_int("Height: ");
    }
    while (height > 8 || height < 1);

    // Creates pyramid
    for (int i = 0; i < height; i++)
    {
        // Create left side of the pyramid
        for (int j = (height - (i + 1)); j > 0; j--)
        {
            printf(" ");
        }
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }

        // Create middle of pyramid
        printf("  ");

        // Create right side of the pyramid
        for (int l = 0; l <= i; l++)
        {
            printf("#");
        }
        printf("\n");
    }
}