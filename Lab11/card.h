/* card.h - Header file for Lab11 Blackjack Strategy */
// Just for eliminating warning

#ifndef CARD_H
#define CARD_H

// Define the CARD structure
struct CARD {
    char suit;  // Card suit: H (Hearts), D (Diamonds), C (Clubs), S (Spades)
    char rank;  // Card rank: 2-9, T, J, Q, K, A
};

// Function prototype for dealercard() to suppress warnings
void dealercard();

#endif // CARD_H
