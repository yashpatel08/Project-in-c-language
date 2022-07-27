#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
static int n = 0;
struct STUDENT
{
	int age, roll_no, maths, physics, chemistry, total;
	char name[10];
	float avg;
};

void add();
void password();
void displayAll();
void record();
void del();
void marksheet();
void modify();
int main()
{
	int i, count = 0, a, n = 0, r, m, ms;
	printf("\n\t\t\t\t\t\t   STUDENT RECORD BOOK\n");
	printf("\n\t\t\t\t========================================================\n");
	while (1) // here 1 is used to run loop infinity timex
	{
		printf("\nchoose an option below");
		printf("\n1.Add a record");
		printf("\n2.Delete a record");
		printf("\n3.Modify a record");
		printf("\n4.Generate Mark Sheet");
		printf("\n5.Search a record");
		printf("\n6.Display all records");
		printf("\n7.exit");
		printf("\n----------------------\n");
		scanf("%d", &a);
		switch (a)
		{
		case 1:
		{
			password();
			add();
			break;
		}
		case 2:
		{
			password();
			del();
			break;
		}
		case 3:
		{
			password();
			modify();
			break;
		}
		case 4:
		{
			marksheet();
			break;
		}
		case 5:
		{
			record();
			break;
		}
		case 6:
		{
			displayAll();
			break;
		}
		case 7:
		{
			exit(0); // it will terminate loop //
		}
		}
	}
}
void add()
{
	int i;
	struct STUDENT s;
	int size;
	FILE *fp;
	size = sizeof(s);
	fp = fopen("MINI_PROJECT_IN_C.DAT", "ab"); // it will append by binary
	printf("\nEnter roll no for record:-");
	scanf("%d", &s.roll_no);
	printf("\nEnter name:-");
	scanf("%s", s.name);
	printf("\nEnter age:-");
	scanf("%d", &s.age);
	printf("\nEnter maths marks:-");
	scanf("%d", &s.maths);
	printf("\nEnter physics marks:-");
	scanf("%d", &s.physics);
	printf("\nEnter chemistry marks:-");
	scanf("%d", &s.chemistry);
	s.total = s.maths + s.physics + s.chemistry; // variable is taken to total marks of all subject
	s.avg = s.total / 3;						 // to get avg
	fwrite(&s, size, 1, fp);					 // to save data file
	fclose(fp);									 // file close
	printf("\nRecord successfully added");
}
void password()
{
	FILE *fp;
	int i = 0, count = 0;
	printf("\nEnter password:-");
	char ch[6], c[6], a, b;
	fp = fopen("password.txt", "r");
	while ((b = getc(fp)) != EOF) // eof means end of file
	{
		c[i] = b;
		i++;
	}
	for (i = 0; i < 6; i++)
	{
		a = getch();
		ch[i] = a;
		// printf("*"); hide password by assterik
		printf("%c", a); // show password by character
		if (ch[i] == c[i])
		{
			count++;
		}
	}
	if (count == 6)
	{
		printf("\nLogin success");
	}
	else
	{
		printf("\nLogin failed re-Enter password");
		password();
	}
	fclose(fp);
}
void displayAll()
{
	FILE *fp;
	struct STUDENT s;
	fp = fopen("MINI_PROJECT_IN_C.DAT", "rb");
	printf("\t\t All Student Details\n\n");
	printf("\n--------------------------------------------------------\n");
	while (1)
	{
		fread(&s, sizeof(s), 1, fp); // to read file and show data of student
		if (feof(fp))				 // to print file till the end of the file
		{
			break;
		}
		printf("\nRollno:%d\t", s.roll_no);
		printf("Name:%s\t", s.name);
		printf("Age:%d\t", s.age);
		printf("Total:%d\n", s.total);
	}
	printf("--------------------------------------------------------\n\n");
	fclose(fp);
}
void record()
{
	FILE *fp;
	struct STUDENT s;
	int id, found = 0;
	fp = fopen("MINI_PROJECT_IN_C.DAT", "rb");
	printf("\nEnter the student roll no:");
	scanf("%d", &id);
	while (1)
	{
		fread(&s, sizeof(s), 1, fp);
		if (feof(fp)) // to print file till the end of the file
		{
			break;
		}
		if (s.roll_no == id)
		{
			found = 1; // print when data founded in data base
			printf("\n-------------------------------------------------------\n\n");
			printf("\t\t Student Record of %d\n\n", s.roll_no);
			printf("\n--------------------------------------------------------\n\n");
			printf("Rollno:%d\t", s.roll_no);
			printf("name:%s\t", s.name);
			printf("Age:%d\t", s.age);
			printf("Total:%d\n", s.total);
			printf("\n--------------------------------------------------------\n\n");
		}
	}
	if (found == 0)
	{
		printf("\nSorry No Record Found");
	}
	fclose(fp);
}
void del()
{
	FILE *fp, *fp1;
	struct STUDENT s, s1;
	int id, found = 0;
	fp = fopen("MINI_PROJECT_IN_C.DAT", "rb");
	fp1 = fopen("temp.dat", "wb"); // created when the data got deleted from the database.
	printf("\nEnter student roll no you want to Delete:");
	scanf("%d", &id);
	while (1) // here 1 is used to run loop infinity time
	{
		fread(&s, sizeof(s), 1, fp);
		if (feof(fp)) // run file to end of file
		{
			break;
		}
		if (s.roll_no == id)
		{
			found = 1;
		}
		else
		{
			fwrite(&s, sizeof(s), 1, fp1);
		}
	}
	fclose(fp);
	fclose(fp1);
	if (found == 0)
	{
		printf("Sorry No Record Found\n\n");
	}
	else
	{
		fp = fopen("MINI_PROJECT_IN_C.DAT", "wb");
		fp1 = fopen("temp.dat", "rb");

		while (1)
		{
			fread(&s, sizeof(s), 1, fp1);

			if (feof(fp1))
			{
				break;
			}
			fwrite(&s, sizeof(s), 1, fp);
		}
	}
	fclose(fp);
	fclose(fp1);
}
void marksheet()
{
	FILE *fp;
	struct STUDENT s;
	int id, found = 0;
	fp = fopen("MINI_PROJECT_IN_C.DAT", "rb");
	printf("\nEnter the student roll no:");
	scanf("%d", &id);
	while (1)
	{
		fread(&s, sizeof(s), 1, fp);
		if (feof(fp))
		{
			break;
		}
		if (s.roll_no == id)
		{
			found = 1;
			printf("\n-------------------------------------------------------\n\n");
			printf("\t\t Student Marksheet of %d\n\n", s.roll_no);
			printf("\n-------------------------------------------------------\n\n");
			printf("Rollno:%d\t", s.roll_no);
			printf("Name:%s\t", s.name);
			printf("Maths:%d\t", s.maths);
			printf("Physics:%d\t", s.physics);
			printf("Chemistry:%d\t", s.chemistry);
			printf("Total:%d\t", s.total);
			printf("Average:%.2f\n", s.avg);
			printf("\n-------------------------------------------------------\n\n");
		}
	}
	if (found == 0)
	{
		printf("\nSorry No Record Found");
	}
	fclose(fp);
}
void modify()
{
	FILE *fp, *fp1;
	struct STUDENT s;
	int id, found = 0;
	fp = fopen("MINI_PROJECT_IN_C.DAT", "rb");
	fp1 = fopen("temp.dat", "wb");
	printf("\n-------------------------------------------------------\n\n");
	printf("\nEnter student roll no you want to Modify:");
	scanf("%d", &id);
	while (1)
	{
		fread(&s, sizeof(s), 1, fp);
		if (feof(fp))
		{
			break;
		}
		if (s.roll_no == id)
		{
			found = 1;
			printf("Enter roll no for record\n");
			scanf("%d", &s.roll_no);
			// fflush(stdin);
			printf("Enter name:-");
			scanf("%s", s.name);
			printf("\nEnter age:-");
			scanf("%d", &s.age);
			printf("\nEnter maths marks:-");
			scanf("%d", &s.maths);
			printf("\nEnter physics marks:-");
			scanf("%d", &s.physics);
			printf("\nEnter chemistry marks:-");
			scanf("%d", &s.chemistry);
			s.total = s.maths + s.physics + s.chemistry;
			s.avg = s.total / 3;
			fwrite(&s, sizeof(s), 1, fp1);
		}
		else
		{
			fwrite(&s, sizeof(s), 1, fp1);
		}
	}
	fclose(fp);
	fclose(fp1);
	if (found == 0)
	{
		printf("Sorry No Record Found\n\n");
	}
	else
	{
		fp = fopen("MINI_PROJECT_IN_C.DAT", "wb");
		fp1 = fopen("temp.dat", "rb");

		while (1)
		{
			fread(&s, sizeof(s), 1, fp1);
			if (feof(fp1))
			{
				break;
			}
			fwrite(&s, sizeof(s), 1, fp);
		}
	}
	fclose(fp);
	fclose(fp1);
}