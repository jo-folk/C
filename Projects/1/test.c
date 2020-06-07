
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
    int i, j;
    struct course *c; 

    c = (struct course*)malloc(*num_courses * sizeof(struct course));

    for(i=0; i< *num_courses; i++){
        fscanf(fp, "%s", c[i].course_name); 
        fscanf(fp, "%d", &c[i].num_sections); 

        for(j=0; j< c[i].num_sections; j++){
            fscanf(fp, "%d %d", &c[i].num_students[j], &c[i].num_scores[j]); 
            c[i].sections[j] = read_sections(fp, c[i].num_students, c[i].num_scores, c[i].num_sections);
        }
    }
    

    return c;
}

int main(){

}