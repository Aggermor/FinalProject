#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Monster.hpp"
#include "Player.hpp"
#include "Battleground.hpp"
#include "Opponent.hpp"

using namespace std;

namespace mainExtraFunction
{
    int monsterSpecificSelection(Player& objectPlayer_) // im hoping creating a namespace will allow us to use this main function here
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
}
// constructors
Battleground::Battleground()
{

}

Battleground::Battleground(Player objectPlayer_, Opponent objectOpponent_)
{
    objectPlayerPtr = new Player(objectPlayer_);
    objectOpponentPtr = new Opponent(objectOpponent_);
}

Battleground::~Battleground()
{
    delete objectPlayerPtr;
    delete objectOpponentPtr;
    delete objectPlayerMonsterPtr_;
    delete objectOpponentMonsterPtr_;
}

// critical hit roll
bool Battleground::isCriticalHit(int chance)
{
    //srand(time(0)); issue
    int critRoll = rand() % 100 + 1;  // from 1 to 100.
    if(critRoll <= chance) {return true;} // (<= 10) is 10%, (<= 20) is 20%
    else {return false;}
}

void Battleground::healCheck(Monster* duck)
{
    const double HEAL_PERCENT = 0.33; // 0.33 is 33% of MAX HEALTH
    double heal = duck -> getMAX_HEALTH() * HEAL_PERCENT;

    // if already max health (or more somehow)
    if(duck -> getHealth() >= duck -> getMAX_HEALTH())
        {cout << duck -> getName() << " is already healthy..." << endl;}

    // else, below max health
    else
    {
        // apply heal
        duck -> setHealth(duck -> getHealth() + heal);

        // check if healed over max health
        if(duck -> getHealth() > duck -> getMAX_HEALTH())
        {
            // cap healing to max health
            cout << duck -> getName() << " fully restored its health." << endl;
            duck -> setHealth(duck -> getMAX_HEALTH());
        }

        // else, healing is within max health
        else
            {cout << duck -> getName() << " restored " << heal << " health." << endl;}
    }
}

// damage & type advantage calculations
double Battleground::getDamage(Monster* attacker, Monster* defender)
{
    double total_damage = 0; // damage to return
    const double CRIT_DAMAGE_MULTIPLIER = 0.30; // (* 0.30) is 30% base damage

    // Really effective = +10% damage
    if
    (
        (attacker -> getType() == "Water" && defender -> getType() == "Fire") ||
        (attacker -> getType() == "Fire" && defender -> getType() == "Wind") ||
        (attacker -> getType() == "Wind" && defender -> getType() == "Water")
    )
    {
        cout << "Really effective!" << endl;
        total_damage = attacker -> getAttack() * 1.10; // +10% base damage
        if(isCriticalHit(30)) // 30% chance to crit
        {
            cout << "Critical hit!" << endl;
            total_damage += attacker -> getAttack() * CRIT_DAMAGE_MULTIPLIER;
        }
    }

    // Same type = base damage
    else if
    (
        (attacker -> getType() == "Water" && defender -> getType() == "Water") ||
        (attacker -> getType() == "Fire" && defender -> getType() == "Fire") ||
        (attacker -> getType() == "Wind" && defender -> getType() == "Wind")
    )
    {
        total_damage = attacker -> getAttack(); // base damage
        if(isCriticalHit(15)) // 15% chance to crit
        {
            cout << "Critical hit!" << endl;
            total_damage += attacker -> getAttack() * CRIT_DAMAGE_MULTIPLIER;
        }
    }

    // Not effective = -10% damage
    else if
    (
        (attacker -> getType() == "Water" && defender -> getType() == "Wind") ||
        (attacker -> getType() == "Fire" && defender -> getType() == "Water") ||
        (attacker -> getType() == "Wind" && defender -> getType() == "Fire")
    )
    {
        cout << "Not effective..." << endl;
        total_damage = attacker -> getAttack() * 0.90; // -10% base damage
        if(isCriticalHit(10)) // 10% chance to crit
        {
            cout << "Critical hit!" << endl;
            total_damage += attacker -> getAttack() * CRIT_DAMAGE_MULTIPLIER;
        }
    }

    // error code
    else
    {
        cout << "DEBUG: Error with Battleground::getBattleAttack()" << endl;
        return 1;
    }

    cout << total_damage << " damage dealt!" << endl << endl;
    return total_damage;
}

