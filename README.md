# Basic College Management System

A simple console-based application for managing student, teacher, and staff records, developed in C. This project is intended for educational purposes to demonstrate file I/O, data structures, and basic CRUD operations in C.

## Author

- **Swarnadeep Paul** - [github.com/codewithchill](https://github.com/codewithchill)

## Features

- **Manage Records**: Separate management portals for Students, Teachers, and Staff.
- **CRUD Operations**:
  - **Create**: Add new records for students, teachers, and staff.
  - **Read**: View all records or search for a single record by ID.
  - **Update**: Modify existing records.
  - **Delete**: Remove records from the system.
- **Data Persistence**: All data is stored and retrieved from `.csv` files (`student.csv`, `teacher.csv`, `staff.csv`).
- **Cross-Platform**: Uses `system("cls")` or `system("clear")` for screen clearing based on the operating system.

## How to Compile and Run

1. **Clone the repository or download the source code.**

    ```ssh
    git clone https://github.com/coderswarna/Basic-College-Management.git
    ```

2. **Navigate to the `Basic-College-Management` directory.**

    ```sh
    cd Basic-College-Management
    ```

3. **Compile the source files using a C compiler (like GCC):**

    ```sh
    gcc main.c functions.c -o main
    ```

4. **Run the executable:**
    - On Windows:

      ```sh
      .\main.exe
      ```

    - On Linux/macOS:

      ```sh
      ./main
      ```

## File Structure

- `main.c`: The main entry point of the application. Handles the main menu and navigates to different management portals.
- `functions.c`: Contains the core logic for all CRUD operations (add, view, update, delete), input handling, and data parsing.
- `college-header.h`: The header file containing all structure definitions (`student`, `teacher`, `staff`), enums, global constants, and function prototypes.
- `student.csv`: Stores the records for all students.
- `teacher.csv`: Stores the records for all teachers.
- `staff.csv`: Stores the records for all staff members.

---
