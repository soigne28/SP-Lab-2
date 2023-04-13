#include <stdio.h>
#include <string.h>
#include "readfile.h"

// Employee structure definition
typedef struct {
    int id;
    char firstName[64];
    char lastName[64];
    int salary;
} Employee;


// Function to print the sorted employee database
void print_sorted_database(Employee* employees, int size) {
    Employee sorted_employees[size];
    memcpy(sorted_employees, employees, size * sizeof(Employee));

    // Sort employees by ID in ascending order
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (sorted_employees[j].id > sorted_employees[j + 1].id) {
                Employee temp = sorted_employees[j];
                sorted_employees[j] = sorted_employees[j + 1];
                sorted_employees[j + 1] = temp;
            }
        }
    }

    printf("ID\tFirst Name\tLast Name\tSalary\n");
    for (int i = 0; i < size; i++) {
        printf("%d\t%s\t\t%s\t\t%d\n", sorted_employees[i].id, sorted_employees[i].firstName, sorted_employees[i].lastName, sorted_employees[i].salary);
    }
}

// Function to perform a linear search by employee ID
int lookup_employee_by_id(Employee *employees, int size, int id) {
    for (int i = 0; i < size; i++) {
        if (employees[i].id == id) {
            return i;
        }
    }
    return -1;
}

// Function to find employees with the same last name (case-insensitive)
void find_employees_by_last_name_case_insensitive(Employee* employees, int size, const char* last_name) {
    for (int i = 0; i < size; i++) {
        if (strcasecmp(employees[i].lastName, last_name) == 0) {
            printf("ID: %d, First Name: %s, Last Name: %s, Salary: %d\n", employees[i].id, employees[i].firstName, employees[i].lastName, employees[i].salary);
        }
    }
}

// Function to perform a linear search by employee last name and print all matching employees
void lookup_employee_by_last_name(Employee* employees, int size, char* last_name) {
    int found = 0;
    for (int i = 0; i < size; i++) {
        if (strcmp(employees[i].lastName, last_name) == 0) {
            found = 1;
            printf("Employee found: ID: %d, First Name: %s, Last Name: %s, Salary: %d\n", employees[i].id, employees[i].firstName, employees[i].lastName, employees[i].salary);
        }
    }
    if (!found) {
        printf("No employees found with that last name.\n");
    }
}

// Function to add an employee to the database
int add_employee(Employee *employees, int *num_employees, int id, const char *first_name, const char *last_name, int salary) {
    if (id < 100000 || id > 999999 || salary < 30000 || salary > 150000) {
        return -1;
    }

    employees[*num_employees].id = id;
    strcpy(employees[*num_employees].firstName, first_name);
    strcpy(employees[*num_employees].lastName, last_name);
    employees[*num_employees].salary = salary;
    (*num_employees)++;
    return 0;
}

// Function to remove an employee from the database
int remove_employee(Employee* employees, int* num_employees, int id) {
    int index = lookup_employee_by_id(employees, *num_employees, id);
    if (index == -1) {
        return -1;
    }

    for (int i = index; i < *num_employees - 1; i++) {
        employees[i] = employees[i + 1];
    }
    (*num_employees)--;
    return 0;
}

// Function to update an employee's information
int update_employee(Employee* employees, int size, int id, const char* first_name, const char* last_name, int salary) {
    int index = lookup_employee_by_id(employees, size, id);
    if (index == -1) {
        return -1;
    }

    if (first_name) {
        strcpy(employees[index].firstName, first_name);
    }
    if (last_name) {
        strcpy(employees[index].lastName, last_name);
    }
    if (salary >= 30000 && salary <= 150000) {
        employees[index].salary = salary;
    }
    return 0;
}

// Function to print the M highest salaries
void print_top_salaries(Employee* employees, int size, int m) {
    Employee sorted_employees[size];
    memcpy(sorted_employees, employees, size * sizeof(Employee));

    // Sort employees by salary in descending order
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (sorted_employees[j].salary < sorted_employees[j + 1].salary) {
                Employee temp = sorted_employees[j];
                sorted_employees[j] = sorted_employees[j + 1];
                sorted_employees[j + 1] = temp;
            }
        }
    }

    // Print top M employees
    printf("Top %d Salaries:\n", m);
    for (int i = 0; i < m && i < size; i++) {
        printf("ID: %d, First Name: %s, Last Name: %s, Salary: %d\n", sorted_employees[i].id, sorted_employees[i].firstName, sorted_employees[i].lastName, sorted_employees[i].salary);
    }
}

