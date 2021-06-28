#include <iostream>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <regex>

using namespace std;

void printMessageError(string &data) {
    cout << "Invalid expression\n";
    if (data.find(' ') != string::npos) {
        cout << "Unexpected token: <whitespace>";
    } else {
        cout << "Unexpected token " << data;
    }
    exit(-1);
}

void printMessageError(char &data) {
    cout << "Invalid expression\n";
    cout << "Unexpected token " << data << "\n";
    exit(-1);
}

int validateRightSideExpression(string input, char character, regex &regx) {
    int tempPos = 0;
    string tempString;
    // Concat right side of the expression
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == character) {
            tempPos = i + 1;
            break;
        }
        tempString += input[i];
        if (!regex_match(tempString, regx)) {
            printMessageError(input[i]);
        }
        tempPos++;
    }
    return tempPos;
}

int main() {
    string userInput;

    cout << "Write an expression: ";
    getline(cin, userInput);

    // Check whether the expression has white-spaces
    for (char i : userInput) {
        if (isspace(i) != 0) {
            cout << "Invalid expression\n";
            cout << "Whitespaces not allowed\n";
            exit(-1);
        }
    }

    const char firstLetter = userInput[0];
    string expression;

    if (isdigit(firstLetter)) {
        bool expressionReset = false;
        bool foundPoint = false;
        for (int i = 0; i < userInput.length(); i++) {
            if (isdigit(userInput[i])) {
                expression += userInput[i];
            } else if (userInput[i] == '.') {
                if (foundPoint) {
                    printMessageError(userInput[i]);
                }
                if (userInput[i + 1] == '\000') {
                    cout << "Incomplete number\n";
                    printMessageError(userInput[i]);
                }
                foundPoint = true;
                expressionReset = true;
                expression.clear();
            } else {
                printMessageError(userInput[i]);
            }
        }

        // Determine if the expression is an even number
        if (!expressionReset) {
            int expressionInt = stoi(expression);
            if ((expressionInt % 2) != 0) {
                printMessageError(expression);
            }
        }
        cout << "Valid expression :)";
        return 0;
    }

    if (isalpha(firstLetter)) {
        expression.clear();
        string tempString;
        int position;
        size_t atFound = userInput.find('@');
        size_t dotFound = userInput.find('.');

        if (atFound != string::npos) {
            regex validUser("[a-z0-9_.]+");
            position = validateRightSideExpression(userInput, '@', validUser);
            tempString = userInput.substr(position, userInput.length());
            regex domains("(?:[a-z0-9]+\\.)+[a-z]+");
            if (!regex_match(tempString, domains)) {
                printMessageError(tempString);
            }
            cout << "Valid expression :)\n";
            return 0;
        } else if (dotFound != string::npos) {
            regex validFilename("[a-zA-Z0-9_-]+");
            position = validateRightSideExpression(userInput, '.', validFilename);
            tempString.clear();
            regex lettersAndNumbers("[a-z0-9]+");
            for (int i = position; i < userInput.length(); i++) {
                tempString += userInput[i];
                if (!regex_match(tempString, lettersAndNumbers)) {
                    printMessageError(userInput[i]);
                }
            }

            regex fileExtensions("mp4|jp(e)?g|png|gif");
            if (!regex_match(tempString, fileExtensions)) {
                printMessageError(tempString);
            }
            cout << "Valid expression :)";
            return 0;
        } else {
            regex onlyLetters("[a-zA-Z]+");
            if (regex_match(userInput, onlyLetters)) {
                cout << "Valid expression :), only letters " << userInput;
                return 0;
            }
            printMessageError(userInput);
        }
    }

    if (firstLetter == '#') {
        regex hexColor(R"(#([\da-fA-F]{2})([\da-fA-F]{2})([\da-fA-F]{2}))");
        if (!regex_match(userInput, hexColor)) {
            printMessageError(userInput);
        }
        cout << "Valid expression :)\n";
        return 0;
    }

    printMessageError(userInput);
}