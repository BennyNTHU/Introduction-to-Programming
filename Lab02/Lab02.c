/* EE231002 Lab02. Currency Exchange
   106061218, Cheng-En Lee
   Date: 2017/10/02
*/

#include <stdio.h>

int main() 
{
    int USD = 0; // Input amount in USD
    int amount_100 = 0, amount_50 = 0, amount_20 = 0, amount_10 = 0; // output amount of bills
    int amount_5 = 0, amount_2 = 0, amount_1 = 0;

    // Prompt user for input
    printf("Enter USD amount: ");
    scanf("%d", &USD);

    // Compute the least number of bills
    amount_100 = USD / 100;
    USD = USD % 100;
    amount_50 = USD / 50;
    USD = USD % 50;
    amount_20 = USD / 20;
    USD = USD % 20;
    amount_10 = USD / 10;
    USD = USD % 10;
    amount_5 = USD / 5;
    USD = USD % 5;
    amount_2 = USD / 2;
    USD = USD % 2;
    amount_1 = USD;

    // Display results only if the bill count is greater than zero
    printf("To pay:\n");
    if (amount_100 > 0) printf("  %d $100 bill%s\n", amount_100, amount_100 > 1 ? "s" : "");
    if (amount_50 > 0) printf("  %d $50 bill%s\n", amount_50, amount_50 > 1 ? "s" : "");
    if (amount_20 > 0) printf("  %d $20 bill%s\n", amount_20, amount_20 > 1 ? "s" : "");
    if (amount_10 > 0) printf("  %d $10 bill%s\n", amount_10, amount_10 > 1 ? "s" : "");
    if (amount_5 > 0) printf("  %d $5 bill%s\n", amount_5, amount_5 > 1 ? "s" : "");
    if (amount_2 > 0) printf("  %d $2 bill%s\n", amount_2, amount_2 > 1 ? "s" : "");
    if (amount_1 > 0) printf("  %d $1 bill%s\n", amount_1, amount_1 > 1 ? "s" : "");
    
    return 0;
}
