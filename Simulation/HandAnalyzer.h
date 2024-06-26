#include <vector>
#include "Deck.h"

using namespace std;

class HandAnalyzer {
public:
    enum class HandRank {
        HighCard, OnePair, TwoPairs, ThreeOfAKind, Straight, Flush, FullHouse, FourOfAKind, StraightFlush, RoyalFlush
    };

    struct PokerHand {
        HandRank rank;
        vector<Card> values;
        vector<Card> kickers;

        bool operator<(const PokerHand& other) const;

        bool operator==(const PokerHand& other) const;

        friend std::ostream& operator<<(std::ostream& os, const PokerHand& obj);
    };

    static PokerHand getBestPokerHand(const vector<Card>& cards);
};