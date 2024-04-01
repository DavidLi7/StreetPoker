#include <iostream>
#include <vector>
#include <array>

#include "HandAnalyzer.h"

using namespace std;

using Hand = array<std::array<bool, 4>, 13>;

std::ostream& operator<<(std::ostream& os, const HandAnalyzer::PokerHand& obj) {
    switch((int)obj.rank) {
        case (int)HandAnalyzer::HandRank::RoyalFlush:
            os << "Royal Flush\n";
            break;
        case (int)HandAnalyzer::HandRank::StraightFlush:
            os << "Straight Flush\n";
            break;
        case (int)HandAnalyzer::HandRank::FourOfAKind:
            os << "Four of a Kind\n";
            break;
        case (int)HandAnalyzer::HandRank::FullHouse:
            os << "Full House\n";
            break;
        case(int) HandAnalyzer::HandRank::Flush:
            os << "Flush\n";
            break;
        case (int)HandAnalyzer::HandRank::Straight:
            os << "Straight\n";
            break;
        case (int)HandAnalyzer::HandRank::ThreeOfAKind:
            os << "Three of a Kind\n";
            break;
        case (int)HandAnalyzer::HandRank::TwoPairs:
            os << "Two Pair\n";
            break;
        case (int)HandAnalyzer::HandRank::OnePair:
            os << "One Pair\n";
            break;
        case (int)HandAnalyzer::HandRank::HighCard:
            os << "High Card\n";
            break;
    }
    os << "Values: ";
    for(Card card: obj.values) {
        cout << card << ", ";
    }
    os << "\n";
    os << "Kickers: ";
    for(Card card: obj.kickers) {
        cout << card << ", ";
    }
    os << "\n";
    return os;
}

bool HandAnalyzer::PokerHand::operator<(const PokerHand& other) const {
    if(rank < other.rank) {
        return true;
    }
    if(rank > other.rank) {
        return false;
    }
    for(int i = 0; i < values.size(); i++) {
        if(values[i] != other.values[i]) {
            return values[i] < other.values[i];
        }
    }
    for(int i = 0; i < kickers.size(); i++) {
        if(kickers[i] != other.kickers[i]) {
            return kickers[i] < other.kickers[i];
        }
    }
    return false;
}

bool HandAnalyzer::PokerHand::operator==(const PokerHand& other) const {
    if(rank != other.rank) {
        return false;
    }
    for(int i = 0; i < values.size(); i++) {
        if(values[i].rank != other.values[i].rank) {
            return false;
        }
    }
    for(int i = 0; i < kickers.size(); i++) {
        if(kickers[i].rank != other.kickers[i].rank) {
            return false;
        }
    }
    return true;
}

