/* COP 3502C Assignment 1
This program is written by: Joanna Folk */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


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
    course **courses;
} testcase;


struct student **read_sections(FILE *fp, int num_students[], int num_scores[], int num_sections){
   
    int j, s, x;
    float sum = 0.0;
    student **sect;

    for(x=0; x< num_sections; x++){
      //GET NUM STUDENTS AND SCORES
      fscanf(fp, "%d %d", &num_students[x], &num_scores[x]); 
    
      //ALLOCATE MEMORY
      sect= (student**) malloc(num_sections * sizeof(student*));

      for(int i=0; i<num_sections; i++){
        sect[i] = (student*) malloc ((num_students[x])* sizeof(student));

        for(int j = 0; j<(num_students[x]); j++){
          //STUDENT ID
          fscanf(fp, "%d", &(sect[i][j].id));
          printf( "%d", (sect[i][j].id));
          //NAME
          sect[i][j].lname = malloc(20*sizeof(char));
          fscanf(fp, "%s", sect[i][j].lname);
          //ALLOCATE SCORES
          sect[i][j].scores = (float*)malloc((num_scores[x])* (sizeof(float)));
          for(s=0; s<num_scores[j]; s++){
              fscanf(fp, "%f", &sect[i][j].scores[s]);
          }
          //AVERAGE
          for(s=0; s< num_scores[x]; s++){
              sum = sum + sect[i][j].scores[s];
          }
          sect[i][j].std_avg = (sum/ num_scores[x]);
        }
      }
    }
  return sect; 
} 

struct course *read_courses(FILE *fp, int *num_courses){
    int i, j, x, y;
    struct course *c;
        //ALLOCATE COURSE
        c = (course*)malloc(sizeof(course));
        while (i<(*num_courses))
        {
            //COURSE NAME
            c[i].course_name = malloc(20*sizeof(char)); 
            fscanf(fp, "%s", (c[i].course_name)); 
            //NUMER OF SECTIIONS
            fscanf(fp, "%d", &(c[i].num_sections));
            //NUMBER OF STUDENTS PER SECTION ARRAY (BLANK)
            c[i].num_students = malloc((c->num_sections)*sizeof(int)); 
            //NUMBER OF SCORES PER SECTION ARRAY (BLANK)    
            c[i].num_scores = malloc((c->num_sections)*sizeof(int)); 
            //NUMBER OF SECTIONS
            c[i].sections = (student**)malloc((c[i].num_sections)*sizeof(student));
            c[i].sections = read_sections(fp, c[i].num_students, c[i].num_scores, c[i].num_sections);
            i++;
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
    int i, j;
    for(i=0;i<num_courses;i++){
      for(j=0;j<courses[i].num_sections; i++){
        free(courses[i].sections[j]);
      }
    free(courses[i].num_students);
    free(courses[i].course_name);
    free(courses[i].num_scores);
    
    }
}


   

int main(){

    //atexit(report_mem_leak);
    int i, j, *numTestCases;
    FILE * fp;

 
      //READ IN FIRST LINE TO KNOW HOW MANY TEST CASES
      fp  = fopen( "in.txt",  "r");
      numTestCases = malloc(sizeof(int));
      fscanf(fp, "%d", numTestCases);
      //ALLOCATE ARRAY OF TESTCASES
      testcase *testcaseArray = malloc((*numTestCases)*sizeof(testcase));

      //LOOP THROUGH CASES TO GET AND DISPLAY INFO
      for(i=0; i< (*numTestCases); i++){
          printf("\ntest case %d", (i+1));
          //NUMBER OF COURSES IN CASE
          fscanf(fp, "%d", &(testcaseArray[i].num_courses));
          testcaseArray[i].courses = malloc((testcaseArray[i].num_courses)*sizeof(course));
          
          //GET VALUES OF TEST CASES
          *testcaseArray[i].courses = read_courses(fp, &testcaseArray[i].num_courses);  
          
          //PROCESS COURSES
          //RELEASE COURSES
      }
      printf("DONE");
  
  fclose(fp);
}