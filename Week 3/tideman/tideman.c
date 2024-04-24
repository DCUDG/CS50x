#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Max number of candidates
#define MAX 9
#define MAX_NAME 20
#define MIN_VOTE 1
#define PAIR_DIF 1

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX] = {0};

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
char *candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2], tmp_pairs;

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, char *name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void flush_buffer(void);

int main(int argc, char *argv[])
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

    printf("Printing preference matrix...\n");
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i", preferences[i][j]);
        }
        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();

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
bool vote(int rank, char *name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
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
            preferences[ranks[0]][ranks[candidate_count - 1]]++;
            break;
        }
        preferences[ranks[i]][ranks[i + 1]]++;
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    printf("\nComputing individual results...\n");
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // Winner is [i]th candidate
            if (preferences[i][j + i] > preferences[j + i][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j + i;
                pair_count++;
                printf("Winner is: %s\n", candidates[i]);
                printf("Loser is: %s\n\n", candidates[j + i]);
            }

            // Winner is [j]th candidate
            else if (preferences[i][j + i] < preferences[j + i][i])
            {
                pairs[pair_count].winner = j + i;
                pairs[pair_count].loser = i;
                pair_count++;
                printf("Winner is: %s\n", candidates[j + i]);
                printf("Loser is: %s\n\n", candidates[i]);
            }

            // We have a tie
            else
            {
                // Nothing is done because it is a tie
            }
        }
    }
    printf("Counting pairs...\n");
    printf("# of pairs: %i\n", pair_count);
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    bool sorted;
    int sum_a, sum_b;

    printf("\nStarting sort...\n");

    // Do-while loop until bool returns true after bubble sort
    do
    {
        sorted = true;
        for (int i = 0; i < pair_count - 1; i++)
        {
            sum_a = preferences[pairs[i].winner][pairs[i].loser];
            sum_b = preferences[pairs[i + 1].winner][pairs[i + 1].loser];

            // If the [i+1]th is bigger than [i]
            if (sum_b > sum_a)
            {
                tmp_pairs = pairs[i + 1];
                pairs[i + 1] = pairs[i];
                pairs[i] = tmp_pairs;
            }
        }
    } while (!sorted);

    for (int i = 0; i < pair_count; i++)
    {
        printf("%s wins %s with %d votes\n", candidates[pairs[i].winner],
               candidates[pairs[i].loser], preferences[pairs[i].winner][pairs[i].loser]);
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    int x, y;
    bool cmp;

    printf("\nLocking pairs...\n");
    for (int i = 0; i < pair_count; i++)
    {
        // Search for cycle on graph to break for function
        for (int j = 0; j < pair_count; j++)
        {
            // Set bool to begin search
            cmp = true;
            for (int k = 0; k < pair_count; k++)
            {
                if (locked[k][j] == true)
                {
                    cmp = false;
                    break;
                }
            }
        }

        if (cmp)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
            printf("%s to %s locked in graph as pair %d\n",
                   candidates[pairs[i].winner], candidates[pairs[i].loser], i + 1);
        }
        else
        {
            printf("%s is the last element in the graph as pair\n", candidates[pairs[i].winner]);
            break;
        }
    }

    // Print visual representation of locked graph
    printf("\nPrinting locked matrix...\n");
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            if (locked[i][j] == true)
            {
                printf("1 ");
            }
            else
            {
                printf("0 ");
            }
        }
        printf("\n");
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int winner;
    bool pass;

    // Search for the graph array with a false column
    for (int i = 0; i < pair_count; i++)
    {
        pass = true;

        for (int j = 0; j < pair_count; j++)
        {
            if (locked[j][i] == true)
            {
                pass = false;
            }
        }

        // Break for if winner found
        if (pass)
        {
            winner = i;
            break;
        }
    }

    printf("\nWinner is: %s\n\n", candidates[winner]);
    return;
}
