#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>      // ���������� ����������� ����� windows.h, ��� SetConsoleCP() �� SetConsoleOutputCP()
#include <stdbool.h>

// ��������� �������
void inputPacient();
void GetElement();
void DeleteElement();
void ChangeElement();
void showAllElement();
void showByTheName();
void showDebtor();
void deleteNoDebtor();
void sortElement();

void debug();

void saveFile();
void loadFile();


struct Pacient* start = NULL;          //�������� ����-��������� �� �������/����� ������
struct Pacient* end = NULL;
struct Pacient* temp = NULL;       //������ ����� ��� ���������� ��������� �� �������

struct Pacient {
	char name[25];
	int card;
	char type_work[25];
	int cost;
	bool check;
	int debt_sum;

	struct Pacient* next;
};

// ������� ������� ��������
int main()
{
	SetConsoleCP(1251); //������������ ��������� Windows-1251 � ���� ��������
	SetConsoleOutputCP(1251); // ������������ ��������� Windows-1251 � ���� ���������
	// ����� ������ �� ���� Lucida Console

	int kod; // ����� ��� ����� 䳿 � ����
	while (1)
	{
		// ���� ��������
		puts("\n        ���� 䳿");
		printf("------------------------\n");
		puts("1 - ��������� ��������");
		puts("2 - ��������� ��������");
		puts("3 - ����������� ��������");
		printf("------------------------\n");
		puts("4 - ��������� ��� �����");
		puts("5 - ��������� ������ ��� �볺��� �� �������� ��������;");
		puts("6 - ��������� ������ ��� �������� �� ������ ���� � �������� �������������");
		printf("------------------------\n");
		puts("7 - ��������� � ���� ������ ��� ��������, �� �� ����� ������������� �� ��������");
		puts("8 - C��������� �� ����� ������������� �� ��������");
		printf("------------------------\n");
		puts("11 - �������� ���");
		puts("12 - ����������� ���");
		printf("------------------------\n");
		puts("0 - �����");
		// ���� ������ 䳿
		puts("\n������ ��� ������ 䳿");
		scanf("%d", &kod);
		printf("\n������� ��� %d \n", kod);
		// ������ ������� ����� ������ 䳿
		switch (kod)
		{
		case 1: GetElement(); break;
		case 2: DeleteElement(); break;
		case 3: ChangeElement(); break;
		case 4: showAllElement(); break;
		case 5: showByTheName(); break;
		case 6: showDebtor(); break;
		case 7: deleteNoDebtor(); break;
		case 8: sortElement(); break;
		case 9: debug(); break;///////////////////
		case 11: saveFile(); break;
		case 12: loadFile(); break;
		case 0: exit(1); break;
		}
	}
	return EXIT_SUCCESS; // EXIT_SUCCESS - ���������, �� ������ ������ ��������� ��������}
}

void GetElement() {

	temp = start;   //�������� �������

	start = (struct Pacient*)malloc(sizeof(struct Pacient));    //�������� ���'��� � ������� ������
	if (start == NULL) {                         //���������� ���'���
		puts("Error with allocation memory");
		return;               //���������� ������� � ��� �������
	}

	if (temp == NULL) end = start;  //������� �����

	start->next = temp;    //������� ��������� �������

	inputPacient();
}


void inputPacient() {
	char debt;
	printf("Enter surname: ");
	scanf("%25s", &(start->name));

	printf("Enter account card number: ");
	scanf("%d", &(start->card));

	printf("Enter type of work: ");
	scanf("%25s", &(start->type_work));

	printf("Enter cost of the work: ");
	scanf("%d", &(start->cost));

	printf("Enter payment note (If a person has no debt [Y]  If debtor [N]): ");
	scanf(" %c", &debt);

	if (debt == 'Y') {

		start->check = true;
		start->debt_sum = 0;

		puts("	No debt\n");
	}
	else {

		start->check = false;

		printf("Enter sum of debt: ");
		scanf("%d", &(start->debt_sum));
	}
	return;
}

