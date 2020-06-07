/*
In a course, there are N number of students. Each student has to complete one assignment, 
attend M number of quizzes and a final exam.
The total score of the student is calculated as follows:
The total score = sum of scores from Mquizzes + score in the assignment + score in thefinal exam

Write a program that will perform the following operation:
•Define a student structure to store student’s lastname (one word), scoresfor one assignment, 
    M quizzes(M is an input from file), final exam, and total.
•Take number of students N and number of quizzes M as the input from the file. 
    Then Dynamically allocate memory for N students. For each student, dynamically allocate 
    memory to store scores of M quizzes.Take input for all the scores for quizzes, 
    assignments, and final exams  for all the students. Calculate the total scores for each student 
    and store it in the corresponding structure.  Do this whole task in a separate method and return 
    the appropriate pointer.

*/

//JO FOLK

#include <stdio.h>

struct Student{    
    char name[20]; 
    int score;
    int final;
    int total;
    int quizScores[];
};

struct Student getHighestTotal (int numStudents, struct Student *s){    
    int i, max_idx = 0;    
    float max = -1;    
    for (i = 0; i < numStudents; i++){        
        if (s[i].total>max){            
            max = s[i].total;            
            max_idx = i;        
        }    
    }    
    return s[max_idx];
};

int calculateQuizTotal (int arrayOfScores[], int size){
    int sum = 0; 
    for (int i = 0; i < size; i++) 
    sum += arrayOfScores[i]; 
    return sum; 
}
            
            
int main () {    
    int n, m;
    FILE * infile;    
    FILE * outfile;

    infile  = fopen(  "input.txt",   "r" );   
    outfile = fopen( "output.txt" , "w");    

    //GET N AND M
    fscanf( infile, "%d %d", &n, &m);  

    struct Student students[n];    
    char name[20];
    int score, final, total;    
    int quizScores[m];

    for (int i =0; i < n; i++){    
        //GET NAME  
        fscanf( infile, "%s", &students[i].name[0]);     
        //GET SINGLE SCORE
        fscanf( infile," %d ",  &students[i].score);
        //GET ARRAY OF SCORES FOR M QUIZZES   
        for (int qc = 0; qc < m; qc++){
             fscanf( infile," %d", &students[i].quizScores[qc]);
        };
        //GET FINAL SCORE
        fscanf( infile," %d",  &students[i].final);
        //CALCULATE TOTAL     
        students[i].total = (students[i].score + students[i].final + calculateQuizTotal(students[i].quizScores, m));   
        
    }    
        
    struct Student maxStudent = getHighestTotal(n, students);  

    fprintf(outfile,"Name: %s \nAssignment: %d \nQuizzes: %d \nFinal exam: %d \nTotal: %d\n", &maxStudent.name[0], maxStudent.score, &maxStudent.quizScores[0], maxStudent.final, maxStudent.total);
     
    fclose(infile); 
    fclose(outfile);   
    printf("\nnew.txt file has been written. Please check the data in output.txt file\n"); 
    
     
    return 0;
}