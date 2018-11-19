#ifndef HOUSE_H
#define HOUSE_H

#include "genericplayer.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

class House : public GenericPlayer
{
public:
    House(const string& name = "House");

    virtual ~House();

    //indicates whether house is hitting - will always hit on 16 or less
    virtual bool IsHitting() const;

    //flips over first card
    void FlipFirstCard();
};

#endif