void DeleteElement() {

	int delete_kod;
	puts("Delete from: start [1]	search [2] ");
	scanf("%d", &delete_kod);

	if (delete_kod == 1) {
		if (start == NULL) {
			printf("No element for deleting");
			return;
		}

		temp = start->next;

		printf("\nRemove : %s\n", start->name);

		free(start);

		start = temp;   //���� ������� ������� ��� ���������, start ���� ��������� �� NULL
		//��� ��������� ������ �������� �� ���� ��������� 
		if (start == NULL) {
			puts("---You delete last element---");
			end = start;
		}
		return;
	}

	if (delete_kod == 2) {         //  
		struct Pacient* cur = start;    //��������
		struct Pacient* prev = start;    //���������

		bool button = true;
		char prompt[25];

		printf("\nEnter surname for search: ");
		scanf("%25s", &prompt);
		while (1) {
			if (cur == NULL) {        //�������� �� �������� �������, ����� � ����� 
				printf("\nNo coincidence\n");
				return;
			}

			if (!strcmp(cur->name, prompt)) {

				temp = cur->next;

				if (temp == NULL) {
					puts("\nDeleted 'End' element");
				}
				printf("\nRemove : %s\n", cur->name);

				if (end == start) puts("\nLast element has been deleted");

				if (start == cur) start = temp;
				if (end == cur) end = prev;

				free(cur);

				prev->next = temp;

				break;
			}

			cur = cur->next;

			if (button) {
				button = false;
				continue;
			}
			prev = prev->next;
		}
		return;
	}
}

void ChangeElement() {

	char prompt[25];

	struct Pacient* cur = start;

	printf("\nEnter surname for change: ");
	scanf("%25s,", &prompt);

	while (1) {
		if (cur == NULL) {   //����� � �����
			printf("\nNo coincidence");
			return;
		}

		if (!strcmp(cur->name, prompt)) {
			printf("\n	-Enter element data again-\n");

			char debt;
			printf("Enter surname: ");
			scanf("%25s", &(cur->name));

			printf("Enter account card number: ");
			scanf("%d", &(cur->card));

			printf("Enter type of work: ");
			scanf("%25s", &(cur->type_work));

			printf("Enter cost of the work: ");
			scanf("%d", &(cur->cost));

			printf("Enter payment note (If a person has no debt [Y]  If debtor [N]): ");
			scanf(" %c", &debt);

			if (debt == 'Y') {
				cur->debt_sum = 0;

				cur->check = true;

				puts("	No debt\n");
			}
			else {
				cur->check = false;

				printf("Enter sum of debt: ");
				scanf("%d", &(cur->debt_sum));
			}

			return;
		}	
		cur = cur->next;
	}
}


void showAllElement() {

	struct Pacient* cur = start;

	while (cur != NULL) {

		printf("\n---------------------------------------\n");
		printf("| Surname:   %-25s|\n", cur->name);
		printf("| Account card number: %-15d|\n", cur->card);
		printf("| Type of work: %-22s|\n", cur->type_work);
		printf("| Cost of the work: %-18d|\n", cur->cost);

		(cur->check) ? printf("|%-37s|\n", " Patient is not a debtor ") : printf("|%-37s|\n", " Patient debtor ");  //����������� ��������� ��������

		printf("| Sum of debt: %-23d|", cur->debt_sum);

		cur = cur->next;
	}
	printf("\n---------------------------------------\n");
}



void showByTheName() {

	char prompt[25];
	struct Pacient* cur = start;

	printf("\nEnter surname for search: ");
	scanf("%25s,", &prompt);

	while (cur != NULL) {

		if (!strcmp(cur->name, prompt)) {

			printf("\n---------------------------------------\n");
			printf("| Surname:   %-25s|\n", cur->name);
			printf("| Account card number: %-15d|\n", cur->card);
			printf("| Type of work: %-22s|\n", cur->type_work);
			printf("| Cost of the work: %-18d|\n", cur->cost);

			(cur->check) ? printf("|%-37s|\n", " Patient is not a debtor ") : printf("|%-37s|\n", " Patient debtor ");  //����������� ��������� ��������

			printf("| Sum of debt: %-23d|", cur->debt_sum);
			printf("\n---------------------------------------\n");

			return;
		}
		cur = cur->next;
	}

	printf("\nNo coincidence\n");
}


