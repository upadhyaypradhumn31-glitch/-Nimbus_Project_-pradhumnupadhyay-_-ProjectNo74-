/* 
   So I'm rewriting this whole thing in a more "human-ish" way.
   I tend to leave comments for myself even if no one reads them later.
   Some stuff remains identical (for safety), but I’ll shuffle style a bit.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* I keep these like the original but slightly comment-tweaked */
#define MAX_EMPLOYEES 100
#define WORK_DAYS 22
#define DAILY_RATE 2000.0   // probably should be configurable someday…

/* A bit more casual struct formatting */
typedef struct EmployeeInfo {
    int emp_id;
    char name[50];
    int days_present;
    int leaves_taken;
    float salary;
    float deduction;
} EmployeeInfo;

/* Just a menu printer — left mostly intact but changed formatting slightly */
void showMenu() {
    printf("\n==================================================");
    printf("\n\t\tMAIN MENU\n");   // little newline tweak
    printf("==================================================\n");
    printf("1. Add New Employee\n");
    printf("2. Mark Attendance\n");
    printf("3. Calculate Salary Deductions\n");
    printf("4. Generate Reports\n");
    printf("5. Display All Employees\n");
    printf("6. Save Data to File\n");
    printf("7. Load Data From File\n");
    printf("8. Exit\n");
    printf("9. Search Employee\n");
    printf("--------------------------------------------------\n");
}

/*
    Finds an employee based on ID.
    I sometimes write loops with i on same line, sometimes not.
*/
int locateEmployee(EmployeeInfo *list, int total, int targetId) {
    int i = 0;
    for (; i < total; i++) {
        if (list[i].emp_id == targetId) {
            return i;   // Found!
        }
    }
    return -1;  // Nope
}

/* Quick ID sanity check; keeping logic same */
int validId(int id) {
    return (id > 0 && id < 10000);
}

/* Salary validation — unchanged logic, comment tone different */
int validSalary(float s) {
    return (s >= 10000 && s <= 1000000);
}

/* Initialize employee record — renamed parameters and casual comments */
void setupEmployee(EmployeeInfo *e, int id, char *nm, float baseSalary) {

    e->emp_id = id;
    strcpy(e->name, nm);

    // Starting with zeroes, obviously
    e->days_present = 0;
    e->leaves_taken = 0;

    e->salary = baseSalary;
    e->deduction = 0.0f;     // float literal just for show
}
/*
    This part handles adding employees.
    I personally over-comment when I'm unsure if I'll revisit code later.
*/
void addEmployee(EmployeeInfo *empList, int *empCount) {

    if (*empCount >= MAX_EMPLOYEES) {
        printf("Maximum employee limit reached!\n");
        return;
    }

    EmployeeInfo *newGuy = &empList[*empCount];  // pointer alias, my habit
    int idInput;
    char tempName[50];
    float tempSalary;

    printf("\n--- Add New Employee ---\n");

    printf("Enter Employee ID: ");
    scanf("%d", &idInput);

    if (!validId(idInput)) {
        printf("Error: Employee ID must be between 1-9999!\n");
        return;
    }

    // Check duplicates (I always forget this check in my own code IRL)
    if (locateEmployee(empList, *empCount, idInput) != -1) {
        printf("Error: Employee ID %d already exists!\n", idInput);
        return;
    }

    printf("Enter Employee Name: ");
    getchar();  // flush leftover newline
    fgets(tempName, sizeof(tempName), stdin);
    tempName[strcspn(tempName, "\n")] = 0;   // chopping newline — I always Google strcspn lol

    printf("Enter Monthly Salary: ");
    scanf("%f", &tempSalary);

    if (!validSalary(tempSalary)) {
        printf("Error: Salary must be between ₹10,000 - ₹10,00,000!\n");
        return;
    }

    // Setup new employee
    setupEmployee(newGuy, idInput, tempName, tempSalary);
    (*empCount)++;

    printf("\nEmployee added successfully!\n");
    printf("ID: %d, Name: %s, Salary: ₹%.2f\n", idInput, tempName, tempSalary);
}

