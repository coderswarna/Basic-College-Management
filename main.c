/*
 *This is a college management system.
 *Author: [Swarnadeep Paul]
 *Date: [03-09-2025]
 *It is just a small CRUD application developed for learning purposes.
 *Functions to be added:
 *    1. Search by ID or Name
 *    2. Printing of all members with a different function
 *        (void printParsedData(student *data, int index);)
 *    3. Add validation for all printing function
 */
#include "college-header.h"

const int MAX_RECORD = 100;
const int FILE_INPUT_BUFFER = 150;
// char *miscellaneous = "miscellaneous.txt";     //*For future use of storing id counters etc

int main(void)
{
	int choice, repeat;
	char *studentFileName = "student.csv";
	char *teacherFileName = "teacher.csv";
	char *staffFileName = "staff.csv";
	do
	{
		clearScreen();
		printf("--------------Welcome!--------------\n");
		printf("-----College Management Solution-----\n");
		printf("Select Option of your Choice:\n");
		printf("\t1. Manage Student Record (Press 1):\n");
		printf("\t2. Manage Teachers Record (Press 2):\n");
		printf("\t3. Manage Staff Record (Press 3):\n");
		printf("Enter a value: ");
		scanf("%d", &choice);
		int c;
		while ((c = getchar()) != '\n' && c != EOF)
			;
		printf("\n");
		switch (choice)
		{
		case 1:
			viewStudent(studentFileName);
			printf("\n");
			break;
		case 2:
			viewTeachers(teacherFileName);
			printf("\n");
			break;
		case 3:
			viewStaff(staffFileName);
			printf("\n");
			break;
		default:
			fprintf(stderr, "Enter a valid number between 1 to 3!\n");
			break;
		}
		printf("Do you want to continue with the main menu? [Press 1 for yes or any other to exit]: ");
		scanf("%d", &repeat);
		while ((c = getchar()) != '\n' && c != EOF)
			;
	} while (repeat == 1);
}

/*
 *Code organise into more functions
 *Error handling
 *Use tmpfile()
 *Allocate memory In the heap for arrays
 *Check for buffer overflow in fgets
 *Input validation for:
 *  1. deptChoice in case 3
 *  2. viewNum in Case 2
 */
