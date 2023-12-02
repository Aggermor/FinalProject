#ifndef OPPONENT_HPP_INCLUDED
#define OPPONENT_HPP_INCLUDED

class Opponent : public Player
{
public:
    Opponent();

    Monster selectMonster();
    int randomChoice();
    int randomMonsterChoice();
};

#endif // OPPONENT_HPP_INCLUDED
