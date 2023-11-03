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

struct Country* head = NULL;    // основа стеку 

struct Country* p = NULL;   //поточний покажчик
struct Country* tmp = NULL;   //буфер

void addCountry();
void deleteCountry();
void searchByPopulationNum();

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
		puts("3 - Пошук по кількості населення");
		/*puts(4 - );
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
	return EXIT_SUCCESS;  // EXIT_SUCCESS - константа, що означає успішне виконання програми}
}



void addCountry() {

	tmp = head;

	if ((head = (struct Country*)malloc(sizeof(struct Country))) == NULL) { //перевірка на виділення пам'яті
		puts("Помилка");
		return;
	}

	if (tmp == NULL) puts("Добавлено перший елемент");  //виводимо доп. інформацію для користувача 

	head->next = tmp;

	//вводимо дані
	printf("Введіть карїну: ");
	scanf("%30s", &(head->country_name));

	printf("Введіть столицю: ");
	scanf("%30s", &(head->country_capital));

	printf("Введіть кількість мешканців: ");
	scanf("%d", &(head->country_population));	

	printf("Введіть площу карїни: ");
	scanf("%d", &(head->country_area));

	printf("Введіть мову: ");
	scanf("%30s", &(head->country_language));

}

void deleteCountry() {

	if (head == NULL) {
		puts("Немає елементів для видалення");
		return;
	}

	tmp = head->next;

	printf("\nВидалення: %s\n", head->country_name);
	free(head);

	head = tmp;

	if (head == NULL) {
		puts("\nОстанній елемент був видалений");
		return;
	}
}

void searchByPopulationNum() {         //пошук країн з кількістю жителів більше заданої

	if (head == NULL) {
		puts("Cписок порожній");
		return;
	}

	int search;
	bool check = false;

	printf("\nВведіть кількість жителів для пошуку: ");
	scanf("%d", &search);

	p = head;

	while (1) {

		if (p->country_population > search) {
			printf("\nКраїна: %s\n", p->country_name);
			printf("Столиця: %s\n", p->country_capital);
			printf("Кількість населення: %d\n", p->country_population);
			printf("Площа: %d\n", p->country_area);
			printf("Мова: %s\n", p->country_language);

			check = true;
		}
		
		p = p->next;

		if (p == NULL) {
			if(check == false) puts("Немає співпадінь");
			return;
		}
	}
}