void viewStudent(char *fileName)
{
	int option, repeat, studentCount, addNum, deptChoice, viewNum, idInput, found = 0, sureCheck = 0, deleteNum = 0, updateNum = 0;
	studentCount = countTotalMembers(fileName);
	do
	{
		clearScreen();
		printf("Welcome to the Student Management portal!\n");
		printf("Please choose from the options below:\n");
		printf("\t1. Add a Student's Record (Press 1):\n");
		printf("\t2. View Student Record (Press 2):\n");
		printf("\t3. Update a student record (Press 3):\n");
		printf("\t4. Delete a Student Record (Press 4):\n");
		option = inputForInt("Enter a value: ");
		switch (option)
		{
		case 1:
			do
			{
				char addStatement[FILE_INPUT_BUFFER];
				snprintf(addStatement, FILE_INPUT_BUFFER, "How many student's record do you want to put? [Max = %d per session]: ", MAX_RECORD);
				addNum = inputForInt(addStatement);
				if (addNum <= MAX_RECORD && addNum >= 0)
				{
					student studentDetails[addNum];
					for (int i = 0; i < addNum; i++)
					{
						studentDetails[i].id = studentCount + i + 1;
						printf("Enter the name of student %d: ", studentCount + i + 1);
						fgets(studentDetails[i].name, 50, stdin);
						studentDetails[i].name[strcspn(studentDetails[i].name, "\n")] = '\0';
						printAllDepartments();
						do
						{
							char deptStatement[FILE_INPUT_BUFFER];
							snprintf(deptStatement, FILE_INPUT_BUFFER, "Enter the Department ID for student %d or %s: ", i + 1, studentDetails[i].name);
							deptChoice = inputForInt(deptStatement);
							if (deptChoice >= 1 && deptChoice <= totalDepartment)
							{
								printf("You have selected the %s department.\n", department_names[deptChoice - 1]);
							}
							else
							{
								fprintf(stderr, "Invalid department choice.\nEnter a valid department number!\n");
							}
						} while (deptChoice < 1 || deptChoice > totalDepartment);
						studentDetails[i].dept = (department)deptChoice;

						char rollStatement[FILE_INPUT_BUFFER];
						snprintf(rollStatement, FILE_INPUT_BUFFER, "Enter the Roll No of student %d: ", studentCount + i + 1);
						studentDetails[i].rollNo = inputForInt(rollStatement);
						do
						{
							char yearStatement[FILE_INPUT_BUFFER];
							snprintf(yearStatement, FILE_INPUT_BUFFER, "Enter the Year of student %d [between 1 to 4]: ", studentCount + i + 1);
							studentDetails[i].year = inputForInt(yearStatement);
							if (studentDetails[i].year > 4 || studentDetails[i].year < 1)
							{
								fprintf(stderr, "Enter a number between '1' - '4' !\n");
							}
						} while (studentDetails[i].year > 4 || studentDetails[i].year < 1);
						do
						{
							char cgpaStatement[FILE_INPUT_BUFFER];
							snprintf(cgpaStatement, FILE_INPUT_BUFFER, "Enter the CGPA of student %d: ", studentCount + i + 1);
							studentDetails[i].cgpa = inputForFloat(cgpaStatement);
							if (studentDetails[i].cgpa > 10 || studentDetails[i].cgpa < 0)
							{
								fprintf(stderr, "Enter a number between 0 to 10!\n");
							}
						} while (studentDetails[i].cgpa > 10 || studentDetails[i].cgpa < 0);
						printf("\n");
					}
					// Save the student details to a file or database
					FILE *file = fopen(fileName, "a");
					if (file)
					{
						for (int i = 0; i < addNum; i++)
						{
							fprintf(file, "%d,%s,%d,%d,%d,%.2f\n", studentDetails[i].id, studentDetails[i].name, studentDetails[i].dept, studentDetails[i].rollNo, studentDetails[i].year, studentDetails[i].cgpa);
							fflush(file);
						}
						printf("Student details added successfully!\n");
						fclose(file);
					}
					else
					{
						fprintf(stderr, "Could not save the student details to database.\n");
					}
				}
				else if (addNum > MAX_RECORD || addNum < 0)
				{
					fprintf(stderr, "Enter a number between 0 - %d!\n", MAX_RECORD);
				}
				else
				{
					fprintf(stderr, "Enter a valid number!\n");
				}
			} while (addNum > MAX_RECORD || addNum < 0);
			printf("Thank You for updating the student record!\n");
			studentCount = countTotalMembers(fileName);
			break;
		case 2:
			if (studentCount > 0)
			{
				do
				{
					printf("Do you want to see records of all student or only one:\n");
					printf("\t1. For all students (Press 1): \n");
					printf("\t2. For single student (Press 2): \n");
					viewNum = inputForInt("Enter a option: ");
					if (viewNum == 1) // all students
					{
						printStudentData(fileName, studentCount, viewNum);
					}
					else if (viewNum == 2)
					{
						printStudentData(fileName, studentCount, viewNum);
					}
					else
					{
						fprintf(stderr, "Enter a valid number either '1' or '2'!\n");
					}
					repeat = inputForInt("Do you want to see the records again?(Press 1 to continue or 0 to exit): ");
				} while (repeat == 1);
				repeat = 0;
			}
			else
			{
				fprintf(stderr, "Please First Enter data of students, then come back to access the details of your college's student.\n");
			}
			found = 0;
			break;
		case 3: // Update student record option
			if (studentCount > 0)
			{
				student stdDetails;
				do
				{
					//* clearScreen(); // Clear the screen for better visibility
					printf("Here is the list of all students:\n");
					printStudentData(fileName, studentCount, 1); //* 1 for all students
					printf("\n");
					idInput = inputForInt("Enter the ID of the student to update his profile: ");
					char fileLine[FILE_INPUT_BUFFER];
					FILE *file = fopen(fileName, "r");
					if (file)
					{
						for (int i = 0; i < studentCount; i++)
						{
							fgets(fileLine, FILE_INPUT_BUFFER, file);
							fileLine[strcspn(fileLine, "\n")] = '\0';
							parseStudent(fileLine, &stdDetails);
							if (stdDetails.id == idInput)
							{
								printf("Student Record Found!\n\tID: %d\n\tName: %s\n\tDepartment: %s\n\tRoll No: %d\n\tYear: %d\n\tCGPA: %.2f\n", stdDetails.id, stdDetails.name, department_names[stdDetails.dept - 1], stdDetails.rollNo, stdDetails.year, stdDetails.cgpa);
								found = 1;
								break;
							}
						}
						fclose(file);
					}
					else
					{
						fprintf(stderr, "Could not read student data from database.\n");
					}
					if (found == 1)
					{
						student studentDetailsTemp; // stdDetails still stores the original data
						printf("Which record do you want to update\n");
						printf("This is a one time function so be correct otherwise you have to restart!\n");
						printf("\t1. Name (Press 1):\n");
						printf("\t2. Department (Press 2):\n");
						printf("\t3. Roll No (Press 3):\n");
						printf("\t4. Year (Press 4):\n");
						printf("\t5. CGPA (Press 5):\n");
						updateNum = inputForInt("Enter a option: ");
						switch (updateNum)
						{
						case 1: // Name
							do
							{
								printf("Enter the name: ");
								fgets(studentDetailsTemp.name, 50, stdin);
								studentDetailsTemp.name[strcspn(studentDetailsTemp.name, "\n")] = '\0';
								printf("The entered name is: '%s'\n\tAre you sure? [Press 1 if sure or press 0 if not sure]: ", studentDetailsTemp.name);
								scanf("%d", &sureCheck);
								getchar();
							} while (sureCheck != 1);
							break;
						case 2: // Department
							do
							{
								printAllDepartments();
								deptChoice = inputForInt("Enter the Department ID: ");
								printf("The entered department is: '%s'\n\tAre you sure? [Press 1 if sure or press 0 if not sure]: ", department_names[deptChoice - 1]);
								scanf("%d", &sureCheck);
							} while (sureCheck != 1);
							break;
						case 3: // RollNo
							do
							{
								studentDetailsTemp.rollNo = inputForInt("Enter the Roll No: ");
								printf("The entered roll no is: '%d'\n\tAre you sure? [Press 1 if sure or press 0 if not sure]: ", studentDetailsTemp.rollNo);
								scanf("%d", &sureCheck);
							} while (sureCheck != 1);
							break;
						case 4: // Year
							do
							{
								do
								{
									studentDetailsTemp.year = inputForInt("Enter the Year [between 1 to 4]: ");
									printf("The entered year is: '%d'\n", studentDetailsTemp.year);
									if (studentDetailsTemp.year > 4 || studentDetailsTemp.year < 1)
									{
										fprintf(stderr, "Enter a number between '1' and '4' !\n");
									}
								} while (studentDetailsTemp.year > 4 || studentDetailsTemp.year < 1);
								printf("\tAre you sure? [Press 1 if sure or press 0 if not sure]: ");
								scanf("%d", &sureCheck);
							} while (sureCheck != 1);
							break;
						case 5: // CGPA
							do
							{
								do
								{
									studentDetailsTemp.cgpa = inputForFloat("Enter the CGPA: ");
								} while (studentDetailsTemp.cgpa > 10 || studentDetailsTemp.cgpa < 0);
								printf("The entered CGPA is: '%.2f'\n\tAre you sure? [Press 1 if sure or press 0 if not sure]: ", studentDetailsTemp.cgpa);
								scanf("%d", &sureCheck);
							} while (sureCheck != 1);
							break;
						default:
							printf("Enter a valid number between '1' and '5'!\n");
							break;
						}
						// Update the record in the file
						{
							studentCount = countTotalMembers(fileName); // Recounting the total members
							FILE *mainFile = fopen(fileName, "r");
							if (mainFile)
							{
								FILE *tempFile = fopen("temp.csv", "w");
								if (tempFile)
								{
									char fileLine2[FILE_INPUT_BUFFER];
									student stdDetails2;
									for (int i = 0; i < studentCount; i++)
									{
										fgets(fileLine2, FILE_INPUT_BUFFER, mainFile);
										char fileLine3[FILE_INPUT_BUFFER];
										strcpy(fileLine3, fileLine2);
										fileLine2[strcspn(fileLine2, "\n")] = '\0';
										parseStudent(fileLine2, &stdDetails2);
										if (stdDetails.id == stdDetails2.id)
										{
											fprintf(tempFile, "%d,%s,%d,%d,%d,%.2f\n", stdDetails2.id, (updateNum == 1) ? studentDetailsTemp.name : stdDetails2.name, (updateNum == 2) ? deptChoice : stdDetails2.dept, (updateNum == 3) ? studentDetailsTemp.rollNo : stdDetails2.rollNo, (updateNum == 4) ? studentDetailsTemp.year : stdDetails2.year, (updateNum == 5) ? studentDetailsTemp.cgpa : stdDetails2.cgpa);
										}
										else
										{
											fputs(fileLine3, tempFile);
										}
									}
									fclose(tempFile);
								}
								fclose(mainFile);
								remove(fileName);							// Deleting the original file
								rename("temp.csv", fileName); // Replacing the original file with the updated temp file
							}
							else
							{
								fprintf(stderr, "Error opening file for editing!\n");
							}
						}
					}
					else if (found == 0)
					{
						fprintf(stderr, "No student record found! Kindly enter a valid student ID!\nSorry for the inconvenience caused.\n");
					}
					repeat = inputForInt("Do you want to update another record?(Press 1 to continue or 0 to exit): ");
				} while (repeat == 1);
				repeat = 0;
			}
			else
			{
				fprintf(stderr, "Please First Enter data of students, then come back to access the details of your college's student.\n");
			}
			break;
		case 4:
			if (studentCount >= 1)
			{
				do
				{
					printf("Here is the list of all students:\n");
					printStudentData(fileName, studentCount, 1); //* 1 for all students
					printf("\n");
					idInput = inputForInt("Enter the ID of the student to DELETE his profile: ");
					student studentDetails;
					char fileLine[FILE_INPUT_BUFFER];
					char fileLineCopy[FILE_INPUT_BUFFER];
					FILE *file = fopen(fileName, "r");
					if (file)
					{
						FILE *tempFile = fopen("temp.csv", "w");
						if (tempFile)
						{
							for (int i = 0; i < studentCount; i++)
							{
								fgets(fileLine, FILE_INPUT_BUFFER, file);
								strcpy(fileLineCopy, fileLine);
								fileLine[strcspn(fileLine, "\n")] = '\0';
								parseStudent(fileLine, &studentDetails);
								if (studentDetails.id == idInput)
								{
									printf("Student Record Found!\n\tID: %d\n\tName: %s\n\tDepartment: %s\n\tRoll No: %d\n\tYear: %d\n\tCGPA: %.2f\n", studentDetails.id, studentDetails.name, department_names[studentDetails.dept - 1], studentDetails.rollNo, studentDetails.year, studentDetails.cgpa);
									printf("Deleting Student Record...\n");
									deleteNum = 1;
									continue;
								}
								else
								{
									if (tempFile)
									{
										fputs(fileLineCopy, tempFile);
									}
								}
							}
							if (!deleteNum)
							{
								fprintf(stderr, "No student record found! Kindly enter a valid student ID!\nSorry for the inconvenience caused.\n");
							}
							fclose(tempFile);
						}
						fclose(file);
						remove(fileName);
						rename("temp.csv", fileName);
						// Refactor the IDs of the students
						studentCount = countTotalMembers(fileName); // Recounting the total members
						FILE *mainFile = fopen(fileName, "r");
						if (mainFile)
						{
							FILE *tempFile2 = fopen("temp2.csv", "w");
							if (tempFile2)
							{
								char fileLine2[FILE_INPUT_BUFFER];
								student stdDetails2;
								for (int i = 0; i < studentCount; i++)
								{
									fgets(fileLine2, FILE_INPUT_BUFFER, mainFile);
									char fileLine3[FILE_INPUT_BUFFER];
									strcpy(fileLine3, fileLine2); // This is just for safety purpose, it is not necessary
									fileLine2[strcspn(fileLine2, "\n")] = '\0';
									parseStudent(fileLine2, &stdDetails2);
									fprintf(tempFile2, "%d,%s,%d,%d,%d,%.2f\n", i + 1, stdDetails2.name, stdDetails2.dept, stdDetails2.rollNo, stdDetails2.year, stdDetails2.cgpa);
								}
								fclose(tempFile2);
							}
							fclose(mainFile);
							remove(fileName);							 // Deleting the original file
							rename("temp2.csv", fileName); // Replacing the original file with the updated temp file
						}
					}
					else
					{
						fprintf(stderr, "Could not read student data from database.\n");
					}
					printf("Student record deleted successfully!\n");
					studentCount = countTotalMembers(fileName); // Recounting the total members
					repeat = inputForInt("Do you want to delete another record?(Press 1 to continue or 0 to exit): ");
				} while (repeat == 1);
				repeat = 0;
			}
			else
			{
				fprintf(stderr, "Please First Enter data of students, then come back to access the details of your college's student.\n");
			}
			break;
		default:
			fprintf(stderr, "Enter a valid number between 1 to 4!\n");
			break;
		}
		found = 0;
		printf("Do you want to continue with student portal or go back?\n\t(Enter 1 to continue or press any key to go back!): ");
		scanf("%d", &repeat);
		int c;
		while ((c = getchar()) != '\n' && c != EOF)
			;
	} while (repeat == 1);
}

