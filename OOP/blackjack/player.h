#ifndef PLAYER_H
#define PLAYER_H

#include "genericplayer.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

class Player : public GenericPlayer
{
public:
    Player(const string& name = "");

    virtual ~Player();

    //returns whether or not the player wants another hit       
    virtual bool IsHitting() const;

    //announces that the player wins
    void Win() const;

    //announces that the player loses
    void Lose() const;

    //announces that the player pushes
    void Push() const;
};

#endif