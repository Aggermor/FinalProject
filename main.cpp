#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Monster.hpp"
#include "Player.hpp"
#include "Battleground.hpp"
#include "Opponent.hpp"

using namespace std;

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
    srand(time(0));

    Monster arrayMonster[MONSTER_SIZE] =
    {
        Monster("Aeroquack", "Wind"),
        Monster("Zephyrtail", "Wind"),
        Monster("Aquaquack", "Water"),
        Monster("Torrentail", "Water"),
        Monster("Saxoheat", "Fire"),
        Monster("Charyuga", "Fire")
    };

    bool userVictory = 0;
    Opponent opponents[5];
    Player player1;

    opponentRandomizer(opponents, arrayMonster);  // randomizes a group of 5 opponents along with 3 random monsters


    titleScreen();

    nameSelection(player1);
    monsterSelection(player1, arrayMonster);

    int loopingCount = 0;

    while(loopingCount < 6) // less than six because there are 5 opponents
    {
        Battleground battleTime(player1, opponents[loopingCount]);

        battleScreen(opponents[loopingCount]);

        battleTime.choosePlayerMonsterToFight();
        battleTime.chooseOpponentMonsterToFight();

        battleTime.battleLoop();

        if(battleTime.battleResult() == true) // if(battleTime.battleResult())
        {
            if(loopingCount == 5)
            {
                userVictory = true;
                break;
            }
            cout << "Continue... Y or N? ";

            if(yes_noSelection() == true) // if(yes_noSelection())
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

    if(userVictory == true)
    {
        cout << "The champion!" << endl;
    }
    else
    {
        cout << "You took out " << loopingCount + 1 << " of 5 opponents!" << endl;
    }

    return 0;
}

// functions
void opponentRandomizer(Opponent objectOpponent_[], const Monster objectMonsterArray_[])
{
    string name[5] = { "Jerry", "Rick", "Morty", "Summer", "Beth" };

    for(int i = 0; i < 5; i++)
    {
        objectOpponent_[i].setName(name[rand()% 5]);
        for(int j = 0; j < 3; j++) // has to be three because opponent has to have 3 buddies
        {
            objectOpponent_[i].addMonster(objectMonsterArray_[rand() % MONSTER_SIZE]);
        }
    }
}

void titleScreen()
{
    // if we do pvp encounter we can have the user select which `game mode` here.
cout << "  _____             _                           " << endl;
cout << " |  __ \\           | |                          " << endl;
cout << " | |  | |_   _  ___| | ___ __ ___   ___  _ __   " << endl;
cout << " | |  | | | | |/ __| |/ / '_ ` _ \\ / _ \\| '_ \\  " << endl;
cout << " | |__| | |_| | (__|   <| | | | | | (_) | | | | " << endl;
cout << " |_____/ \\__,_|\\___|_|\\_\\_| |_| |_|\\___/|_| |_| " << endl << endl;




}

void nameSelection(Player& objectPlayer_)
{
    string userName_;

    cout << "Enter your character's name: ";
    getline(cin, userName_);

    objectPlayer_.setName(userName_);

    cout << endl;
}

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


void battleScreen(Opponent& objectOpponent_)
{
    cout << "An opponent is approaching - " << objectOpponent_.getName() << "!" << endl << endl;
}

int battleSelection()
{
    int userChoice_;
    cout << "Action [#]: ";
    cin >> userChoice_;
    cout << endl;

    return userChoice_;
}

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


