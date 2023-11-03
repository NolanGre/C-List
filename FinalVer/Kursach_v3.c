#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>      // Підключення заголовного файлу windows.h, для SetConsoleCP() та SetConsoleOutputCP()
#include <stdbool.h>

// Прототипи функцій
void inputPacient(struct Pacient* cur, bool mode, int item);
void getElement();
void deleteElement();
void changeElement();
void showAllElement();
void showByTheName();
void showDebtors();
void deleteNoDebtor();
void sortElement();
void swap(struct Pacient* cur);

void saveFile();
void loadFile();


struct Pacient* start = NULL;          // Глобальні змінні-покажчики на початок/кінець списку
struct Pacient* end = NULL;

struct Pacient* temp = NULL;       // Робимо буфер для збереження покажчику на елемент


struct Pacient {         // Cтруктура-нода
	char name[25];
	int card;
	char type_work[25];
	int cost;
	bool check;
	int debt_sum;

	struct Pacient* next;    // Покажчик для з'єднання елементів
};

// Головна функція програми
int main()
{
	SetConsoleCP(1251); // Встановлення кодування Windows-1251 в потік введення
	SetConsoleOutputCP(1251); // Встановлення кодування Windows-1251 в потік виведення
	// Шрифт консолі має бути Lucida Console

	int kod; // Зміння для вводу дії в меню
	int err;	//Змінна для перевірки вводу

	while (1)
	{
		// меню програми
		puts("\n        Menu");
		printf("------------------------\n");
		puts("1 - Add element");
		puts("2 - Delete element");
		puts("3 - Change element");
		printf("------------------------\n");
		puts("4 - Show all element");
		puts("5 - Show by the name");
		puts("6 - Show all debtors");
		printf("------------------------\n");
		puts("7 - Delete no debtor");
		puts("8 - Make sorted list");
		printf("------------------------\n");
		puts("11 - Save data");
		puts("12 - Load data");
		printf("------------------------\n");
		puts("10 - Clear console");
		puts("0 - Exit");


		// Вибір бажаної дії
		printf("\n\nВведіть код бажаної дії: ");
		while ((err = scanf("%d", &kod)) == 0 || (kod < 0 || kod > 12)) { 	//Поки невдалий ввод, або 0 > kod > 12

			while (getchar() != '\n');     //Очищення потоку (fflush для потоку stdin по стандарту С/C++ спричиняє "undefined behavior") 
			printf("\nInvalid input. Введіть код бажаної дії: ");
		}
		while (getchar() != '\n');     //Додаткове очищення потоку
		if (err == EOF) printf("Nothing more to read - and no number found\n"); //якщо scanf повернув EOF	   
		else printf("\nОбраний код %d \n", kod); 	//Можна використати тернарний оператор	


		// Запуск функції згідно обраної дії
		switch (kod)
		{
		case 1: getElement(); break;
		case 2: deleteElement(); break;
		case 3: changeElement(); break;
		case 4: showAllElement(); break;
		case 5: showByTheName(); break;
		case 6: showDebtors(); break;
		case 7: deleteNoDebtor(); break;
		case 8: sortElement(); break;
		case 10: system("cls"); break;    // Очищення консолі windows (DOS)
		case 11: saveFile(); break;
		case 12: loadFile(); break;
		case 0: exit(1); break;      // Вихід
		}
	}
	return EXIT_SUCCESS; 
}


void getElement() {  // Cтворення едементу 

	char cont;   // Змінна для продовження 

	temp = start;   //Записуємо початок

	if ((start = (struct Pacient*)malloc(sizeof(struct Pacient))) == NULL) {  //Виділяємо пам'ять в початку списку, перевіряємо пам'ять

		puts(" [ Error with allocation memory ] ");
		return;               //Перериваємо функцію в разі помилки
	}

	if (temp == NULL) end = start;  //Ставимо кінець

	inputPacient(start, true, 0);		//Функція вводу даних     or, if mod true => in func cur = start

	start->next = temp;    //Вказуємо наступний елемент

	//-------------------------------------------------------------
	printf("\nWanna continue? (y/n): ");
	while ((cont = getchar()) && (cont != 'y' && cont != 'n')) {  // Відносно безпечне введення 
		while (getchar() != '\n');
		printf("Invalid input. Wanna continue? (y/n): ");
	}
	while (getchar() != '\n');

	if (cont == 'y') getElement();   // Рекурсивне повторення
	//-------------------------------------------------------------
}


