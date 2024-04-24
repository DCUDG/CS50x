#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define PLAYERS 2
#define SIZE_WORD 20
#define UPPER_A 65
#define UPPER_Z 90

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(char *word);
void flush_buffer(void);

int main(void)
{
    char word_1[SIZE_WORD], word_2[SIZE_WORD];
    int score_1, score_2;

    // Get input words from both players
    printf("Player 1: ");
    scanf("%s", word_1);
    flush_buffer();

    printf("Player 2: ");
    scanf("%s", word_2);
    flush_buffer();

    // Compute score of both players
    score_1 = compute_score(word_1);
    score_2 = compute_score(word_2);

    // TODO: Print the winner
    if (score_1 > score_2)
    {
        printf("Player 1 Wins!");
    }
    else if (score_1 < score_2)
    {
        printf("Player 2 Wins!");
    }
    else
    {
        printf("Tie!");
    }
}

int compute_score(char *word)
{
    int score = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        word[i] = (int)toupper(word[i]);
        if (UPPER_A <= word[i] && word[i] <= UPPER_Z)
        {
            score += POINTS[(word[i] - UPPER_A)];
        }
    }
    return score;
}

void flush_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        // Wait for buffer to clear
    }
}