HandAnalyzer::PokerHand HandAnalyzer::getBestPokerHand(const vector<Card>& cards) {

    Hand hand;
    for(int i = 0; i < 13; i++) {
        for(int j = 0; j < 4; j++) {
            hand[i][j] = false;
        }
    }
    for(Card card: cards) {
        hand[(int)card.rank][(int)card.suit] = true;
    }

    //check for royal/straight flush
    for(int lowest = 9; lowest >= 0; lowest--) {
        for(int suit = 0; suit < 4; suit++) {
            HandAnalyzer::PokerHand temporaryHand;
            bool isOk = true;
            for(int rank = lowest; rank < lowest + 5 && isOk; rank++) {
                isOk &= hand[rank % 13][suit];
                if(isOk) {
                    temporaryHand.values.push_back((Card){(Rank)(rank % 13), (Suit)suit});
                }
            }
            if(isOk) {
                if(lowest == 9) {
                    temporaryHand.rank = HandAnalyzer::HandRank::RoyalFlush;
                } else {
                    temporaryHand.rank = HandAnalyzer::HandRank::StraightFlush;
                }
                return temporaryHand;
            }
        }
    }

    //check for four of a kind
    for(int rank = 13; rank >= 1; rank--) {
        HandAnalyzer::PokerHand temporaryHand;
        bool isOk = true;
        for(int suit = 0; suit < 4 && isOk; suit++) {
            isOk &= hand[rank % 13][suit];
            if(isOk) {
                temporaryHand.values.push_back((Card){(Rank)(rank % 13), (Suit)suit});
            }
        }
        if(isOk) {
            temporaryHand.rank = HandAnalyzer::HandRank::FourOfAKind;
            for(int rank2 = 13; rank2 >= 1; rank2--) if(rank != rank2){
                for(int suit = 0; suit < 4; suit++) {
                    if(hand[rank2 % 13][suit]) {
                        temporaryHand.kickers.push_back((Card){(Rank)(rank2 % 13), (Suit)suit});
                        return temporaryHand;
                    }
                }
            }
            return temporaryHand;
        }
    }

    //check for full house
    for(int rank1 = 13; rank1 >= 1; rank1--) {
        vector<Card> instances;
        for(int suit = 0; suit < 4; suit++) {
            if(hand[rank1 % 13][suit]) {
                instances.push_back((Card){(Rank)(rank1 % 13), (Suit)suit});
            }
        }
        if(instances.size() != 3)
            continue;
        for(int rank2 = 13; rank2 >= 1; rank2--) if(rank1 != rank2) {
            vector<Card> instances2;
            for(int suit = 0; suit < 4; suit++) {
                if(hand[rank2 % 13][suit]) {
                    instances2.push_back((Card){(Rank)(rank2 % 13), (Suit)suit});
                    if(instances2.size() == 2)
                        break;
                }
            }
            if(instances2.size() == 2) {
                HandAnalyzer::PokerHand temporaryHand;
                temporaryHand.values.insert(temporaryHand.values.end(), instances.begin(), instances.end());
                temporaryHand.values.insert(temporaryHand.values.end(), instances2.begin(), instances2.end());
                temporaryHand.rank = HandAnalyzer::HandRank::FullHouse;
                return temporaryHand;
            }
        }
    }

    //check for flush
    {
        HandAnalyzer::PokerHand returnedHand;
        returnedHand.rank = HandAnalyzer::HandRank::HighCard;
        for(int suit = 0; suit < 4; suit++) {
            HandAnalyzer::PokerHand temporaryHand;
            for(int rank = 13; rank >= 1; rank--) {
                if(hand[rank % 13][suit]) {
                    temporaryHand.values.push_back((Card){(Rank)(rank % 13), (Suit)suit});
                    if(temporaryHand.values.size() == 5) {
                        break;
                    }
                }
            }
            if(temporaryHand.values.size() == 5) {
                temporaryHand.rank = HandAnalyzer::HandRank::Flush;
                returnedHand = max(returnedHand, temporaryHand);
            }
        }
        if(returnedHand.rank == HandAnalyzer::HandRank::Flush) {
            return returnedHand;
        }
    }
    
    //check for straight
    for(int lowest = 9; lowest >= 0; lowest--) {
        HandAnalyzer::PokerHand temporaryHand;
        for(int rank = lowest; rank < lowest + 5; rank++) {
            for(int suit = 0; suit < 4; suit++) {
                if(hand[rank % 13][suit]) {
                    temporaryHand.values.push_back((Card){(Rank)(rank % 13), (Suit)suit});
                    break;
                }
            }
        }
        if(temporaryHand.values.size() == 5) {
            temporaryHand.rank = HandAnalyzer::HandRank::Straight;
            return temporaryHand;
        }
    }


    //check for three of a kind
    for(int rank = 13; rank >= 1; rank--) {
        HandAnalyzer::PokerHand temporaryHand;
        for(int suit = 0; suit < 4; suit++) if(hand[rank % 13][suit]){
            temporaryHand.values.push_back((Card){(Rank)(rank % 13), (Suit)suit});
        }
        if(temporaryHand.values.size() != 3) 
            continue;
        temporaryHand.rank = HandAnalyzer::HandRank::ThreeOfAKind;
        for(int rank2 = 13; rank2 >= 1; rank2--) if(rank != rank2){
            for(int suit = 0; suit < 4; suit++) {
                if(hand[rank2 % 13][suit]) {
                    temporaryHand.kickers.push_back((Card){(Rank)(rank2 % 13), (Suit)suit});
                    if(temporaryHand.kickers.size() == 2) {
                        return temporaryHand;
                    }
                }
            }
        }
        return temporaryHand;
    }

    //check for two pair
    for(int rank1 = 13; rank1 >= 1; rank1--) {
        vector<Card> instances;
        for(int suit = 0; suit < 4; suit++) {
            if(hand[rank1 % 13][suit]) {
                instances.push_back((Card){(Rank)(rank1 % 13), (Suit)suit});
            }
        }
        if(instances.size() != 2)
            continue;
        for(int rank2 = 13; rank2 >= 1; rank2--) if(rank1 != rank2) {
            vector<Card> instances2;
            for(int suit = 0; suit < 4; suit++) {
                if(hand[rank2 % 13][suit]) {
                    instances2.push_back((Card){(Rank)(rank2 % 13), (Suit)suit});
                    if(instances2.size() == 2)
                        break;
                }
            }
            if(instances2.size() == 2) {
                HandAnalyzer::PokerHand temporaryHand;
                temporaryHand.rank = HandAnalyzer::HandRank::TwoPairs;
                temporaryHand.values.insert(temporaryHand.values.end(), instances.begin(), instances.end());
                temporaryHand.values.insert(temporaryHand.values.end(), instances2.begin(), instances2.end());
                for(int rank3 = 13; rank3 >= 1; rank3--) if(rank3 != rank2 && rank3 != rank1){
                    for(int suit = 0; suit < 4; suit++) {
                        if(hand[rank3 % 13][suit]) {
                            temporaryHand.kickers.push_back((Card){(Rank)(rank3 % 13), (Suit)suit});
                            return temporaryHand;
                            
                        }
                    }
                }
                return temporaryHand;
            }
        }
    }

    //check for pair
    for(int rank = 13; rank >= 1; rank--) {
        HandAnalyzer::PokerHand temporaryHand;
        for(int suit = 0; suit < 4; suit++) if(hand[rank % 13][suit]){
            temporaryHand.values.push_back((Card){(Rank)(rank % 13), (Suit)suit});
        }
        if(temporaryHand.values.size() != 2) 
            continue;
        temporaryHand.rank = HandAnalyzer::HandRank::OnePair;
        for(int rank2 = 13; rank2 >= 1; rank2--) if(rank != rank2){
            for(int suit = 0; suit < 4; suit++) {
                if(hand[rank2 % 13][suit]) {
                    temporaryHand.kickers.push_back((Card){(Rank)(rank2 % 13), (Suit)suit});
                    if(temporaryHand.kickers.size() == 3) {
                        return temporaryHand;
                    }
                }
            }
        }
        return temporaryHand;
    }

    //high card
    HandAnalyzer::PokerHand temporaryHand;
    temporaryHand.rank = HandAnalyzer::HandRank::HighCard;
    for(int rank = 13; rank >= 1; rank--){
        for(int suit = 0; suit < 4; suit++) {
            if(hand[rank % 13][suit]) {
                temporaryHand.kickers.push_back((Card){(Rank)(rank % 13), (Suit)suit});
                if(temporaryHand.kickers.size() == 5) {
                    return temporaryHand;
                }
            }
        }
    }
    return temporaryHand;
    
}