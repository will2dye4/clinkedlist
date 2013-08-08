/* William Dye
 * 902606082
 * test.c
 */

#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Here we are going to write some functions to support a linked list that stores Students (first name, last name, grade, gtid)  */
/* Here is the data the user in this case us will be storing into our linked list */
/* YOU ARE REQUIRED TO COMPLETE THIS PART */
typedef struct Student
{
	char* first_name; /* This will be malloc'd!*/
	char* last_name; /* This will also be malloc'd */
	int grade;
	long gtid;
} Student;

Student* create_student(const char* first_name, const char* last_name, int grade, long gtid)
{
    Student *newstudent = NULL;
    if ((newstudent = malloc(sizeof(Student))) != NULL) {
        char *first, *last;
        if ((first = malloc(strlen(first_name) + 1)) != NULL) {
            strncpy(first, first_name, strlen(first_name) + 1);
            newstudent->first_name = first;
        }
        if ((last = malloc(strlen(last_name) + 1)) != NULL) {
            strncpy(last, last_name, strlen(last_name) + 1);
            newstudent->last_name = last;
        }
        newstudent->grade = grade;
        newstudent->gtid = gtid;
    } 
	return newstudent;
}

/* For these functions below you should never be passed in NULL */
/* You will always get valid data here */
void print_student(void* data)
{
    Student *student = (Student *)data;
    printf("Student: %s %s\n", student->first_name, student->last_name);
    printf("Grade: %d\n", student->grade);
    printf("GtID: %ld\n", student->gtid);
}

void free_student(void* data)
{
    Student *student = (Student *)data;
    free(student->first_name);
    free(student->last_name);
    free(student);
}

int student_eq(const void* a, const void* b)
{
    Student *x = (Student *)a;
    Student *y = (Student *)b;
    int first_min = (strlen(x->first_name) > strlen(y->first_name) ? strlen(y->first_name) : strlen(x->first_name));
    int last_min = (strlen(x->last_name) > strlen(y->last_name) ? strlen(y->last_name) : strlen(x->last_name));
    if (strncmp(x->first_name, y->first_name, first_min) == 0 &&
            strncmp(x->last_name, y->last_name, last_min) == 0 &&
            x->grade == y->grade && x->gtid == y->gtid) {
        return 1;
    }
	return 0;
}

int student_pred(const void *data)
{
    Student *student = (Student *)data;
    return (strncmp(student->first_name, "William", 7) == 0 ? 1 : 0);
}

