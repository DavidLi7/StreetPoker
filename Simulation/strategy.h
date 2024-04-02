#include <vector>
#include <array>
#include "Deck.h"

using namespace std;

using SimulationRule = array<array<bool, 4>, 13>;

bool ruleSatisfied(SimulationRule rule, Card card);

class Strategy {
private:
public:
    SimulationRule getAction(vector<Card>& houseCards, vector<Card>& playerCards) const;
};