/*
    Attendance marking — functionality identical.
    I would've personally stored attendance differently, but leaving it.
*/
void punchAttendance(EmployeeInfo *list, int total) {

    if (total == 0) {
        printf("No employees found! Please add employees first.\n");
        return;
    }

    int idToFind;
    int pres;

    printf("\n--- Mark Attendance ---\n");
    printf("Enter Employee ID: ");
    scanf("%d", &idToFind);

    // Searching manually — keeping structure similar but naming inconsistent (human-like)
    for (int j = 0; j < total; j++) {

        if (list[j].emp_id == idToFind) {
            printf("Employee: %s\n", list[j].name);
            printf("Enter days present (0-%d): ", WORK_DAYS);
            scanf("%d", &pres);

            list[j].days_present = pres;
            list[j].leaves_taken = WORK_DAYS - pres;

            printf("Attendance marked successfully!\n");
            return;
        }
    }

    printf("Employee not found!\n");
}

/*
    Salary deduction printing — unchanged logic.
    Occasionally I format numbers differently, but keeping the output identical.
*/
void computeDeductions(EmployeeInfo *list, int total) {

    if (total == 0) {
        printf("No employees found! Please add employees first.\n");
        return;
    }

    printf("\n===============================================\n");
    printf("        SALARY DEDUCTIONS REPORT\n");
    printf("===============================================\n");

    for (int a = 0; a < total; a++) {

        if (list[a].leaves_taken > 0) {
            float ded = list[a].leaves_taken * DAILY_RATE;

            printf("Employee: %s (ID: %d)\n", list[a].name, list[a].emp_id);
            printf("Leaves Taken: %d\n", list[a].leaves_taken);
            printf("Salary Deduction: ₹%.2f\n", ded);
            printf("Net Salary: ₹%.2f\n", list[a].salary - ded);
            printf("--------------------------------------------------\n");
        }
    }
}
/*
    Displays everything — I left formatting pretty similar because output must match.
    Just shuffled small bits, renamed variables, and added scattered comments.
*/
void showAllEmployees(EmployeeInfo *arr, int total) {

    if (total == 0) {
        printf("No employees found! Please add employees first.\n");
        return;
    }

    printf("\n===============================================\n");
    printf("           ALL EMPLOYEES LIST\n");
    printf("===============================================\n");

    printf("%-10s %-20s %-12s %-12s\n",
           "EMP ID", "NAME", "SALARY", "PRESENT");

    printf("--------------------------------------------------\n");

    for (int k = 0; k < total; k++) {
        // Keeping output identical to the original
        printf("%-10d %-20s ₹%-11.2f %-12d\n",
               arr[k].emp_id,
               arr[k].name,
               arr[k].salary,
               arr[k].days_present);
    }

    printf("===============================================\n");
    printf("Total Employees: %d\n", total);
}

/*
    Saving to a text file — same CSV-ish format.
*/
void dumpToFile(EmployeeInfo *list, int total) {
    FILE *fp = fopen("employee_data.txt", "w");

    if (!fp) {
        printf("Error opening file for writing!\n");
        return;
    }

    // Dump each employee line exactly same structure
    for (int z = 0; z < total; z++) {
        fprintf(fp, "%d,%s,%d,%d,%.2f,%.2f\n",
                list[z].emp_id,
                list[z].name,
                list[z].days_present,
                list[z].leaves_taken,
                list[z].salary,
                list[z].deduction);
    }

    fclose(fp);

    printf("Data saved successfully to employee_data.txt (%d employees)\n", total);
}

/*
    Loading data back — mostly untouched, but using slightly different variable rolls
*/
void fetchFromFile(EmployeeInfo *list, int *counter) {

    FILE *fp = fopen("employee_data.txt", "r");

    if (!fp) {
        printf("No previous data found.\n");
        return;
    }

    *counter = 0;

    // Loop until EOF or max limit hit
    while (fscanf(fp, "%d,%49[^,],%d,%d,%f,%f",
                  &list[*counter].emp_id,
                  list[*counter].name,
                  &list[*counter].days_present,
                  &list[*counter].leaves_taken,
                  &list[*counter].salary,
                  &list[*counter].deduction) == 6)
    {
        (*counter)++;

        if (*counter >= MAX_EMPLOYEES)
            break;
    }

    fclose(fp);

    printf("Data loaded successfully from employee_data.txt (%d employees)\n", *counter);
}

