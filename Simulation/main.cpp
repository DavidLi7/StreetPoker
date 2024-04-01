#include <iostream>

#include "StreetPoker.h"

using namespace std;

int main() {

    ios_base::sync_with_stdio(0);
    cin.tie (0);
    cout.tie (0);

    // vector<Card> cards;
    // cards.push_back((Card){(Rank)0, (Suit)0});
    // cards.push_back((Card){(Rank)12, (Suit)0});
    // cards.push_back((Card){(Rank)10, (Suit)0});
    // cards.push_back((Card){(Rank)8, (Suit)0});
    // cards.push_back((Card){(Rank)7, (Suit)0});
    // cards.push_back((Card){(Rank)0, (Suit)1});
    // cards.push_back((Card){(Rank)11, (Suit)1});
    // cards.push_back((Card){(Rank)10, (Suit)1});
    // cards.push_back((Card){(Rank)8, (Suit)1});
    // cards.push_back((Card){(Rank)7, (Suit)1});

    // HandAnalyzer::PokerHand hand = HandAnalyzer::getBestPokerHand(cards);
    // cout << hand << "\n";

    StreetPoker sp;
    Strategy st;
    cout << sp.simulate(st, 100) << "\n";

}   