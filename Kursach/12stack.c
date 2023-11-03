#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>      
#include <stdbool.h>

struct Country {
	char country_name[30];
	char country_capital[30];
	int	country_population;
	int country_area;
	char country_language[30];

	struct Country* next;
};

struct Country* head = NULL;    // ������ ����� 

struct Country* p = NULL;   //�������� ��������
struct Country* tmp = NULL;   //�����

void addCountry();
void deleteCountry();
void searchByPopulationNum();

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
		puts("3 - ����� �� ������� ���������");
		/*puts(4 - );
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
		case 1: addCountry(); break;
		case 2: deleteCountry(); break;
		case 3: searchByPopulationNum(); break;
			//case 4: testI(); break;
			//case 5: testF(); break;
			//case 6: testA(); break;
			//case 7: testS(); break;
			//case 8: testD(); break;
		case 0: exit(1); break;
		}
	}
	return EXIT_SUCCESS;  // EXIT_SUCCESS - ���������, �� ������ ������ ��������� ��������}
}



void addCountry() {

	tmp = head;

	if ((head = (struct Country*)malloc(sizeof(struct Country))) == NULL) { //�������� �� �������� ���'��
		puts("�������");
		return;
	}

	if (tmp == NULL) puts("��������� ������ �������");  //�������� ���. ���������� ��� ����������� 

	head->next = tmp;

	//������� ���
	printf("������ �����: ");
	scanf("%30s", &(head->country_name));

	printf("������ �������: ");
	scanf("%30s", &(head->country_capital));

	printf("������ ������� ���������: ");
	scanf("%d", &(head->country_population));	

	printf("������ ����� �����: ");
	scanf("%d", &(head->country_area));

	printf("������ ����: ");
	scanf("%30s", &(head->country_language));

}

void deleteCountry() {

	if (head == NULL) {
		puts("���� �������� ��� ���������");
		return;
	}

	tmp = head->next;

	printf("\n���������: %s\n", head->country_name);
	free(head);

	head = tmp;

	if (head == NULL) {
		puts("\n������� ������� ��� ���������");
		return;
	}
}

void searchByPopulationNum() {         //����� ���� � ������� ������ ����� ������

	if (head == NULL) {
		puts("C����� �������");
		return;
	}

	int search;
	bool check = false;

	printf("\n������ ������� ������ ��� ������: ");
	scanf("%d", &search);

	p = head;

	while (1) {

		if (p->country_population > search) {
			printf("\n�����: %s\n", p->country_name);
			printf("�������: %s\n", p->country_capital);
			printf("ʳ������ ���������: %d\n", p->country_population);
			printf("�����: %d\n", p->country_area);
			printf("����: %s\n", p->country_language);

			check = true;
		}
		
		p = p->next;

		if (p == NULL) {
			if(check == false) puts("���� ��������");
			return;
		}
	}
}