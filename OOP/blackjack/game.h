#ifndef GAME_H
#define GAME_H

#include "deck.h"
#include "house.h"
#include "player.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

class Game
{
public:
    Game(const vector<string>& names);
    
    ~Game();
    
    //plays the game of blackjack    
    void Play();

private:
    Deck m_Deck;
    House m_House;
    vector<Player> m_Players;  
};

#endif