void inputPacient(struct Pacient* cur, bool mode, int item) {    // Функція підтримує 2 режими, повне введення, та вибіркове
	int err;  //Змінна для перевірки вводу

	if (item == 1 || mode) {

		printf("\nEnter surname: ");
		while (fgets(cur->name, sizeof(cur->name), stdin) == NULL) {   // Безпечне введення 

			while (getchar() != '\n');
			printf("Invalid input. Enter surname: ");
		}

		err = strcspn(cur->name, "\n");  // Пошук \n

		if (cur->name[err] == '\n') cur->name[err] = '\0';	// Видалення символу \n, якщо його нема - очищення потоку
		else
			while (getchar() != '\n');
	}
	///////////////////////////////////////////
	if (item == 2 || mode) {

		printf("Enter account card number: ");
		while ((err = scanf("%d", &(cur->card))) == 0 || cur->card < 1) { 	// Поки невдалий ввод, або card < 1

			while (getchar() != '\n');        // Очищення потоку
			printf("Invalid input. Enter account card number: ");
		}
		while (getchar() != '\n');
	}
	//////////////////////////////////////////
	if (item == 3 || mode) {

		printf("Enter type of work: ");
		while (fgets(cur->type_work, sizeof(cur->type_work), stdin) == NULL) {

			while (getchar() != '\n');
			printf("Invalid input. Enter type of work: ");
		}

		err = strcspn(cur->type_work, "\n");     // Пошук \n

		if (cur->type_work[err] == '\n') cur->type_work[err] = '\0';   // Видалення символу \n
		else 
			while (getchar() != '\n');
	}
	////////////////////////////////////////
	if (item == 4 || mode) {

		printf("Enter cost of the work: ");
		while ((err = scanf("%d", &(cur->cost))) == 0 || cur->cost < 0) { 	//Поки невдалий ввод, або cost < 0

			while (getchar() != '\n');        //Очищення потоку
			printf("Invalid input. Enter cost of the work: ");
		}
		while (getchar() != '\n');
	}
	////////////////////////////////////////
	if (item == 5 || mode) {
		char is_debt;

		printf("Pacient have debt? (y/n): ");        
		while ((is_debt = getchar()) != 'y' && is_debt != 'n') {  // Безпечне введення
			while (getchar() != '\n');
			printf("Invalid input. Pacient have debt? (y/n): ");
		}
		while (getchar() != '\n');


		if (is_debt == 'y') {  // Якщо є борг 

			cur->check = true;

			printf("Enter sum of debt: ");    // Безпечне введення
			while ((err = scanf("%d", &(cur->debt_sum))) == 0 || cur->debt_sum < 1) { 	//Поки невдалий ввод, або sum < 1

				while (getchar() != '\n');        //Очищення потоку
				printf("Invalid input. Enter sum of debt: ");
			}
			while (getchar() != '\n');
		}
		else {        // Якщо боргу немає
			cur->check = false;   // false - боргу немає
			cur->debt_sum = 0;    // Обнуляємо 
		}
		
	}
}


