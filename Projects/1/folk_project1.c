/* COP 3502C Assignment 1
This program is written by: Joanna Folk */

#include <stdio.h>
#include "leak_detector_c.h"

typedef struct student{
    int id;
    char *lname; //stores last name of student
    float *scores; //stores scores of the student. Size is taken from num_scores array.
    float std_avg; //average score of the student (to be calculated)
 } student;

typedef struct course{
    char *course_name; //stores course name
    int num_sections; //number of sections
    student **sections;//stores array of student arrays(2D array). Size is num_sections;
    int *num_students;//stores array of number of students in each section. Size is num_sections; 
    int *num_scores; //stores array of number of assignments in each section. Size is num_sections;
} course;



struct course *read_courses(FILE *fp, int *num_courses){
    /*This function takes a file pointer and reference of an integer to track how 
    may courses the file has. Then it reads the data for an entire test case and 
    return the allocated memory for all the courses (including sections) for a test case. 
    Note that you can call other functions from this function asneeded.*/
    int i, j, x;
    //fp = fopen(  "in.txt",   "r" );
    // SKIP FIRST TWO LINES OF FILE
    //fscanf( fp, "%*[^\n]\n %*[^\n]\n");

    //POINTER TO ARRAY OF COURSES- WILL BE RETURNED
    
    
    course *c;
    fscanf( fp, "%s", c->course_name);
    printf("%s",c->course_name);
    /*
    for (i=0;i<*num_courses; i++){
        printf("%d", *num_courses);
        fscanf( fp, "%s", c[i].course_name);
        c[i].course_name = (char*)malloc(*c[i].course_name *sizeof(char));

        fscanf( fp, "%d", &c[i].num_sections);
        c[i].num_sections = (int)malloc(c[i].num_sections*sizeof(int));
        
        for (j=0; j<c[i].num_sections; j++){
        
            fscanf(fp, "%d %d", c[i].num_students, c[i].num_scores);

            for(x=0; x<c[i].num_sections; x++){
                //array of student arrays
              //  c[i].sections[x] = read_sections(fp, c[i].num_students, c[i].num_scores, c[i].num_sections);  
            }
    
        }

    } */

    return c;
}

/* struct student **read_sections(FILE *fp, int num_students[], int num_scores[], int num_sections){
    /* This function takes the file pointer, references of two arrays, one for
    number of students, and one for number of scores for a course. The function 
    also takes an integer that indicates the number of sections the course has. 
    The function reads all the data for all the sections of a course, fill-up the 
    num_students and num_socres array of the course and returns 2D array of students 
    that contains all the data for all the sections of a course. A good idea would be 
    calling this function from the read_course function.
    
    fp  = fopen(  "in.txt",   "r" );   
    student *s; 


} */

void process_courses(course *courses, int num_courses){
    /* This function takes the array of courses produced and filled by all the courses of 
    a test case and also takes the size of the array. Then it displays the required data 
    in the same format discussed in the sample output. You can write and use more functions in 
    this process as you wish. */

}

void release_courses( course *courses, int num_courses){
    /* This function takes the array of courses produced and filled by all the courses of a 
    test case and also takes the size of the array. Then it free up all the memory allocated within 
    it. You can create more function as needed to ease the process. */

}



int main(){

    //atexit(report_mem_leak);

    int i, numTestCases, *numCourses;
    FILE * infile; 
    course testCaseArray[numTestCases];

    //READ IN FIRST LINE TO KNOW HOW MANY TEST CASES EXIST
    infile  = fopen(  "in.txt",   "r" );
    fscanf( infile, "%d", &numTestCases); 
    //course allCases[numTestCases];

    for (i=0;i<numTestCases; i++){
        fscanf( infile, "%d", numCourses);
        testCaseArray[i]= *read_courses(infile, numCourses);
    }




    /*allCases should hold
    - number of test case
    - test case number of courses
    - struct array for each course
        -course name 
        -number of sections
        -array of student structs
        -number of assignemtns(gets saved into student struct)
        -array of num students

    */



    
    //allocate memory for number of struct courses
    //allocate memore in struct courses for name, 


}