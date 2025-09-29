#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef _WIN32
#include <windows.h>
#endif

extern const int MAX_RECORD;
extern const int FILE_INPUT_BUFFER;
extern const char *staffRole_names[];
extern const char *department_names[];
extern const char *subject_names[];

typedef enum
{
	CSE = 1,
	ECE = 2,
	BCA = 3,
	BCS = 4,
	IT = 5,
	ME = 6,
	CE = 7,
	AE = 8
} department;
#define totalDepartment 8

typedef enum
{
	MATH = 1,
	PHYSICS = 2,
	COMPUTER_SCIENCE = 3,
	DISCRETE_MATH = 4,
	DATA_STRUCTURES = 5,
	ALGORITHMS = 6
} subject;
#define totalSubject 6

typedef enum
{
	ADMIN = 1,
	LIBRARIAN = 2,
	LAB_ASSISTANT = 3,
	JANITOR = 4,
	SECURITY = 5,
	IT_SUPPORT = 6,
} staffRole;
#define totalStaffRole 6

typedef struct
{
	int id;
	char name[50];
	department dept;
	int rollNo;
	int year;
	float cgpa;
} student;
#define totalStudentFields 6

typedef struct
{
	int id;
	char name[50];
	subject sub;
	float salary;
} teacher;
#define totalTeacherFields 4

typedef struct
{
	int id;
	char name[50];
	staffRole role;
	float salary;
} staff;
#define totalStaffFields 4

//? All below functions are defined in main.c
void viewStudent(char *fileName);
void viewTeachers(char *fileName);
void viewStaff(char *fileName);

//? All below functions are defined in functions.c
int inputForInt(const char *_statement);
float inputForFloat(const char *_statement);

void printAllDepartments(void);
void printAllSubjects(void);
void printAllStaffRoles(void);

void clearScreen(void);
int countTotalMembers(char *fileName); //* Returns -1 for file not found

void parseStudent(char *input, student *result);
void parseTeacher(char *input, teacher *result);
void parseStaff(char *input, staff *result);

void printStudentHeader(void);
void printTeacherHeader(void);
void printStaffHeader(void);

void printStudentData(char *fileName, int studentCount, int viewNum); // viewNum: 1 for all, 2 for single
void printTeacherData(char *fileName, int teacherCount, int viewNum); // viewNum: 1 for all, 2 for single
void printStaffData(char *fileName, int staffCount, int viewNum);			// viewNum: 1 for all, 2 for single
