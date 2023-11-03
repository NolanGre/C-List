#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>      

struct Pattern {		//stack
	char curse_name[30];  //������������ �����
	char teach_info[30];   //������� �� ������� ���������
	char language[30];      //�������� ����
	int lessons_num;       //������� ����� �� ������� 
	int educ_cost;        //������� �������� 
	int educ_period;       //��������� �������� 

	struct Pattern* next;
};

struct Pattern* head = NULL;
struct Pattern* temp = NULL;

void getPattern();
void enterForPattern();
void removePattern();

int main() {
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
		/*puts(3 - );
		puts(4 - );
		puts(5 - );
		puts(6 - );
		puts(7 - );
		puts(8 - );*/
		puts("0 - �����");
		// ���� ������ 䳿
		puts("������ ��� ������ 䳿");
		scanf("%d", &kod);
		printf("\n������� ��� %d \n", kod);
		// ������ ������� ����� ������ 䳿
		switch (kod)
		{
		case 1: getPattern(); break;
		case 2: removePattern(); break;
			//case 3: ChangeStrings(); break;
			//case 4: testI(); break;
			//case 5: testF(); break;
			//case 6: testA(); break;
			//case 7: testS(); break;
			//case 8: testD(); break;
		case 0: exit(1); break;
		}
	}
	return EXIT_SUCCESS;  // EXIT_SUCCESS - ���������, �� ������ ������ ��������� ��������}

	return 0;
}

void getPattern() {
	if(head == NULL) {
		if ((head = (struct Pattern*)malloc(sizeof(struct Pattern))) == NULL) {
			printf("\nError allocation memory\n");
			return 1;
		}
		head->next = NULL;    // ��������� �������� 1(������� �������)

		enterForPattern();

		return;
	}

	if (head != NULL) {
		temp = head;
		if ((head = (struct Pattern*)malloc(sizeof(struct Pattern))) == NULL) {
			printf("\nError allocation memory\n");
			return 1;
		}
		head->next = temp;

		enterForPattern();
	}
}

void enterForPattern() {

	printf("Enter curse name: ");
	scanf("%30s", &(head->curse_name));

	printf("Enter teach info: ");
	scanf("%30s", &(head->teach_info));

	printf("Enter landuage: ");
	scanf("%30s", &(head->language));

	printf("Enter lesson num: ");
	scanf("%d", &(head->lessons_num));

	printf("Enter educ cost: ");
	scanf("%d", &(head->educ_cost));

	printf("Enter educ period: ");
	scanf("%d", &(head->educ_period));
}

void removePattern() {  //��������� � ������� �����
	if (head == NULL) {
		printf("\nNo element to delete");

		return;
	}

	temp = head->next;

	printf("Remove: %s", head->curse_name);
	
	free(head);

	if (temp == NULL) {
		printf("\nLast pattern deleted\n");

	}
	head = temp;
	
}