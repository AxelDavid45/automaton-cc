#include <iostream>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <regex>
using namespace std;

string userInput;
char firstLetter;
int main () {
    cout<<"Write an expression: ";
    getline(cin, userInput);


    // Check whether the expression has white-spaces
    for (int i = 0; i < userInput.length(); i++) {
        if (isspace(userInput[i]) != 0) {
            cout<<"Invalid expression\n";
            cout<<"Whitespaces not allowed\n";
            exit(-1);
        }
    }

    firstLetter = userInput[0];
    string expression;

    if (isdigit(firstLetter)) {
        bool isValid = true;
        bool expressionReset = false;
        bool foundPoint = false;
        int startingPoint = 0;
        while(isValid){
            for (int i = startingPoint; i < userInput.length(); i++) {
                if (isdigit(userInput[i])) {
                    expression[i] = userInput[i];
                } else if (userInput[i] == '.') {
                    if (foundPoint) {
                        cout<<"Invalid expression\n";
                        cout<<"Unexpected token: "<<userInput[i]<<"\n";
                        exit(-1);
                    }
                    foundPoint = true;
                    startingPoint = i + 1;
                    expressionReset = true;
                    expression.clear();
                } else {
                    cout<<"Invalid expression\n";
                    cout<<"Unexpected token: "<<userInput[i]<<"\n";
                    exit(-1);
                }
            }
            // Convert to false to exit from loop
            isValid = false;

            // Determine if the expression is an even number
            if (!expressionReset) {
                int expressionInt = stoi(expression);
                if ((expressionInt % 2) != 0) {
                    cout<<"Invalid expression\n";
                    cout<<"Invalid number: "<<expressionInt<<"\n";
                    exit(-1);
                }
            }
            cout<<"Valid expression :)";
        }
    }

    if (isalpha(firstLetter)) {
        expression.clear();
        string temp;
        int position = 0;
        bool isAtSymbol = false;
        bool isDotSymbol = false;

        size_t atFound = userInput.find("@");
        size_t dotFound = userInput.find(".");

        if (atFound != string::npos) {
            regex validUser("[a-z0-9_.]+");
            // Concat right side of the expression
            for (int i = 0; i < userInput.length(); i++) {
                if (userInput[i] == '@') {
                    position = i + 1;
                    isAtSymbol = true;
                    break;
                } else {
                    temp += userInput[i];
                    if (!regex_match(temp, validUser)) {
                        cout<<"Invalid expression\n";
                        cout<<"Unexpected token "<<userInput[i];
                        exit(-1);
                    }
                }
                position++;
            }

            if (isAtSymbol) {
                temp = userInput.substr(position, userInput.length());
                cout<<temp<<"\n";
                regex domains("(?:[a-z0-9]+\\.)+[a-z]+");
                if (!regex_match(temp, domains)) {
                    cout<<"Invalid expression\n";
                    cout<<"Unexpected token "<<temp;
                    exit(-1);
                }
                cout<<"Valid expression :)\n";
            }
        } else if (dotFound != string::npos) {
            regex validUser("[a-zA-Z0-9_-]+");
            // Concat right side of the expression
            for (int i = 0; i < userInput.length(); i++) {
                if (userInput[i] == '.') {
                    position = i + 1;
                    isDotSymbol = true;
                    break;
                } else {
                    temp += userInput[i];
                    if (!regex_match(temp, validUser)) {
                        cout<<"Invalid expression\n";
                        cout<<"Unexpected token "<<userInput[i];
                        exit(-1);
                    }
                }
                position++;
            }

            if (isDotSymbol) {
                temp.clear();
                regex lettersAndNumbers("[a-z0-9]+");
                for (int i = position; i < userInput.length(); i++) {
                    temp += userInput[i];
                    if (!regex_match(temp, lettersAndNumbers)) {
                        cout<<"Invalid expression";
                        cout<<"Unexpected token "<<userInput[i];
                        exit(-1);
                    }
                }
                // Validate if a valid extension
                regex fileExtensions("mp4|jp(e)?g|png|gif");
                if (!regex_match(temp, fileExtensions)) {
                    cout<<"Invalid expression";
                    exit(-1);
                }
                cout<<"Valid expression :)";
            }
        } else {
            regex onlyLetters("[a-z]+");
            if (regex_match(userInput, onlyLetters)) {
                cout<<"Valid expression :), only letters "<<userInput;
            }
        }
    }

    if (firstLetter == '#') {
        printf("es #");
    }


    return 0;
}
