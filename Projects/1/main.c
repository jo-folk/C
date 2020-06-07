/* COP 3502C Assignment 1
This program is written by: Joanna Folk */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "leak_detector_c.h"

typedef struct student{
    int id;
    char *lname;
    float *scores; 
    float std_avg; 
 } student;

typedef struct course{
    char *course_name; 
    int num_sections; 
    student **sections;
    int *num_students;//Size is num_sections; 
    int *num_scores; //Size is num_sections;
} course;

typedef struct testcase{
    int num_courses; 
    course *courses;
} testcase;


struct student **read_sections(FILE *fp, int num_students[], int num_scores[], int num_sections){

    int j, s, x, i;
    float sum;
    student **sect;
  
    sect= (student**) malloc(num_sections * sizeof(student*));

    for(x=0; x< num_sections; x++){
      //GET NUM STUDENTS AND SCORES FOR SECTION
      fscanf(fp, "%d %d", &num_students[x], &num_scores[x]); 
      printf("\n%d %d", num_students[x], num_scores[x]);
      sect[x] = (student*) malloc ((num_students[x])* sizeof(student*));

        for(int j = 0; j<(num_students[x]); j++){
          //STUDENT ID
          fscanf(fp, "%d", &(sect[x][j].id));
          //NAME
          sect[i][j].lname = malloc(20*sizeof(char));
          fscanf(fp, "%s", sect[x][j].lname);

           printf("\nstudent: %d %s", (sect[x][j].id), sect[x][j].lname);
          //ALLOCATE SCORES
          sect[x][j].scores = (float*)malloc((num_scores[x])* (sizeof(float*)));
          for(s=0; s<num_scores[x]; s++){
              fscanf(fp, "%f", &sect[x][j].scores[s]);
              printf(" %.2f ", sect[x][j].scores[s]);
          }
          sum = 0.0;
          for(s=0; s< num_scores[x]; s++){
              sum = sum + sect[i][j].scores[s];
          }
          sect[i][j].std_avg = (sum/ num_scores[x]);
          printf(" avg: %.2f ", sect[i][j].std_avg);
        }
    }
  return sect; 
} 

struct course *read_courses(FILE *fp, int *num_courses){
    int i, j, x, y;
    struct course *c;
        //ALLOCATE COURSE
        c = (course*)malloc(sizeof(course));
        for (i=0; i<(*num_courses);i++)
        {
            //ALLOCATE
            c[i].course_name = malloc(20*sizeof(char)); 
            c[i].num_students = malloc((c[i].num_sections)*sizeof(int)); 
            c[i].num_scores = malloc((c[i].num_sections)*sizeof(int));
            c[i].sections = (student**)malloc((c[i].num_sections)*sizeof(student)); 
            //VALUES
            fscanf(fp, "%s %d ", c[i].course_name , &(c[i].num_sections)); 
            printf("\n%s", c[i].course_name);
            c[i].sections = read_sections(fp, c[i].num_students, c[i].num_scores, c[i].num_sections);
        } 
    return c; //COURSE
}


void process_courses(course *courses, int num_courses){
    /* This function takes the array of courses produced and filled by all the courses of 
    a test case and also takes the size of the array. Then it displays the required data 
    in the same format discussed in the sample output. You can write and use more functions in 
    this process as you wish. */
  
}

void release_courses(course *courses, int num_courses){
    /* This function takes the array of courses produced and filled by all the courses of a 
    test case and also takes the size of the array. Then it free up all the memory allocated within 
    it. You can create more function as needed to ease the process. */
    
}


   

int main(){

    atexit(report_mem_leak);
    int i, j, *numTestCases;
    FILE * fp;

 
      //READ IN FIRST LINE TO KNOW HOW MANY TEST CASES
      fp  = fopen( "in.txt",  "r");
      numTestCases = malloc(sizeof(int));
      fscanf(fp, "%d", numTestCases);
      //ALLOCATE ARRAY OF TESTCASES
      testcase *testcaseArray = (testcase*)malloc((*numTestCases)*sizeof(testcase));

      //LOOP THROUGH CASES TO GET AND DISPLAY INFO
      for(i=0; i< (*numTestCases); i++){
          printf("\ntest case %d", (i+1));
          //NUMBER OF COURSES IN CASE
          fscanf(fp, "%d", &(testcaseArray[i].num_courses));
          testcaseArray[i].courses = malloc((testcaseArray[i].num_courses)*sizeof(course));
          
          //GET VALUES OF TEST CASES
          testcaseArray[i].courses = read_courses(fp, &testcaseArray[i].num_courses);  
          
          //PROCESS COURSES
          //process_courses(testcaseArray[i].courses, testcaseArray[i].num_courses);

          //RELEASE COURSES
          printf("\n");
      }
      printf("DONE");
  
  fclose(fp);
}