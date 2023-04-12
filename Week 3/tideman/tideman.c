#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Max number of candidates
#define MAX 9
#define MAX_NAME 20
#define MIN_VOTE 1

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX] = {0};

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
char* candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, char* name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void flush_buffer(void);

int main(int argc, char* argv[])
{
    int voter_count;

    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;

    do
    {
        printf("Number of voters: ");
        scanf("%i", &voter_count);
        flush_buffer();
    } while (voter_count < MIN_VOTE);   

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            char name[MAX_NAME];
            
            printf("Rank %i: ", j + 1);
            scanf("%s", name);
            flush_buffer();

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    
    //sort_pairs();
    //lock_pairs();
    //print_winner();

    return 0;
}

void flush_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) 
    { 
        // Wait for buffer to clear
    }
}

// Update ranks given a new vote
bool vote(int rank, char* name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name,candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (i == candidate_count - 1)
        {
            preferences[ranks[0]][ranks[candidate_count-1]]++;
            break;
        }
        preferences[ranks[i]][ranks[i+1]]++;
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}