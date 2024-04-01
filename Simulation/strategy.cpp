#include "strategy.h"

bool ruleSatisfied(SimulationRule rule, Card card) {
    return rule[(int)card.suit][(int)card.rank];
}