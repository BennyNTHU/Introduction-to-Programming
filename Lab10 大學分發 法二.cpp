/* EE231002 Lab10. College Admission
   106061127, Liu chia wei
   Date:2017/12/4
*/

#include <stdio.h>
#include <string.h>    // For the purpose of calling string function

/*****   Define the types for this program    *****/
typedef enum sDEPT {        // Define 4 departments
    mathD, physD, chemD, geosD, none
} DEPT;
typedef struct sStu {
    int appNum;             // application number
    char fName[20];         // first name
    char lName[20];         // last name
    int math, phys, chem;   // test scores
    int total;              // total score
    DEPT pris[4];           // student's priority
    DEPT dept;              // admitted dept
} Stu;
typedef struct {
	char firstName[20];
	char lastName[20];
} name;
/*****     The variables for this program   *****/

int adm=0,adp=0,adc=0,adg=0; // The counters for the admission vacancy
int appnum;			// The variable to store the application number in function
int compare;		// The variable to store the score in function
int index;			// The variable to store the index in function
int minscore=300;	// The variable to store the minimum score in function	
char name1[20];		// The array to store the name 
char name2[20];
Stu data[100];      // The array to store the input

/*****    The functions for this program    *****/
void change(int b);	 // The function to put the admitted college into dept
void readStu(void);  // The function to read in the data
int findStu(Stu data[100]); // The function to find the admitted students

int main(void)
{
    int i=0,j=1;  // i is the counter of loops
				  // j is the order of the students
    readStu();    // Read in the students' datas
    
	for (i=0; i<100; i++) { 	// Store the department that the students
		change(findStu(data));	// admitted into the dept(by calling function)
	}	
	
	
	for (i=0; i<100; i++) {		// Find out the minimum admitted score 
		if (data[i].dept==mathD) { // of math department
			if (minscore>(data[i].math+data[i].phys+data[i].chem))
				minscore=data[i].math+data[i].phys+data[i].chem;
		}	// Because the data[i].total is reset to 0,
	}		// I use the sum of three datas instead
	printf("Math Department: Minimum score %d\n",minscore);
	
	
	
	
	for (i=0; i<100; i++) {	// Print out the admitted student
		if (data[i].dept==mathD) { // Choose the department
			printf("  %d %d ",j,data[i].appNum);
			printf("%s %s\n",data[i].fName,data[i].lName);
			j++;	// Count the order of the datas
		}
	}
	j=1;			// Reset the order
	minscore=300;   // Reset the minimum score
	
	
	
	for (i=0; i<100; i++) {	// Find out the minimum admitted score 
		if (data[i].dept==physD) { // of physics department
			if (minscore>(data[i].math+data[i].phys+data[i].chem))
				minscore=data[i].math+data[i].phys+data[i].chem;
		}	// Because the data[i].total is reset to 0,
	}		// I use the sum of three datas instead
	printf("Phys Department: Minimum score %d\n",minscore);
	
	
	
	for (i=0; i<100; i++) {          // Print out the admitted student
		if (data[i].dept==physD) {   // Choose the department
			printf("  %d %d ",j,data[i].appNum);
			printf("%s %s\n",data[i].fName,data[i].lName);
			j++; // Count the order of the datas
		}	
	}
	j=1;		  // Reset the order
	minscore=300; // Reset the minimum score
	
	
	
	for (i=0; i<100; i++) {	// Find out the minimum admitted score 
		if (data[i].dept==chemD) { // of chemistry department
			if (minscore>(data[i].math+data[i].phys+data[i].chem))
				minscore=data[i].math+data[i].phys+data[i].chem;
		}	// Because the data[i].total is reset to 0,
	}		// I use the sum of three datas instead
	printf("Chem Department: Minimum score %d\n",minscore);
	
	
	
	for (i=0; i<100; i++) {  // Print out the admitted student
		if (data[i].dept==chemD) { 
			printf("  %d %d ",j,data[i].appNum);
			printf("%s %s\n",data[i].fName,data[i].lName);
			j++; // Count the order of the datas
		}	
	}
	j=1;		   // Reset the order
	minscore=300;  // Reset the minimum score
	
	
	
	for (i=0; i<100; i++) {	 // Find out the minimum admitted score 
		if (data[i].dept==geosD) { // of chemistry department
			if (minscore>(data[i].math+data[i].phys+data[i].chem))
				minscore=data[i].math+data[i].phys+data[i].chem;
		}	// Because the data[i].total is reset to 0,
	}		// I use the sum of three datas instead
	printf("Geos Department: Minimum score %d\n",minscore);
	
	
	
	for (i=0; i<100; i++) {  // Print out the admitted student
		if (data[i].dept==geosD) { 
			printf("  %d %d ",j,data[i].appNum);
			printf("%s %s\n",data[i].fName,data[i].lName);
			j++; // Count the order of the datas
		}	
	}
	
	
	
	
    return 0;   // End of the program
}


