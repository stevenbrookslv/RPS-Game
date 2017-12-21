// Rock Paper Scissors game

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

// Global constants
const int MAX_ROUNDS = 15;     // maximum number of rounds the user can choose

// Global variables
double prob_rock     = 35.4;    // initialized probability that the user will throw rock
double prob_scissors = 35;      // initialized probability that the user will throw scissors
double prob_paper    = 29.6;    // initialized probability that the user will throw paper

enum player { tie, computer, user };    // use for returning winner of the throw
enum hand { R = 0, P = 1, S = 2 };      // use for quantifying possible moves
char hand_choices[] = { 'R', 'P', 'S' };// character representation of enum hand type
const player win_table[3][3] =          // table to determine the winner of any given throw
    {
        { tie, user, computer },
        { computer, tie, user },
        { user, computer, tie },
    };

hand choices[] = { R, P, S };  // for the purpose of randomly selecting a throw


// ***********************************************************
// Manipulator for bolding output text
ostream& bold(ostream& out) { return out << "\e[1m"; }
// Manipulator for unbolding output text
ostream& unbold(ostream& out) { return out << "\e[0m"; }

// ***********************************************************
// Determine what hand the computer should throw 
hand computerThrow() {
    // Returns either 'R', 'P', or 'S' based off user probability 

    // For testing purposes, return random throw
    srand(time(NULL));
    return choices[rand()%3];
}

// ***********************************************************
// Compute new probabilities based off user's/computer's previous choices 
void calculateProb(const vector<hand> &comp, const vector<hand> &user) {
}

// ***********************************************************
// Print entirety of the computer and user moves vector
void printThrows(const vector<hand> &comp, const vector<hand> &user) {
    cout << "Computer throws:\t";
    for(int i = 0; i < comp.capacity(); i++)
        cout << comp[i] << " ";

    cout << "User throws:    \t";
    for(int i = 0; i < user.capacity(); i++)
        cout << user[i] << " ";
}

// ***********************************************************
// Returns the winner of the round
player findWinner(hand comp, hand user) { 
    cout << comp << " against " << user << "\twinner: " << win_table[comp][user];
    return win_table[comp][user]; 
}

// ***********************************************************
int main() {
    // Main function variables
    int rounds = 1;
    int user_wins = 0;
    int comp_wins = 0;
    int tie_count = 0;          // number of ties between computer and user
    char c_user;                // char user throw
    hand user_throw;            // throw choice of the user
    hand comp_throw;            // throw choice of the computer 
    
    vector<hand> user_moves;    // past moves made by the user
    vector<hand> comp_moves;    // past moves made by the computer


    // Print banners, prompt user to enter amount of rounds
    /*
    cout << bold << "ROCK PAPER SCISSORS: The Game" << unbold << endl;
    cout << "The rules are simple: choose either rock(R), paper(P), or scissors(S).\n\n";
    cout << "Enter number of rounds to play (each round consists of 3 throws): ";
    cin >> rounds;
    // Checking bounds of number of rounds entered 
    while(rounds > MAX_ROUNDS) {
        cout << "Too many rounds, please enter a smaller number: ";
        cin >> rounds;
    }
    */

    // Reserve required space based on the number of rounds
    user_moves.reserve(rounds*3);       // space for user's documented moves 
    comp_moves.reserve(rounds*3);       // space for computer's documented moves


    // Play specified amount of rounds
    for(int i = 0; i < rounds; i++) {
        cout << bold << "\tROUND " << (i+1) <<  unbold << endl;
        for(int j = 0; j < 3; j++) {            // each round consists of 3 throws

            comp_throw = computerThrow();       // call function to determine computer's hand
            comp_moves.push_back(comp_throw);   // document computer's most recent hand

            cout << "\tYour throw: ";           // prompt user to enter their throw
            cin >> c_user;                      // read in user's hand as a char
            user_throw = static_cast<hand>(toupper(c_user));    // static cast the capitalized throw as a hand type 
            user_moves.push_back(user_throw);   // document user's most recent hand
            cout << "\t user: " << user_throw << endl;
            cout << "\tComputer's throw: " << hand_choices[comp_throw] << endl;
            //calculateProb(comp_moves, user_moves); // calculate new probabilities based on most recent throws

            // Determine winner, update wins and ties
            /*
            if(findWinner(comp_throw, user_throw) == tie) {
                cout << "tie game" << endl;
                tie_count++;
            }
            */
            findWinner(comp_throw, user_throw);
            cout << endl;
        }
        cout << endl;
    }

    // Print out win/loss statistics per round
    cout << bold << "GAME STATS" << unbold << endl;
    cout << "  User wins: " << setw(5) << user_wins << endl;
    cout << "  Computer wins: " << comp_wins << endl;
    cout << "  Tie throws: " << setw(4) << tie_count << endl;
    cout << "\n  Computer won " << bold << setprecision(2) << double(comp_wins / rounds) << "%" << unbold << " of the time" << endl;
}
