#ifndef OPPONENT_HPP_INCLUDED
#define OPPONENT_HPP_INCLUDED

class Opponent : public Player
{
public:
    Opponent();

    Monster selectMonster(); //random opponent choice
    int randomChoice(Monster* objectMonster_); //healing odds
};

#endif // OPPONENT_HPP_INCLUDED
