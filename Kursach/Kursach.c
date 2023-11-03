#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>      // підключення заголовного файлу windows.h, для SetConsoleCP() та SetConsoleOutputCP()
#include <stdbool.h>

// Прототипи функцій
void inputPacient();	
void GetElement();
void DeleteElement();

//void PutStrings(int n);         заглушки
//void FreeStrings(int n);
//void ChangeStrings(int n);


struct Pacient* start = NULL;          //Глобальні змінні-покажчики на початок/кінець списку
struct Pacient* end = NULL;
struct Pacient* temp = NULL;       //Робимо буфер для збереження покажчику на елемент

struct Pacient {      //моя структура 
	char name[25];
	int card;
	char type_work[25];
	int cost;
	bool check;      //вирішив зробити через bool (оскільки змінна може набувати тільки двох значень)
	int debt_sum;

	struct Pacient* next;	//покажчик на наступний елемент
};

// Головна функція програми
int main()
{
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
		/*puts("3 - Можливість коригування даних");
		puts("4 - Виведення всіх даних");
		puts("5 - Виведення довідки про клієнта за введеним прізвищем;");
		puts("6 - Виведення довідки про боржників за видами робіт і загальної заборгованості");
		puts("7 - Видалення з бази записів про пацієнтів, які не мають заборгованості за лікування");
		puts("8 - Cортування за сумою заборгованості за лікування");*/
		puts("0 - Вихід");
		// Вибір бажаної дії
		puts("Введіть код бажаної дії");
		scanf("%d", &kod);
		printf("\nОбраний код %d \n", kod);
		// Запуск функції згідно обраної дії
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
	return EXIT_SUCCESS; // EXIT_SUCCESS - константа, що означає успішне виконання програми}
}

// Функція створення елементу
void GetElement() //Аргументи для функції не потрібні
{
	if (start == NULL) {       //Якщо це перший елемент
		
		start = (struct Pacient*)malloc(sizeof(struct Pacient));    //Виділяємо пам'ять в початку списку
		if (start == NULL) {                         //Перевіряємо пам'ять
			puts("Error with allocation memory");
			return;               //Перериваємо функцію в разі помилки
		}
		
		end = start;   //Вказуємо кінець списку	
		
		end->next = NULL;    //Позначаємо покажчик кінчевого елементу як 0

		inputPacient();     //Вводимо 

		return;       //Перериваємо функцію 
	}

	if (start != NULL) {  //Якщо це не перший елемент

		temp = start;    //Запам'ятвоуємо початок
		
		start = (struct Pacient*)malloc(sizeof(struct Pacient));    //Виділяємо пам'ять в початку списку
		if (start == NULL) {                         //Перевіряємо пам'ять
			puts("Error with allocation memory");
			return;               //Перериваємо функцію в разі помилки
		}

		start->next = temp;  //Новий елемент вказує на минулий

		inputPacient();    //Вводимо данні

		return;
	}
}
		

void inputPacient()      //зручна функція для вводу данних в комірки
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
	if (start == NULL) {		//перевірка на нульовий елемент, вихід з циклу 
		printf("\nNo element to delete\n");
		return;
	}

	puts("Delete from: start [1]	search [2] ");   //Вибір користувача
	scanf("%d", &delete_kod);
	
	if (delete_kod == 1) {

		temp = start->next;

		printf("\nRemove : %s\n", start->name);
		
		free(start);

		start = temp;   //Якщо останній елемент був видалений, start буде вказувати на NULL
									//Тоді створення нового елементу не буде проблемою 
		if (start == NULL) {
			printf("---You delete last element---");
			return;
		}
		return;
	}

	if (delete_kod == 2) {         // 
		struct Pacient* cur = start;    //Поточний
		struct Pacient* prev = start;    //Попередній

		bool button = true;      //пермикач для шафлу(відставання prev)
		char prompt[25];

		printf("\nEnter surname for search: ");
		scanf("%25s", &prompt);
		while (1) {	
			if (cur == NULL) {        //перевірка на нульовий елемент, вихід з циклу 
				printf("\nNo coincidance\n");
				return;
			}

			if (!strcmp(cur->name, prompt)) {  		//якщо співпадає, то

				temp = cur->next;

				if (temp == NULL) puts("\nDeleted element from end");      //перевірка на граничний елемент

				if ((temp == NULL) && (start == cur)) {   //якщо видаляємо останній елемент
					puts("\nDeleteded last element\n");

					free(cur);             // видалення 

					start = NULL;            //знову занулюємо старт і кінець
					end = NULL;

					return;
				}

				printf("\nRemove : %s\n", cur->name);

				free(cur);

				prev->next = temp;

				return;
			}
			
			cur = cur->next;        //зміщення cur

			if (button) {           //робимо відставання для prev
				button = false;
				continue;
			}	
			prev = prev->next;			
		}
		return;
	}
}