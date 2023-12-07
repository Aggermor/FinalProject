#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Monster.hpp"
#include "Player.hpp"
#include "Battleground.hpp"
#include "Opponent.hpp"
#include "main.hpp"

using namespace std;

/* Function PROTOTYPES */

void opponentRandomizer(Opponent objectOpponent_[], const Monster objectMonsterArray_[]);

void titleScreen();

void nameSelection(Player& objectPlayer_);
void monsterSelection(Player& objectPlayer_, const Monster objectMonsterArray_[]);
int monsterSpecificSelection(Player& objectPlayer_);
bool yes_noSelection();

void battleScreen(Opponent& objectOpponent_);
int battleSelection();

const int MONSTER_SIZE = 6;

int main()
{
    srand(time(0)); //Provides functionality to our rand functions by setting time to 0

    //Array of 6 monsters to choose from
    Monster arrayMonster[MONSTER_SIZE] =
    {
        Monster("Aeroquack", "Wind"),
        Monster("Zephyrtail", "Wind"),
        Monster("Aquaquack", "Water"),
        Monster("Torrentail", "Water"),
        Monster("Saxoheat", "Fire"),
        Monster("Charyuga", "Fire")
    };

    bool userVictory = 0; //Win count
    Opponent opponents[5]; //Creates array of opponent objects
    Player player1; //Creates a player object

    opponentRandomizer(opponents, arrayMonster);  // randomizes a group of 5 opponents along with 3 random monsters


    titleScreen(); //Outputs title scrren

    nameSelection(player1); //Prompt and set name for player 1
    monsterSelection(player1, arrayMonster); //Display monsters and prompt player to select 3

    int loopingCount = 0;
    int defeated = 0;

    while(loopingCount < 6) //Loop to iterate through each of the 5 opponents
    {
        /* Setting up the battle */

        //Sets up battle scenario between player 1 and opponent(s)
        Battleground battleTime(player1, opponents[loopingCount]);

        battleScreen(opponents[loopingCount]); //Opponent approaching message for each opponent

        battleTime.choosePlayerMonsterToFight(); //Player selects monster for battle
        battleTime.chooseOpponentMonsterToFight(); //Opponent selects monster for battle

        battleTime.battleLoop(); //Executes battle scenario between player 1 and opponent(s)

        if(battleTime.battleResult() == true) //Checks battle result. If player wins, the game continues. If they lose, the loop is exited and the game ends.
        {
            defeated++; // tracks oppoonents defeated
            
            if(loopingCount == 5)
            {
                userVictory = true;
                break;
            }
            cout << "You have defeated " << defeated << "/5 opponents." << endl;
            cout << "Heal your party of ducks and continue... Y or N? ";

            if(yes_noSelection() == true)
            {
                cout << "You heal your party..." << endl << endl;
                loopingCount++;
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }

    if(userVictory == true) //Displays victory message for clearing all 5 opponents.
    {
        cout << "The champion!" << endl;
    }
    else //Message for the amount of opponents the player has beaten.
    {
        cout << "You took out " << defeated << " of 5 opponents!" << endl;
    }

    return 0;
}

/* Function DEFINITIONS */

/*
This function takes an array of opponent objects and monster objects. Next, it assigns random names to
5 opponents and fills the opponent monster inventory with 3 random monsters from the objectMonsterArray_
*/
void opponentRandomizer(Opponent objectOpponent_[], const Monster objectMonsterArray_[])
{
    string name[5] = { "Jerry", "Rick", "Morty", "Summer", "Beth" };

    for(int i = 0; i < 5; i++)
    {
        objectOpponent_[i].setName(name[rand()% 5]);
        for(int j = 0; j < 3; j++) // has to be three because opponent has to have 3 monsters
        {
            objectOpponent_[i].addMonster(objectMonsterArray_[rand() % MONSTER_SIZE]);
        }
    }
}

/*
This function displays the title screen of the game. It prints a stylized title using ASCII art.
*/
void titleScreen()
{
cout << "  _____             _                           " << endl;
cout << " |  __ \\           | |                          " << endl;
cout << " | |  | |_   _  ___| | ___ __ ___   ___  _ __   " << endl;
cout << " | |  | | | | |/ __| |/ / '_ ` _ \\ / _ \\| '_ \\  " << endl;
cout << " | |__| | |_| | (__|   <| | | | | | (_) | | | | " << endl;
cout << " |_____/ \\__,_|\\___|_|\\_\\_| |_| |_|\\___/|_| |_| " << endl << endl;




}

/*
This function takes a Player object by reference, prompts the user for their character's name, and
sets the name.
*/
void nameSelection(Player& objectPlayer_)
{
    string userName_;

    cout << "Enter your character's name: ";
    getline(cin, userName_);

    objectPlayer_.setName(userName_);

    cout << endl;
}

/*
This function takes a Player object and an array of Monsters. It displays the 6 available monsters
and prompts the user to select 3 for their party.
*/
void monsterSelection(Player& objectPlayer_, const Monster objectMonsterArray_[])
{
    int userChoice_;
    string numberLetter[3] = { "first", "second", "third" };

    for(int i = 0; i < MONSTER_SIZE; i++)
    {
        cout << "[" << i + 1 << "]" << endl;
        cout << objectMonsterArray_[i] << endl;
    }

    cout << "Choose a party size of 3!" <<endl;

    int userGate_ = 0;
    while(userGate_ < 3) // has to be three
    {
        cout << "Enter the [#] of your " << numberLetter[userGate_] << " monster: ";
        cin >> userChoice_;

        if(userChoice_ > 0 && userChoice_ <= MONSTER_SIZE) // from 1 to ARRAY_MONSTERS_SIZE
        {
            objectPlayer_.addMonster(objectMonsterArray_[userChoice_ - 1]);
            userGate_++;
        }
        else // not valid input
        {
            cout << "Not possible! Type a number from 1 to " << MONSTER_SIZE << endl;
        }
    }

    objectPlayer_.monsterTagging();

    cout << endl;
}

/*
This function takes a Player object and returns the index of the selected monster. It is used to select
a specific monster from the party during battle when sending a Duckmon out to fight.
*/
int monsterSpecificSelection(Player& objectPlayer_)
{
    int userChoice_ = 0;

    while(1)
    {
        cout << "Choose [#] a fighter: ";
        cin >> userChoice_;

        if(userChoice_ > 0 && userChoice_ <= objectPlayer_.getSize())
        {
            cout << endl;
            return userChoice_ - 1;
        }
        else
        {
            cout << "Not possible! Type a number from 1 to " << objectPlayer_.getSize() << endl;
        }
    }
}

/*
This function indicates an opponent is approaching by displaying a message and the opponent's name.
*/
void battleScreen(Opponent& objectOpponent_)
{
    cout << "An opponent is approaching - " << objectOpponent_.getName() << "!" << endl << endl;
}

/*
This function prompts the player to input an action during battle via a number and returns the choice.
*/
int battleSelection()
{
    int userChoice_;
    cout << "Action [#]: ";
    cin >> userChoice_;
    cout << endl;

    return userChoice_;
}

/*
This function prompts the user to enter Yes or No for a decision. It returns true or false.
*/
bool yes_noSelection()
{
    char userChoice_;
    cin >> userChoice_;

    if(userChoice_ == 'Y' || userChoice_ == 'y')
    {
        cout << endl;
        return 1;
    }
    else
    {
        cout << endl;
        return 0;
    }
}