void deleteElement() {   //Список видаляє кінечь

	if (end == NULL) {       // Перевірка на наявіність елементів
		printf("\n  [ Nothing to delete ]\n");
		return;
	}

	struct Pacient* prev = start;
	char sure;   // Змінна для підтвердження 

	// Вивід елементу
	printf("\n-------------------------------------------------------------------------------------------------------------\n");
	printf("| %-25s | %-10d | %-25s | %-10d ", end->name, end->card, end->type_work, end->cost);
	(end->check) ? printf("|    Yes   | %-12d |\n", end->debt_sum) : printf("|   No     |    ------    ||\n");
	printf("-------------------------------------------------------------------------------------------------------------\n");
	printf("You sure want to delete? (y/n): ");

	while ((sure = getchar()) != 'y' && sure != 'n') {  // Безпечне введення
		while (getchar() != '\n');
		printf("Invalid input. You sure want to delete? (y/n): ");
	}
	while (getchar() != '\n');

	if (sure == 'n') return;

	if (start == end) {    // Перевірка на останній елемент
		printf("\n  [ Last element deleted ]\n");
		free(end);
		start = NULL;
		end = NULL;
		return;
	}

	while (prev->next != end) prev = prev->next;  // Якщо елементів > 1
	free(end);  // Очищення пам'яті
	end = prev;
	prev->next = NULL;
}


void changeElement() {

	struct Pacient* cur = start;
	int card_tmp, item_tmp;

	printf("Enter account card number: ");
	while (scanf("%d", &card_tmp) != 1 && card_tmp < 1) {

		while (getchar() != '\n');        //Очищення потоку
		printf("Invalid input. Enter account card number: ");
	}
	while (getchar() != '\n');

	while (cur != NULL) {

		if (card_tmp == cur->card) {

			printf("\n[1]Surname  [2]Card num  [3]Type of work  [4]Cost  [5]Debt\n");
			printf("\nWhat you wanna change? :");
			while (scanf("%d", &item_tmp) != 1 || (item_tmp < 1 || item_tmp > 5)) {

				while (getchar() != '\n');        //Очищення потоку
				printf("Invalid input. What you wanna change? : ");
			}
			while (getchar() != '\n');

			inputPacient(cur, false, item_tmp);

			return;
		}

		cur = cur->next;
	}
	printf("\n [ No coincidence ]\n");
}


void saveFile() {

	FILE* f = fopen("save.bin", "wb");
	if (f == NULL) {
		printf("\n [ The file was opened incorrectly ] \n");
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
		printf("\n [ The file was opened incorrectly / the file does not exist ] \n");
		return;
	}

	if (start != NULL) printf("\n [ The data was added to the existing data ] \n");

	while (1) {

		temp = start;

		if ((start = (struct Pacient*)malloc(sizeof(struct Pacient))) == NULL) {
			puts(" [ Error with allocation memory ] ");
			return;
		}

		fread(start, sizeof(struct Pacient), 1, f);

		if (temp == NULL) end = start;

		if (feof(f)) {  //Перевірка на EOF
			free(start);   //Видалення зайвої структури
			start = temp;   //Повернення start
			break;
		}

		start->next = temp;
	}

	fclose(f);
}


void showAllElement() {

	struct Pacient* cur = start;

	if (cur == NULL) {
		printf("\n [ No element ] \n");
		return;
	}

	printf("===============================================================================================================\n");
	printf("||          Surname          |  Card num  |       Type of work        |    Cost    |  Debtor? |   Debt sum   ||\n");
	printf("||===========================================================================================================||\n");

	while (cur != NULL) {

		printf("|| %-25s | %-10d | %-25s | %-10d ", cur->name, cur->card, cur->type_work, cur->cost);

		(cur->check) ? printf("|    Yes   | %-12d ||\n", cur->debt_sum) : printf("|   No     |    ------    ||\n");    // Тернарний оператор

		if (cur->next != NULL) printf("||-----------------------------------------------------------------------------------------------------------||\n");
		else printf("||===========================================================================================================||\n");

		cur = cur->next;
	}

}