void viewTeachers(char *fileName)
{
	int option, repeat, teacherCount, addNum, subjectChoice, viewNum, idInput, found = 0, sureCheck = 0, deleteNum = 0, updateNum = 0;
	teacherCount = countTotalMembers(fileName);
	do
	{
		clearScreen();
		printf("Welcome to the Teacher Management portal!\n");
		printf("Please choose from the options below:\n");
		printf("\t1. Add a Teacher's Record (Press 1):\n");
		printf("\t2. View Teacher Record (Press 2):\n");
		printf("\t3. Update a Teacher record (Press 3):\n");
		printf("\t4. Delete a Teacher Record (Press 4):\n");
		option = inputForInt("Enter a value: ");
		switch (option)
		{
		case 1:
			do
			{
				char addStatement[FILE_INPUT_BUFFER];
				snprintf(addStatement, FILE_INPUT_BUFFER, "How many Teacher's record do you want to put? [Max = %d per session]: ", MAX_RECORD);
				addNum = inputForInt(addStatement);
				if (addNum <= MAX_RECORD && addNum >= 0)
				{
					teacher *teacherDetails = malloc(addNum * sizeof(teacher));
					for (int i = 0; i < addNum; i++)
					{
						teacherDetails[i].id = teacherCount + i + 1;
						printf("Enter the name of Teacher %d: ", teacherCount + i + 1);
						fgets(teacherDetails[i].name, 50, stdin);
						teacherDetails[i].name[strcspn(teacherDetails[i].name, "\n")] = '\0';

						printAllSubjects();
						do
						{
							char subjectStatement[FILE_INPUT_BUFFER];
							snprintf(subjectStatement, FILE_INPUT_BUFFER, "Enter the Subject ID for Teacher %d or %s: ", teacherCount + i + 1, teacherDetails[i].name);
							subjectChoice = inputForInt(subjectStatement);
							if (subjectChoice >= 1 && subjectChoice <= totalSubject)
							{
								printf("You have selected the %s subject.\n", subject_names[subjectChoice - 1]);
								teacherDetails[i].sub = (subject)subjectChoice;
							}
							else
							{
								fprintf(stderr, "Invalid subject choice.\nEnter a valid subject number!\n");
							}
						} while (subjectChoice < 1 || subjectChoice > totalSubject);

						do
						{
							char salaryStatement[FILE_INPUT_BUFFER];
							snprintf(salaryStatement, FILE_INPUT_BUFFER, "Enter the Salary of Teacher %d: ", teacherCount + i + 1);
							teacherDetails[i].salary = inputForFloat(salaryStatement);
							if (teacherDetails[i].salary <= 0)
							{
								printf("Are you kidding with the salary of a teacher?\n\tEnter a number greater than 0!\n");
							}
						} while (teacherDetails[i].salary <= 0);
						printf("\n");
					}
					// Logic for saving the teacher details to a file or database
					FILE *file = fopen(fileName, "a");
					if (file)
					{
						for (int i = 0; i < addNum; i++)
						{
							fprintf(file, "%d,%s,%d,%.2f\n", teacherDetails[i].id, teacherDetails[i].name, teacherDetails[i].sub, teacherDetails[i].salary);
							fflush(file);
						}
						printf("Teacher details added successfully!\n");
						fclose(file);
					}
					else
					{
						fprintf(stderr, "Could not save the Teacher details to database.\n");
					}
					free(teacherDetails);
				}
				else if (addNum > MAX_RECORD || addNum < 0)
				{
					printf("Enter a number between 0 - %d!\n", MAX_RECORD);
				}
				else
				{
					printf("Enter a valid number!");
				}
			} while (addNum > MAX_RECORD || addNum < 0);
			printf("Thank You for updating the Teacher record!\n");
			break;
		case 2:
			teacherCount = countTotalMembers(fileName);
			if (teacherCount > 0)
			{
				do
				{
					printf("Do you want to see records of all teachers or only one:\n");
					printf("\t1. For all teachers (Press 1): \n");
					printf("\t2. For single teachers (Press 2): \n");
					viewNum = inputForInt("Enter a option: ");

					if (viewNum == 1 || viewNum == 2) // all Teachers
					{
						printTeacherData(fileName, teacherCount, viewNum);
					}
					else
					{
						printf("Enter a valid number either '1' or '2'!\n");
					}

					repeat = inputForInt("Do you want to see the records again?(Press 1 to continue or 0 to exit): ");
				} while (repeat == 1);
			}
			else
			{
				fprintf(stderr, "Please First Enter data of Teachers, then come back to access the details of your college's Teacher.\n");
			}
			break;
		case 3:
			teacherCount = countTotalMembers(fileName);
			if (teacherCount >= 1)
			{
				do
				{
					teacher tchDetails;
					printf("Here is the list of all teachers:\n");
					printTeacherData(fileName, teacherCount, 1); //* 1 for all teachers
					printf("\n");
					idInput = inputForInt("Enter the ID of the Teacher to update the profile: ");
					char fileLine[FILE_INPUT_BUFFER];
					FILE *file = fopen(fileName, "r");
					if (file)
					{
						for (int i = 0; i < teacherCount; i++)
						{
							fgets(fileLine, FILE_INPUT_BUFFER, file);
							fileLine[strcspn(fileLine, "\n")] = '\0';
							parseTeacher(fileLine, &tchDetails);
							if (tchDetails.id == idInput)
							{
								printf("Teacher Record Found!\n\tID: %d\n\tName: %s\n\tSubject: %s\n\tSalary: %.2f\n", tchDetails.id, tchDetails.name, subject_names[tchDetails.sub - 1], tchDetails.salary);
								found = 1;
								break;
							}
						}
						fclose(file);
					}
					else
					{
						fprintf(stderr, "Could not read Teacher data from database.\n");
					}
					if (found == 1)
					{
						teacher tchDetailsTemp; // tchDetails still stores the original data, this will store the updated data temporarily
						printf("Which record do you want to update\n");
						printf("This is a one time function so be correct otherwise you have to restart!\n");
						printf("\t1. Name (Press 1):\n");
						printf("\t2. Subject (Press 2):\n");
						printf("\t3. Salary (Press 3):\n");
						updateNum = inputForInt("Enter an option: ");
						switch (updateNum)
						{
						case 1:
							do
							{
								printf("Enter the name:");
								fgets(tchDetailsTemp.name, 50, stdin);
								tchDetailsTemp.name[strcspn(tchDetailsTemp.name, "\n")] = '\0';
								printf("The entered name is: '%s'\n\tAre you sure? [Press 1 if sure or press 0 if not sure]: ", tchDetailsTemp.name);
								scanf("%d", &sureCheck);
								getchar();
							} while (sureCheck != 1);
							break;
						case 2:
							do
							{
								printAllSubjects();
								do
								{
									subjectChoice = inputForInt("Enter the Subject ID: ");
									if (subjectChoice < 1 || subjectChoice > totalSubject)
									{
										printf("Invalid Subject ID. Please try again.\n");
									}
								} while (subjectChoice < 1 || subjectChoice > totalSubject);
								printf("The entered Subject is: '%s'\n\tAre you sure? [Press 1 if sure or press 0 if not sure]: ", subject_names[subjectChoice - 1]);
								scanf("%d", &sureCheck);
								getchar();
							} while (sureCheck != 1);
							break;
						case 3:
							do
							{
								do
								{
									tchDetailsTemp.salary = inputForFloat("Enter the Salary: ");
									if (tchDetailsTemp.salary <= 0)
									{
										printf("Invalid Salary. Please enter a positive value.\n");
									}
								} while (tchDetailsTemp.salary <= 0);
								printf("The entered Salary is: '%.2f'\n\tAre you sure? [Press 1 if sure or press 0 if not sure]: ", tchDetailsTemp.salary);
								scanf("%d", &sureCheck);
								getchar();
							} while (sureCheck != 1);
							break;
						default:
							printf("Enter a valid number between '1' and '3'!\n");
							break;
						}
						// Update the record in the file
						{
							teacherCount = countTotalMembers(fileName); // Recounting the total members
							FILE *mainFile = fopen(fileName, "r");
							if (mainFile)
							{
								FILE *tempFile = fopen("temp-tch.csv", "w");
								if (tempFile)
								{
									char fileLine2[FILE_INPUT_BUFFER];
									teacher tchDetails2;
									for (int i = 0; i < teacherCount; i++)
									{
										fgets(fileLine2, FILE_INPUT_BUFFER, mainFile);
										char fileLine3[FILE_INPUT_BUFFER];
										strcpy(fileLine3, fileLine2);
										fileLine2[strcspn(fileLine2, "\n")] = '\0';
										parseTeacher(fileLine2, &tchDetails2);
										if (tchDetails.id == tchDetails2.id)
										{
											fprintf(tempFile, "%d,%s,%d,%.2f\n", tchDetails2.id, (updateNum == 1) ? tchDetailsTemp.name : tchDetails2.name, (updateNum == 2) ? subjectChoice : tchDetails2.sub, (updateNum == 3) ? tchDetailsTemp.salary : tchDetails2.salary);
										}
										else
										{
											fputs(fileLine3, tempFile);
										}
									}
									fclose(tempFile);
								}
								fclose(mainFile);
								remove(fileName);									// Deleting the original file
								rename("temp-tch.csv", fileName); // Replacing the original file with the updated temp file
							}
							else
							{
								fprintf(stderr, "Error opening file for editing!\n");
							}
						}
					}
					else if (found == 0)
					{
						fprintf(stderr, "No Teacher record found! Kindly enter a valid Teacher ID!\nSorry for the inconvenience caused.\n");
					}
					repeat = inputForInt("Do you want to update the Teacher's records again?(Press 1 to continue or 0 to exit): ");
				} while (repeat == 1);
				repeat = 0;
			}
			else
			{
				printf("Please First Enter data of Teachers, then come back to access the details of your college's Teacher.\n");
			}
			break;
		case 4:
			if (teacherCount >= 1)
			{
				do
				{
					printf("Here is the list of all teachers:\n");
					printTeacherData(fileName, teacherCount, 1); //* 1 for all teachers
					printf("\n");
					idInput = inputForInt("Enter the ID of the Teacher to DELETE the Teacher's profile: ");
					teacher tchDetails;
					char fileLine[FILE_INPUT_BUFFER];
					char fileLineCopy[FILE_INPUT_BUFFER];
					FILE *file = fopen(fileName, "r");
					if (file)
					{
						FILE *tempFile = fopen("temp-tch.csv", "w");
						if (tempFile)
						{
							for (int i = 0; i < teacherCount; i++)
							{
								fgets(fileLine, FILE_INPUT_BUFFER, file);
								strcpy(fileLineCopy, fileLine);
								fileLine[strcspn(fileLine, "\n")] = '\0';
								parseTeacher(fileLine, &tchDetails);
								if (tchDetails.id == idInput)
								{
									printf("Teacher Record Found!\n\tID: %d\n\tName: %s\n\tSubject: %s\n\tSalary: %.2f\n", tchDetails.id, tchDetails.name, subject_names[tchDetails.sub - 1], tchDetails.salary);
									printf("Deleting Teacher Record...\n");
									deleteNum = 1;
									continue;
								}
								else
								{
									if (tempFile)
									{
										fputs(fileLineCopy, tempFile);
									}
								}
							}
							if (!deleteNum)
							{
								fprintf(stderr, "No Teacher record found! Kindly enter a valid Teacher ID!\nSorry for the inconvenience caused.\n");
							}
							deleteNum = 0; // Resetting deleteNum for future use
							fclose(tempFile);
						}
						fclose(file);
						remove(fileName);
						rename("temp-tch.csv", fileName);
						// Refactor the IDs of the teachers
						teacherCount = countTotalMembers(fileName);
						FILE *mainFile = fopen(fileName, "r");
						if (mainFile)
						{
							FILE *tempFile2 = fopen("temp2-tch.csv", "w");
							if (tempFile2)
							{
								char fileLine2[FILE_INPUT_BUFFER];
								teacher tchDetails2;
								for (int i = 0; i < teacherCount; i++)
								{
									fgets(fileLine2, FILE_INPUT_BUFFER, mainFile);
									char fileLine3[FILE_INPUT_BUFFER];
									strcpy(fileLine3, fileLine2); // This is just for safety purpose, it is not necessary
									fileLine2[strcspn(fileLine2, "\n")] = '\0';
									parseTeacher(fileLine2, &tchDetails2);
									fprintf(tempFile2, "%d,%s,%d,%.2f\n", i + 1, tchDetails2.name, tchDetails2.sub, tchDetails2.salary);
								}
								fclose(tempFile2);
							}
							fclose(mainFile);
							remove(fileName);									 // Deleting the original file
							rename("temp2-tch.csv", fileName); // Replacing the original file with the updated temp file
						}
					}
					else
					{
						fprintf(stderr, "Could not read Teacher data from database.\n");
					}
					teacherCount = countTotalMembers(fileName); // Recounting the total members
					repeat = inputForInt("Do you want to delete another record?(Press 1 to continue or 0 to exit):");
				} while (repeat == 1);
				repeat = 0;
			}
			else
			{
				fprintf(stderr, "Please First Enter data of Teachers, then come back to access the details of your college's Teacher.\n");
			}
			break;
		default:
			fprintf(stderr, "Enter a valid number between 1 to 4!\n");
			break;
		}
		found = 0;
		repeat = inputForInt("Do you want to continue with Teacher portal or go back?\n\t(Enter 1 to continue or press any key to go back!):");
	} while (repeat == 1);
}

