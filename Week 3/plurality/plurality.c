#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Max number of candidates
#define MAX 9
#define MIN_VOTE 1

// Candidates have name and vote count
typedef struct
{
    char *name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(char *name);
void print_winner(void);
void flush_buffer(void);

int main(int argc, char *argv[])
{
    int voter_count;

    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    do
    {
        printf("Number of voters: ");
        scanf("%i", &voter_count);
        flush_buffer();

    } while (voter_count < MIN_VOTE);

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        char *name;

        printf("Vote: ");
        scanf("%s", name);
        flush_buffer();

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(char *name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int highest_vote = 0;

    // Get highest value of votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (highest_vote < candidates[i].votes)
        {
            highest_vote = candidates[i].votes;
        }
    }

    // Search for each candidate and compare highest value for it to print it
    for (int i = 0; i < candidate_count; i++)
    {
        if (highest_vote == candidates[i].votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}

void flush_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        // Wait for buffer to clear
    }
}