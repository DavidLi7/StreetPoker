#include <iostream>
#include <vector>

#include "StreetPoker.h"

using namespace std;

//Deal until we get to next card
void StreetPoker::simulateRound(Strategy s) {    
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

//Simulate one entire game
bool StreetPoker::simulate(Strategy s) {
    reset();
    for(int round = 0; round < 5; round++) 
        simulateRound(s);
    while(houseCards.size() < 8) {
        Card newCard = deck.dealCard();
        houseCards.push_back(newCard);
    }
    HandAnalyzer::PokerHand houseHand = HandAnalyzer::getBestPokerHand(houseCards);
    HandAnalyzer::PokerHand playerHand = HandAnalyzer::getBestPokerHand(playerCards);

    // cout << "House:\n";
    // for(Card card: houseCards) {
    //     cout << card << ", ";
    // }
    // cout << "\n";
    // cout << houseHand;

    // cout << "Player:\n";
    // for(Card card: playerCards) {
    //     cout << card << ", ";
    // }
    // cout << "\n";
    // cout << playerHand;

    
    return houseHand < playerHand;
}

StreetPoker::StreetPoker(){}

//Simulate iterations rounds and return the success rate
double StreetPoker::simulate(Strategy s, int iterations) {
    int playerWins = 0;
    for(int iterationCount = 0; iterationCount < iterations; iterationCount++) {
        playerWins += simulate(s);
    }
    cout << playerWins << " " << iterations << "\n";
    return (double)playerWins / iterations;
}

void StreetPoker::reset() {
    deck.reset();
    houseCards.clear();
    playerCards.clear();
}