void viewStaff(char *fileName)
{
	int option, repeat, staffCount, addNum, roleChoice, viewNum, idInput, found = 0, sureCheck = 0, deleteNum = 0, updateNum = 0;
	staffCount = countTotalMembers(fileName);
	do
	{
		clearScreen();
		printf("Welcome to the Staff Management portal!\n");
		printf("Please choose from the options below:\n");
		printf("\t1. Add a Staff's Record (Press 1):\n");
		printf("\t2. View Staff Record (Press 2):\n");
		printf("\t3. Update a Staff record (Press 3):\n");
		printf("\t4. Delete a Staff Record (Press 4):\n");
		option = inputForInt("Enter a value: ");
		switch (option)
		{
		case 1:
			do
			{
				char addStatement[FILE_INPUT_BUFFER];
				snprintf(addStatement, FILE_INPUT_BUFFER, "How many Staff's record do you want to put? [Max = %d per session]: ", MAX_RECORD);
				addNum = inputForInt(addStatement);
				if (addNum <= MAX_RECORD && addNum >= 0)
				{
					staff *staffDetails = malloc(addNum * sizeof(staff));
					staffCount = countTotalMembers(fileName);
					for (int i = 0; i < addNum; i++)
					{
						staffDetails[i].id = staffCount + i + 1;
						printf("Enter the name of Staff %d: ", staffCount + i + 1);
						fgets(staffDetails[i].name, 50, stdin);
						staffDetails[i].name[strcspn(staffDetails[i].name, "\n")] = '\0';
						printAllStaffRoles();
						do
						{
							char roleStatement[FILE_INPUT_BUFFER];
							snprintf(roleStatement, FILE_INPUT_BUFFER, "Enter the Role ID for Staff %d or '%s': ", staffCount + i + 1, staffDetails[i].name);
							roleChoice = inputForInt(roleStatement);
							if (roleChoice >= 1 && roleChoice <= totalStaffRole)
							{
								printf("You have selected the %s role.\n", staffRole_names[roleChoice - 1]);
								staffDetails[i].role = (staffRole)roleChoice;
							}
							else
							{
								fprintf(stderr, "Invalid role choice.\nEnter a valid role ID!\n");
							}
						} while (roleChoice < 1 || roleChoice > totalStaffRole);
						do
						{
							char salaryStatement[FILE_INPUT_BUFFER];
							snprintf(salaryStatement, FILE_INPUT_BUFFER, "Enter the Salary of Staff %d: ", staffCount + i + 1);
							staffDetails[i].salary = inputForFloat(salaryStatement);
							if (staffDetails[i].salary <= 0)
							{
								printf("Are you kidding with the salary of a Staff?\n\tEnter a number greater than 0!\n");
							}

						} while (staffDetails[i].salary <= 0);
						printf("\n");
					}
					FILE *file = fopen(fileName, "a");
					if (file)
					{
						for (int i = 0; i < addNum; i++)
						{
							fprintf(file, "%d,%s,%d,%.2f\n", staffDetails[i].id, staffDetails[i].name, staffDetails[i].role, staffDetails[i].salary);
							fflush(file);
						}
						printf("Staff details added successfully!\n");
						fclose(file);
					}
					else
					{
						fprintf(stderr, "Could not save the Staff details to database.\n");
					}
					free(staffDetails);
				}
				else if (addNum > MAX_RECORD || addNum < 0)
				{
					printf("Enter a number between 0 - %d!\n", MAX_RECORD);
				}
			} while (addNum > MAX_RECORD || addNum < 0);
			printf("Thank You for updating the Staff record!\n");
			break;
		case 2:
			staffCount = countTotalMembers(fileName);
			if (staffCount > 0)
			{
				do
				{
					printf("Do you want to see records of all staff or only one:\n");
					printf("\t1. For all staff (Press 1): \n");
					printf("\t2. For single staff (Press 2): \n");
					viewNum = inputForInt("Enter a option: ");
					if (viewNum == 1 || viewNum == 2) // all Teachers
					{
						printStaffData(fileName, staffCount, viewNum);
					}
					else
					{
						printf("Enter a valid number either '1' or '2'!\n");
					}

					repeat = inputForInt("Do you want to see the records again?(Press 1 to continue or 0 to exit): ");
				} while (repeat == 1);
			}
			else
			{
				fprintf(stderr, "Please First Enter data of Staffs, then come back to access the details of your college's Staff.\n");
			}
			found = 0;
			break;
		case 3:
			staffCount = countTotalMembers(fileName);
			if (staffCount > 0)
			{
				do
				{
					staff staffDetails;
					printf("Here is the list of all staff:\n");
					printStaffData(fileName, staffCount, 1); //* 1 for all staff
					printf("\n");
					idInput = inputForInt("Enter the ID of the Staff to update the profile: ");
					char fileLine[FILE_INPUT_BUFFER];
					FILE *file = fopen(fileName, "r");
					if (file)
					{
						for (int i = 0; i < staffCount; i++)
						{
							fgets(fileLine, FILE_INPUT_BUFFER, file);
							fileLine[strcspn(fileLine, "\n")] = '\0';
							parseStaff(fileLine, &staffDetails);
							if (staffDetails.id == idInput)
							{
								printf("Staff Record Found!\n\tID: %d\n\tName: %s\n\tRole: %s\n\tSalary: %.2f\n", staffDetails.id, staffDetails.name, staffRole_names[staffDetails.role - 1], staffDetails.salary);
								found = 1;
								break;
							}
							else
							{
								found = 0;
							}
						}
						fclose(file);
					}
					else
					{
						fprintf(stderr, "Could not read Staff data from database.\n");
					}
					if (found == 1)
					{
						staff staffDetailsTemp; // staffDetails still stores the original data, this will store the updated data temporarily
						printf("Which record do you want to update\n");
						printf("This is a one time function so be correct otherwise you have to restart!\n");
						printf("\t1. Name (Press 1):\n");
						printf("\t2. Role (Press 2):\n");
						printf("\t3. Salary (Press 3):\n");
						updateNum = inputForInt("Enter an option: ");
						switch (updateNum)
						{
						case 1:
							do
							{
								printf("Enter the name: ");
								fgets(staffDetailsTemp.name, 50, stdin);
								staffDetailsTemp.name[strcspn(staffDetailsTemp.name, "\n")] = '\0';
								printf("The entered name is: '%s'\n\tAre you sure? [Press 1 if sure or press 0 if not sure]: ", staffDetailsTemp.name);
								scanf("%d", &sureCheck);
								getchar();
							} while (sureCheck != 1);
							break;
						case 2:
							do
							{
								printAllStaffRoles();
								do
								{
									roleChoice = inputForInt("Enter the Role ID: ");
									if (roleChoice < 1 || roleChoice > totalStaffRole)
									{
										fprintf(stderr, "Invalid Role ID. Please try again.\n");
									}
								} while (roleChoice < 1 || roleChoice > totalStaffRole);
								printf("The entered Role is: '%s'\n\tAre you sure? [Press 1 if sure or press 0 if not sure]: ", staffRole_names[roleChoice - 1]);
								scanf("%d", &sureCheck);
								getchar();
							} while (sureCheck != 1);
							break;
						case 3:
							do
							{
								do
								{
									staffDetailsTemp.salary = inputForFloat("Enter the Salary: ");
									if (staffDetailsTemp.salary <= 0)
									{
										printf("Invalid Salary. Please enter a positive value.\n");
									}
								} while (staffDetailsTemp.salary <= 0);
								printf("The entered Salary is: '%.2f'\n\tAre you sure? [Press 1 if sure or press 0 if not sure]: ", staffDetailsTemp.salary);
								scanf("%d", &sureCheck);
								getchar();
							} while (sureCheck != 1);
							break;
						default:
							printf("Enter a valid number between '1' and '3'!\n");
							break;
						}

						// Update the record in the file
						{
							staffCount = countTotalMembers(fileName); // Recounting the total members
							FILE *mainFile = fopen(fileName, "r");
							if (mainFile)
							{
								FILE *tempFile = fopen("temp-stf.csv", "w");
								if (tempFile)
								{
									char fileLine2[FILE_INPUT_BUFFER];
									staff staffDetails2;
									for (int i = 0; i < staffCount; i++)
									{
										fgets(fileLine2, FILE_INPUT_BUFFER, mainFile);
										char fileLine3[FILE_INPUT_BUFFER];
										strcpy(fileLine3, fileLine2);
										fileLine2[strcspn(fileLine2, "\n")] = '\0';
										parseStaff(fileLine2, &staffDetails2);
										if (staffDetails.id == staffDetails2.id)
										{
											fprintf(tempFile, "%d,%s,%d,%.2f\n", staffDetails2.id, (updateNum == 1) ? staffDetailsTemp.name : staffDetails2.name, (updateNum == 2) ? roleChoice : staffDetails2.role, (updateNum == 3) ? staffDetailsTemp.salary : staffDetails2.salary);
										}
										else
										{
											fputs(fileLine3, tempFile);
										}
									}
									fclose(tempFile);
								}
								fclose(mainFile);
								remove(fileName);									// Deleting the original file
								rename("temp-stf.csv", fileName); // Replacing the original file with the updated temp file
							}
							else
							{
								fprintf(stderr, "Error opening file for editing!\n");
							}
						}
					}
					else if (found == 0)
					{
						printf("No Staff record found! Kindly enter a valid Staff ID!\nSorry for the inconvenience caused.\n");
					}
					repeat = inputForInt("Do you want to update the Staff's records again?(Press 1 to continue or 0 to exit):");
				} while (repeat == 1);
				repeat = 0;
			}
			else
			{
				fprintf(stderr, "Please First Enter data of Staffs, then come back to access the details of your college's Staff.\n");
			}
			found = 0;
			break;
		case 4:
			staffCount = countTotalMembers(fileName);
			if (staffCount >= 1)
			{
				do
				{
					printf("Here is the list of all Staff:\n");
					printStaffData(fileName, staffCount, 1); //* 1 for all Staff
					printf("\n");
					idInput = inputForInt("Enter the ID of the Staff to DELETE the Staff's profile: ");
					staff staffDetails;
					char fileLine[FILE_INPUT_BUFFER];
					char fileLineCopy[FILE_INPUT_BUFFER];
					FILE *file = fopen(fileName, "r");
					if (file)
					{
						FILE *tempFile = fopen("temp-stf.csv", "w");
						if (tempFile)
						{
							for (int i = 0; i < staffCount; i++)
							{
								fgets(fileLine, FILE_INPUT_BUFFER, file);
								strcpy(fileLineCopy, fileLine);
								fileLine[strcspn(fileLine, "\n")] = '\0';
								parseStaff(fileLine, &staffDetails);
								if (staffDetails.id == idInput)
								{
									printf("Staff Record Found!\n\tID: %d\n\tName: %s\n\tRole: %d\n\tSalary: %.2f\n", staffDetails.id, staffDetails.name, staffDetails.role, staffDetails.salary);
									printf("Deleting Staff Record...\n");
									deleteNum = 1;
									continue;
								}
								else
								{
									if (tempFile)
									{
										fputs(fileLineCopy, tempFile);
									}
								}
							}
							if (!deleteNum)
							{
								fprintf(stderr, "No Staff record found! Kindly enter a valid Staff ID!\nSorry for the inconvenience caused.\n");
							}
							deleteNum = 0; // Resetting deleteNum for future use
							fclose(tempFile);
						}
						fclose(file);
						remove(fileName);
						rename("temp-stf.csv", fileName);
						// Refactor the IDs of the staff
						staffCount = countTotalMembers(fileName);
						FILE *mainFile = fopen(fileName, "r");
						if (mainFile)
						{
							FILE *tempFile2 = fopen("temp2-stf.csv", "w");
							if (tempFile2)
							{
								char fileLine2[FILE_INPUT_BUFFER];
								staff staffDetails2;
								for (int i = 0; i < staffCount; i++)
								{
									fgets(fileLine2, FILE_INPUT_BUFFER, mainFile);
									char fileLine3[FILE_INPUT_BUFFER];
									strcpy(fileLine3, fileLine2); // This is just for safety purpose, it is not necessary
									fileLine2[strcspn(fileLine2, "\n")] = '\0';
									parseStaff(fileLine2, &staffDetails2);
									fprintf(tempFile2, "%d,%s,%d,%.2f\n", i + 1, staffDetails2.name, staffDetails2.role, staffDetails2.salary);
								}
								fclose(tempFile2);
							}
							fclose(mainFile);
							remove(fileName);									 // Deleting the original file
							rename("temp2-stf.csv", fileName); // Replacing the original file with the updated temp file
						}
					}
					else
					{
						fprintf(stderr, "Could not read Staff data from database.\n");
					}
					staffCount = countTotalMembers(fileName); // Recounting the total members
					repeat = inputForInt("Do you want to delete another record?(Press 1 to continue or 0 to exit):");
				} while (repeat == 1);
				repeat = 0;
			}
			else
			{
				fprintf(stderr, "Please First Enter data of Staff, then come back to access the details of your college's Staff.\n");
			}
			break;
		default:
			printf("Enter a valid number between 1 to 4!\n");
			break;
		}
		found = 0;
		repeat = inputForInt("Do you want to continue with Staff portal or go back?\n\t(Enter 1 to continue or press any key to go back!): ");
	} while (repeat == 1);
}
