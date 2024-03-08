#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_STATES 100
#define MAX_SYMBOLS 10

typedef struct {
    int nextState;
    char symbol;
} Transition;

typedef struct {
    int numTransitions;
    Transition transitions[MAX_SYMBOLS];
} State;

typedef struct {
    int numStates;
    int startState;
    int acceptStates[MAX_STATES];
    int numAcceptStates;
    State states[MAX_STATES];
} NFA;

NFA createNFA() {
    NFA nfa;

    nfa.states[0].numTransitions = 2;
    nfa.states[0].transitions[0].nextState = 0;
    nfa.states[0].transitions[0].symbol = 'a';
    nfa.states[0].transitions[1].nextState = 1;
    nfa.states[0].transitions[1].symbol = 'b';

    nfa.states[1].numTransitions = 1;
    nfa.states[1].transitions[0].nextState = 2;
    nfa.states[1].transitions[0].symbol = 'b';

    nfa.states[2].numTransitions = 1;
    nfa.states[2].transitions[0].nextState = 2; 
    nfa.states[2].transitions[0].symbol = 'b'; 

    nfa.numStates = 3;
    nfa.startState = 0;
    nfa.acceptStates[0] = 2;
    nfa.numAcceptStates = 1;

    return nfa;
}

int recognizes(NFA nfa, char *input) {
    int currentStates[MAX_STATES];
    int numCurrentStates = 1;
    currentStates[0] = nfa.startState;

    for (int i = 0; input[i] != '\0'; i++) {
        int nextStates[MAX_STATES];
        int numNextStates = 0;

        for (int j = 0; j < numCurrentStates; j++) {
            int currentState = currentStates[j];
            for (int k = 0; k < nfa.states[currentState].numTransitions; k++) {
                Transition t = nfa.states[currentState].transitions[k];
                if (t.symbol == input[i]) {
                    nextStates[numNextStates++] = t.nextState;
                }
            }
        }

        numCurrentStates = numNextStates;
        memcpy(currentStates, nextStates, numCurrentStates * sizeof(int));
    }

    for (int i = 0; i < numCurrentStates; i++) {
        for (int j = 0; j < nfa.numAcceptStates; j++) {
            if (currentStates[i] == nfa.acceptStates[j]) {
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    NFA myNFA = createNFA();

    char input[100]; 
    printf("Enter an input string: ");
    scanf("%s", input);

    FILE *outputFile = fopen("output/NFAoutput.txt", "a");
    if (outputFile == NULL) {
        printf("Error opening output file!\n");
        return 1;
    }

    fprintf(outputFile, "Enter an input string: %s\n", input); 

    if (recognizes(myNFA, input)) {
        fprintf(stdout, "String accepted!\n");
        fprintf(outputFile, "String accepted!\n"); 
    } else {
        fprintf(stdout, "String rejected.\n");
        fprintf(outputFile, "String rejected.\n");
    }

    fclose(outputFile); 

    return 0;
}
