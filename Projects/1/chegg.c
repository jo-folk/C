#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_NAME 21

//create the stuctures
typedef struct
{
    unsigned int id;
    char lname[MAX_NAME];
    double* marks; //stores the marks
    double avg; //stores the average of a student
} student;


typedef struct
{
    int st; //the number of students
    int m;//the number of assignments
    double avg_s; //stores the average of section
    int passed_s; //the number of students passed in the section
    student* students;
    student* max_avg_student_s; //stores pointer to the student with max avg in a section
} section;

//structure for course
typedef struct
{
    char cn[MAX_NAME];
    int s; // the number of sections
    int passed_c; //the number of students passed in the course
    section* sections; //stores the sections
    student* max_avg_student_c; ///stores pointer to the student with max avg in a course
} course;

//this stores all the courses of a case
typedef struct
{
    int numCourses;
    course* courses;
} testcase;


void getstudentinput(FILE *fp, student* stu, int m){
    //get student id
    fscanf(fp, "%d", &stu->id);
    //get the student name
    fscanf(fp, "%s", stu->lname);
    //allocate the marks arrat
    stu->marks = malloc(sizeof(double) * m);
    //initialise a sum variable
    double sum = 0.0;
    //get the marks
    for(int i = 0; i < m; i++){
        scanf("%lf", (stu->marks) + i);
        sum += (stu->marks)[i];
    }
    //store the average
    stu->avg = sum / m;
}


void getsectioninput(FILE *fp, section *sec){
    //get number of students
    fscanf(fp, "%d", &(sec->st));
    //get number of assignments
    fscanf(fp, "%d", &(sec->m));
    //allocate students
    sec->students = malloc(sizeof(student) * (sec->st));
    //initilise passed to 0
    sec->passed_s = 0;
    //initialise a sum variable
    double sum = 0.0;
    double max_avg = -1.0; //the max average encountered
    //input all students data
    for(int i = 0; i < sec->st; i++){
        getstudentinput(fp, (sec->students) + i, sec->m);
        //add the student average
        double s_avg = ((sec->students) + i)->avg;
        //update max_avg
        if(s_avg > max_avg){
            max_avg = s_avg;
            //set the pointer
            sec->max_avg_student_s = (sec->students) + i;
        }
        sum += s_avg;
        //if s_avg >= 70, then increment passed count
        if(s_avg >= 70.0){
            (sec->passed_s)++;
        }
    }
    //set the section average
    sec->avg_s = sum / sec->st;
}


void getcourseinput(FILE *fp, course* c){
    //get the name of the course
    fscanf(fp, "%s", c->cn);
    fscanf(fp, "%d", &(c->s));
    //allocate the sections
    c->sections = malloc(sizeof(section) * (c->s));
    //initialise passed to 0
    c->passed_c = 0;
    double max_avg = -1.0;
    //get all sections
    for(int i = 0; i < c->s; i++){
        getsectioninput(fp, (c->sections)+ i);
        //add the total pass count
        c->passed_c += ((c->sections) + i)->passed_s;
        double avg = (c->sections)[i].max_avg_student_s->avg;
        if(avg > max_avg){
            //update max_avg
            max_avg = avg;
            //update pointer
            c->max_avg_student_c = (c->sections)[i].max_avg_student_s;
        }
    }
}

struct course *read_courses(FILE *fp, int *num_courses){
  
}
void getcasesinput(FILE *fp, testcase *curr_case){
    //get the number of courses
    fscanf(fp, "%d", &(curr_case->numCourses));
    printf("\n%d", curr_case->numCourses);
    //allocate the courses
    curr_case->courses = malloc(sizeof(course) * (curr_case->numCourses));
    //input all courses
    for(int i = 0; i < curr_case->numCourses; i++){
        getcourseinput(fp, (curr_case->courses) + i);
    }
}


//function for deallocating all the data
void deallocate(testcase* cases, int n){
    //n is the number of cases
    for(int i = 0; i < n; i++){
        //now loop over each course
        testcase cur_case = cases[i];
        for(int case_i = 0; case_i < cur_case.numCourses; case_i++){
            course cur_c = cur_case.courses[case_i];
            //loop over all sections
            for(int sec_i = 0; sec_i < cur_c.s; sec_i++){
                //loop over all students
                section cur_sec = cur_c.sections[sec_i];
                for(int st_i = 0; st_i < cur_sec.st; st_i++){
                    //free the marks array of each student
                    free(cur_sec.students[st_i].marks);
                }
                //free the students array of each section
                free(cur_sec.students);
            }
            //free the sections array of each course
            free(cur_c.sections);
        }
        //free the courses array of each case
        free(cur_case.courses);
    }
    //now free cases array
    free(cases);
}


//-------------------MAIN--------------------------------------------------------
int main(){
    FILE * fp; 
    int numTestCases;

    fp  = fopen( "in.txt",  "r");
    fscanf(fp,"%d", &numTestCases);
    printf("\n%d", numTestCases);
    //create array of cases
    testcase* testcases = malloc(sizeof(testcase) * numTestCases);
    //call functoion for each test case
    //get the inputs
    for(int i = 0; i < numTestCases; i++){
      printf("\nin loop");
        getcasesinput(fp, testcases + i);
    }

    //print the output
    for(int i = 0; i < numTestCases; i++){
        //print test case number
        testcase c_case = testcases[i];
        printf("test case %d\n", i + 1);
        //print output for each courses
        for(int j = 0; j < testcases[i].numCourses; j++){
            course c_course = c_case.courses[j];
            printf("%s %d ", c_course.cn, c_course.passed_c);
            //print the avergae of sections
            for(int k = 0; k < c_course.s; k++){
                printf("%.2lf ", c_course.sections[k].avg_s);
            }
            //ouptut max scorer student details
            printf("%d %s %.2lf\n", c_course.max_avg_student_c->id,
                c_course.max_avg_student_c->lname, c_course.max_avg_student_c->avg );
        }
    }
    //delllocate
    deallocate(testcases, numTestCases);
    return 0;
}