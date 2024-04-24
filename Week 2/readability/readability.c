#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CONST_LTR 0.0588
#define CONST_SNT 0.296
#define CONST_IND 15.8
#define GRAD_MIN 1
#define GRAD_MAX 16
#define MAX_TEXT 2000
#define PER_CENT 100

int count_letters(char *text);
int count_sentences(char *text);
int count_words(char *text);
void print_results(int letters, int words, int sentences);

int main(void)
{
    int letters = 0, words = 0, sentences = 0;
    char text[MAX_TEXT];

    // Get input text from user
    printf("Text: ");
    fgets(text, MAX_TEXT, stdin);

    // Count letters, words & sentences
    letters = count_letters(text);
    words = count_words(text);
    sentences = count_sentences(text);

    // Print results of text
    print_results(letters, words, sentences);
}

int count_letters(char *text)
{
    int letter = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            letter++;
        }
    }
    return letter;
}

int count_sentences(char *text)
{
    int sentence = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentence++;
        }
    }
    return sentence;
}

int count_words(char *text)
{
    bool next_s = true;
    int word = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isspace(text[i]))
        {
            if (next_s == false)
            {
                break;
            }
            else
            {
                next_s = false;
                word++;
            }
        }
        else
        {
            next_s = true;
        }
    }
    return word;
}

void print_results(int letters, int words, int sentences)
{
    // Calculate average per 100 words
    float L = PER_CENT * (letters / (float)words);
    float S = PER_CENT * (sentences / (float)words);

    // Evaluate Coleman-Liau index
    float index = (CONST_LTR * L) - (CONST_SNT * S) - CONST_IND;
    index = round(index);
    if (index < GRAD_MIN)
    {
        printf("Before Grade 1");
    }
    else if (index > GRAD_MAX)
    {
        printf("Grade 16+");
    }
    else
    {
        printf("Grade %i", (int)index);
    }
}
