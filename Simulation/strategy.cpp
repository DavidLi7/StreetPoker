#include "Strategy.h"

bool ruleSatisfied(SimulationRule rule, Card card) {
    return rule[(int)card.rank][(int)card.suit];
}

SimulationRule Strategy::getAction(vector<Card> houseCards, vector<Card> playerCards) {
    SimulationRule rule;
    for(int rank = 0; rank < 13; rank++) {
        for(int suit = 0; suit < 4; suit++) {
            rule[rank][suit] = (rank >= 10 || rank == 0);
        }
    }
    return rule;
}