/* This main function does a little testing
   Like all good CS Majors you are required to test
   your code here. There is no substitute for testing
   and you should be sure to test for all edge cases
   e.g., calling remove_front on an empty list.
*/
int main(void) 
{
	/* Now to make use of all of this stuff */
	list* llist = create_list();
  
  	/* What does an empty list contain?  Let's use our handy traversal function */
  	printf("TEST CASE 1\nAn empty list should print nothing here:\n");
  	traverse(llist, print_student);
	printf("\n");

 	/* Let's add a student and then print */
 	push_front(llist, create_student("David", "Davenport", 130, 123456789));
 	printf("TEST CASE 2\nA list with one student should print that student:\n");
 	traverse(llist, print_student);
 	printf("\n");
 	
 	/* Let's remove that student and then print */
 	remove_front(llist, free_student);
 	printf("TEST CASE 3\nAnother empty list should print nothing here:\n");
 	traverse(llist, print_student);
 	printf("\n");

 	/* Let's add two elements and then print */
 	push_front(llist, create_student("David", "Davenport", 130, 123456789));
 	push_front(llist, create_student("Matt", "Emmel", 65, 902313373));
 	printf("TEST CASE 4\nA list with two students should print those two students:\n");
 	traverse(llist, print_student);
 	printf("\n"); 	

 	/* Test find occurence when the node is not found */
	// Notice the commented line below is BAD because the return value from create_point was malloc'd and you never free it!
	// find_occurence(llist, create_student("Nurse", "Joy", 3, 131313137), student_eq));
	Student* p = create_student("Nurse", "Joy", 3, 131313137);
	printf("TEST CASE 5\nFinding occurence when a node is not in the list should fail: ");
	printf("%d\n\n", find_occurrence(llist, p, student_eq));
	/* Remember to FREE everything you malloc I malloc'd space for p and now I am done with it so I free it */
	free_student(p);

  	/* Let's kill the list */
  	empty_list(llist, free_student);
 	printf("TEST CASE 6\nAfter freeing all nodes the list should be empty:\n");
 	traverse(llist, print_student);
 	printf("\n");

    /* While we have an empty list, let's test remove_front, remove_back, and remove_index for that case */
    printf("TEST CASE 7\nCalling remove_front on an empty list should fail: ");
    printf("%d\n", remove_front(llist, free_student));	
 	printf("Calling remove_back on an empty list should fail: ");
    printf("%d\n", remove_back(llist, free_student));
    printf("Calling remove_index on an empty list should fail: ");
    printf("%d\n\n", remove_index(llist, 2, free_student));

    /* Test the size of an empty list */
    printf("TEST CASE 8\nThe size of the list should currently be 0: %d\n\n", size(llist));

 	/* Test push_back */
    push_back(llist, create_student("George", "Burdell", 99, 987654321));
    push_back(llist, create_student("William", "Dye", 100, 902606082));
    push_back(llist, create_student("Brandon", "Whitehead", 100, 901420348));
    printf("TEST CASE 9\nAfter pushing three nodes onto the back of the list, the first one (George) should be the head:\n");
    traverse(llist, print_student);
    printf("\n");

    /* Test size, front, and back */
    printf("TEST CASE 10\nThe size of the list should currently be 3: %d\n", size(llist));
    printf("The front function should return the data for George:\n");
    print_student(front(llist));
    printf("The back function should return the data for Brandon:\n");
    print_student(back(llist));
    printf("\n");

    /* Let's add several more nodes and test the various remove functions ... */
    push_front(llist, create_student("George", "Boole", 100, 901910019));
    push_front(llist, create_student("Zvi", "Galil", 1000, 999888777));    
    push_front(llist, create_student("Java", "Girata", 42, 902538219));
    push_front(llist, create_student("William", "Leahy", 9001, 902902902));
    push_front(llist, create_student("Samuel", "Morse", 111, 911432685));
    push_front(llist, create_student("Buzz", "Bee", 100, 123456789));
    printf("TEST CASE 11\nCalling remove_back should remove Brandon from the list:\n");
    remove_back(llist, free_student);
    traverse(llist, print_student);
    printf("\nTEST CASE 12\nCalling remove_front should remove Buzz from the list:\n");
    remove_front(llist, free_student);
    traverse(llist, print_student);
    printf("\nTEST CASE 13\nCalling remove_index(2) should remove Java from the list:\n");
    remove_index(llist, 2, free_student);
    traverse(llist, print_student);
    printf("\n");

    /* Testing remove_data and remove_if */
    Student *s = create_student("Samuel", "Morse", 111, 911432685);
    printf("TEST CASE 14\nCalling remove_data should remove Samuel from the list:\n");
    remove_data(llist, s, student_eq, free_student);
    traverse(llist, print_student);
    printf("\nTEST CASE 15\nCalling remove_if should remove both Williams from the list:\n");
    remove_if(llist, student_pred, free_student);
    traverse(llist, print_student);
    printf("\n");
    free_student(s);

    /* Testing get_index */
    printf("TEST CASE 16\nCalling get_index(1) should return the data for George Boole:\n");
    print_student(get_index(llist, 1));
    printf("\n");

    /* Testing find_occurrence when the item is in the list */
    Student *t = create_student("George", "Burdell", 99, 987654321);
    printf("TEST CASE 17\nCalling find_occurrence should return true: ");
    printf("%d\n\n", find_occurrence(llist, t, student_eq));
    free_student(t);

    /* Testing is_empty */
    printf("TEST CASE 18\nCalling is_empty should return false: %d\n\n", is_empty(llist));
    empty_list(llist, free_student);
    printf("TEST CASE 19\nCalling is_empty should now return true: %d\n", is_empty(llist));

 	/* Testing over clean up*/
 	free(llist);
 	
  	return 0;
}