void Battleground::choosePlayerMonsterToFight()
{
    objectPlayerPtr -> displayAllMonster();
    objectPlayerMonsterPtr_ = new Monster(objectPlayerPtr -> selectMonster(mainExtraFunction::monsterSpecificSelection(*objectPlayerPtr)));

    cout << objectPlayerPtr -> getName() << " chooses " << objectPlayerMonsterPtr_ -> getName() << "!" << endl << endl;
}

void Battleground::chooseOpponentMonsterToFight()
{
    objectOpponentMonsterPtr_ = new Monster(objectOpponentPtr -> Opponent::selectMonster());

    cout << objectOpponentPtr -> getName() << " chooses " << objectOpponentMonsterPtr_ -> getName() << "!" << endl;
}

void Battleground::battleInterface()
{
    cout << "***************************************************************" << endl;
    cout << "                                "; battleInventory(objectOpponentPtr -> getSize()); cout << endl;
    cout << "                                Duck: " << objectOpponentMonsterPtr_ -> getName() << endl;
    cout << "                                Type: " << objectOpponentMonsterPtr_ -> getType() << endl;
    cout << "                                Health: " << objectOpponentMonsterPtr_ -> getHealth() << endl;

    battleInventory(objectPlayerPtr -> getSize()); cout << endl;
    cout << "Duck: " << objectPlayerMonsterPtr_ -> getName() << endl;
    cout << "Type: " << objectPlayerMonsterPtr_ -> getType() << endl;
    cout << "Health: " << objectPlayerMonsterPtr_ -> getHealth() << endl;
    cout << "***************************************************************" << endl << endl;
    cout << "[1] Attack: " << objectPlayerMonsterPtr_ -> getAttack() << endl;
    cout << "[2] Roost: " << objectPlayerMonsterPtr_ -> getMAX_HEALTH() * 0.33 << endl;
    cout << "[3] Switch Ducks " << endl;
    cout << "[4] Information about moves " << endl << endl;
}
int Battleground::battleInput()
{

    int userChoice_;
    cout << "Action [#]: ";
    cin >> userChoice_;
    cout << endl;
    return userChoice_;
}