void showByTheName() {

	struct Pacient* cur = start;
	char name_tmp[25];
	int err;
	bool turn = false;   //0 співпадінь

	if (cur == NULL) {
		printf("\n [ No element ] \n");
		return;
	}

	//--------------------------------------------
	printf("\nEnter surname: ");
	while (fgets(name_tmp, sizeof(name_tmp), stdin) == NULL) {

		while (getchar() != '\n');
		printf("Invalid input. Enter surname: ");
	}
	err = strcspn(name_tmp, "\n");  //Пошук \n

	if (name_tmp[err] == '\n') name_tmp[err] = '\0';	//видалення символу \n, якщо його нема - очищення потоку
	else
		while (getchar() != '\n');
	//--------------------------------------------

	while (cur != NULL) {

		if (!strcmp(name_tmp, cur->name)) {

			printf("\n--------------------------------------------------------------------------------------------------------------\n");
			printf("| %-25s | %-10d | %-25s | %-10d ", cur->name, cur->card, cur->type_work, cur->cost);
			(cur->check) ? printf("|    Yes   | %-12d |\n", cur->debt_sum) : printf("|   No     |    ------    ||\n");
			printf("--------------------------------------------------------------------------------------------------------------\n");

			turn = true;
		}
		cur = cur->next;
	}
	if (!turn) printf("\n [ No coincidence ]\n");
}


void showDebtors() {

	struct Pacient* cur = start;
	bool turn = false;   //0 боржників

	if (cur == NULL) {
		printf("\n [ No element ] \n");
		return;
	}

	printf("\n===============================================================================================================\n");
	printf("||          Surname          |  Card num  |       Type of work        |    Cost    |  Debtor? |   Debt sum   ||\n");
	printf("||===========================================================================================================||\n");

	while (cur != NULL) {

		if (cur->check) {

			turn = true;

			printf("|| %-25s | %-10d | %-25s | %-10d ", cur->name, cur->card, cur->type_work, cur->cost);
			printf("|    Yes   | %-12d ||\n", cur->debt_sum);
			printf("||-----------------------------------------------------------------------------------------------------------||\n");
		}

		cur = cur->next;
	}
	if (!turn) printf("\n [ No coincidence ]\n");
}


void deleteNoDebtor() {

	struct Pacient* cur = start;
	struct Pacient* prev = start;
	char sure;

	if (cur == NULL) {    // Перевірка
		printf("\n [ No element ] \n");
		return;
	}

	printf("You sure want to delete? (y/n): ");     // Уточнення 
	while ((sure = getchar()) != 'y' && sure != 'n') {  
		while (getchar() != '\n');
		printf("Invalid input. You sure want to delete? (y/n): ");
	}
	while (getchar() != '\n');

	if (sure == 'n') return;


	while (cur != NULL) {

		if (!cur->check) {

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

		prev = cur;   //Зробив шафл
		cur = cur->next;
	}
}


void sortElement() {

	struct Pacient* cur = start;

	if (cur == NULL) {   //  Перевірка 
		printf("\n [ No element ] \n");
		return;
	}

	size_t size = 0;
	while (cur != NULL) {  // Знаходимо розмір
		size++;
		cur = cur->next;
	}
	printf("\nSize: %zu", size);

	for (int i = 0; i < size - 1; i++) {   // Бульбашковий метод
		cur = start;
		while (cur != NULL) {
			if (cur->next == NULL) break;  // Межа для сортування 
			if (cur->debt_sum > cur->next->debt_sum) swap(cur);	  // Простый перепис даних (не покажчика)
			cur = cur->next;
		}
	}
}

void swap(struct Pacient* cur) {

	struct Pacient swap;

	strcpy(swap.name, cur->name);     //strcpy для масивів char
	strcpy(cur->name, cur->next->name);
	strcpy(cur->next->name, swap.name);

	swap.card = cur->card;
	cur->card = cur->next->card;
	cur->next->card = swap.card;

	swap.cost = cur->cost;
	cur->cost = cur->next->cost;
	cur->next->cost = swap.cost;

	strcpy(swap.type_work, cur->type_work);
	strcpy(cur->type_work, cur->next->type_work);
	strcpy(cur->next->type_work, swap.type_work);

	swap.check = cur->check;
	cur->check = cur->next->check;
	cur->next->check = swap.check;

	swap.debt_sum = cur->debt_sum;
	cur->debt_sum = cur->next->debt_sum;
	cur->next->debt_sum = swap.debt_sum;
}