int main(int argc, char* argv[]) {
    // Check if the user provided a filename as an argument
    if (argc != 2) {
        printf("Usage: ./workerDB <filename>\n");
        return 1;
    }

    // Open the input file
    int ret = open_file(argv[1]);
    if (ret == -1) {
        printf("Error opening file.\n");
        return 1;
    }

    Employee employees[1024];
    int num_employees = 0;

    // Read the file and store the data in the employees array
    while (1) {
        int id;
        ret = read_int(&id);
        if (ret == -1) break;
        employees[num_employees].id = id;

        read_string(employees[num_employees].firstName);
        read_string(employees[num_employees].lastName);

        int salary;
        ret = read_int(&salary);
        if (ret == -1) break;
        employees[num_employees].salary = salary;

        num_employees++;
    }

    // Close the file
    close_file();

    int choice;

    // Main loop for menu interaction

    while (1) {
        printf("\n1. Print the Database\n2. Lookup employee by ID\n3. Lookup employee by last name\n4. Add an Employee\n5. Quit\n6. Remove an employee (by ID)\n7. Update Employee Information\n8. Print 'M' employees with the highest salary\n9. Print employees with same last name (case insensitive)\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            print_sorted_database(employees, num_employees);
        }
        else if (choice == 2) {
            int id;
            printf("Enter employee ID: ");
            scanf("%d", &id);
            int index = lookup_employee_by_id(employees, num_employees, id);
            if (index == -1) {
                printf("Employee not found.\n");
            }
            else {
                printf("Employee found: ID: %d, First Name: %s, Last Name: %s, Salary: %.2f\n", employees[index].id, employees[index].firstName, employees[index].lastName, employees[index].salary);

            }
        }
        //Option 3
        
        else if (choice == 3) {
            char last_name[50];
            printf("Enter employee last name: ");
            scanf("%s", last_name);
            lookup_employee_by_last_name(employees, num_employees, last_name);
        }
            // Option 4
        
        else if (choice == 4) {
            int id, salary;
            char first_name[50], last_name[50];
            printf("Enter employee ID (100000-999999): ");
            scanf("%d", &id);
            printf("Enter employee first name: ");
            scanf("%s", first_name);
            printf("Enter employee last name: ");
            scanf("%s", last_name);
            printf("Enter employee salary (30000-150000): ");
            scanf("%d", &salary);
            int result = add_employee(employees, &num_employees, id, first_name, last_name, salary);
            if (result == -1) {
                printf("Invalid input. Employee not added.\n");
            }
            else {
                printf("Employee added successfully.\n");

            }
        }
        else if (choice == 5) {
            break;
        }
        else if (choice == 6) {
            int id;
            printf("Enter employee ID: ");
            scanf("%d", &id);
            printf("Do you really want to delete this employee ID? (1 for Yes, 0 for No): ");
            int confirm;
            scanf("%d", &confirm);
            if (confirm) {
                int result = remove_employee(employees, &num_employees, id);
                if (result == -1) {
                    printf("Employee not found.\n");
                }
                else {
                    printf("Employee removed successfully.\n");
                }
            }
        }
        else if (choice == 7) {
            int id, salary;
            char first_name[50], last_name[50];
            printf("Enter employee ID: ");
            scanf("%d", &id);
            printf("Enter employee first name (rewrite even if unchanged): ");
            getchar(); // Consume newline character from previous input
            fgets(first_name, sizeof(first_name), stdin);
            strtok(first_name, "\n"); // Remove newline character
            printf("Enter employee last name (rewrite even if unchanged): ");
            fgets(last_name, sizeof(last_name), stdin);
            strtok(last_name, "\n"); // Remove newline character
            printf("Enter employee salary (leave -1 to keep current): ");
            scanf("%d", &salary);

            int result = update_employee(employees, num_employees, id, (strlen(first_name) > 0 ? first_name : NULL), (strlen(last_name) > 0 ? last_name : NULL), salary);
            if (result == -1) {
                printf("Employee not found.\n");
            }
            else {
                printf("Employee updated successfully.\n");
            }

        }
        else if (choice == 8) {
            int m;
            printf("Enter the number of top salaries to display: ");
            scanf("%d", &m);
            print_top_salaries(employees, num_employees, m);
        }
        //Option 9
        else if (choice == 9) {
            char last_name[64];
            printf("Enter employee last name: ");
            scanf("%s", last_name);
            find_employees_by_last_name_case_insensitive(employees, num_employees, last_name);
        }
    
        else {
            printf("Invalid choice.\n");
        }
    }
}