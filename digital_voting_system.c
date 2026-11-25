#include <stdio.h>
#include <string.h>

#define MAX_CAND  10
#define MAX_VOTER 100

struct Candidate {
    int  id;
    char name[40];
    int  votes;
};

struct Candidate cand[MAX_CAND];
int voters[MAX_VOTER]; 
int nCand = 0, nVoted = 0;

int hasVoted(int voterId) {
    for (int i = 0; i < nVoted; i++)
        if (voters[i] == voterId) return 1;
    return 0;
}

void addCandidate(void) {
    if (nCand >= MAX_CAND) { printf("Maximum candidates reached!\n"); return; }
    cand[nCand].id = nCand + 1;
    printf("Enter candidate name: ");
    scanf(" %39[^\n]", cand[nCand].name);
    cand[nCand].votes = 0;
    nCand++;
    printf("Candidate added with ID %d.\n", nCand);
}

void showCandidates(void) {
    printf("\n%-5s %-30s\n", "ID", "Candidate");
    printf("------------------------------------\n");
    for (int i = 0; i < nCand; i++)
        printf("%-5d %-30s\n", cand[i].id, cand[i].name);
}

void castVote(void) {
    int voterId, choice;
    if (nCand == 0) { printf("No candidates registered yet.\n"); return; }
    if (nVoted >= MAX_VOTER) { printf("Voter limit reached!\n"); return; }
    printf("Enter your voter ID: ");
    scanf("%d", &voterId);
    if (hasVoted(voterId)) { printf("This voter ID has already voted!\n"); return; }
    showCandidates();
    printf("Enter candidate ID to vote: ");
    scanf("%d", &choice);
    if (choice < 1 || choice > nCand) { printf("Invalid candidate ID. Vote not counted.\n"); return; }
    cand[choice - 1].votes++;
    voters[nVoted++] = voterId;
    printf("Thank you! Your vote has been recorded.\n");
}

void showResults(void) {
    if (nCand == 0) { printf("No candidates registered yet.\n"); return; }
    printf("\n%-5s %-30s %-6s\n", "ID", "Candidate", "Votes");
    printf("--------------------------------------------\n");
    int max = 0;
    for (int i = 0; i < nCand; i++) {
        printf("%-5d %-30s %-6d\n", cand[i].id, cand[i].name, cand[i].votes);
        if (cand[i].votes > max) max = cand[i].votes;
    }
    printf("\nTotal votes cast: %d\n", nVoted);
    if (max == 0) { printf("No votes cast yet.\n"); return; }

    int winners = 0;
    for (int i = 0; i < nCand; i++) if (cand[i].votes == max) winners++;
    if (winners > 1) {
        printf("Result: It's a TIE between:\n");
        for (int i = 0; i < nCand; i++)
            if (cand[i].votes == max) printf("  - %s\n", cand[i].name);
    } else {
        for (int i = 0; i < nCand; i++)
            if (cand[i].votes == max) printf("Winner: %s with %d votes!\n", cand[i].name, max);
    }
}

int main(void) {
    int choice;
    do {
        printf("\n===== DIGITAL VOTING SYSTEM =====\n");
        printf("1. Add Candidate\n2. View Candidates\n3. Cast Vote\n");
        printf("4. View Results\n5. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) { while (getchar() != '\n'); choice = 0; }
        switch (choice) {
            case 1: addCandidate();   break;
            case 2: showCandidates(); break;
            case 3: castVote();       break;
            case 4: showResults();    break;
            case 5: printf("Thank you!\n"); break;
            default: printf("Invalid choice, try again.\n");
        }
    } while (choice != 5);
    return 0;
}
