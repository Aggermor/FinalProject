#ifndef OPPONENT_HPP_INCLUDED
#define OPPONENT_HPP_INCLUDED

class Opponent : public Player
{
public:
    Opponent();

    Monster selectMonster();
    int randomChoice(Monster* objectMonster_);
    int randomMonsterChoice();
};

#endif // OPPONENT_HPP_INCLUDED
