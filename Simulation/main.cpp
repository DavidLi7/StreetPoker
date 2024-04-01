#include <iostream>

#include "StreetPoker.h"

using namespace std;

int main() {

    ios_base::sync_with_stdio(0);
    cin.tie (0);
    cout.tie (0);

    vector<Card> cards;
    cards.push_back((Card){(Rank)0, (Suit)0});
    cards.push_back((Card){(Rank)1, (Suit)0});
    cards.push_back((Card){(Rank)2, (Suit)0});
    cards.push_back((Card){(Rank)3, (Suit)0});
    cards.push_back((Card){(Rank)4, (Suit)1});

    HandAnalyzer::PokerHand hand = HandAnalyzer::getBestPokerHand(cards);
    cout << hand << "\n";

    vector<Card> cards2;
    cards2.push_back((Card){(Rank)1, (Suit)0});
    cards2.push_back((Card){(Rank)2, (Suit)0});
    cards2.push_back((Card){(Rank)3, (Suit)0});
    cards2.push_back((Card){(Rank)4, (Suit)0});
    cards2.push_back((Card){(Rank)5, (Suit)1});

    HandAnalyzer::PokerHand hand2 = HandAnalyzer::getBestPokerHand(cards2);
    cout << hand2 << "\n";

    cout << (hand < hand2) << "\n";

    // StreetPoker sp;
    // Strategy st;
    // cout << sp.simulate(st, 1000000) << "\n";

}   