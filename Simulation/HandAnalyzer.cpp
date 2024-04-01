#include <vector>
#include <array>

#include "HandAnalyzer.h"

using namespace std;

using Hand = array<std::array<bool, 4>, 13>;

struct HandAnalyzer::PokerHand {
    HandRank rank;
    vector<Card> values;
    vector<Card> kickers;

    bool operator<(const PokerHand& other) const {
        if(rank < other.rank) {
            return true;
        }
        if(rank > other.rank) {
            return false;
        }
        for(int i = 0; i < values.size(); i++) {
            if(values[i].rank < other.values[i].rank) {
                return (int)values[i].rank != 0;
            }
            if(values[i].rank > other.values[i].rank) {
                return (int)other.values[i].rank != 0;
            }
        }
        for(int i = 0; i < kickers.size(); i++) {
            if(kickers[i].rank < other.kickers[i].rank) {
                return (int)kickers[i].rank != 0;
            }
            if(kickers[i].rank < other.kickers[i].rank) {
                return (int)other.kickers[i].rank != 0;
            }
        }
        return false;
    }

    bool operator==(const PokerHand& other) const {
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
};

HandAnalyzer::PokerHand getBestPokerHand(const vector<Card>& cards) {

    Hand hand;
    for(Card card: cards) {
        hand[(int)card.suit][(int)card.rank] = true;
    }

    //check for royal/straight flush
    for(int lowest = 9; lowest >= 0; lowest--) {
        for(int suit = 0; suit < 4; suit++) {
            HandAnalyzer::PokerHand temporaryHand;
            bool isOk = true;
            for(int rank = lowest; rank < lowest + 5 && isOk; rank++) {
                isOk &= hand[suit][rank % 13];
                if(isOk) {
                    temporaryHand.values.push_back({(Rank)(rank % 13), (Suit)suit});
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
            isOk &= hand[suit][rank % 13];
            if(isOk) {
                temporaryHand.values.push_back({(Rank)(rank % 13), (Suit)suit});
            }
        }
        if(isOk) {
            temporaryHand.rank = HandAnalyzer::HandRank::FourOfAKind;
            for(int rank2 = 13; rank2 >= 1; rank2--) if(rank != rank2){
                for(int suit = 0; suit < 4; suit++) {
                    if(hand[suit][rank2 % 13]) {
                        temporaryHand.kickers.push_back({(Rank)(rank2 % 13), (Suit)suit});
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
            if(hand[suit][rank1 % 13]) {
                instances.push_back({(Rank)(Rank)(rank1 % 13), (Suit)suit});
            }
        }
        if(instances.size() != 3)
            continue;
        for(int rank2 = 13; rank2 >= 1; rank2--) if(rank1 != rank2) {
            vector<Card> instances2;
            for(int suit = 0; suit < 4; suit++) {
                if(hand[suit][rank2 % 13]) {
                    instances2.push_back({(Rank)(rank2 % 13), (Suit)suit});
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
                if(hand[suit][rank % 13]) {
                    temporaryHand.values.push_back({(Rank)(rank % 13), (Suit)suit});
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
                if(hand[suit][rank % 13]) {
                    temporaryHand.values.push_back({(Rank)(rank % 13), (Suit)suit});
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
        for(int suit = 0; suit < 4; suit++) {
            temporaryHand.values.push_back({(Rank)rank, (Suit)suit});
        }
        if(temporaryHand.values.size() != 3) 
            continue;
        temporaryHand.rank = HandAnalyzer::HandRank::ThreeOfAKind;
        for(int rank2 = 13; rank2 >= 1; rank2--) if(rank != rank2){
            for(int suit = 0; suit < 4; suit++) {
                if(hand[suit][rank2 % 13]) {
                    temporaryHand.kickers.push_back({(Rank)(rank2 % 13), (Suit)suit});
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
            if(hand[suit][rank1 % 13]) {
                instances.push_back({(Rank)(Rank)(rank1 % 13), (Suit)suit});
            }
        }
        if(instances.size() != 2)
            continue;
        for(int rank2 = 13; rank2 >= 1; rank2--) if(rank1 != rank2) {
            vector<Card> instances2;
            for(int suit = 0; suit < 4; suit++) {
                if(hand[suit][rank2 % 13]) {
                    instances2.push_back({(Rank)(rank2 % 13), (Suit)suit});
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
                        if(hand[suit][rank3 % 13]) {
                            temporaryHand.kickers.push_back({(Rank)(rank3 % 13), (Suit)suit});
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
        for(int suit = 0; suit < 4; suit++) {
            temporaryHand.values.push_back({(Rank)rank, (Suit)suit});
        }
        if(temporaryHand.values.size() != 2) 
            continue;
        temporaryHand.rank = HandAnalyzer::HandRank::ThreeOfAKind;
        for(int rank2 = 13; rank2 >= 1; rank2--) if(rank != rank2){
            for(int suit = 0; suit < 4; suit++) {
                if(hand[suit][rank2 % 13]) {
                    temporaryHand.kickers.push_back({(Rank)(rank2 % 13), (Suit)suit});
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
            if(hand[suit][rank % 13]) {
                temporaryHand.kickers.push_back({(Rank)(rank % 13), (Suit)suit});
                if(temporaryHand.kickers.size() == 5) {
                    return temporaryHand;
                }
            }
        }
    }
    return temporaryHand;
    
}