#include <cs50.h>
#include <stdio.h>
#include <string.h>


int main(int argc, string argv[]);
// Max number of candidates

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[8];

// Number of candidates
int candidate_count = 9;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > 9)
    {
        printf("Maximum number of candidates is 9");
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (vote(name))
        {
            printf("Invadil vote.\n");
            return false;
        }

    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int a = 0; a < candidate_count; a++)
    {
        if (strcmp(name, candidates[a].name) == 0)
        {
            candidates[a].votes = candidates[a].votes + 1 ;
            return true;
        }
    }
    return false;

}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    int total = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        if (total < candidates[i].votes)
        {
            total = candidates[i].votes;
        }
    }



    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == total)
        {
            printf("%s\n", candidates[i].name);
        }
    }

    return;
}