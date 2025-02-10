/* EE231002 Lab01. Purchasing Petroleum
   106061218, Cheng-En Lee
   Date: 2017/09/18
*/

#include <stdio.h>

int main(void) 
{
    int NTD = 0; // Input amount in NTD
    float tw_liters = 0.0f, tw_gallons = 0.0f; // Petroleum in Taiwan (liters & gallons)
    float us_liters = 0.0f, us_gallons = 0.0f; // Petroleum in the US (liters & gallons)

    // Prompt user for input
    printf("Input amount: ");
    scanf("%d", &NTD);

    // Compute petroleum purchase in Taiwan
    tw_liters = NTD / 25.8f;         // Convert NTD to liters
    tw_gallons = tw_liters / 3.785f; // Convert liters to gallons

    // Compute petroleum purchase in the US
    us_gallons = (NTD / 30.08f) / 3.161f; // Convert NTD to USD, then to gallons
    us_liters = us_gallons * 3.785f;      // Convert gallons to liters

    // Display results
    printf("Petroleum bought in Taiwan: %.6f liters or %.6f gallons\n", tw_liters, tw_gallons);
    printf("Petroleum bought in US: %.6f liters or %.6f gallons\n", us_liters, us_gallons);

    return 0;
}
