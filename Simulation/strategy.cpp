#include <iostream>
#include "Strategy.h"

bool ruleSatisfied(SimulationRule rule, Card card) {
    return rule[(int)card.rank][(int)card.suit];
}

SimulationRule Strategy::getAction(vector<Card>& houseCards, vector<Card>& playerCards) const {
    // SimulationRule rule;
    // for(int rank = 0; rank < 13; rank++) {
    //     for(int suit = 0; suit < 4; suit++) {
    //         rule[rank][suit] = (rank >= 9 || rank == 0);
    //     }
    // }
    // return rule;

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