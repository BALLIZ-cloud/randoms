// File:A1_T1_20231182.cpp.
// Purpose:a program includes many problems which user can be use hem
// Author:MOHAND SALAH TAMER BADAWY
// Section:NONE YET
// ID:20231182
// TA:NONE YET
// Date: 10 Oct 2024
// Detailed explanation of the file and how program works
/*
 * This program is a collection of four different problem-solving utilities, each solving a unique task. Here's a brief description of each part:

Problem 1 (String Splitter): This function takes a string and a delimiter as input and splits the string based on the given delimiter. It outputs each part of the string in quotes, separated by commas, and ends the output with a period.

Problem 2 (Binary Operations): This problem has two functionalities:

V1 (Binary Print): It converts an integer into its binary representation and prints it.
V2 (Binary Numbers): It generates and prints all binary numbers of a given length, with a specified prefix.
Problem 3 (Teddy Bear Game): This recursive game starts with a number of bears, and the goal is to reduce the number to exactly 42. The player can make moves according to a set of rules based on whether the current number is divisible by 2, 3, 4, or 5. The function checks if it's possible to win the game from the given number of bears.

Problem 4 (Phishing Scanner): This function scans a file to detect common phishing terms and assigns a point value to each term based on its likelihood of appearing in phishing emails. It then calculates a total score and classifies the message as having a low, medium, or high likelihood of being phishing based on the score.

The program features a menu system that allows users to choose which problem to run.
 */


#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <sstream>

using namespace std;

// Problem 1 (String Splitting)
vector<string> split(string target, string delimiter) {
    vector<string> m;
    int s = 0;
    string k;

    while ((s = target.find(delimiter)) != string::npos) {
        k = target.substr(0, s);
        m.push_back(k);
        target.erase(0, s + delimiter.length());
    }
    m.push_back(target);
    return m;
}

void problem_1(){
    string x, y;
    cout << "welcome to problem 1" << endl;
    cout << "please enter a string" << endl;
    getline(cin >> ws, x); // read the string
    cout << "please enter a delimiter" << endl;
    getline(cin, y); // read the delimiter
    vector<string> z = split(x, y); // passing the parameters

    for (size_t i = 0; i < z.size(); ++i) {
        cout << "\"" << z[i] << "\"";
        if (i != z.size() - 1) {
            cout << ", ";
        } else {
            cout << ".";
        }
    }
    cout << endl;
}

// Problem 2 (Binary Printing and Prefix Generation)
void recursive_f(int n) {
    if (n > 1) {
        recursive_f(n / 2);
    }
    cout << n % 2;
}

void binaryPrint(int n) {
    if (n == 0) {
        cout << "0";
    } else {
        recursive_f(n);
    }
}

void numbers(string prefix, int k) {
    if (k == 0) {
        cout << prefix << endl;
        return;
    }
    numbers(prefix + "0", k - 1);
    numbers(prefix + "1", k - 1);
}

void problem_2() {
    while (true) {
        cout << "please enter a number from the menu" << endl;
        cout << "1) V1 (Binary Print)" << endl;
        cout << "2) V2 (Binary Numbers)" << endl;
        cout << "3) Exit" << endl;
        int x;
        cin >> x;
        if (x == 1) {
            cout << "Enter a number" << endl;
            int y;
            cin >> y;
            binaryPrint(y);
            cout << endl;
        }
        else if (x == 2) {
            cout << "Enter a prefix" << endl;
            string s;
            cin >> s;
            cout << "Enter a number" << endl;
            int k;
            cin >> k;
            numbers(s, k);
        }
        else if (x == 3) {
            break; // Exit the loop
        }
        else
            cout<<"invalid choise.please enter a valid choice:"<<endl;
    }
}

// Problem 3 (Teddy Bear Game)
bool bears(int n) {
    if (n == 42) {
        return true;
    }
    if (n < 42) {
        return false;
    }
    if (n % 2 == 0 && bears(n / 2)) {
        return true;
    }
    if ((n % 3 == 0 || n % 4 == 0)) {
        int l = n % 10;
        int s = (n % 100) / 10;
        int p = l * s;

        if (p > 0 && bears(n - p)) {
            return true;
        }
    }
    if (n % 5 == 0 && bears(n - 42)) {
        return true;
    }
    return false;
}

void problem_3() {
    int x;
    cout << "Enter number of bears: " << endl;
    cin >> x;
    if (bears(x)) {
        cout << "is true" << endl;
    } else {
        cout << "is false" << endl;
    }
}

// Problem 4 (Phishing Scanner)
string toL(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

int s(const string& filename, const unordered_map<string, int>& phishingTerms) {
    ifstream file(filename);
    if (!file) {
        cout << "Error opening file." << endl;
        return -1;
    }

    string word;
    int totalScore = 0;
    unordered_map<string, int> wordCount;

    while (file >> word) {
        word = toL(word);
        word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());

        if (phishingTerms.find(word) != phishingTerms.end()) {
            wordCount[word]++;
            totalScore += phishingTerms.at(word);
        }
    }

    cout << "Phishing terms found:" << endl;
    for (const auto& entry : wordCount) {
        cout << entry.first << " - occurrences: " << entry.second
             << ", points: " << phishingTerms.at(entry.first) * entry.second << endl;
    }

    cout << "Total Phishing Score: " << totalScore;
    if (totalScore >= 31) {
        cout << " - High score detected." << endl;
    } else if (totalScore >= 11 && totalScore <= 30) {
        cout << " - Medium score detected." << endl;
    } else if (totalScore >= 0 && totalScore <= 10) {
        cout << " - Low score detected." << endl;
    }

    return totalScore;
}

void problem_4() {
    unordered_map<string, int> phishingTerms = {
            {"verify", 3}, {"urgent", 3}, {"click", 2}, {"update", 2},
            {"password", 3}, {"reset", 2}, {"suspicious", 3}, {"paypal", 3},
            {"compromised", 3}, {"login", 2}, {"attempt", 2}, {"bank", 3},
            {"credit", 3}, {"social", 3}, {"security", 3}, {"identity", 3},
            {"alert", 2}, {"free", 3}, {"gift", 3}, {"won", 3}, {"payment", 2},
            {"failed", 2}, {"congratulations", 3}, {"immediate", 3}, {"response", 2},
            {"amazon", 3}, {"ebay", 2}, {"account", 3}, {"flagged", 3}, {"offer", 2},
            {"unauthorized", 3}
    };

    string f;
    cout << "create a text file and pass its name: "<<endl;
    cout << "Enter the filename to scan: ";
    cin >> f;

    s(f, phishingTerms);
}

// Menu Function
void menu() {
    while (true) {
        cout << "Please enter a choice:" << endl;
        cout << "1) Problem 1: String Splitter" << endl;
        cout << "2) Problem 2: Binary Operations" << endl;
        cout << "3) Problem 3: Teddy Bear Game" << endl;
        cout << "4) Problem 4: Phishing Scanner" << endl;
        cout << "5) Exit" << endl;
        int choice;
        cin >> choice;
        cin.ignore(); // Ignore newline after input

        if (choice == 1) {
            problem_1();
        } else if (choice == 2) {
            problem_2();
        } else if (choice == 3) {
            problem_3();
        } else if (choice == 4) {
            problem_4();
        } else if (choice == 5) {
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}

int main() {
    menu();
    return 0;
}
