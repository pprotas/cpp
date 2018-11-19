// simple_boss2.cpp
// Compile with: g++ simple_boss2.cpp -o simple_boss2

#include <iostream>
using namespace std;

class Enemy
{
  public:
    Enemy();
    void Attack() const;

  protected:
    int m_Damage;
};

Enemy::Enemy() : m_Damage(10)
{
}

void Enemy::Attack() const
{
    cout << "Attack inflicts " << m_Damage << " damage points!\n";
}

class Boss : public Enemy
{
  public:
    Boss();
    void SpecialAttack() const;

  protected:
    int m_DamageMultiplier;
};

Boss::Boss() : m_DamageMultiplier(3)
{
}

void Boss::SpecialAttack() const
{
    cout << "Special Attack inflicts " << (m_DamageMultiplier * m_Damage);
    cout << " damage points!\n";
}

class FinalBoss : public Boss
{
  public:
    FinalBoss();
    void MegaAttack() const;
};

FinalBoss::FinalBoss()
{
}

void FinalBoss::MegaAttack() const
{
    cout << "Mega Attack inflicts " << (10 * m_DamageMultiplier * m_Damage);
    cout << " damage points!\n";
}
int main()
{
    cout << "Creating an enemy.\n";
    Enemy enemy1;
    enemy1.Attack();

    cout << "\nCreating a boss.\n";
    Boss boss1;
    boss1.Attack();
    boss1.SpecialAttack();

    cout << "\nCreating a final boss.\n";
    FinalBoss finalboss1;
    finalboss1.Attack();
    finalboss1.SpecialAttack();
    finalboss1.MegaAttack();
    return 0;
}
