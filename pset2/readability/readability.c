#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
float coleman_liau(string text);


int main(void)
{
    // Prompt user for text
    string text = get_string("Text: ");

    // Calculate CL Index, round to obtain reading level
    int reading_level = (int) round(coleman_liau(text));
    if (reading_level >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (reading_level < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", reading_level);
    }
}

// Count number of letters in given text
int count_letters(string text)
{
    int sum = 0;

    // Add 1 letter for every ascii-mapped character present
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (toupper(text[i]) >= 65 && toupper(text[i]) <= 90)
        {
            sum += 1;
        }
    }
    return sum;
}

// Count number of words in given text
int count_words(string text)
{
    int sum = 0;

    // If even one letter exists, then one word exists
    if (text[0] != '\0')
    {
        sum += 1;
    }

    // Add 1 word for every space present
    for (int i = 0, n = strlen(text); i < n; i ++)
    {
        if (text[i] == ' ')
        {
            sum += 1;
        }
    }

    return sum;
}

// Count number of sentences in given text
int count_sentences(string text)
{
    int sum = 0;
    for (int i = 0, n = strlen(text); i < n; i ++)
    {
        // Add 1 sentence for every punctuation character present
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sum += 1;
        }
    }
    return sum;
}

// Calculate Coleman-Liau Index
float coleman_liau(string text)
{
    float letterCount = (float) count_letters(text);
    float wordCount = (float) count_words(text);
    float sentenceCount = (float) count_sentences(text);
    float cl_ind = (0.0588 * ((letterCount / wordCount) * 100)) - (0.296 * ((sentenceCount / wordCount) * 100)) - 15.8;
    return cl_ind;
}