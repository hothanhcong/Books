// libraries that included in this project :
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// constant that will be the initial size of the student array
#define INITIAL_SIZE 10
#define MAXNAMELENGTH 100

// struct definition for a student
typedef struct {
    int id;
    double avg;
    char fullName[MAXNAMELENGTH];
} Student;

// project prototype function:
void displayMainMenu();
void addStudent(Student **students, int *size, int *capacity);
void removeStudent(Student *students, int *size);
void searchForStudent(Student *students, int size);
void uploadDataFile(Student **students, int *size, int *capacity);
void updateDataFile(Student *students, int size);
void printStudents(Student *students, int size);

// global variables:
Student *students = NULL;
int n = 0;
int capacity = INITIAL_SIZE;

int main() { 
    students = (Student*) malloc(INITIAL_SIZE * sizeof(Student));
    if (students == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    printf("\nWelcome to my Student Management System:\n\n");
    uploadDataFile(&students, &n, &capacity);
    return 0;
}

void displayMainMenu() {
    int choice; 

    printf("\nPlease Select an operation (1-5):\n");
    printf("1- Add a Student:\n");
    printf("2- Remove a Student:\n");
    printf("3- Search for a Student:\n");
    printf("4- Print Student List:\n");
    printf("5- Save Info to File And Exit:\n");
    printf("\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1: addStudent(&students, &n, &capacity); break;
        case 2: removeStudent(students, &n); break;
        case 3: searchForStudent(students, n); break;
        case 4: printStudents(students, n); break;
        case 5: updateDataFile(students, n); break;
        default: 
            printf("No such operation! Please try again.\n\n");
            displayMainMenu();
            break;
    }
}

// addStudent: used to add a new id number, full name, and average:
void addStudent(Student **students, int *size, int *capacity) {
    if (*size >= *capacity) {
        *capacity *= 2;
        *students = realloc(*students, *capacity * sizeof(Student));
        if (*students == NULL) {
            printf("Memory reallocation failed\n");
            return;
        }
    }

    Student newStudent;
    int isSimilar = 0;

    printf("Please enter id number for Student: \n");
    scanf("%d", &newStudent.id);

    for(int i = 0; i < *size; i++) {
        if ((*students)[i].id == newStudent.id) {
            printf("The id that you are trying to add is similar to another id (please try again!)\n\n");
            isSimilar = 1;
            break;
        }
    }

    if (isSimilar == 0) {
        printf("Please enter full name for Student: \n");
        scanf(" %[^\n]", newStudent.fullName);
        printf("Please enter average of Student: \n");
        scanf("%lf", &newStudent.avg);

        (*students)[*size] = newStudent;
        (*size)++;

        printf("Student with id: %d has been added. \n\n", newStudent.id);

        // Ascending sort by Bubble sort
        for(int i = 0; i < *size - 1; i++) {
            for(int j = 0; j < *size - 1 - i; j++) {
                if ((*students)[j].id > (*students)[j + 1].id) {
                    Student temp = (*students)[j];
                    (*students)[j] = (*students)[j + 1];
                    (*students)[j + 1] = temp;
                }
            }
        }
    }
    displayMainMenu();
}

void removeStudent(Student *students, int *size) {
    if(*size > 0) {
        int idNum;
        int isSimilar = 0;

        printf("Please enter id number for Student to remove: \n");
        scanf("%d", &idNum);

        for(int i = 0; i < *size; i++) {
            if (students[i].id == idNum) {
                isSimilar = 1;
                for(int j = i; j < *size - 1; j++) {
                    students[j] = students[j + 1];
                }
                (*size)--;
                printf("Student with id: %d has been removed. \n\n", idNum);
                break;
            }
        }

        if(isSimilar == 0) {
            printf("Student with id %d does not exist.\n\n", idNum);
        }
    } else {
        printf("\nThere are no students to remove \n");
    }
    displayMainMenu();
}

void searchForStudent(Student *students, int size) { 
    if(size > 0) {
        int idNum;
        int isSimilar = 0;

        printf("Please enter id number for Student to search for: \n");
        scanf("%d", &idNum);

        for(int i = 0; i < size; i++) {
            if (students[i].id == idNum) {
                isSimilar = 1;
                printf("id# = %d \t\t avg = %.2f \t\t name = %s\n\n", students[i].id, students[i].avg, students[i].fullName);
                break;
            }
        }

        if(isSimilar == 0) {
            printf("Student with id %d does not exist (you can add one).\n\n", idNum);
        }
    } else {
        printf("\nThere are no students to search for \n");
    }
    displayMainMenu();
}

void uploadDataFile(Student **students, int *size, int *capacity) {
    printf("Uploading data file ... \n");

    FILE *input; 
    input = fopen("students.txt", "r");
    if (input == NULL) {
        printf("Could not open file\n");
        return;
    }

    int idInput;
    double avgInput;
    char nameInput[MAXNAMELENGTH];
    int lines = 0;

    while(fscanf(input, "%d %lf %[^\n]", &idInput, &avgInput, nameInput) != EOF) {
        if (lines >= *capacity) {
            *capacity *= 2;
            *students = realloc(*students, *capacity * sizeof(Student));
            if (*students == NULL) {
                printf("Memory reallocation failed\n");
                fclose(input);
                return;
            }
        }
        (*students)[lines].id = idInput;
        (*students)[lines].avg = avgInput;
        strcpy((*students)[lines].fullName, nameInput);
        lines++;
    }

    *size = lines;
    fclose(input);
    printf("Data File uploaded \n\n");
    displayMainMenu();
}

void updateDataFile(Student *students, int size) {
    printf("\nUpdating data file ... \n");

    FILE *output;
    output = fopen("students.txt", "w");
    if (output == NULL) {
        printf("Could not open file\n");
        return;
    }

    for(int i = 0; i < size; i++) {
        fprintf(output, "%d %.2lf %s\n", students[i].id, students[i].avg, students[i].fullName);
    }
    fclose(output);

    printf("Data File updated. \n\n");
    printf("Thank you for using My Student Management System. Goodbye :)\n\n");

    // Free the allocated memory
    free(students);
}

void printStudents(Student *students, int size) {
    for(int i = 0; i < size; i++) {   
        printf("id# = %d \t\t avg = %.2f \t\t name = %s\n", students[i].id, students[i].avg, students[i].fullName);
    }
    printf("\n");
    displayMainMenu();
}
