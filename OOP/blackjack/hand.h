#ifndef HAND_H
#define HAND_H

#include "card.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

class Hand
{
  public:
    Hand();

    virtual ~Hand();

    //adds a card to the hand
    void Add(Card *pCard);

    //clears hand of all cards
    void Clear();

    //gets hand total value, intelligently treats aces as 1 or 11
    int GetTotal() const;

  protected:
    vector<Card *> m_Cards;
};

#endif