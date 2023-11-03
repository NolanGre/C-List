#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>      
#include <stdbool.h>

struct Animal {

	char animal_name[25];     //назва тварини
	char animal_type[25];		//тип
	char animal_class[25];		//клас
	char animal_family[25];		  //сімейство
	char animal_kind[25];			//рід
	char animal_species[25];		//вид
	char animal_habitat[25];		//середовище проживання
	int  animal_population;       //чисельність в світі

	struct Animal* next;
	struct Animal* prev;
};

struct Animal* end = NULL;
struct Animal* begin = NULL;

struct Animal* temp = NULL;
struct Animal* current = NULL;

bool check = true;      //перевірка на перший єлемент

void GetAnimal();
void insertAnimal();
void DeleteAnimal();


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
	return EXIT_SUCCESS;  // EXIT_SUCCESS - константа, що означає успішне виконання програми}
}


// Функція створення елементу
void GetAnimal() {
	if (check) {			// Перевірка на першу вхідну комірку
		if((end = (struct Animal*)malloc(sizeof(struct Animal))) == NULL) {                         
			puts("Error with allocation memory");
			return;              
		}

		begin = end;  
		begin->next = NULL;    // Нулюємо покажчики в остан комірк
		begin->prev = NULL;

		insertAnimal();    
		
		check = false;
		return;      
	}
	////////////////
	temp = end;   //покажчик на старий елемент
	
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

void DeleteAnimal() {   //по пошуку
	char search[25];

	struct Animal* prev_t = NULL;
	struct Animal* next_t = NULL;

	current = end;   
	
	if (current == NULL) {		//if element == NULL  
		printf("\n no element to delete\n");    // немає елементів для видалення
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

			if ((next_t == NULL) && (prev_t == NULL)) {  //перевірка кінцевість едементу
				printf("Last element destroy");
				end = NULL;
				begin = NULL;
				check = true;
				return;
			}
			else if (prev_t == NULL) {   //перевірка граничний елемент
				end = next_t;
				next_t->prev = NULL;
				printf("Deleted end border element");    // for test
				return;
			}
			else if (next_t == NULL) {      //перевірка на граничний
				begin = prev_t;
				prev_t->next = NULL;
				printf("Deleted begin border element");    // for test
				return;
			}
			
			prev_t->next = next_t;   //зшиваємо 
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
