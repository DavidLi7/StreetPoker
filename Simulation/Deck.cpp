#include <vector>
#include "deck.h"
#include <random>

using namespace std;

class Deck {
private:
    vector<Card> cards;

public:
    Deck() {
        for(int suit = 0; suit < 4; suit++) {
            for(int rank = 0; rank < 13; rank++) {
                cards.push_back({(Rank)rank, (Suit)suit});
            }
        }
    }

    void reset() {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(cards.begin(), cards.end(), g);
    }

    Card dealCard() {
        Card toDeal = cards.back();
        cards.pop_back();
        return toDeal;
    }

};