void Battleground::battleLoop()
{
    while(objectPlayerPtr -> getSize() > 0 && objectOpponentPtr -> getSize() > 0)
    {
        bool player_blocked = false; // oponent can still heal
        bool player_switched = false; // oponent can still heal
        bool skip_opponent_turn = false; // used to loop again

        // Player's turn to battle
        battleInterface();
        switch(battleInput()) // battleSelection() defined in main, could it be moved battleground class for simplicity?
        {

        case 1: // attack
            cout << objectPlayerPtr -> getName() << "'s " << objectPlayerMonsterPtr_-> getName() << " uses " << objectPlayerMonsterPtr_ -> getAttackName() << "!" << endl;
            objectOpponentMonsterPtr_ -> setHealth(objectOpponentMonsterPtr_ -> getHealth() - getDamage(objectPlayerMonsterPtr_, objectOpponentMonsterPtr_));
            battleCheck();
            break;
        case 2: // heal
            cout << objectPlayerPtr -> getName() << "'s " << objectPlayerMonsterPtr_-> getName() << " REINFORCES their health!" << endl;

            healCheck(objectPlayerMonsterPtr_);
            player_blocked = rand() % 2;  // 50% chance to block next attack;
            battleCheck();
            break;
        case 3: // switch
            cout << objectPlayerPtr -> getName() << " SWITCHES out " << objectPlayerMonsterPtr_-> getName() << endl;
            player_switched = true;
            objectPlayerPtr -> updateMonsterInVector(objectPlayerMonsterPtr_);
            choosePlayerMonsterToFight();
            break;
        case 4: // information
            cout << objectPlayerMonsterPtr_ -> getName() << "'s elemental type (" << objectPlayerMonsterPtr_ -> getType() << ") is accounted for during battle:" << endl;
            cout << "Water is strong to Fire" << endl;
            cout << "Fire is strong to Wind" << endl;
            cout << "Wind is strong to Water" << endl;
            cout << "All ducks have some chance to hit critically, boosting its damage by 30%." << endl;
            cout << endl;
            cout << "Entering [1]: Attack will damage your opponent based on your duck's type (" << objectPlayerMonsterPtr_ -> getType() << ") and attack strength (" << objectPlayerMonsterPtr_ -> getAttack() << ")." << endl;
            cout << "            > Strong types do +10% more damage and are 30% likely to hit critically." << endl;
            cout << "            > Same types do normal damage and are 15% likely to hit critically." << endl;
            cout << "            > Weak types do -10% damage and are 10% likely to hit critically." << endl;
            cout << "Entering [2]: Roost will increases health and has a 50% chance to block your opponent's hit." << endl;
            cout << "            > Healing amount is 33% of maximum health (" << objectPlayerMonsterPtr_ -> getMAX_HEALTH() * 0.33 << ") and wont go higher than max (" << objectPlayerMonsterPtr_ -> getMAX_HEALTH() << ")." << endl;
            cout << "Entering [3]: Switch will let you choose a new duck fighter." << endl;
            cout << "            > " << objectPlayerMonsterPtr_ -> getName() << "'s health will be saved for next time it fights this opponent." << endl << endl;
            skip_opponent_turn = true; // used to loop again
            break;
        default:
            cout << "Not possible! Enter a valid number." << endl;
            skip_opponent_turn = true; // used to loop again
            break;
        }

        // if player is defeated, then skip opponents turn and end this loop
        if(objectPlayerPtr -> getSize() == 0 || objectOpponentPtr -> getSize() == 0) {break;}

        // Opponent's turn to battle
        cout << endl; // new line for Opponent's turn

        if(!skip_opponent_turn) // do not skip turn
        {
            switch(objectOpponentPtr -> randomChoice(objectOpponentMonsterPtr_))
            {
            case 1:

                if(player_blocked)
                {
                    cout << objectOpponentPtr -> getName() << "'s " << objectOpponentMonsterPtr_-> getName() << " uses " << objectOpponentMonsterPtr_ -> getAttackName() << "!" << endl << endl;
                    cout << objectPlayerPtr -> getName() << "'s " << objectPlayerMonsterPtr_ -> getName() <<" BLOCKS the attack!" << endl <<  endl;
                }
                else if(player_switched) {cout << "The challenger bides their time..." << endl <<  endl;}
                else
                {
                    cout << objectOpponentPtr -> getName() << "'s " << objectOpponentMonsterPtr_-> getName() << " uses " << objectOpponentMonsterPtr_ -> getAttackName() << "!"<< endl; // needs to be only applied if the opponent attacks
                    objectPlayerMonsterPtr_ -> setHealth(objectPlayerMonsterPtr_ -> getHealth() - getDamage(objectOpponentMonsterPtr_, objectPlayerMonsterPtr_));
                    battleCheck();
                }
                break;
            case 2:
                cout << objectOpponentPtr -> getName() << "'s REINFORCES their health!" << endl;
                healCheck(objectOpponentMonsterPtr_);
                battleCheck();
                break;
            default:
                cout << "Not possible!" << endl;
                break;
            }
        }

        // halt interface so the player can summarize turn before next screen is created
        cout << "Press any key to continue: ";
        char input;
        cin >> input;
    }
}

void Battleground::battleCheck()
{
    if(objectPlayerMonsterPtr_ -> getHealth() <= 0)
    {
        cout << "Oh! " << objectPlayerPtr -> getName() << "'s "<< objectPlayerMonsterPtr_ -> getName() << " is down!" << endl << endl;

        objectPlayerPtr -> removeMonster(*objectPlayerMonsterPtr_);

        if(objectPlayerPtr -> getSize() > 0)
        {
            choosePlayerMonsterToFight();
        }
    }
    else if(objectOpponentMonsterPtr_ -> getHealth() <= 0)
    {
        cout << "Oh! " << objectOpponentPtr -> getName() << "'s "<< objectOpponentMonsterPtr_ -> getName() <<" is down!" << endl << endl;

        objectOpponentPtr -> removeMonster(*objectOpponentMonsterPtr_);

        if(objectOpponentPtr -> getSize() > 0)
        {
            chooseOpponentMonsterToFight();
        }
    }
}

bool Battleground::battleResult()
{
    if(objectPlayerPtr -> getSize() > 0 )
    {
        cout << "Victory against " << objectOpponentPtr -> getName() << "!" << endl << endl;
        return true;
    }
    else
    {
        cout << "Defeat by the hands " << objectOpponentPtr -> getName() << "!" << endl << endl;
        return false;
    }
}

void Battleground::battleInventory(int sizeMonster)
{
    for(int i = 0; i < sizeMonster; i++)
    {
        cout << "o ";
    }
    for(int i = 0; i < 3 - sizeMonster; i++)
    {
        cout << "x ";
    }

}
