#include <iostream>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <regex>
using namespace std;

char userInput[100];
char firstLetter;
int main () {
    cout<<"Escribe algo:";
    fgets(userInput, 100, stdin);

    // Check whether the expression has white-spaces
    for (int i = 0; i < strlen(userInput) - 1; i++) {
        if (isspace(userInput[i]) != 0) {
            fprintf(stderr, "Espacios no permitidos\n");
            exit(-1);
        }
    }

    firstLetter = userInput[0];
    char expression[100];

    if (isdigit(firstLetter)) {
        bool isValid = true;
        bool expressionReset = false;
        bool foundPoint = false;
        int startingPoint = 0;
        while(isValid){
            for (int i = startingPoint; i < strlen(userInput) - 1; i++) {
                if (isdigit(userInput[i])) {
                    expression[i] = userInput[i];
                } else if (userInput[i] == '.') {
                    if (foundPoint) {
                        printf("Unexpected token: %c\n", userInput[i]);
                        exit(-1);
                    }
                    foundPoint = true;
                    startingPoint = i + 1;
                    expressionReset = true;
                    memset(expression,0, sizeof(expression));
                } else {
                    isValid = false;
                    printf("Unexpected token: %c\n", userInput[i]);
                    exit(-1);
                }
            }
            isValid = false;

            // Determine if the expression is an even number
            if (!expressionReset) {
                int expressionInt = atol(expression);
                if ((expressionInt % 2) != 0) {
                    printf("Invalid number: %i\n", expressionInt);
                    exit(-1);
                }
            }
            printf("Valid expression :)");
        }
    }

    if (isalpha(firstLetter)) {
        memset(expression,0, sizeof(expression));
        // TODO: FIND @ OR DOT(.)
        int position = 0;
        bool isAtSymbol = false;
        bool isDotSymbol = false;

        regex onlyLetters("[a-z0-9_]");

        // Concat right side of the expression
        for (int i = 0; i <= strlen(userInput) - 1; i++) {
            if (userInput[i] == '@') {
                position = i + 1;
                isAtSymbol = true;
                break;
            } else if (userInput[i] == '.') {
                position = i + 1;
                isDotSymbol = true;
                break;
            } else {
                string temp = reinterpret_cast<const char *>(userInput[i]);
                cout<<"valor: "<<temp<< "\n";
                if (regex_match(temp, onlyLetters)) {
                    cout<<"valor:\n";
                } else {
                    cout<<"noentro\n";
                }
            }
            position++;
        }

        if (isAtSymbol) {
            // TODO
        }

        if (isDotSymbol) {
            // TODO
        }

        // TODO: ONLY LETTERS
    }

    if (firstLetter == '#') {
        printf("es #");
    }


    return 0;
}
