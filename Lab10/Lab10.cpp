/* EE2310 Lab10. College Admission
   106061218, Cheng En, Lee.
   2017/12/4
*/


#include <stdio.h>
#include <string.h>


/*  Global Variables: 
	sDEPT: define four department in an enum.
   	sStu: Basic information of students.
   	student[100]: An array of structures, which include 100 
				  students' data.
   	X_admitted: Counting the students get admitted to each 
				department, each departments has limit = 20 
				students. 'X' stands for each departments, 
				where their first alphabet implies.
	minxxxx: The minimum score to be admitted.
			 xxxx stands for each departments.
*/
typedef enum sDEPT {
	mathD, physD, chemD, geosD, none,
} DEPT;

typedef struct sStu{
	int appNum;
	char fName[20];
	char lName[20];
	int math, phys, chem;
	int total;
	DEPT pris[4];
	DEPT dept;
} Stu;

Stu student[100];

int M_admitted = 0;
int P_admitted = 0;
int C_admitted = 0;
int G_admitted = 0;
int minmath = 0;
int minphys = 0;
int minchem = 0;
int mingeos = 0;

/*  Functions: 
	readstudent: The function reads in the data of every student.
	student_rank: The students who has higher score has higher
				  priority to be allocated to the departments first.
				  This fuction let the students "queue" for admitted
	admit_list: Assign each student to departments according to their
				priorities (DEPT pris[4] in Stu).
*/
void readstudent(void);
int student_rank(Stu student[100]);
void admit_list(int wait_admit);


/* Main function */
int main(void)
{
	int i = 0, j = 0;
	
 /* Allocate The students. */
	readstudent();
	for (i = 0; i < 100; i++)
    	admit_list(student_rank(student));
 
 /* List the students admitted for each departments and the minimum score. */
	printf("Math Department: Minimum score %d\n",minmath);
 	for (i = 0,j = 1; i < 100; i++)
 	{
   		if (student[i].dept == mathD)
     		printf("%3d %d %s %s\n",j++, student[i].appNum, 
						student[i].fName, student[i].lName);
 	} 
 
 	printf("\nPhys Department: Minimum score %d\n",minphys);
	for (i = 0,j = 1; i < 100; i++)
 	{
   		if (student[i].dept == physD)
     		printf("%3d %d %s %s\n",j++, student[i].appNum, 
						student[i].fName, student[i].lName);
 	} 
 
 	printf("\nChem Department: Minimum score %d\n",minchem);
 	for (i = 0,j = 1; i < 100; i++)
 	{
   		if (student[i].dept == chemD)
     		printf("%3d %d %s %s\n",j++, student[i].appNum, 
						student[i].fName, student[i].lName);
 	}
 
 	printf("\nGeos Department: Minimum score %d\n",mingeos);
 	for (i = 0,j = 1; i < 100; i++)
 	{
   		if (student[i].dept == geosD)
     	printf("%3d %d %s %s\n",j++, student[i].appNum, 
					student[i].fName, student[i].lName);
 	} 
	
 	printf("\nAs for the others, good luck for next year! See you!\n");
	return 0;
}


/* "readstudent" function */
void readstudent(void)
{
	int i = 0;		// Index of priorities. 
	int num = 0;	// Index of students.
	char buf[5];	// The priorities of students listed in lab10.dat.
	
	while (getchar() != '\n');	// Skip the first line.
	
	for (num = 0; num < 100; num++)
	{
	 /* Reads in the data. */
		scanf("%d",&student[num].appNum);
		scanf("%s",student[num].fName);
		scanf("%s",student[num].lName);
		scanf("%d",&student[num].math);
		scanf("%d",&student[num].phys);
		scanf("%d",&student[num].chem);
	
	/* Calculating the total score of three subjects */
    	student[num].total = student[num].math 
						   + student[num].phys 
						   + student[num].chem;
	
	/* Reads in the priority list. 
	   It can be determined by the first character. */
		for (i = 0; i <= 3; i++)
		{
			scanf("%s",buf);
			switch (buf[0])	// First character of the department.
			{
				case 'M': student[num].pris[i] = mathD; break;
				case 'P': student[num].pris[i] = physD; break;
				case 'C': student[num].pris[i] = chemD; break;
				case 'G': student[num].pris[i] = geosD;
			}	
		} 
   		
	 /* Initialize the students admittied department */	
		student[num].dept = none;
 	}
}


/* "student_rank" function */
int student_rank(Stu student[100])
{
	int num = 0;			// Index of students.
  	int wait_admit = 0;		// The index of a student who would be allocated.
  	int current_maxima = 0;	// Compare the total score.
  

 /* In this function, students will be allocated by the order 
 	of their total score. 
	That is, for one who has the higher total score than those 
	who haven't be admitted, his or her index will be recorded 
	in "wait_admit" and passed to the "admit_list" function. */ 
  	for (num = 0; num < 100; num++)
  	{
    	if (student[num].total > current_maxima)
    	{
      		current_maxima = student[num].total;
      		wait_admit = num;
    	}
  	}
  
  	return wait_admit;
}


/* "admit_list" function */
void admit_list(int wait_admit)
{
	int i = 0;  
  
 /* If all department was full, The student has to wait for next year */
  	for (i = 0; i <= 3 && student[wait_admit].dept == none; i++)
  	{
    	switch (student[wait_admit].pris[i])	
 	 // The students priority list was checked by order.
    	{

   	 	 /* In each case, if a student want to be admitted, then the
   	  		department has to less than 20 student when his or her turn. */
     		case mathD:
           		if (M_admitted < 20)
           	 	{

		  		 /* If one is admitted, his or her score would be 
				 	the current minimum score to get admitted. 
					Unless there's another student got admitted. 
					The last one be admitted to a department, 
					his score would be the absolute minimum. */

             		student[wait_admit].dept = mathD;
             		M_admitted++;
             		minmath = student[wait_admit].total;
           	 	}  break;

      		case physD: 
           		if (P_admitted < 20)
           		{	
             		student[wait_admit].dept = physD;
             		P_admitted++;
             		minphys = student[wait_admit].total;
           		}  break;

     		case chemD: 
           		if (C_admitted < 20)
           		{
             		student[wait_admit].dept = chemD;
             		C_admitted++;
             		minchem = student[wait_admit].total;
           		}  break;

      		case geosD: 
           		if (G_admitted < 20)
           		{
             		student[wait_admit].dept = geosD;
             		G_admitted++;
             		mingeos = student[wait_admit].total;
           		}  
      	}
    }
    
 /* Reset the total score of the admitted students.
 	Then the process of finding the next one to 
	admit could skip this student. */		
    student[wait_admit].total = 0;
}



