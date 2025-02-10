/* EE231002 Lab11. Blackjack Strategy
   ID: 106061218, Cheng-En Lee
   Date: 2017/12/16
*/

#include <stdio.h>
#include "card.h"

extern int step_display;
extern int Nhands;

char play4_name[7] = "me";

// Function to initialize bet based on available credit
int play4_bet_init(const int credit) 
{
    step_display = 1; // Turn off for faster gameplay
    Nhands = 100;     // Number of hands to be played
    return (credit >= 3) ? 3 : credit; // Bet up to 3 credits
}

// Function to decide whether to hit, stand, double, or surrender
int play4_hit_or_stand(const struct CARD mycard[], int Nmycard, const struct CARD dealercard[], int Ndealercard) 
{
    int my_total = sum_cards(mycard, Nmycard);
    int dealer_upcard = card_value(dealercard[0]);

    // Basic strategy for Blackjack
    if (my_total >= 17) return 0; // Always stand on 17+
    if (my_total <= 11) return 1; // Always hit on 11 or lower
    if (my_total == 12 && (dealer_upcard == 2 || dealer_upcard == 3)) 
        return 1; // Hit on 12 vs 2-3
    if (my_total >= 13 && my_total <= 16 && dealer_upcard >= 7) 
        return 1; // Hit when dealer has 7+
    if (my_total == 10 && dealer_upcard < 10) 
        return 2; // Double on 10 if dealer has 9 or lower
    if (my_total == 9 && dealer_upcard >= 3 && dealer_upcard <= 6) 
        return 2; // Double on 9 vs 3-6
    if (my_total == 16 && dealer_upcard >= 9) 
        return 3; // Surrender on 16 vs 9+
    return 0;     // Otherwise, stand
}

// Function called when the deck is reshuffled
void play4_shuffle() 
{
    return; // No action needed
}

// Function called when a card is dealt
void play4_deal_one_card(const struct CARD cd) 
{
    return; // No action needed
}
