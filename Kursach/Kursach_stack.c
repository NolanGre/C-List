#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>      

struct Pattern {		//stack
	char curse_name[30];  //найменування курсів
	char teach_info[30];   //призвіще та ініціали викладача
	char language[30];      //іноземна мова
	int lessons_num;       //кількість уроків на тиждень 
	int educ_cost;        //вартість навяання 
	int educ_period;       //тривалість навчання 

	struct Pattern* next;
};

struct Pattern* head = NULL;
struct Pattern* temp = NULL;

void getPattern();
void enterForPattern();
void removePattern();

int main() {
	SetConsoleCP(1251); //встановлення кодування Windows-1251 в потік введення
	SetConsoleOutputCP(1251); // встановлення кодування Windows-1251 в потік виведення
	// шрифт консолі має бути Lucida Console

	int kod; // зміння для вводу дії в меню
	while (1)
	{
		// меню програми
		puts("\nВибір дії");
		puts("1 - Додавання елемента");            //rework
		puts("2 - Видалення елемента");
		/*puts(3 - );
		puts(4 - );
		puts(5 - );
		puts(6 - );
		puts(7 - );
		puts(8 - );*/
		puts("0 - Вихід");
		// Вибір бажаної дії
		puts("Введіть код бажаної дії");
		scanf("%d", &kod);
		printf("\nОбраний код %d \n", kod);
		// Запуск функції згідно обраної дії
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
	return EXIT_SUCCESS;  // EXIT_SUCCESS - константа, що означає успішне виконання програми}

	return 0;
}

void getPattern() {
	if(head == NULL) {
		if ((head = (struct Pattern*)malloc(sizeof(struct Pattern))) == NULL) {
			printf("\nError allocation memory\n");
			return 1;
		}
		head->next = NULL;    // Занулюємо покажчик 1(останній елемент)

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

void removePattern() {  //видаляэмо з початку стеку
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