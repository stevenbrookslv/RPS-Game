// Rock Paper Scissors game

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <limits>
#include <stdlib.h>
#include <time.h>

using namespace std;

// Global constants
const int MAX_ROUNDS = 15;     // maximum number of rounds the user can choose

// Global variables
double prob_rock     = 35.4;    // initialized probability that the user will throw rock
double prob_scissors = 35.0;    // initialized probability that the user will throw scissors
double prob_paper    = 29.6;    // initialized probability that the user will throw paper

enum player { tie, computer, user };    // use for returning winner of the throw
string player_choices[] = { "tie", "computer", "user" }; // string representation of enum player type 
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
hand userProb() {
    hand likely = R;    // hand with the highest likelihood of being played 
    if(prob_paper > prob_rock)
        likely = P;
    else if(prob_scissors > prob_rock)
        likely = S;

    return likely;      // returns the hand the user is most likely to throw     
}

// ***********************************************************
// Determine what hand the computer should throw 
hand computerThrow() {
    // Returns either 'R', 'P', or 'S' based off user probability 
    //double comp_choice; // the decided throw of the computer
    //cout << "best choice: " << comp_choice << endl;

    // For testing purposes, return random throw
    srand(time(NULL));
    return choices[rand()%3];
    
}

// ***********************************************************
// Returns the winner of the round
player findWinner(hand comp, hand user) { return win_table[comp][user]; }

// ***********************************************************
// Compute new probabilities based off user's/computer's previous choices 
void calculateProb(const vector<hand> &comp, const vector<hand> &user) {


}

// ***********************************************************
// Print entirety of the computer and user moves vector
void printThrows(const vector<hand> &comp, const vector<hand> &user) {
    cout << bold << "THROWS MADE BY PLAYERS" << unbold << endl;
    cout << "  Computer throws:\t";
    for(int i = 0; i < comp.capacity(); i++)
        cout << hand_choices[comp[i]] << " ";

    cout << "\n  User throws:    \t";
    for(int i = 0; i < user.capacity(); i++)
        cout << hand_choices[user[i]] << " ";
    
    cout << "\n  Computer win:   \t";
    for(int i = 0; i < comp.capacity(); i++) {
        if(findWinner(comp[i], user[i]) == 1) // returning 1 indicates a computer win 
            cout << "* ";
        else
            cout << "  ";
    }

    cout << "\n\n";
}


// ***********************************************************
// Returns the given character as a hand enum type 
hand convertInput(char user_char) {
    hand user_hand;
    switch(user_char) {
        case 'R': user_hand = R; break;
        case 'S': user_hand = S; break;
        case 'P': user_hand = P; break; 
    }
    return user_hand;
}


// ***********************************************************
int main() {
    // Main function variables
    int rounds = 1;
    int user_wins = 0;          // number of times the user has won a throw
    int comp_wins = 0;          // number of times the computer has won a throw
    int tie_count = 0;          // number of ties between computer and user
    char c_user;                // char user throw
    hand user_throw;            // throw choice of the user
    hand comp_throw;            // throw choice of the computer 
    
    vector<hand> user_moves;    // past moves made by the user
    vector<hand> comp_moves;    // past moves made by the computer

    player winner;


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
    cout << "\n\n";
    for(int i = 0; i < rounds; i++) {
        cout << bold << "\tROUND " << (i+1) <<  unbold << endl;
        for(int j = 0; j < 3; j++) {            // each round consists of 3 throws

            comp_throw = computerThrow();       // call function to determine computer's hand
            comp_moves.push_back(comp_throw);   // document computer's most recent hand

            cout << "\tYour throw: ";           // prompt user to enter their throw
            cin >> c_user;                      // read in user's hand as a char
            c_user = toupper(c_user);           // guarenteed capital letter for user throw

            while(c_user != 'R' && c_user != 'S' && c_user != 'P') { // error check user input 
                cout << "\tError, please enter 'r' or 'p' or 's' (capital or lowercase): ";
                cin >> c_user;
                c_user = toupper(c_user);
            }
            user_throw = convertInput(c_user);  // convert the user's character input to a hand enum type
            user_moves.push_back(user_throw);   // document user's most recent hand

            cout << "\tComputer throw: " << hand_choices[comp_throw] << endl; // show user the computer's selected throw

            //calculateProb(comp_moves, user_moves); // calculate new probabilities based on most recent throws

            winner = findWinner(comp_throw, user_throw);// determine the winner of the round
            switch(winner) {
                case 0: 
                    tie_count++; // case 0 indicates a tie
                    j--;         // a tie leads to a replay of the last throw
                    cout << bold << "\t TIE GAME, REPLAY" << unbold << endl;
                    break; 
                case 1: comp_wins++; break;
                case 2: user_wins++; break;
            }
            cout << endl;
        } // end of throws loop 
        cout << endl;
    } // end of rounds loop


    // For testing, print out the moves thrown by each player
    printThrows(comp_moves, user_moves);    

    // Print out win/loss statistics per round
    cout << bold << "GAME STATS" << unbold << endl;
    cout << "  User wins: " << setw(5) << user_wins << endl;
    cout << "  Computer wins: " << comp_wins << endl;
    cout << "  Tie throws: " << setw(4) << tie_count << endl;
    cout << "\n  Computer won " << bold << setprecision(4) << (double(comp_wins) / double(rounds*3)) * 100 << "%" << unbold << " of the time" << endl;
}
