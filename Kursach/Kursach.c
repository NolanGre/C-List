#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>      // ���������� ����������� ����� windows.h, ��� SetConsoleCP() �� SetConsoleOutputCP()
#include <stdbool.h>

// ��������� �������
void inputPacient();	
void GetElement();
void DeleteElement();

//void PutStrings(int n);         ��������
//void FreeStrings(int n);
//void ChangeStrings(int n);


struct Pacient* start = NULL;          //�������� ����-��������� �� �������/����� ������
struct Pacient* end = NULL;
struct Pacient* temp = NULL;       //������ ����� ��� ���������� ��������� �� �������

struct Pacient {      //��� ��������� 
	char name[25];
	int card;
	char type_work[25];
	int cost;
	bool check;      //������ ������� ����� bool (������� ����� ���� �������� ����� ���� �������)
	int debt_sum;

	struct Pacient* next;	//�������� �� ��������� �������
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
		puts("\n���� 䳿");
		puts("1 - ��������� ��������");            //rework
		puts("2 - ��������� ��������");
		/*puts("3 - ��������� ����������� �����");
		puts("4 - ��������� ��� �����");
		puts("5 - ��������� ������ ��� �볺��� �� �������� ��������;");
		puts("6 - ��������� ������ ��� �������� �� ������ ���� � �������� �������������");
		puts("7 - ��������� � ���� ������ ��� ��������, �� �� ����� ������������� �� ��������");
		puts("8 - C��������� �� ����� ������������� �� ��������");*/
		puts("0 - �����");
		// ���� ������ 䳿
		puts("������ ��� ������ 䳿");
		scanf("%d", &kod);
		printf("\n������� ��� %d \n", kod);
		// ������ ������� ����� ������ 䳿
		switch (kod)
		{
			case 1: GetElement(); break;
			case 2: DeleteElement(); break;
			/*case 3: ChangeStrings(); break;
			case 4: testI(); break;
			case 5: testF(); break;
			case 6: testA(); break;
			case 7: testS(); break;
			case 8: testD(); break;*/
			case 0: exit(1); break;
		}
	}
	return EXIT_SUCCESS; // EXIT_SUCCESS - ���������, �� ������ ������ ��������� ��������}
}

// ������� ��������� ��������
void GetElement() //��������� ��� ������� �� ������
{
	if (start == NULL) {       //���� �� ������ �������
		
		start = (struct Pacient*)malloc(sizeof(struct Pacient));    //�������� ���'��� � ������� ������
		if (start == NULL) {                         //���������� ���'���
			puts("Error with allocation memory");
			return;               //���������� ������� � ��� �������
		}
		
		end = start;   //������� ����� ������	
		
		end->next = NULL;    //��������� �������� �������� �������� �� 0

		inputPacient();     //������� 

		return;       //���������� ������� 
	}

	if (start != NULL) {  //���� �� �� ������ �������

		temp = start;    //�����'������� �������
		
		start = (struct Pacient*)malloc(sizeof(struct Pacient));    //�������� ���'��� � ������� ������
		if (start == NULL) {                         //���������� ���'���
			puts("Error with allocation memory");
			return;               //���������� ������� � ��� �������
		}

		start->next = temp;  //����� ������� ����� �� �������

		inputPacient();    //������� ����

		return;
	}
}
		

void inputPacient()      //������ ������� ��� ����� ������ � ������
{
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
	if (start == NULL) {		//�������� �� �������� �������, ����� � ����� 
		printf("\nNo element to delete\n");
		return;
	}

	puts("Delete from: start [1]	search [2] ");   //���� �����������
	scanf("%d", &delete_kod);
	
	if (delete_kod == 1) {

		temp = start->next;

		printf("\nRemove : %s\n", start->name);
		
		free(start);

		start = temp;   //���� ������� ������� ��� ���������, start ���� ��������� �� NULL
									//��� ��������� ������ �������� �� ���� ��������� 
		if (start == NULL) {
			printf("---You delete last element---");
			return;
		}
		return;
	}

	if (delete_kod == 2) {         // 
		struct Pacient* cur = start;    //��������
		struct Pacient* prev = start;    //���������

		bool button = true;      //�������� ��� �����(���������� prev)
		char prompt[25];

		printf("\nEnter surname for search: ");
		scanf("%25s", &prompt);
		while (1) {	
			if (cur == NULL) {        //�������� �� �������� �������, ����� � ����� 
				printf("\nNo coincidance\n");
				return;
			}

			if (!strcmp(cur->name, prompt)) {  		//���� �������, ��

				temp = cur->next;

				if (temp == NULL) puts("\nDeleted element from end");      //�������� �� ��������� �������

				if ((temp == NULL) && (start == cur)) {   //���� ��������� ������� �������
					puts("\nDeleteded last element\n");

					free(cur);             // ��������� 

					start = NULL;            //����� ��������� ����� � �����
					end = NULL;

					return;
				}

				printf("\nRemove : %s\n", cur->name);

				free(cur);

				prev->next = temp;

				return;
			}
			
			cur = cur->next;        //������� cur

			if (button) {           //������ ���������� ��� prev
				button = false;
				continue;
			}	
			prev = prev->next;			
		}
		return;
	}
}