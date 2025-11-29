#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES 100
#define WORKING_DAYS 22

// Employee structure
typedef struct {
    int emp_id;
    char name[50];
    int days_present;
    int leaves_taken;
    float salary;
    float deduction;
} Employee;

// Function to display menu
void displayMenu() {
    printf("\n==================================================");
    printf("\n\t\tMAIN MENU");
    printf("\n==================================================");
    printf("\n1. Add New Employee");
    printf("\n2. Mark Attendance");
    printf("\n3. Calculate Salary Deductions");
    printf("\n4. Generate Reports");
    printf("\n5. Display All Employees");
    printf("\n6. Save Data to File");
    printf("\n7. Load Data from File");
    printf("\n8. Exit");
    printf("\n--------------------------------------------------");
}

// Main function
int main() {
    Employee employees[MAX_EMPLOYEES];
    int count = 0;
    int choice;
    
    printf("===============================================\n");
    printf("   EMPLOYEE LEAVE AND ATTENDANCE TRACKER\n");
    printf("===============================================\n");
    
    do {
        displayMenu();
        printf("\nEnter your choice (1-8): ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printf("\n--> Add Employee selected\n");
                break;
            case 2:
                printf("\n--> Mark Attendance selected\n");
                break;
            case 3:
                printf("\n--> Calculate Deductions selected\n");
                break;
            case 4:
                printf("\n--> Generate Reports selected\n");
                break;
            case 5:
                printf("\n--> Display Employees selected\n");
                break;
            case 6:
                printf("\n--> Save Data selected\n");
                break;
            case 7:
                printf("\n--> Load Data selected\n");
                break;
            case 8:
                printf("\n--> Exiting program. Goodbye!\n");
                break;
            default:
                printf("\n--> Invalid choice! Please try again.\n");
        }
    } while (choice != 8);
    
    return 0;
}
