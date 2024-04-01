#include <vector>
#include "Strategy.h"
#include "HandAnalyzer.h"

using namespace std;

class StreetPoker {
private:
    Deck deck;
    vector<Card> houseCards;
    vector<Card> playerCards;

    //simulates one round using the given strategy
    bool simulate(Strategy s);
    void simulateRound(Strategy s);

public:
    StreetPoker();

    //simulates a given number of rounds using given strategy and returns percent of successes
    double simulate(Strategy s, int iterations);

    //resets the game
    void reset();
    
};