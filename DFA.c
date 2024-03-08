#include <stdio.h>
#include <string.h>

#define Q0 0
#define Q1 1
#define Q2 2

int delta(int currentState, char inputSymbol) {
   switch(currentState) {
       case Q0: 
           if (inputSymbol == '0') return Q1; 
           else return Q0;
       case Q1:
           if (inputSymbol == '0') return Q0; 
           else return Q2;
       case Q2:
           if (inputSymbol == '0') return Q1;
           else return Q2;
       default: return -1;
   }
}

int main() {
    char inputString[100];
    int currentState = Q0;  
    int i;
    FILE *outputFile;

    printf("Enter an input string: ");
    scanf("%s", inputString);

    outputFile = fopen("output/DFAoutput.txt", "a"); 
    if (outputFile == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(outputFile, "Enter an input string: %s\n", inputString); 

    for (i = 0; i < strlen(inputString); i++) {
        currentState = delta(currentState, inputString[i]);
        if (currentState == -1) {
            printf("Invalid input.\n"); 
            fprintf(outputFile, "Invalid input.\n"); 
            fclose(outputFile); 
            return 0;
        }
    }

    if (currentState == Q2) { 
        printf("String accepted.\n");
        fprintf(outputFile, "String accepted.\n");
    } else {
        printf("String rejected.\n");
        fprintf(outputFile, "String rejected.\n");
    }

    fclose(outputFile); 
    return 0;
}
