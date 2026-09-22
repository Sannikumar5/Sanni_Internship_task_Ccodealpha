#include <stdio.h>
#include <string.h>

struct Student
{
    int roll;
    char name[50];
    float marks;
};

void addStudent()
{
    struct Student s;
    FILE *fp;

    fp = fopen("students.dat", "ab");

    if(fp == NULL)
    {
        printf("File could not be opened.\n");
        return;
    }

    printf("Enter Roll Number: ");
    scanf("%d", &s.roll);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);

    fclose(fp);

    printf("Student added successfully.\n");
}

void displayStudents()
{
    struct Student s;
    FILE *fp;

    fp = fopen("students.dat", "rb");

    if(fp == NULL)
    {
        printf("No student records found.\n");
        return;
    }

    printf("\n--- Student Records ---\n");

    while(fread(&s, sizeof(s), 1, fp))
    {
        printf("Roll  : %d\n", s.roll);
        printf("Name  : %s\n", s.name);
        printf("Marks : %.2f\n", s.marks);
        printf("----------------------\n");
    }

    fclose(fp);
}

void searchStudent()
{
    struct Student s;
    FILE *fp;
    int roll, found = 0;

    fp = fopen("students.dat", "rb");

    if(fp == NULL)
    {
        printf("No records found.\n");
        return;
    }

    printf("Enter Roll Number to search: ");
    scanf("%d", &roll);

    while(fread(&s, sizeof(s), 1, fp))
    {
        if(s.roll == roll)
        {
            printf("\nStudent Found!\n");
            printf("Roll  : %d\n", s.roll);
            printf("Name  : %s\n", s.name);
            printf("Marks : %.2f\n", s.marks);

            found = 1;
            break;
        }
    }

    if(!found)
        printf("Student not found.\n");

    fclose(fp);
}

void deleteStudent()
{
    struct Student s;
    FILE *fp, *temp;
    int roll, found = 0;

    fp = fopen("students.dat", "rb");
    temp = fopen("temp.dat", "wb");

    if(fp == NULL)
    {
        printf("No records found.\n");
        return;
    }

    printf("Enter Roll Number to delete: ");
    scanf("%d", &roll);

    while(fread(&s, sizeof(s), 1, fp))
    {
        if(s.roll == roll)
        {
            found = 1;
        }
        else
        {
            fwrite(&s, sizeof(s), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if(found)
        printf("Student deleted successfully.\n");
    else
        printf("Student not found.\n");
}

void updateStudent()
{
    struct Student s;
    FILE *fp;
    int roll, found = 0;

    fp = fopen("students.dat", "rb+");

    if(fp == NULL)
    {
        printf("No records found.\n");
        return;
    }

    printf("Enter Roll Number to update: ");
    scanf("%d", &roll);

    while(fread(&s, sizeof(s), 1, fp))
    {
        if(s.roll == roll)
        {
            printf("Enter New Name: ");
            scanf(" %[^\n]", s.name);

            printf("Enter New Marks: ");
            scanf("%f", &s.marks);

            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);

            found = 1;
            break;
        }
    }

    fclose(fp);

    if(found)
        printf("Student updated successfully.\n");
    else
        printf("Student not found.\n");
}

int main()
{
    int choice;

    do
    {
        printf("\n===== STUDENT MANAGEMENT SYSTEM =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                printf("Program exited.\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while(choice != 6);

    return 0;
}