void saveFile() {

	FILE* f = fopen("save.bin", "wb");
	if (f == NULL) {
		printf("\nThe file was opened incorrectly\n");
		return;
	}

	struct Pacient* cur = start;

	while (cur != NULL) {

		fwrite(cur, sizeof(struct Pacient), 1, f);

		cur = cur->next;
	}

	fclose(f);
}


void loadFile() {

	FILE* f = fopen("save.bin", "rb");
	if (f == NULL) {
		printf("\nThe file was opened incorrectly / the file does not exist\n");
		return;
	}

	if (start != NULL) printf("\nThe data was added to the existing data\n");

	while (1) {

		temp = start;

		if ((start = (struct Pacient*)malloc(sizeof(struct Pacient))) == NULL) {
			puts("Error with allocation memory");
			return;
		}

		fread(start, sizeof(struct Pacient), 1, f);

		if (temp == NULL) end = start;

		if (feof(f)) {  //�������� �� EOF
			free(start);   //��������� ����� ���������
			start = temp;   //���������� start
			break;   
		}

		start->next = temp;
	}

	fclose(f);
}


void showDebtor() {

	struct Pacient* cur = start;

	char prompt_type[25];
	int prompt_debt;

	printf("\nTotal debt is more than: ");
	scanf("%d,", &prompt_debt);

	printf("\nEnter type of work for search: ");
	scanf("%25s,", &prompt_type);

	while (cur != NULL) {

		if (cur->check) {    //³������ �������� ��� �����

			cur = cur->next;
			continue;
		}

		if ((cur->debt_sum > prompt_debt) && !strcmp(cur->type_work, prompt_type)) {  

			printf("\n---------------------------------------\n");
			printf("| Surname:   %-25s|\n", cur->name);
			printf("| Account card number: %-15d|\n", cur->card);
			printf("| Type of work: %-22s|\n", cur->type_work);
			printf("| Cost of the work: %-18d|\n", cur->cost);

			(cur->check) ? printf("|%-37s|\n", " Patient is not a debtor ") : printf("|%-37s|\n", " Patient debtor ");  //����������� ��������� ��������

			printf("| Sum of debt: %-23d|", cur->debt_sum);
			printf("\n---------------------------------------\n");

		}

		cur = cur->next;
	}
	puts("\nEnd");
}


void deleteNoDebtor() {

	struct Pacient* cur = start;
	struct Pacient* prev = start;

	while (cur != NULL) {

		if (cur->check) {

			temp = cur->next;

			printf("\nRemove : %s\n", cur->name);

			if (start == cur) {

				start = temp;

				free(cur);

				cur = start;
				prev = start;

				continue;
			}

			if (end == cur) end = prev;

			free(cur);

			prev->next = temp;
			cur = prev;
		}

		prev = cur;   //������ ���� �������
		cur = cur->next;
	}
}



void sortElement() {

	struct Pacient* cur = start;
	struct Pacient* prev = start;
	size_t size = 0;

	while (cur != NULL) {   //  ��������� ������� �������� 
		size++;
		cur = cur->next;
	}

	printf("SIZE: %zu\n", size);

	for (int i = 0; i < size - 1; i++) {  //��� ������ ����� ��������������� ���� ���������� (��������� Merge Sort)

		cur = start;
		prev = start;

		while (cur->next != NULL) {   //������� ���������

			if (cur->debt_sum > cur->next->debt_sum) {

				temp = cur->next->next;
				cur->next->next = cur;

				if (cur != start) prev->next = cur->next;
				else {                    //(cur == start)
					start = cur->next;
					prev = start;    // cur->next;
				}
				if (cur->next == end) end = cur;

				cur->next = temp;
				
				continue;
			}

			prev = cur;
			cur = cur->next;
		}
	}
}


void debug() {

	printf("\nStart: %s", start->name);
	printf("\nEnd: %s", end->name);
	/////////////////////////////////////////////////
	struct Pacient* cur = start;
	size_t size = 0;
	while (cur != NULL) {   //  ��������� ������� �������� 
		size++;
		cur = cur->next;
	}
	printf("\nSIZE: %zu\n", size);
}