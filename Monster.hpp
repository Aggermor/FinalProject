#ifndef MONSTER_HPP_INCLUDED
#define MONSTER_HPP_INCLUDED

class Monster
{
private:
    std::string name;
    std::string type;
    double attack;
    double health;
    double MAX_HEALTH; // cant use const in a constructor I guess but we should pretend it is
    std::vector<std::string> attack_name;

public:
    Monster();
    Monster(std::string name_, std::string type_);

    std::string getName() const;
    std::string getType() const;
    double getAttack() const;
    double getHealth() const;
    double getMAX_HEALTH() const;
    // std::string getAttackName(Monster* objectMonster_); // I plan on recreating this without argument to look cleaner, see constructor and new vector member variable
    std::string getAttackName() const;

    void setName(std::string name_);
    void setType(std::string type_);
    void setAttack(double attack_);
    void setHealth(double health_);

    bool operator ==(const Monster& objectMonster_);

    friend std::ostream& operator <<(std::ostream& out, const Monster& objectMonster_);
    //friend std::operator =(const Monster& objectRightSide_);
};

#endif // MONSTER_HPP_INCLUDED
