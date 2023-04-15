/*
EE2310 Lab01 Purchasing Petroleum
106061218, Cheng-En, Lee
2017/09/18
*/

#include <stdio.h>

int main(void)
{
	int NTD; //input amount of NTD.
	float twlit,twgal; //how many liters or gallons can you buy in Taiwan.
	float uslit,usgal; //how many liters or gallons can you buy in the US.

	printf("Input amount: "); 
	scanf("%d",&NTD); //input amount
	
	twlit = NTD/25.8;
		//Calculating the amount of petroleum that could be bought
	twgal = (NTD/25.8)/3.785;
		//Calculatiog the amount of petroleum that could be bought
	uslit = ((NTD/30.08)/3.161)*3.785;
		//Calculating the amount of petroleum that could be bought
	usgal = (NTD/30.08)/3.161;
		//Calculating the amount of petroleum that could be biught
	
	printf("Petroleum bought in Taiwan: %f liters or %f gallons\n"
			,twlit ,twgal);
	printf("Petroleum bought in US: %f liters or %f gallons\n"
			,uslit,usgal);


	return 0;

}


