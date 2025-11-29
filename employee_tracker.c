#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES 100

// Employee structure
typedef struct {
    int emp_id;
    char name[50];
    int days_present;
    int leaves_taken;
    float salary;
    float deduction;
} Employee;

// Main function
int main() {
    Employee employees[MAX_EMPLOYEES];
    int count = 0;
    
    printf("=== EMPLOYEE LEAVE TRACKER ===\n");
    printf("System Ready!\n");
    printf("Total employees can be stored: %d\n", MAX_EMPLOYEES);
    
    return 0;
}