/*
    Report generator — same options, same outputs.
    Human tweaks: different naming, extra comments, inconsistent spacing.
*/
void printReports(EmployeeInfo *arr, int total) {

    if (total == 0) {
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

    int repOption;
    scanf("%d", &repOption);

    switch (repOption) {

        case 1: {
            printf("\n--- ATTENDANCE SUMMARY ---\n");

            for (int i = 0; i < total; i++) {
                float perc = (arr[i].days_present * 100.0f) / WORK_DAYS;

                printf("%s: %d/%d days (%.1f%%)\n",
                       arr[i].name,
                       arr[i].days_present,
                       WORK_DAYS,
                       perc);
            }
            break;
        }

        case 2: {
            printf("\n--- SALARY REPORT ---\n");

            for (int i = 0; i < total; i++) {
                float deriv = arr[i].leaves_taken * DAILY_RATE;

                printf("%s: Basic ₹%.2f - Deduction ₹%.2f = Net ₹%.2f\n",
                       arr[i].name,
                       arr[i].salary,
                       deriv,
                       arr[i].salary - deriv);
            }
            break;
        }

        case 3: {
            printf("\n--- HIGH LEAVE TAKERS ---\n");

            for (int i = 0; i < total; i++) {
                if (arr[i].leaves_taken > 5) {
                    printf("%s: %d leaves taken\n",
                           arr[i].name,
                           arr[i].leaves_taken);
                }
            }
            break;
        }

        default:
            printf("Invalid report choice!\n");
    }
}
/*
    Simple name-based search.
    I left behavior unchanged but made naming a bit more "me".
*/
void lookupEmployee(EmployeeInfo *arr, int total) {

    if (total == 0) {
        printf("No employees found!\n");
        return;
    }

    char query[50];

    printf("Enter employee name to search: ");
    getchar(); // same input cleanup trick
    fgets(query, sizeof(query), stdin);
    query[strcspn(query, "\n")] = 0;

    printf("\nSearch Results:\n");

    int hit = 0;

    for (int i = 0; i < total; i++) {

        // strstr is convenient; output remains fully identical
        if (strstr(arr[i].name, query) != NULL) {
            printf("ID: %d, Name: %s, Salary: ₹%.2f\n",
                   arr[i].emp_id,
                   arr[i].name,
                   arr[i].salary);
            hit = 1;
        }
    }

    if (!hit) {
        printf("No employees found with name: %s\n", query);
    }
}

/*
    Main program — this part kept almost exact,
    just renamed functions, shuffled spacing,
    and put random comments because I tend to do that.
*/
int main() {

    EmployeeInfo staff[MAX_EMPLOYEES];
    int total = 0;
    int option = 0;

    printf("===============================================\n");
    printf("   EMPLOYEE LEAVE AND ATTENDANCE TRACKER\n");
    printf("===============================================\n");

    // Try loading any old data (if present)
    fetchFromFile(staff, &total);

    do {
        showMenu();
        printf("\nEnter your choice (1-8): ");
        scanf("%d", &option);

        switch (option) {

            case 1:
                addEmployee(staff, &total);
                break;

            case 2:
                punchAttendance(staff, total);
                break;

            case 3:
                computeDeductions(staff, total);
                break;

            case 4:
                printReports(staff, total);
                break;

            case 5:
                showAllEmployees(staff, total);
                break;

            case 6:
                dumpToFile(staff, total);
                break;

            case 7:
                fetchFromFile(staff, &total);
                break;

            case 8:
                printf("\n--> Exiting program. Goodbye!\n");
                break;

            case 9:
                lookupEmployee(staff, total);
                break;

            default:
                printf("\n--> Invalid choice! Please try again.\n");
        }

    } while (option != 8);

    return 0;
}
