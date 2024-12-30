#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    int age;
    float gpa;
} student;

typedef struct {
    student data;
    struct node *next;
} node;

node *head = NULL;


void printSeparator(void){
    printf("------------------------------------------------------------\n");
}

// helper function to find ID
int findID(int id) {
    node *current = NULL;

    if (head == NULL) {
        return 0;
    }

    current = head;
    while (current != NULL) {
        if (current->data.id == id) {
            return 1;
        }
        current = (node*)current->next;
    }
    return 0;
}

// helper function to calculate list size
int listSize(void) {
    int count = 0;
    node *current = NULL;
    if (head == NULL) {
        return 0;
    }
    current = head;
    while (current != NULL) {
        current = (node*)current->next;
        count++;
    }
    return count;
}

void addStudent(const student *const ptr) {

    // checking if the ID is already exist or not
    if (findID(ptr->id)) {
        printf("This ID is already exists!\n");
        return;
    }

    // create new memory allocation and check if it successfully created or not
    node *link = (node *)malloc(sizeof(node));
    if (link == NULL) {
        printf("Memory Allocation Failed");
        return;
    }

    link->data = *ptr;

    link->next = NULL;

    if (head == NULL) {
        head = link;
        return;
    }

    node *current = NULL;
    current = head;
    while (current->next != NULL) {
        current = (node*)current->next;
    }
    current->next = (struct node*)link;
}

void displayStudents(void) {

    node *current = NULL;

    if (head == NULL) {
        printf("There are no students.\n");
        return;
    }

    printf("Students:\n");
    current = head;
    while (current != NULL) {
        printf("        [ ID: %d, Name: %s, Age: %d, GPA: %.1f ]\n", current->data.id, current->data.name, current->data.age, current->data.gpa);

        current = (node*)current->next;
    }
}

void searchStudentByID(int id) {
    node *current = NULL;
    if (head == NULL) {
        printf("There are no students.\n");
        return;
    }
    current = head;
    while (current != NULL) {
        if (current->data.id == id) {
            printf("Student with ID %d:\n" , id);
            printf("        [ ID: %d, Name: %s, Age: %d, GPA: %.1f ]\n",
                   current->data.id, current->data.name, current->data.age, current->data.gpa);
            return;
        }
        current = (node*)current->next;
    }
    printf("There is no student with ID %d\n" , id);
}

void updateStudent(int id) {
    char newName[50];
    int newAge;
    float newGPA;
    if (head == NULL) {
        printf("There are no students\n");
        return;
    }
    node *current = NULL;
    current = head;
    while (current != NULL) {
        if (current->data.id == id) {
            printf("Enter new name: ");
            scanf("%s" , newName);

            printf("Enter new age: ");
            scanf("%d", &newAge);

            printf("Enter new GPA: ");
            scanf("%f", &newGPA);

            current->data.gpa = newGPA;
            current->data.age = newAge;
            strcpy(current->data.name, newName);
            printf("Student information updated successfully!\n");
            return;
        }
        current = (node*)current->next;
    }
    printf("There is no student with ID %d\n",id);
}

float calculateAverageGPA(void) {

    if (listSize() == 0) {
        return 0;
    }
    float totalGPA = 0;

    node *current = NULL;
    current = head;
    while (current != NULL) {
        totalGPA += current->data.gpa;
        current = (node*)current->next;
    }

    return (totalGPA / (float)listSize());
}

void searchHighestGPA(void) {
    if (listSize() == 0) {
        printf("There are no students\n");
        return;
    }
    float maxGPA = 0;
    node *current = head;
    while (current != NULL) {
        if (current->data.gpa > maxGPA) {
            maxGPA = current->data.gpa;
        }
        current = (node*)current->next;
    }
    // Print all students with maxGPA
    current = head;
    while (current != NULL) {
        if (current->data.gpa == maxGPA) {
            printf("Student with the highest GPA:\n");
            printf("        [ ID: %d, Name: %s, Age: %d, GPA: %.1f ]\n", current->data.id, current->data.name, current->data.age, current->data.gpa);
        }
        current = (node*)current->next;
    }
}

void deleteStudent(int id){

    if(head == NULL){
        printf("There are no students to delete.\n");
        return;
    }
    if (findID(id) == 0) {
        printf("There is no student with ID %d to delete.\n",id);
        return;
    }
    node *prev = NULL;
    node *current = NULL;
    node *deletedNode = NULL;

    if (listSize() == 1) {
        deletedNode = head;
        head = (node*)head->next;
        free(deletedNode);
        printf("Student with ID %d has been deleted\n" , id);
        return;
    }

    current = (node*)head->next;
    prev = head;

    //if the deleted node is the first one
    if(prev->data.id == id){
        deletedNode = prev;
        head = (node*)prev->next;
        free(deletedNode);
        printf("Student with ID %d has been deleted\n" , id);
        return;
    }
    while (current != NULL) {
        if (current->data.id == id) {
            deletedNode = current;
            prev->next = current->next;
            free(deletedNode);
            printf("Student with ID %d has been deleted\n" , id);
            return;
        }
        prev = current;
        current = (node*)current->next;
    }
}

void menu() {

    printSeparator();
    printf("1. Add Student\n");
    printf("2. Display Students\n");
    printf("3. Search Student By ID\n");
    printf("4. Update Student Information\n");
    printf("5. Delete Student\n");
    printf("6. Calculate Average GPA\n");
    printf("7. Search for Student with Highest GPA\n");
    printf("8. Exit\n");
    printSeparator();

}

int main(void) {
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    int choice;
    int id;
    student x;

    do {
        menu();

        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Student ID: ");
                scanf("%d", &x.id);

                printf("Enter Student Name: ");
                scanf("%s",x.name);

                printf("Enter Student Age: ");
                scanf("%d", &x.age);

                printf("Enter Student GPA: ");
                scanf("%f", &x.gpa);

                addStudent(&x);
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                printf("Enter ID: ");
                scanf("%d", &id);
                searchStudentByID(id);
                break;

            case 4:
                printf("Enter ID: ");
                scanf("%d", &id);
                updateStudent(id);
                break;

            case 5:
                printf("Enter ID: ");
                scanf("%d", &id);
                deleteStudent(id);
                break;

            case 6:
                printf("AVG GPA: %.2f\n", calculateAverageGPA());
                break;

            case 7:
                searchHighestGPA();
                break;

            case 8:
                printf("Exiting...\n");
                break;

            default:
                printf("Wrong choice!\n");
                break;
        }
    } while (choice != 8);

    return 0;
}
