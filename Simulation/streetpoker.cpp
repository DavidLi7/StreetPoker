#include <vector>

#include "streetpoker.h"

using namespace std;

class StreetPoker {
private:
    Deck deck;
    vector<Card> houseCards;
    vector<Card> playerCards;

//add try catch
    void simulateRound(Strategy s) {
        SimulationRule rule = s.getAction(houseCards, playerCards);

        bool finished = false;
        while(!finished) {
            Card newCard = deck.dealCard();
            if(ruleSatisfied(rule, newCard))  {
                playerCards.push_back(newCard);
                finished = true;
            } else {
                houseCards.push_back(newCard);
            }   
        }
    }

    bool simulate(Strategy s) {
        reset();
        for(int round = 0; round < 5; round++) 
            simulateRound(s);

    }

public:
    StreetPoker(){}

    double simulate(Strategy s, int iterations) {
        int playerWins = 0;
        for(int iterationCount = 0; iterationCount < iterations; iterationCount++)
            playerWins += simulate(s);
        return (double)playerWins / iterations;
    }

    void reset() {
        deck.reset();
        houseCards.clear();
        playerCards.clear();
    }
    
};