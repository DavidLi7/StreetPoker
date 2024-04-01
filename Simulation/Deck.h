#include <vector>

using namespace std;

enum class Rank {
    Ace, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King
};

enum class Suit {
    Hearts, Diamonds, Clubs, Spades
};

struct Card {
    Rank rank;
    Suit suit;
};

class Deck {
private:
    vector<Card> cards;

public:
    Deck();

    //resets the deck and shuffles it
    void reset();

    //deals the card at the top of the deck
    Card dealCard();
};