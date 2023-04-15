/*
 EE231002 Lab02 Currency Exchange
 106061218, Cheng-En Lee
 2017/10/02
*/

#include <stdio.h>

int main()
{
	int USD;	//The amount input.
	int amount_100, amount_50, amount_20, amount_10;
	int amount_5, amount_2, amount_1;
		//The amount of each kind of bill that will be output.

	printf("Enter USD amount: ");
	scanf("%d", &USD);	//Input the amount of US dollors.

	amount_100 = (USD/100);	//the amount of $100 bill is the hundred digit.
	amount_50 = (USD%100)/50;
		//The amount of $50 bill is
		//the quotient of "remainder of USD%100" divided by 50.
	amount_20 = ((USD%100)%50)/20;
		//the lines below show the calculating process of each amount required,
		//which is same idea with line 19~23.
	amount_10 = (((USD%100)%50)%20)/10;
	amount_5 = ((((USD%100)%50)%20)%10)/5;
	amount_2 = (((((USD%100)%50)%20)%10)%5)/2;
	amount_1 = ((((((USD%100)%50)%20)%10)%5)%2)/1;

	printf("To pay:\n");

	//For lines below, due to the rule of English grammer,
	//when the amount of a kind of bill more then 1,
	//we need to convert "bill" into "bills".
	//however, if it doesn't need one kind of bill,
	//nothing would be output as required.

	if (amount_100 == 1)
		printf("  %d $100 bill\n" ,amount_100);
	else if (amount_100 > 1)
		printf("  %d $100 bills\n" ,amount_100);
	
	if (amount_50 == 1)
		printf("  %d $50 bill\n" ,amount_50);
	else if (amount_50 > 1)
		printf("  %d $50 bills\n" ,amount_50);

	if (amount_20 == 1)
		printf("  %d $20 bill\n" ,amount_20);
	else if (amount_20 > 1)
		printf("  %d $20 bills\n" ,amount_20);

	if (amount_10 == 1)
		printf("  %d $10 bill\n" ,amount_10);
	else if (amount_10 > 1)
		printf("  %d $10 bills\n" ,amount_10);

	if (amount_5 == 1)
		printf("  %d $5 bill\n" ,amount_5);
	else if (amount_5 > 1)
		printf("  %d $5 bills\n" ,amount_5);

	if (amount_2 == 1)
		printf("  %d $2 bill\n" ,amount_2);
	else if (amount_2 > 1)
		printf("  %d $2 bills\n" ,amount_2);

	if (amount_1 == 1)
		printf("  %d $1 bill\n" ,amount_1);
	else if (amount_1 > 1)
		printf("  %d $1 bills\n" ,amount_1);

	return 0;
}

