#include "college-header.h"

const char *department_names[] = {"CSE", "ECE", "BCA", "BCS", "IT", "ME", "CE", "AE"};
const char *subject_names[] = {"MATH", "PHYSICS", "COMPUTER_SCIENCE", "DISCRETE_MATH", "DATA_STRUCTURES", "ALGORITHMS"};
const char *staffRole_names[] = {"ADMIN", "LIBRARIAN", "LAB_ASSISTANT", "JANITOR", "SECURITY", "IT_SUPPORT"};

int inputForInt(const char *_statement)
{
	int validInput = 0; // Flag to check if input is valid
	int _num;
	while (!validInput)
	{
		printf("%s", _statement);
		if (scanf("%d", &_num) != 1)
		{
			printf("Enter numeric value!\nEnter the number correctly!\n");
		}
		else
		{
			validInput = 1;
		}
		while (getchar() != '\n')
			;
	}
	validInput = 0; // Reset for the next input
	return _num;
}
float inputForFloat(const char *_statement)
{
	int validInput = 0; // Flag to check if input is valid, assuming it to be false
	float _num;
	while (!validInput) // Checking if the input is valid "!" -> NOT true[or false]
	{
		printf("%s", _statement);
		if (scanf("%f", &_num) != 1)
		{
			fprintf(stderr, "Enter numeric value!\nEnter the number correctly!\n");
		}
		else
		{
			validInput = 1;
		}
		while (getchar() != '\n')
			;
	}
	validInput = 0; // Reset for the next input
	return _num;
}

void printAllDepartments()
{
	printf("Available Departments are:\n");
	for (int j = 0; j < totalDepartment; j++)
	{
		printf("\tDepartment %d: \"%s\"\n", j + 1, department_names[j]);
	}
}
void printAllSubjects()
{
	printf("Available Subjects are:\n");
	for (int j = 0; j < totalSubject; j++)
	{
		printf("\tSubject %d: \"%s\"\n", j + 1, subject_names[j]);
	}
}
void printAllStaffRoles()
{
	printf("Available Staff Roles are:\n");
	for (int j = 0; j < totalStaffRole; j++)
	{
		printf("\tStaff Role %d: \"%s\"\n", j + 1, staffRole_names[j]);
	}
}

void clearScreen()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}
int countTotalMembers(char *fileName) // Returns -1 for file not found
{
	int count = 0; // Line counter
	char fileLine[FILE_INPUT_BUFFER];
	FILE *ptr = fopen(fileName, "r");
	if (ptr == NULL)
	{
		perror("Could not initialize the memory file!");
		return -1;
	}
	while (fgets(fileLine, FILE_INPUT_BUFFER, ptr) != NULL)
	{
		count++;
	}
	rewind(ptr);
	fclose(ptr);
	return count;
}

void parseStudent(char *input, student *result)
{
	char inputCopy[FILE_INPUT_BUFFER];
	strcpy(inputCopy, input);
	char *tokens = strtok(inputCopy, ",");
	int index = 0;

	while (tokens != NULL)
	{
		if (index == 0)
		{
			result->id = atoi(tokens);
		}
		else if (index == 1)
		{
			strcpy(result->name, tokens);
		}
		else if (index == 2)
		{
			result->dept = (department)atoi(tokens);
		}
		else if (index == 3)
		{
			result->rollNo = atoi(tokens);
		}
		else if (index == 4)
		{
			result->year = atoi(tokens);
		}
		else if (index == 5)
		{
			result->cgpa = atof(tokens);
		}
		index++;
		tokens = strtok(NULL, ",");
	}
}
void parseTeacher(char *input, teacher *result)
{
	char inputCopy[FILE_INPUT_BUFFER];
	strcpy(inputCopy, input);
	char *tokens = strtok(inputCopy, ",");
	int index = 0;
	while (tokens != NULL)
	{
		if (index == 0)
		{
			result->id = atoi(tokens);
		}
		else if (index == 1)
		{
			strcpy(result->name, tokens);
		}
		else if (index == 2)
		{
			result->sub = (subject)atoi(tokens);
		}
		else if (index == 3)
		{
			result->salary = atof(tokens);
		}
		index++;
		tokens = strtok(NULL, ",");
	}
}
void parseStaff(char *input, staff *result)
{
	char inputCopy[FILE_INPUT_BUFFER];
	strcpy(inputCopy, input);
	char *tokens = strtok(inputCopy, ",");
	int index = 0;
	while (tokens != NULL)
	{
		if (index == 0)
		{
			result->id = atoi(tokens);
		}
		else if (index == 1)
		{
			strcpy(result->name, tokens);
		}
		else if (index == 2)
		{
			result->role = (staffRole)atoi(tokens);
		}
		else if (index == 3)
		{
			result->salary = atof(tokens);
		}
		index++;
		tokens = strtok(NULL, ",");
	}
}

