#include <iostream>
#include <vector>
#include <random>
#include "Deck.h"

using namespace std;

std::ostream& operator<<(std::ostream& os, const Card& obj) {
    os << "(";
    switch((int)obj.rank) {
        case (int)Rank::King:
            os << "K";
            break;
        case (int)Rank::Queen:
            os << "Q";
            break;
        case (int)Rank::Jack:
            os << "J";
            break;
        case (int)Rank::Ace:
            os << "A";
            break;
        default:
            os << (int)obj.rank;
    }
    os << ", " << (int)obj.suit << ")";
    return os;
}

bool Card::operator<(const Card& other) const {
    if(rank < other.rank) {
        return (int)rank != 0;
    }
    if(rank > other.rank) {
        return (int)other.rank == 0;
    }
    return false;
}

bool Card::operator==(const Card& other) const {
    return rank == other.rank;
}

bool Card::operator!=(const Card& other) const {
    return rank != other.rank;
}

Deck::Deck() {
    for(int suit = 0; suit < 4; suit++) {
        for(int rank = 0; rank < 13; rank++) {
            cards.push_back((Card){(Rank)rank, (Suit)suit});
        }
    }
}

void Deck::reset() {
    cards.clear();
    for(int suit = 0; suit < 4; suit++) {
        for(int rank = 0; rank < 13; rank++) {
            cards.push_back((Card){(Rank)rank, (Suit)suit});
        }
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}

Card Deck::dealCard() {
    Card toDeal = cards.back();
    cards.pop_back();
    return toDeal;
}