void readStu(void)
{
    int i,j;		// The counter for the loops
    char judge[5];  // The extra array to store the text for judgement

    while (getchar() != '\n');	// Skip the first line of the file

    for (i=0; i<100; i++) {
        scanf("%d",&data[i].appNum);// Read in application numbers
        scanf("%s",data[i].fName);  // Read in first name
        scanf("%s",data[i].lName);  // Read in last name
        scanf("%d",&data[i].math);  // Read in math score
        scanf("%d",&data[i].phys);  // Read in physics score
        scanf("%d",&data[i].chem);  // Read in chemistry score
        data[i].total = data[i].math + data[i].phys + data[i].chem;
        for (j=0; j<4; j++) {   // Do four times,for the 4 order of priority
            scanf("%s",judge);           // use a extra array to check the
            if (strcmp(judge,"Math")==0) // priority of students' deaprtments
                data[i].pris[j]=mathD; 	 
            if (strcmp(judge,"Geos")==0)
                data[i].pris[j]=geosD;  
            if (strcmp(judge,"Phys")==0)
                data[i].pris[j]=physD;
            if (strcmp(judge,"Chem")==0)
                data[i].pris[j]=chemD;
        }
        
    }
    return ;  // The function's return value is void
}



int findStu(Stu data[100])
{
    int i;		// The counters for the loop 
    
    compare=0;	// The initialization of the first data
    
    for (i=0; i<100; i++) {
        if (compare < data[i].total) {  
        	compare=data[i].total;  // Record the score
			index=i; // and the index of the student 
        }    		 // who has the highest score now
    }
    data[index].total=0;    // set the highest score to zero
    					// then next time we can skip this data
	return index;// Return the index of student so that	we can deal with it
}



void change(int b)
{	
	int flag=1;	// The variable to end the loop when the student is admitted
	int i=0;	// The counter for the loop	
	
	for (i=0; i<4 && flag!=0; i++) { // To check the students' priorities
		switch (data[b].pris[i]) {	 // about the departments
			case 0:				
				if (adm<20) {	// To check whether there is any vacancy
					data[b].dept=mathD;
					adm++;   // The admitted student number plus 1
					flag=0;	 // Terminate the loop
				}
				break;
			case 1:
				if (adp<20) {  // To check whether there is any vacancy
					data[b].dept=physD;
					adp++;   // The admitted student number plus 1
					flag=0;  // Terminate the loop
				}
				break;
			case 2:
				if (adc<20) { // To check whether there is any vacancy
					data[b].dept=chemD;
					adc++;  // The admitted student number plus 1
					flag=0; // Terminate the loop
				}
				break;
			case 3:
				if (adg<20) { // To check whether there is any vacancy
					data[b].dept=geosD;
					adg++;  // The admitted student number plus 1
					flag=0; // Terminate the loop
				}
				break;
			default: 
				break;
		}
	}	
	if (flag == 1) 		// If the loop terminates and the student hasn't
		data[b].dept=none;// been admitted to any department,
						  // let the student into none department
	return ;
}
																							                                                                                                      
