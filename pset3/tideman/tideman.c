#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

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
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
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
    int voter_count = get_int("Number of voters: ");

    // For every voter
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // For every ranking given by voter
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

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
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // For (all candidates)
    for (int i = 0; i < candidate_count; i++)
    {
        // If name matches candidate
        if (strcmp(name, candidates[i]) == 0)
        {
            // Add candidate, with corresponding ranking, to ranks array
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // For every stronger candidate (no need to check final candidate since that one is weakest)
    for (int i = 0; i < candidate_count - 1; i++)
    {
        // For every weaker candidate
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] ++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Loop over every matrix element and check if pair can be added
    // To Optimize: Only loop over upper right half of matrix
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count ++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // To optimize: Implement bubble sort or merge sort
    for (int i = 0; i < pair_count; i++)
    {
        int to_swap = i;
        int strongest_victory = 0;
        for (int j = i; j < pair_count; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner] > strongest_victory)
            {
                strongest_victory = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
                to_swap = j;
            }
        }
        int t1 = pairs[i].winner;
        int t2 = pairs[i].loser;
        pairs[i].winner = pairs[to_swap].winner;
        pairs[i].loser = pairs[to_swap].loser;
        pairs[to_swap].winner = t1;
        pairs[to_swap].loser = t2;

    }
    return;
}

bool isCyclic(int source, int target)
{
    // Base case: There is already an edge from the target to the source
    if (locked[target][source] == true)
    {
        return true;
    }

    // No edge from target to source
    else
    {
        // Loop through all possible edges originating from target
        for (int i = 0; i < candidate_count; i++)
        {
            // Is there an edge from target to new target?
            if (locked[target][i] == true)
            {
                // Does that edge go back to the source? If so, then cyclic
                if (isCyclic(source, i))
                {
                    return true;
                }
            }
        }
    }

    // All edges have been checked, cycle does not exist
    return false;

}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!(isCyclic(pairs[i].winner, pairs[i].loser)))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // If a given col is completely false, then that col's candidate is a winner
    for (int i = 0; i < candidate_count; i++)
    {
        bool win = true;
        for (int j = 0; j < candidate_count; j++)
        {
            // If candidate i is beaten by any candidate j, then i cannot be the winner.
            if (locked[j][i] == true)
            {
                win = false;
            }
        }
        // Someone has to win, so print the candidate i with zero losses.
        if (win == true)
        {
            int winner = i;
            printf("%s\n", candidates[winner]);
            return;
        }
    }
    return;
}