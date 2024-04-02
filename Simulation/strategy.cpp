#include <iostream>
#include "Strategy.h"

bool ruleSatisfied(SimulationRule rule, Card card) {
    return rule[(int)card.rank][(int)card.suit];
}

/*
    CHANGE THIS METHOD
    SimulationRule is defined in Strategy.h as array<array<bool, 4>, 13>;
    Given houseCards and playerCards, return a 13x4 boolean array denoting whether you want that card
*/
SimulationRule Strategy::getAction(vector<Card>& houseCards, vector<Card>& playerCards) const {
    
    //This strategy will ask for a 10 or higher for the first card and then try to get a royal flush
    SimulationRule rule;
    if(playerCards.size() == 0) {
        for(int rank = 0; rank < 13; rank++) {
            for(int suit = 0; suit < 4; suit++) {
                rule[rank][suit] = (rank >= 9 || rank == 0);
            }
        }
    } else {
        int targetSuit = (int)playerCards[0].suit;
        for(int rank = 0; rank < 13; rank++) {
            for(int suit = 0; suit < 4; suit++) {
                rule[rank][suit] = (suit == targetSuit && (rank >= 9 || rank == 0));
            }
        }
    }
    return rule;
}