/* EE231002 Lab10. College Admission
   106061218, Cheng En Lee
   Date: 2017/12/4
*/

#include <stdio.h>
#include <string.h>
#define MAX_STUDENTS 25
#define MAX_ADMITTED 3

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
    mathD, physD, chemD, geosD, none
} DEPT;

/* Define the structure for students */
typedef struct sStu {
    int appNum;          // Application number
    char fName[20];      // First name
    char lName[20];      // Last name
    int math, phys, chem;// Test scores
    int total;           // Total score
    DEPT pris[4];        // Priority list for departments
    DEPT dept;           // Assigned department
} Stu;

Stu student[MAX_STUDENTS];
int M_admitted = 0, P_admitted = 0, C_admitted = 0, G_admitted = 0;
int minmath = 0, minphys = 0, minchem = 0, mingeos = 0;

/*  Function declarations
	readstudent: The function reads in the data of every student.
	student_rank: The students who has higher score has higher
				  priority to be allocated to the departments first.
				  This fuction let the students "queue" for admitted
	admit_list: Assign each student to departments according to their
				priorities (DEPT pris[4] in Stu).
*/
void readstudent(void);
int student_rank(void);
void admit_list(int wait_admit);
void print_admitted_students(void);

int main(void) 
{
    int i;
    readstudent(); // Read student data
    
    // Assign students to departments
    for (i = 0; i < MAX_STUDENTS; i++)
        admit_list(student_rank());
    
    // Print admitted students and minimum scores
    print_admitted_students();
    
    return 0;
}

/* Function to read student data */
void readstudent(void) 
{
    int i, num;
    char buf[5];
    while (getchar() != '\n'); // Skip first line
    
    for (num = 0; num < MAX_STUDENTS; num++) 
	{
        scanf("%d %s %s %d %d %d", &student[num].appNum, 
									student[num].fName, 
									student[num].lName, 
									&student[num].math, 
									&student[num].phys, 
									&student[num].chem);
        student[num].total = student[num].math + student[num].phys + student[num].chem;
        
        for (i = 0; i < 4; i++) 
		{
            scanf("%s", buf);
            switch (buf[0]) 
			{
                case 'M': student[num].pris[i] = mathD; break;
                case 'P': student[num].pris[i] = physD; break;
                case 'C': student[num].pris[i] = chemD; break;
                case 'G': student[num].pris[i] = geosD; break;
            }
        }
        student[num].dept = none;
    }
}

/* Function to find the highest-ranked student */
int student_rank(void) 
{
    int i, wait_admit = -1;
    int max_score = -1;
    
    for (i = 0; i < MAX_STUDENTS; i++) 
        if (student[i].dept == none)	// Consider only non-admitted students
            if (student[i].total > max_score || (student[i].total == max_score && student[i].appNum < student[wait_admit].appNum))
			{
                max_score = student[i].total;
                wait_admit = i;
            }

    return wait_admit;
}

/* Function to assign students to departments */
void admit_list(int wait_admit) 
{
    int i;
    if (wait_admit == -1) 
		return;
    
    for (i = 0; i < 4; i++) 
	{
        DEPT choice = student[wait_admit].pris[i];
        switch (choice) 
		{
            case mathD:
                if (M_admitted < MAX_ADMITTED) 
				{
                    student[wait_admit].dept = mathD;
                    M_admitted++;
                    minmath = student[wait_admit].total;
                    return;
                }
                break;
            case physD:
                if (P_admitted < MAX_ADMITTED) 
				{
                    student[wait_admit].dept = physD;
                    P_admitted++;
                    minphys = student[wait_admit].total;
                    return;
                }
                break;
            case chemD:
                if (C_admitted < MAX_ADMITTED) 
				{
                    student[wait_admit].dept = chemD;
                    C_admitted++;
                    minchem = student[wait_admit].total;
                    return;
                }
                break;
            case geosD:
                if (G_admitted < MAX_ADMITTED) 
				{
                    student[wait_admit].dept = geosD;
                    G_admitted++;
                    mingeos = student[wait_admit].total;
                    return;
                }
                break;
            default:
                break;
        }
    }
    student[wait_admit].total = -1; // Mark as processed but not admitted
}

/* Function to print admitted students by department */
void print_admitted_students(void) 
{
    int i, j, k;
    const char *deptNames[] = {"Math", "Phys", "Chem", "Geos"};
    int minScores[] = {minmath, minphys, minchem, mingeos};
    DEPT departments[] = {mathD, physD, chemD, geosD};
    
    for (i = 0; i < 4; i++) 
	{
        printf("%s Department: Minimum score %d\n", deptNames[i], minScores[i]);
        for (j = 1, k = 0; k < MAX_STUDENTS; k++)
            if (student[k].dept == departments[i])
                printf("%3d %d %s %s\n", j++, student[k].appNum, student[k].fName, student[k].lName);

        printf("\n");
    }
}
