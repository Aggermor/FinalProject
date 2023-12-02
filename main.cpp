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

void opponentRandomizer(Opponent objectOpponent_[]);

void titleScreen();
void nameSelection(Player& objectPlayer_);
void monsterSelection(Player& objectPlayer_);
int monsterSpecificSelection(Player& objectPlayer_);
bool yes_noSelection();

void battleScreen(Opponent& objectOpponent_);
int battleSelection();

int main()
{
    bool userVictory = 0;
    Opponent opponents[5];
    Player player1;

    opponentRandomizer(opponents);  // randomizes a group of 5 opponents along with 3 random monsters


    titleScreen();

    nameSelection(player1);
    monsterSelection(player1);

    int loopingCount = 0;

    while(loopingCount < 6)
    {
        Battleground battleTime(player1, opponents[loopingCount]);

        battleScreen(opponents[loopingCount]);

        battleTime.choosePlayerMonsterToFight();
        battleTime.chooseOpponentMonsterToFight();

        battleTime.battleLoop();

        if(battleTime.battleResult() == true)
        {
            if(loopingCount == 5)
            {
                userVictory = true;
                break;
            }
            cout << "Continue... Y or N? ";

            if(yes_noSelection() == true)
            {
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
void opponentRandomizer(Opponent objectOpponent_[])
{
    Monster arrayMonster[6] =
    {
        Monster("Aeroquack", "Wind", 20, 30, 10),
        Monster("Zephyrtail", "Wind", 25, 25, 20),
        Monster("Aquaquack", "Water", 20, 25, 20),
        Monster("Torrentail", "Water", 30, 20, 10),
        Monster("Saxoheat", "Fire", 20, 20, 5),
        Monster("Charyuga", "Fire", 20, 20, 10)
    };

    string name[5] = { "Jerry", "Rick", "Morty", "Summer", "Beth" };

    srand(time(0));

    for(int i = 0; i < 5; i++)
    {
        objectOpponent_[i].setName(name[rand()% 5]);
        for(int j = 0; j < 3; j++)
        {
            objectOpponent_[i].addMonster(arrayMonster[rand() % 6]);
        }
    }
}

void titleScreen()
{
    cout << "MONSTERS" << endl << endl;
}

void nameSelection(Player& objectPlayer_)
{
    string userName_;


    cout << "Enter your character's name: ";
    getline(cin, userName_);

    objectPlayer_.setName(userName_);

    cout << endl;
}

void monsterSelection(Player& objectPlayer_)
{
    int userChoice_;
    string numberLetter[3] = { "first", "second", "third" };

    Monster arrayMonster[6] =
    {
        Monster("Aeroquack", "Wind", 20, 30, 10),
        Monster("Zephyrtail", "Wind", 25, 25, 20),
        Monster("Aquaquack", "Water", 20, 25, 20),
        Monster("Torrentail", "Water", 30, 20, 10),
        Monster("Saxoheat", "Fire", 20, 20, 5),
        Monster("Charyuga", "Fire", 20, 20, 10)
    };

    Monster* objectMonsterPtr_ = new Monster();

    for(int i = 0; i < 6; i++)
    {
        cout << "[" << i + 1 << "]" << endl;
        cout << arrayMonster[i] << endl;
    }

    cout << "Choose a party size of 3!" <<endl;

    int userGate_ = 0;
    while(userGate_ < 3)
    {
        cout << "Enter the [#] of your " << numberLetter[userGate_] << " monster: ";
        cin >> userChoice_;

        if(userChoice_ > 0 && userChoice_ <= 6)
        {
            *objectMonsterPtr_ = arrayMonster[userChoice_ - 1];
            objectPlayer_.addMonster(*objectMonsterPtr_);

            userGate_++;
        }
        else
        {
            cout << "Not possible!" << endl;
        }
    }

    cout << endl;
    delete objectMonsterPtr_;
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
            cout << "Not possible!" << endl;
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
        cout << endl << endl;
        return 1;
    }
    else
    {
        cout << endl << endl;
        return 0;
    }
}