//! Update the name lenght of the
void printStudentHeader()
{
	printf("\n|-----|--------------------------------|-------|------|------|------|\n");
	printf("| %-3s | %-30s | %-5s | %-4s | %-4s | %-4s |\n", "ID", "Name", "Dept.", "Roll", "Year", "CGPA");
	printf("|-----|--------------------------------|-------|------|------|------|\n");
}
void printTeacherHeader()
{
	printf("\n|-----|--------------------------------|------------------|----------|\n");
	printf("| %-3s | %-30s | %-16s | %-8s |\n", "ID", "Name", "Subject", "Salary");
	printf("|-----|--------------------------------|------------------|----------|\n");
}
void printStaffHeader()
{
	printf("\n|-----|--------------------------------|---------------|---------|\n");
	printf("| %-3s | %-30s | %-13s | %-7s |\n", "ID", "Name", "Role", "Salary");
	printf("|-----|--------------------------------|---------------|---------|\n");
}

void printStudentData(char *fileName, int studentCount, int viewNum) // viewNum: 1 for all, 2 for single
{
	student stdDetails;
	char fileLine[FILE_INPUT_BUFFER];
	FILE *file = fopen(fileName, "r");
	if (viewNum == 1)
	{
		if (file)
		{
			printStudentHeader();
			for (int i = 0; (fgets(fileLine, FILE_INPUT_BUFFER, file)) != NULL; i++)
			{
				fileLine[strcspn(fileLine, "\n")] = '\0';
				parseStudent(fileLine, &stdDetails);
				printf("| %03d | %-30s | %-5s | %04d | %04d | %04.2f |\n", stdDetails.id, stdDetails.name, department_names[stdDetails.dept - 1], stdDetails.rollNo, stdDetails.year, stdDetails.cgpa);
			}
			printf("|-----|--------------------------------|-------|------|------|------|\n\n");
		}
		else
		{
			fprintf(stderr, "Could not read student data from database.\n");
		}
	}
	else if (viewNum == 2)
	{
		int idInput, found = 0;
		printf("Enter the ID of the student to view their record: ");
		scanf("%d", &idInput);
		if (idInput > 0 && idInput <= studentCount)
		{
			if (file)
			{
				for (int i = 0; i < studentCount; i++)
				{
					fgets(fileLine, FILE_INPUT_BUFFER, file);
					fileLine[strcspn(fileLine, "\n")] = '\0';
					parseStudent(fileLine, &stdDetails);
					if (stdDetails.id == idInput)
					{
						printStudentHeader();
						printf("| %03d | %-30s | %-5s | %04d | %04d | %04.2f |\n", stdDetails.id, stdDetails.name, department_names[stdDetails.dept - 1], stdDetails.rollNo, stdDetails.year, stdDetails.cgpa);
						printf("|-----|--------------------------------|-------|------|------|------|\n\n");
						found = 1;
						break;
					}
				}
				if (found == 0)
				{
					fprintf(stderr, "No student record found! Kindly enter a valid student ID!\nSorry for the inconvenience caused.\n");
				}
			}
			else
			{
				fprintf(stderr, "Could not read student data from database.\n");
			}
		}
		else
		{
			fprintf(stderr, "Enter a valid student ID between 1 to %d!\n", studentCount);
		}
	}
	if (file) //*Close the file if not closed already!
	{
		fclose(file);
	}
}
void printTeacherData(char *fileName, int teacherCount, int viewNum) // viewNum: 1 for all, 2 for single
{
	teacher tchDetails;
	char fileLine[FILE_INPUT_BUFFER];
	FILE *file = fopen(fileName, "r");
	if (file)
	{
		if (viewNum == 1)
		{
			printTeacherHeader();
			for (int i = 0; i < teacherCount; i++)
			{
				fgets(fileLine, FILE_INPUT_BUFFER, file);
				fileLine[strcspn(fileLine, "\n")] = '\0';
				parseTeacher(fileLine, &tchDetails);
				printf("| %03d | %-30s | %-16s | $%07.2f |\n", tchDetails.id, tchDetails.name, subject_names[tchDetails.sub - 1], tchDetails.salary);
			}
			printf("|-----|--------------------------------|------------------|----------|\n\n");
		}
		else if (viewNum == 2)
		{
			int idInput = inputForInt("Enter the ID of the Teacher to view their record: ");
			int found = 0;
			for (int i = 0; i < teacherCount; i++)
			{
				fgets(fileLine, FILE_INPUT_BUFFER, file);
				fileLine[strcspn(fileLine, "\n")] = '\0';
				parseTeacher(fileLine, &tchDetails);
				if (tchDetails.id == idInput)
				{
					printTeacherHeader();
					printf("| %03d | %-30s | %-16s | $%07.2f |\n", tchDetails.id, tchDetails.name, subject_names[tchDetails.sub - 1], tchDetails.salary);
					printf("|-----|--------------------------------|------------------|----------|\n\n");
					found = 1;
					break;
				}
			}
			if (!found)
			{
				fprintf(stderr, "No Teacher record found! Kindly enter a valid Teacher ID!\nSorry for the inconvenience caused.\n");
			}
		}
		else
		{
			fprintf(stderr, "Could not read teacher data from database.\n");
		}
		fclose(file);
	}
	else
	{
		fprintf(stderr, "Could not read teacher data from database.\n");
	}
}
void printStaffData(char *fileName, int staffCount, int viewNum) // viewNum: 1 for all, 2 for single
{
	staff staffDetails;
	char fileLine[FILE_INPUT_BUFFER];
	FILE *file = fopen(fileName, "r");
	if (file)
	{
		if (viewNum == 1)
		{
			printStaffHeader();
			for (int i = 0; i < staffCount; i++)
			{
				fgets(fileLine, FILE_INPUT_BUFFER, file);
				fileLine[strcspn(fileLine, "\n")] = '\0';
				parseStaff(fileLine, &staffDetails);
				printf("| %03d | %-30s | %-13s | $%06.2f |\n", staffDetails.id, staffDetails.name, staffRole_names[staffDetails.role - 1], staffDetails.salary);
			}
			printf("|-----|--------------------------------|---------------|---------|\n\n");
		}
		else if (viewNum == 2)
		{
			int idInput = inputForInt("Enter the ID of the Staff to view their record: ");
			int found = 0;
			for (int i = 0; i < staffCount; i++)
			{
				fgets(fileLine, FILE_INPUT_BUFFER, file);
				fileLine[strcspn(fileLine, "\n")] = '\0';
				parseStaff(fileLine, &staffDetails);
				if (staffDetails.id == idInput)
				{
					printStaffHeader();
					printf("| %03d | %-30s | %-13s | $%06.2f |\n", staffDetails.id, staffDetails.name, staffRole_names[staffDetails.role - 1], staffDetails.salary);
					printf("|-----|--------------------------------|---------------|---------|\n\n");
					found = 1;
					break;
				}
			}
			if (!found)
			{
				fprintf(stderr, "No Staff record found! Kindly enter a valid Staff ID!\nSorry for the inconvenience caused.\n");
			}
		}
		else
		{
			fprintf(stderr, "Could not read staff data from database.\n");
		}
		fclose(file);
	}
	else
	{
		fprintf(stderr, "Could not read staff data from database.\n");
	}
}
