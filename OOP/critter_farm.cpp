// critter_farm.cpp
// Compile with: g++ critter_farm.cpp -o critter_farm

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Critter
{
    friend ostream &operator<<(ostream &os, const Critter &aCritter);

  public:
    Critter(const string &name = "");
    string GetName() const;

  private:
    string m_Name;
};

Critter::Critter(const string &name) : m_Name(name)
{
}

inline string Critter::GetName() const
{
    return m_Name;
}

class Farm
{
    friend ostream &operator<<(ostream &os, const Farm &aFarm);

  public:
    Farm(int spaces = 1);
    void Add(const Critter &aCritter);
    void RollCall() const;

  private:
    vector<Critter> m_Critters;
};

Farm::Farm(int spaces)
{
    m_Critters.reserve(spaces);
}

void Farm::Add(const Critter &aCritter)
{
    m_Critters.push_back(aCritter);
}

void Farm::RollCall() const
{
    for (vector<Critter>::const_iterator iter = m_Critters.begin();
         iter != m_Critters.end();
         ++iter)
    {
        cout << iter->GetName() << " here.\n";
    }
}

ostream &operator<<(ostream &os, const Critter &aCritter)
{
    os << aCritter.m_Name;
    return os;
}

ostream &operator<<(ostream &os, const Farm &aFarm)
{
    os << "Critters in this farm:\n";
    for (auto it = aFarm.m_Critters.begin(); it != aFarm.m_Critters.end(); ++it)
    {
        os << *it << endl;
    }
}
int main()
{
    Critter crit("Poochie");
    cout << "My critter's name is " << crit.GetName() << endl;

    cout << "\nCreating critter farm.\n";
    Farm myFarm(3);

    cout << "\nAdding three critters to the farm.\n";
    myFarm.Add(Critter("Moe"));
    myFarm.Add(Critter("Larry"));
    myFarm.Add(Critter("Curly"));

    cout << "\nCalling Roll...\n";
    myFarm.RollCall();

    cout << crit << endl << myFarm;
    return 0;
}
