#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>      
#include <stdbool.h>

struct Animal {

	char animal_name[25];     //����� �������
	char animal_type[25];		//���
	char animal_class[25];		//����
	char animal_family[25];		  //��������
	char animal_kind[25];			//��
	char animal_species[25];		//���
	char animal_habitat[25];		//���������� ����������
	int  animal_population;       //���������� � ���

	struct Animal* next;
	struct Animal* prev;
};

struct Animal* end = NULL;
struct Animal* begin = NULL;

struct Animal* temp = NULL;
struct Animal* current = NULL;

bool check = true;      //�������� �� ������ �������

void GetAnimal();
void insertAnimal();
void DeleteAnimal();


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
			case 1: GetAnimal(); break;
			case 2: DeleteAnimal(); break;
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
}


// ������� ��������� ��������
void GetAnimal() {
	if (check) {			// �������� �� ����� ������ ������
		if((end = (struct Animal*)malloc(sizeof(struct Animal))) == NULL) {                         
			puts("Error with allocation memory");
			return;              
		}

		begin = end;  
		begin->next = NULL;    // ������� ��������� � ����� �����
		begin->prev = NULL;

		insertAnimal();    
		
		check = false;
		return;      
	}
	////////////////
	temp = end;   //�������� �� ������ �������
	
	if((end = (struct Animal*)malloc(sizeof(struct Animal))) == NULL) {                         
		puts("Error with allocation memory");
		return;               
	}
	
	end->next = temp;  
	temp->prev = end;
	end->prev = NULL;

	insertAnimal();    

	return;
}

void insertAnimal() {

	printf("Enter animal name: ");
	scanf("%25s", &(end->animal_name));

	printf("Enter animal type: ");
	scanf("%25s", &(end->animal_type));

	printf("Enter animal class: ");
	scanf("%25s", &(end->animal_class));

	printf("Enter animal family: ");
	scanf("%25s", &(end->animal_family));

	printf("Enter animal kind: ");
	scanf("%25s", &(end->animal_kind));

	printf("Enter animal species: ");
	scanf("%25s", &(end->animal_species));

	printf("Enter animal habitat: ");
	scanf("%25s", &(end->animal_habitat));

	printf("Enter animal population: ");
	scanf("%d", &(end->animal_population));
}

void DeleteAnimal() {   //�� ������
	char search[25];

	struct Animal* prev_t = NULL;
	struct Animal* next_t = NULL;

	current = end;   
	
	if (current == NULL) {		//if element == NULL  
		printf("\n no element to delete\n");    // ���� �������� ��� ���������
		return;
	}	

	printf("\nSearch: ");
	scanf("%25s", &search);	

	while (1) {   //if    current->next == NULL 
		
		if (!strcmp(current->animal_name, search)) {
			prev_t = current->prev;
			next_t = current->next;
			
			printf("\nDelete: %s\n", current->animal_name);

			free(current);

			if ((next_t == NULL) && (prev_t == NULL)) {  //�������� �������� ��������
				printf("Last element destroy");
				end = NULL;
				begin = NULL;
				check = true;
				return;
			}
			else if (prev_t == NULL) {   //�������� ��������� �������
				end = next_t;
				next_t->prev = NULL;
				printf("Deleted end border element");    // for test
				return;
			}
			else if (next_t == NULL) {      //�������� �� ���������
				begin = prev_t;
				prev_t->next = NULL;
				printf("Deleted begin border element");    // for test
				return;
			}
			
			prev_t->next = next_t;   //������� 
			next_t->prev = prev_t;
			return;
		}
		current = current->next;
		if (current == NULL) {
			printf("No comp at all");   //exit from loop
			return;
		}
	}
}
