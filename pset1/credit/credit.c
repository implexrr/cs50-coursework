#include <cs50.h>
#include <math.h>
#include <stdio.h>

bool luhn(long n, int k);

int main(void)
{
    const int AMEX_LEN = 15;
    const int MASTERCARD_LEN = 16;
    const int VISA_LEN = 13;

    // Prompt user for credit card info
    long cc_number = get_long("Number: ");

    // Check length of cc
    long temp = cc_number;
    int counter = 0;
    while (temp > 0)
    {
        counter++;
        temp = temp / 10;
    }
    temp = cc_number;

    // If cc is luhn valid, check CC type
    if (luhn(cc_number, counter) == true)
    {
        // Extract first 2 digits of cc
        temp = temp / (pow(10, (counter - 2)));

        // Check card type
        if ((counter == AMEX_LEN) && (temp == 34 || temp == 37))
        {
            printf("AMEX\n");
        }
        else if ((counter == MASTERCARD_LEN) &&
                 (temp == 51 || temp == 52 || temp == 53 || temp == 54 || temp == 55))
        {
            printf("MASTERCARD\n");
        }
        else if ((counter == MASTERCARD_LEN) && (temp / 10 == 4))
        {
            printf("VISA\n");
        }
        else if ((counter == VISA_LEN) && (temp / 10 == 4))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

// Luhn's algorithm
bool luhn(long n, int k)
{
    int sum = 0;
    for (int i = 0; i < k; i++)
    {
        if (i % 2 == 0)
        {
            sum = sum + (n % 10);
        }
        else
        {
            sum = sum + ((2 * (n % 10)) % 10) + ((2 * (n % 10)) / 10);
        }
        n = n / 10;
    }
    if (sum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}