Employee Management System
Description
This program is a simple employee management system that allows users to interact with an employee database. Users can perform various operations such as printing the database, looking up employees by ID or last name, adding new employees, removing employees, updating employee information, and printing top salaries or employees with the same last name.

Compilation
To compile the program, ensure you have a C compiler (such as GCC) installed on your system. Run the following command in your terminal:

gcc -o workerDB empdata.c readfile.c

This command will compile the program and create an executable file named `workerDB`.

Usage
To run the program, execute the following command in your terminal, replacing <filename> with the name of the input file containing the employee data:

./workerDB <input_file>

Once the program is running, follow the prompts to interact with the employee database.

Functions
The program includes the following functions:

print_sorted_database(): Prints the sorted employee database (sorted by ID).
lookup_employee_by_id(): Performs a linear search by employee ID.
find_employees_by_last_name_case_insensitive(): Finds employees with the same last name (case-insensitive).
lookup_employee_by_last_name(): Performs a linear search by employee last name and prints all matching employees.
add_employee(): Adds an employee to the database.
remove_employee(): Removes an employee from the database (by ID).
update_employee(): Updates an employee's information.
print_top_salaries(): Prints the 'M' highest salaries.

Input File Format
The input file should contain the employee data in the following format:
ID1 FirstName1 LastName1 Salary1


Each employee (ID, first name, last name, and salary) should be on a separate line. The program will read the data from the file and store it in the employees array.

