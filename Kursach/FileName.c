#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>      // підключення заголовного файлу windows.h, для SetConsoleCP() та SetConsoleOutputCP()

// Прототипи функцій
void CreateElement();
void DeleteElement();
void PutStrings(int n);
void FreeStrings(int n);
void AllStrings(int n);
void TableSport(int n);
void DataSport(int n);
void DataMember(int n);
void AllMemberCountry(int n);
void AllInfo(int n);
void SortingKindSport(int n);

struct sport* begin = NULL;
struct sport* end = NULL;
struct sport* tt = NULL;


struct blank {
    char surname[20];
    char country[20];
    float result;
    float personal_result;
};

struct sport {
    char tipe_sport[30];
    struct blank first;
    struct blank second;
    struct blank therd;

    struct sport* next;
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
        puts("Вибір дії");
        puts("1 - Додавання елемента;");
        puts("2 - Видалення елемента;");
        puts("3 - Можливість коригування даних;");
        puts("4 - Виведення всіх даних;");
        puts("5 - Початкове формування даних про всі спортсменів у вигляді таблиці;");
        puts("6 - Виведення даних про введені види спорту;");
        puts("7 - Виведення даних про спортсменів, які поліпшили свій особистий рекорд;");
        puts("8 - Пошук всіх спортсменів з введеної країни;");
        puts("9 - Виведення зведеної таблиці із зазначенням країни, кількості перших, других, третіх місць;");
        puts("10 - Сортування по полю «вид спорту».");
        puts("0 - Вихід");

        // Вибір бажаної дії
        puts("Введіть код бажаної дії");
        scanf("%d", &kod);
        printf("Обраний код %d \n", kod);
        // Запуск функції згідно обраної дії
        switch (kod)
        {
        case 1: CreateElement(); break;
        case 2: DeleteElement(); break;
            //      case 3: AllStrings(); break;
            //      case 4: FreeStrings(); break;
            //      case 5: TableSport(); break;
            //      case 6: DataSport(); break;
            //      case 7: DataMember(); break;
            //      case 8: AllMemberCountry(); break;
            //      case 9: AllInfo(); break;
            //      case 10: SortingKindSport(); break;
        case 0: exit(1); break;
        }
    }
    return EXIT_SUCCESS; // EXIT_SUCCESS - константа, що означає успішне виконання програми}
}
// Функція введення списку рядків
void CreateElement() // приймає кількість рядків, в даному випадку можна не передавати,
//так як оголошено глобальною константою
{
    if (begin == NULL) {       //Якщо це перший елемент

        begin = (struct sport*)malloc(sizeof(struct sport));    //Виділяємо пам'ять в початку списку
        if (begin == NULL) {                         //Перевіряємо пам'ять
            puts("Error with allocation memory");
            return;               //Перериваємо функцію в разі помилки
        }

        end = begin;   //Вказуємо кінець списку

        end->next = NULL;    //Позначаємо покажчик кінчевого елементу як 0

        enterSport();     //Вводимо

        return;       //Перериваємо функцію
    }


    if (begin != NULL) {  //Якщо це не перший елемент

        tt = begin;    //Запам'ятвоуємо початок

        begin = (struct sport*)malloc(sizeof(struct sport));    //Виділяємо пам'ять в початку списку
        if (begin == NULL) {                         //Перевіряємо пам'ять
            puts("Error with allocation memory");
            return;               //Перериваємо функцію в разі помилки
        }

        begin->next = tt;  //Новий елемент вказує на минулий

        enterSport();    //Вводимо данні

        return;
    }
}
void enterSport()
{
    printf("Enter type of sport: ");
    scanf("%30s", &(begin->tipe_sport));
    ////////////
    puts("\nFirst:");
    printf("Enter surname: ");
    scanf("%20s", &(begin->first.surname));

    printf("Enter country: ");
    scanf("%20s", &(begin->first.country));

    printf("Enter result: ");
    scanf("%f", &(begin->first.result));

    printf("Enter personal result: ");
    scanf("%f", &(begin->first.personal_result));
    //////
    puts("\nSecond:");
    printf("Enter surname: ");
    scanf("%20s", &(begin->second.surname));

    printf("Enter country: ");
    scanf("%20s", &(begin->second.country));

    printf("Enter result: ");
    scanf("%f", &(begin->second.result));

    printf("Enter personal result: ");
    scanf("%f", &(begin->second.personal_result));
    /////////
    puts("\nTherd:");
    printf("Enter surname: ");
    scanf("%20s", &(begin->therd.surname));

    printf("Enter country: ");
    scanf("%20s", &(begin->therd.country));

    printf("Enter result: ");
    scanf("%f", &(begin->therd.result));

    printf("Enter personal result: ");
    scanf("%f", &(begin->therd.personal_result));
}

void DeleteElement()
{
    struct sport* cur;    //Поточний
    struct sport* prev;    //Попередній

    char ask_sport[30];
    int turn = 1;

    puts("\nEnter sport for search"); //
    scanf("%30s", &ask_sport);

    cur = begin;
    prev = begin;
    
    while (1) {
  
        if (!strcmp(cur->tipe_sport, ask_sport)) {

            tt = cur->next;

            if (tt == NULL) puts("Last element has been deleted");

            printf("\nDelete 2: %30s\n", cur->tipe_sport);

            free(cur); 

            prev->next = tt;
                            
            break;
        }
        cur = cur->next;

        if (turn) {
            turn++;
            continue;
        }
        prev = prev->next;
    }

    return;
}










//void AllStrings()
//{
//    printf("Coming soon...");
//}
//
//void FreeStrings()
//{
//    printf("Coming soon...");
//}
//
//void TableSport()
//{
//    printf("Coming soon...");
//}
//
//void DataSport()
//{
//    printf("Coming soon...");
//}
//
//void DataMember()
//{
//    printf("Coming soon...");
//}
//
//void AllMemberCountry()
//{
//    printf("Coming soon...");
//}
//
//void AllInfo()
//{
//    printf("Coming soon...");
//}
//
//void SortingKindSport()
//{
//    printf("Coming soon...");
//}
