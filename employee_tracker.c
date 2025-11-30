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
// Function to find employee by ID
int findEmployee(Employee *employees, int count, int emp_id) {
    for (int i = 0; i < count; i++) {
        if (employees[i].emp_id == emp_id) {
            return i;
        }
    }
    return -1;
}
// Function to initialize employee
void initializeEmployee(Employee *emp, int emp_id, char *name, float salary) {
    emp->emp_id = emp_id;
    strcpy(emp->name, name);
    emp->days_present = 0;
    emp->leaves_taken = 0;
    emp->salary = salary;
    emp->deduction = 0.0;
}
// Function to add new employee
void addEmployee(Employee *employees, int *count) {
    if (*count >= MAX_EMPLOYEES) {
        printf("Maximum employee limit reached!\n");
        return;
    }
    
    Employee *newEmp = &employees[*count];
    int emp_id;
    char name[50];
    float salary;
    
    printf("\n--- Add New Employee ---\n");
    
    printf("Enter Employee ID: ");
    scanf("%d", &emp_id);
    
    // Check if employee ID already exists
    if (findEmployee(employees, *count, emp_id) != -1) {
        printf("Error: Employee ID %d already exists!\n", emp_id);
        return;
    }
    
    printf("Enter Employee Name: ");
    getchar(); // Clear input buffer
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0; // Remove newline
    
    printf("Enter Monthly Salary: ");
    scanf("%f", &salary);
    
    initializeEmployee(newEmp, emp_id, name, salary);
    (*count)++;
    
    printf("\nEmployee added successfully!\n");
    printf("ID: %d, Name: %s, Salary: ₹%.2f\n", emp_id, name, salary);
}
// Function to display all employees
void displayAllEmployees(Employee *employees, int count) {
    if (count == 0) {
        printf("No employees found! Please add employees first.\n");
        return;
    }
    
    printf("\n===============================================\n");
    printf("           ALL EMPLOYEES LIST\n");
    printf("===============================================\n");
    printf("%-10s %-20s %-12s %-12s\n", 
           "EMP ID", "NAME", "SALARY", "PRESENT");
    printf("--------------------------------------------------\n");
    
    for (int i = 0; i < count; i++) {
        printf("%-10d %-20s ₹%-11.2f %-12d\n", 
               employees[i].emp_id, 
               employees[i].name, 
               employees[i].salary,
               employees[i].days_present);
    }
    printf("===============================================\n");
    printf("Total Employees: %d\n", count);
}
// Function to calculate salary deductions
void calculateDeductions(Employee *employees, int count) {
    if (count == 0) {
        printf("No employees found! Please add employees first.\n");
        return;
    }
    
    printf("\n===============================================\n");
    printf("        SALARY DEDUCTIONS REPORT\n");
    printf("===============================================\n");
    
    for (int i = 0; i < count; i++) {
        if (employees[i].leaves_taken > 0) {
            float deduction = employees[i].leaves_taken * 2000.0;
            printf("Employee: %s (ID: %d)\n", employees[i].name, employees[i].emp_id);
            printf("Leaves Taken: %d\n", employees[i].leaves_taken);
            printf("Salary Deduction: ₹%.2f\n", deduction);
            printf("Net Salary: ₹%.2f\n", employees[i].salary - deduction);
            printf("--------------------------------------------------\n");
        }
    }
}
// Function to save data to file
void saveToFile(Employee *employees, int count) {
    FILE *file = fopen("employee_data.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }
    
    // Save each employee
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%s,%d,%d,%.2f,%.2f\n",
                employees[i].emp_id,
                employees[i].name,
                employees[i].days_present,
                employees[i].leaves_taken,
                employees[i].salary,
                employees[i].deduction);
    }
    
    fclose(file);
    printf("Data saved successfully to employee_data.txt (%d employees)\n", count);
}
// Function to load data from file
void loadFromFile(Employee *employees, int *count) {
    FILE *file = fopen("employee_data.txt", "r");
    if (file == NULL) {
        printf("No previous data found.\n");
        return;
    }
    
    *count = 0;
    while (fscanf(file, "%d,%49[^,],%d,%d,%f,%f",
                  &employees[*count].emp_id,
                  employees[*count].name,
                  &employees[*count].days_present,
                  &employees[*count].leaves_taken,
                  &employees[*count].salary,
                  &employees[*count].deduction) == 6) {
        (*count)++;
        if (*count >= MAX_EMPLOYEES) break;
    }
    
    fclose(file);
    printf("Data loaded successfully from employee_data.txt (%d employees)\n", *count);
}
// Function to generate reports
void generateReports(Employee *employees, int count) {
    if (count == 0) {
        printf("No employees found! Please add employees first.\n");
        return;
    }
    
    printf("\n===============================================\n");
    printf("           EMPLOYEE REPORTS\n");
    printf("===============================================\n");
    printf("1. Attendance Summary\n");
    printf("2. Salary Report\n");
    printf("3. High Leave Takers\n");
    printf("Enter your choice: ");
    
    int reportChoice;
    scanf("%d", &reportChoice);
    
    switch(reportChoice) {
        case 1:
            printf("\n--- ATTENDANCE SUMMARY ---\n");
            for (int i = 0; i < count; i++) {
                float attendance = (employees[i].days_present * 100.0) / WORKING_DAYS;
                printf("%s: %d/%d days (%.1f%%)\n", 
                       employees[i].name, 
                       employees[i].days_present, 
                       WORKING_DAYS, 
                       attendance);
            }
            break;
            
        case 2:
            printf("\n--- SALARY REPORT ---\n");
            for (int i = 0; i < count; i++) {
                float deduction = employees[i].leaves_taken * 2000.0;
                printf("%s: Basic ₹%.2f - Deduction ₹%.2f = Net ₹%.2f\n",
                       employees[i].name,
                       employees[i].salary,
                       deduction,
                       employees[i].salary - deduction);
            }
            break;
            
        case 3:
            printf("\n--- HIGH LEAVE TAKERS ---\n");
            for (int i = 0; i < count; i++) {
                if (employees[i].leaves_taken > 5) {
                    printf("%s: %d leaves taken\n", 
                           employees[i].name, 
                           employees[i].leaves_taken);
                }
            }
            break;
            
        default:
            printf("Invalid report choice!\n");
    }
}
// Main function
int main() {
    Employee employees[MAX_EMPLOYEES];
    int count = 0;
    int choice;
    
    printf("===============================================\n");
    printf("   EMPLOYEE LEAVE AND ATTENDANCE TRACKER\n");
    printf("===============================================\n");

    loadFromFile(employees, &count);
    
    do {
        displayMenu();
        printf("\nEnter your choice (1-8): ");
        scanf("%d", &choice);
        
        switch(choice) {
           switch(choice) {
           case 1:
                addEmployee(employees, &count);
                break;
            case 2:
                printf("\n--> Mark Attendance selected\n");
                break; 
            case 3:
                calculateDeductions(employees, count);
                break;
            case 4:
                printf("\n--> Generate Reports selected\n");
                break;
            case 5:
                printf("\n--> Display Employees selected\n");
                break;
            case 6:
                saveToFile(employees, count);
                break;
            case 7:
                loadFromFile(employees, &count);
                break;
                printf("\n--> Exiting program. Goodbye!\n");
                break;
            default:
                printf("\n--> Invalid choice! Please try again.\n");
        }
    } while (choice != 8);
    
    return 0;
}
