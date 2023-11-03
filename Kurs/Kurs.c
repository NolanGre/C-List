#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>

struct DATE{
    int day;
    int month;
    int year;
};
struct vacation{
    char name[25];
    char surname[25];
    char vacation_type[25];
    struct DATE date_start;
    struct DATE date_end;
    struct DATE date_create;
    int max_days;
    int days_left;

    struct vacation* prev;
    struct vacation* next;


};


struct vacation* head = NULL;
struct vacation* tail = NULL;
struct vacation* curr = NULL;
int check;
// Прототипи функцій
void menu();
void addEmployee();
void creationList();
void createRequest();
void pendingList();
void deletion();
void deleteRequest();
void editRequest();
void vacationTypeList();
void surnameList();
void sortByDaysLeft();
void saveDataToFile(const char* filename);
void loadDataFromFile(const char* filename);
void saveDataToBinaryFile(const char* filename);
bool isPending();
void editing();


int main(){
 SetConsoleCP(1251);
 SetConsoleOutputCP(1251);
 while(1)
 {
 menu();
 }
return EXIT_SUCCESS;
}
bool isPending(){
    time_t current_time;
    time(&current_time);
    struct tm *current_date = localtime(&current_time);

    if (curr->date_start.year > current_date->tm_year+1900){
        return true;
    }
    else if (curr->date_start.year == current_date->tm_year+1900 && curr->date_start.month > current_date->tm_mon+1){
        return true;
    }
    else if (curr->date_start.year == current_date->tm_year+1900 && curr->date_start.month == current_date->tm_mon+1 && curr->date_start.day > current_date->tm_mday){
        return true;
    }
    else {
        return false;
    }
}
void menu(){
printf("\n");
 puts("Select action");
 puts("1 - Add employee");
 puts("2 - Create a new vacation request");
 puts("3 - Deleting a vacation request");
 puts("4 - Edit request");
 puts("5 - List by vacation type");
 puts("6 - List by surname");
 puts("7 - Sort by days left");
 puts("------------------------------");
 puts("8 - Save changes");
 puts("9 - Upload save");
 puts("------------------------------");
 puts("0 - Exit");

int code;
puts("Enter the action code: ");
while (scanf("%d", &code) != 1 || code > 9 || code < 0) {
    while (getchar() != '\n');
    printf("Invalid action code. Please enter a valid code: ");
}
while (getchar() != '\n');

    switch(code) {
        case 1: addEmployee(); break;
        case 2: createRequest(); break;
        case 3: deleteRequest(); break;
        case 4: editRequest(); break;
        case 5: vacationTypeList(); break;
        case 6: surnameList(); break;
        case 7: sortByDaysLeft(); break;
        case 8: saveDataToFile("data.txt"); break;
        case 9: loadDataFromFile("load.bin"); break;
        case 0: exit(1); break;
    }
}
void addEmployee() {
    if (!(curr = (struct vacation *)malloc(sizeof(struct vacation)))) {
        printf("Memory allocation error\n");
        return;
    }
    memset(curr, 0, sizeof(struct vacation));
    printf("Enter employee surname \n");
    scanf("%24s", curr->surname);
    printf("Enter employee name \n");
    scanf("%24s", curr->name);
    curr->prev = NULL;
    curr->next = NULL;

    if (head == NULL) {
        head = curr;
        tail = curr;
    }
    else {
        tail->next = curr;
        curr->prev = tail;
        tail = curr;
    }
}
void creationList(){
    curr=head;
    printf("+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+\n");
    printf("| Surname         | Name            | Creation date   | Vacation type   | Start date      | End date        | Max days        | Days left       |\n");
    printf("+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+\n");
    while(curr!=NULL){
        if(curr->date_create.day==0){
            printf("| %-15s | %-15s | %02d.%02d.%04d      | %-15s | %02d.%02d.%04d      | %02d.%02d.%04d      | %-15d | %-15d |\n", curr->surname, curr->name, curr->date_create.day, curr->date_create.month, curr->date_create.year, curr->vacation_type, curr->date_start.day, curr->date_start.month, curr->date_start.year, curr->date_end.day, curr->date_end.month, curr->date_end.year, curr->max_days, curr->days_left);
            printf("+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+\n");
        }
        curr=curr->next;
    }
    }
void createRequest(){
     if(head==NULL){
     printf("No employees found\n");
     return;
    }
    curr=head;
    int found = 0;
    while (curr != NULL) {
        if (curr->date_create.day == 0) {
            found = 1;
            break;
        }
        curr = curr->next;
    }

    if (!found) {
        printf("No employees found\n");
        return;
    }

    creationList();
    char search[30];
    printf("Enter surname to create request: ");
    scanf("%s", &search);
     int count=0;
      curr=head;
        while (curr != NULL){
                if(!strcmp(curr->surname, search)){
                    count++;
                }
           curr = curr->next;
        }
    if (count == 1){
    curr=head;
    while(curr!=NULL){
        if(!strcmp(curr->surname, search)){
                if(curr->date_create.day!=0){
                    printf("Request has already been created\n");
                    return;
                }
			printf("Enter creation date \n");
            while (curr->date_create.day == 0) {
                printf("Day: ");
                if (scanf("%d", &curr->date_create.day) != 1) {
                    printf("Error, try one more time\n");
                    fflush(stdin);
                    curr->date_create.day = 0;
                    }
                else if (curr->date_create.day < 1 || curr->date_create.day > 31) {
                    printf("Error, try one more time\n");
                    curr->date_create.day = 0;
                    }
                }
            while (curr->date_create.month == 0) {
                printf("Month: ");
                if (scanf("%d", &curr->date_create.month) != 1) {
                    printf("Error, try one more time\n");
                    fflush(stdin);
                    curr->date_create.month = 0;
                }
                else if (curr->date_create.month < 1 || curr->date_create.month > 12) {
                    printf("Error, try one more time\n");
                    curr->date_create.month = 0;
                    }
                }

            while (curr->date_create.year == 0) {
                printf("Year: ");
                if (scanf("%d", &curr->date_create.year) != 1) {
                    printf("Error, try one more time\n");
                    fflush(stdin);
                    curr->date_create.year = 0;
                }
                else if (curr->date_create.year < 1) {
                    printf("Error, try one more time\n");
                    curr->date_create.year = 0;
                    }
                }

			printf("Enter vacation type (paid/unpaid): ");
            do {
                scanf("%24s", curr->vacation_type);
                if (strcmp(curr->vacation_type, "paid") != 0 && strcmp(curr->vacation_type, "unpaid") != 0) {
                    printf("Invalid vacation type. Please enter either 'paid' or 'unpaid': ");
                }
            }
            while (strcmp(curr->vacation_type, "paid") != 0 && strcmp(curr->vacation_type, "unpaid") != 0);


			printf("Enter date_start\n");
            while (curr->date_start.day == 0) {
                printf("Day: ");
                if (scanf("%d", &curr->date_start.day) != 1) {
                    printf("Error, try one more time\n");
                    fflush(stdin);
                    curr->date_start.day = 0;
                }
                else if (curr->date_start.day < 1 || curr->date_start.day > 31) {
                    printf("Error, try one more time\n");
                    curr->date_start.day = 0;
                    }
                }
            while (curr->date_start.month == 0) {
                printf("Month: ");
                if (scanf("%d", &curr->date_start.month) != 1) {
                    printf("Error, try one more time\n");
                    fflush(stdin);
                    curr->date_start.month = 0;
                }
                else if (curr->date_start.month < 1 || curr->date_start.month > 12) {
                    printf("Error, try one more time\n");
                    curr->date_start.month = 0;
                    }
                }

            while (curr->date_start.year == 0) {
                printf("Year: ");
                if (scanf("%d", &curr->date_start.year) != 1) {
                    printf("Error, try one more time\n");
                    fflush(stdin);
                    curr->date_start.year = 0;
                }
                else if (curr->date_start.year < 1) {
                    printf("Error, try one more time\n");
                    curr->date_start.year = 0;
                    }
                }
			printf("Enter date_end \n");
			 while (curr->date_end.day == 0) {
                printf("Day: ");
                if (scanf("%d", &curr->date_end.day) != 1) {
                    printf("Error, try one more time\n");
                    fflush(stdin);
                    curr->date_end.day = 0;
                }
                else if (curr->date_end.day < 1 || curr->date_end.day > 31) {
                    printf("Error, try one more time\n");
                    curr->date_end.day = 0;
                    }
                }
            while (curr->date_end.month == 0) {
                printf("Month: ");
                if (scanf("%d", &curr->date_end.month) != 1) {
                    printf("Error, try one more time\n");
                    fflush(stdin);
                    curr->date_end.month = 0;
                }
                else if (curr->date_end.month < 1 || curr->date_end.month > 12) {
                    printf("Error, try one more time\n");
                    curr->date_end.month = 0;
                    }
                }

            while (curr->date_end.year == 0) {
                printf("Year: ");
                if (scanf("%d", &curr->date_end.year) != 1) {
                    printf("Error, try one more time\n");
                    fflush(stdin);
                    curr->date_end.year = 0;
                }
                else if (curr->date_end.year < 1) {
                    printf("Error, try one more time\n");
                    curr->date_end.year = 0;
                }
            }
			printf("Enter max days of vacation :");
			while (scanf("%d", &curr->max_days) != 1 || curr->max_days < 1) {
                printf("Error, try one more time\n");
                fflush(stdin);
            }
			printf("Enter days left of vacation :");
			while (scanf("%d", &curr->days_left) != 1 || curr->days_left < 0) {
                printf("Error, try one more time\n");
                fflush(stdin);
            }
			return;
        }
        curr = curr->next;
		}
        printf("\nEmployee with last name %s not found\n", search);
    }

    else if(count>1){
            curr=head;
       char searchName[25];
        printf("Write name to confirm person: ");
        scanf("%24s", searchName);
        while (curr != NULL){
            if (!strcmp(curr->surname, search) && !strcmp(curr->name, searchName)) {
                    if(curr->date_create.day!=0){
                    printf("Request has already been created\n");
                    return;
                }
              printf("Enter creation date \n");
            while (curr->date_create.day == 0) {
                printf("Day: ");
                if (scanf("%d", &curr->date_create.day) != 1) {
                    printf("Error, try one more time\n");
                    fflush(stdin);
                    curr->date_create.day = 0;
                    }
                else if (curr->date_create.day < 1 || curr->date_create.day > 31) {
                    printf("Error, try one more time\n");
                    curr->date_create.day = 0;
                    }
                }
            while (curr->date_create.month == 0) {
                printf("Month: ");
                if (scanf("%d", &curr->date_create.month) != 1) {
                    printf("Error, try one more time\n");
                    fflush(stdin);
                    curr->date_create.month = 0;
                }
                else if (curr->date_create.month < 1 || curr->date_create.month > 12) {
                    printf("Error, try one more time\n");
                    curr->date_create.month = 0;
                    }
                }

            while (curr->date_create.year == 0) {
                printf("Year: ");
                if (scanf("%d", &curr->date_create.year) != 1) {
                    printf("Error, try one more time\n");
                    fflush(stdin);
                    curr->date_create.year = 0;
                }
                else if (curr->date_create.year < 1) {
                    printf("Error, try one more time\n");
                    curr->date_create.year = 0;
                    }
                }

			printf("Enter vacation type (paid/unpaid): ");
            do {
                scanf("%24s", curr->vacation_type);
                if (strcmp(curr->vacation_type, "paid") != 0 && strcmp(curr->vacation_type, "unpaid") != 0) {
                    printf("Invalid vacation type. Please enter either 'paid' or 'unpaid': ");
                }
            }
            while (strcmp(curr->vacation_type, "paid") != 0 && strcmp(curr->vacation_type, "unpaid") != 0);


			printf("Enter date_start\n");
            while (curr->date_start.day == 0) {
                printf("Day: ");
                if (scanf("%d", &curr->date_start.day) != 1) {
                    printf("Error, try one more time\n");
                    fflush(stdin);
                    curr->date_start.day = 0;
                }
                else if (curr->date_start.day < 1 || curr->date_start.day > 31) {
                    printf("Error, try one more time\n");
                    curr->date_start.day = 0;
                    }
                }
            while (curr->date_start.month == 0) {
                printf("Month: ");
                if (scanf("%d", &curr->date_start.month) != 1) {
                    printf("Error, try one more time\n");
                    fflush(stdin);
                    curr->date_start.month = 0;
                }
                else if (curr->date_start.month < 1 || curr->date_start.month > 12) {
                    printf("Error, try one more time\n");
                    curr->date_start.month = 0;
                    }
                }

            while (curr->date_start.year == 0) {
                printf("Year: ");
                if (scanf("%d", &curr->date_start.year) != 1) {
                    printf("Error, try one more time\n");
                    fflush(stdin);
                    curr->date_start.year = 0;
                }
                else if (curr->date_start.year < 1) {
                    printf("Error, try one more time\n");
                    curr->date_start.year = 0;
                    }
                }
			printf("Enter date_end \n");
			 while (curr->date_end.day == 0) {
                printf("Day: ");
                if (scanf("%d", &curr->date_end.day) != 1) {
                    printf("Error, try one more time\n");
                    fflush(stdin);
                    curr->date_end.day = 0;
                }
                else if (curr->date_end.day < 1 || curr->date_end.day > 31) {
                    printf("Error, try one more time\n");
                    curr->date_end.day = 0;
                    }
                }
            while (curr->date_end.month == 0) {
                printf("Month: ");
                if (scanf("%d", &curr->date_end.month) != 1) {
                    printf("Error, try one more time\n");
                    fflush(stdin);
                    curr->date_end.month = 0;
                }
                else if (curr->date_end.month < 1 || curr->date_end.month > 12) {
                    printf("Error, try one more time\n");
                    curr->date_end.month = 0;
                    }
                }

            while (curr->date_end.year == 0) {
                printf("Year: ");
                if (scanf("%d", &curr->date_end.year) != 1) {
                    printf("Error, try one more time\n");
                    fflush(stdin);
                    curr->date_end.year = 0;
                }
                else if (curr->date_end.year < 1) {
                    printf("Error, try one more time\n");
                    curr->date_end.year = 0;
                }
            }
			printf("Enter max days of vacation :");
			while (scanf("%d", &curr->max_days) != 1 || curr->max_days < 1) {
                printf("Error, try one more time\n");
                fflush(stdin);
            }
			printf("Enter days left of vacation :");
			while (scanf("%d", &curr->days_left) != 1 || curr->days_left < 0) {
                printf("Error, try one more time\n");
                fflush(stdin);
            }
			return;
                    }
            curr = curr->next;
    }
    printf("\nEmployee: %s %s not found\n", search, searchName);
}
else printf("\nEmployee with last name %s not found\n", search);
}
void pendingList(){
      time_t current_time;
    time(&current_time);
    struct tm *current_date = localtime(&current_time);
        int found=0;
      curr=head;
      printf("+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+\n");
    printf("| Surname         | Name            | Creation date   | Vacation type   | Start date      | End date        | Max days        | Days left       |\n");
    printf("+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+\n");
    while(curr!=NULL){
        if(isPending()){
            found = 1;
           printf("| %-15s | %-15s | %02d.%02d.%04d      | %-15s | %02d.%02d.%04d      | %02d.%02d.%04d      | %-15d | %-15d |\n", curr->surname, curr->name, curr->date_create.day, curr->date_create.month, curr->date_create.year, curr->vacation_type, curr->date_start.day, curr->date_start.month, curr->date_start.year, curr->date_end.day, curr->date_end.month, curr->date_end.year, curr->max_days, curr->days_left);
            printf("+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+\n");
        }
        curr=curr->next;
    }
    if (!found) {
        printf("No requests found\n");
        check=1;
    }
}
void deletion(){
    time_t current_time;
    time(&current_time);
    struct tm *current_date = localtime(&current_time);
    if (isPending()){
            curr->date_create.day=0;
            curr->date_create.month=0;
            curr->date_create.year=0;
            curr->date_start.day=0;
            curr->date_start.month=0;
            curr->date_start.year=0;
            curr->date_end.day=0;
            curr->date_end.month=0;
            curr->date_end.year=0;
            curr->days_left=0;
            curr->max_days=0;
            strcpy(curr->vacation_type, "");
            check=1;
    }
    else{
        if(curr->date_create.day!=0)printf("Vacation has already started\n");
        else printf("No request found\n");
    }
}
void deleteRequest() {
    check=0;
    time_t current_time;
    time(&current_time);
    struct tm *current_date = localtime(&current_time);
     if(head==NULL){
     printf("No employees found\n");
     return;
    }

    curr=head;
    int found = 0;
    while (curr != NULL) {
        if (curr->date_create.day != 0) {
            found = 1;
            break;
        }
        curr = curr->next;
    }
    if (!found) {
        printf("No requests found\n");
        return;
    }
        pendingList();
        if(check==1)return;
        check=0;
        char search[25];
        printf("Enter surname to delete request\n");
        scanf("%24s", search);
        curr=head;
        int count=0;
        while (curr != NULL){
                if(!strcmp(curr->surname, search)){
                    count++;
                }
           curr = curr->next;
        }
        if(count == 1){
            curr=head;
        while (curr != NULL) {
            if (!strcmp(curr->surname, search)) {
                deletion();
                if(check == 1)printf("\nRequest for employee: %s %s has been deleted\n", search, curr->name);
                return;
            }
            curr = curr->next;
        }
        printf("\nEmployee with last name %s not found\n", search);
        }
        if (count > 1){
                curr=head;
            char searchName[25];
            printf("Write name to confirm person\n");
            scanf("%24s", &searchName);
            while (curr != NULL){
              if (strcmp(curr->surname, search)==0 && strcmp(curr->name, searchName)==0) {
                deletion();
                    if(check == 1)printf("\nRequest for employee: %s %s has been deleted\n", search, searchName);
                return;
                }
                curr = curr->next;
            }
        printf("\nEmployee: %s %s not found\n", search, searchName);
        }
        else printf("\nEmployee with last name %s not found\n", search);
    }
void editing(){
    time_t current_time;
    time(&current_time);
    struct tm *current_date = localtime(&current_time);

    if (isPending()){
            puts("1 - Creation date");
            puts("2 - Vacation type");
            puts("3 - Start date");
            puts("4 - Date end");
            puts("5 - Max days");
            puts("6 - Left days");
            int code;
            printf("What do you want to change\n");
            scanf("%d", &code);
            switch(code){
                case 1:
                    curr->date_create.day = 0;
                     printf("Enter creation date \n");
                while (curr->date_create.day == 0) {
                    printf("Day: ");
                    if (scanf("%d", &curr->date_create.day) != 1) {
                        printf("Error, try one more time\n");
                        fflush(stdin);
                        curr->date_create.day = 0;
                        }
                    else if (curr->date_create.day < 1 || curr->date_create.day > 31) {
                        printf("Error, try one more time\n");
                        curr->date_create.day = 0;
                        }
                    }
                    curr->date_create.month = 0;
                while (curr->date_create.month == 0) {
                    printf("Month: ");
                    if (scanf("%d", &curr->date_create.month) != 1) {
                        printf("Error, try one more time\n");
                        fflush(stdin);
                        curr->date_create.month = 0;
                    }
                    else if (curr->date_create.month < 1 || curr->date_create.month > 12) {
                        printf("Error, try one more time\n");
                        curr->date_create.month = 0;
                        }
                    }
                    curr->date_create.year=0;
                while (curr->date_create.year == 0) {
                    printf("Year: ");
                    if (scanf("%d", &curr->date_create.year) != 1) {
                        printf("Error, try one more time\n");
                        fflush(stdin);
                        curr->date_create.year = 0;
                    }
                    else if (curr->date_create.year < 1) {
                        printf("Error, try one more time\n");
                        curr->date_create.year = 0;
                        }
                    }break;

                case 2: printf("Enter vacation type (paid/unpaid): ");
                        do {
                            scanf("%24s", curr->vacation_type);
                            if (strcmp(curr->vacation_type, "paid") != 0 && strcmp(curr->vacation_type, "unpaid") != 0) {
                                printf("Invalid vacation type. Please enter either 'paid' or 'unpaid': ");
                            }
                        }
                        while (strcmp(curr->vacation_type, "paid") != 0 && strcmp(curr->vacation_type, "unpaid") != 0);break;
                case 3:
                    curr->date_start.day=0;
                    printf("Enter date_start\n");
                while (curr->date_start.day == 0) {
                    printf("Day: ");
                    if (scanf("%d", &curr->date_start.day) != 1) {
                        printf("Error, try one more time\n");
                        fflush(stdin);
                        curr->date_start.day = 0;
                    }
                    else if (curr->date_start.day < 1 || curr->date_start.day > 31) {
                        printf("Error, try one more time\n");
                        curr->date_start.day = 0;
                        }
                    }
                    curr->date_start.month=0;
                while (curr->date_start.month == 0) {
                    printf("Month: ");
                    if (scanf("%d", &curr->date_start.month) != 1) {
                        printf("Error, try one more time\n");
                        fflush(stdin);
                        curr->date_start.month = 0;
                    }
                    else if (curr->date_start.month < 1 || curr->date_start.month > 12) {
                        printf("Error, try one more time\n");
                        curr->date_start.month = 0;
                        }
                    }
                    curr->date_start.year=0;
                while (curr->date_start.year == 0) {
                    printf("Year: ");
                    if (scanf("%d", &curr->date_start.year) != 1) {
                        printf("Error, try one more time\n");
                        fflush(stdin);
                        curr->date_start.year = 0;
                    }
                    else if (curr->date_start.year < 1) {
                        printf("Error, try one more time\n");
                        curr->date_start.year = 0;
                        }
                    }break;
                case 4:
                    printf("Enter date_end \n");
                    curr->date_end.day=0;
                 while (curr->date_end.day == 0) {
                    printf("Day: ");
                    if (scanf("%d", &curr->date_end.day) != 1) {
                        printf("Error, try one more time\n");
                        fflush(stdin);
                        curr->date_end.day = 0;
                    }
                    else if (curr->date_end.day < 1 || curr->date_end.day > 31) {
                        printf("Error, try one more time\n");
                        curr->date_end.day = 0;
                        }
                    }
                    curr->date_end.month=0;
                while (curr->date_end.month == 0) {
                    printf("Month: ");
                    if (scanf("%d", &curr->date_end.month) != 1) {
                        printf("Error, try one more time\n");
                        fflush(stdin);
                        curr->date_end.month = 0;
                    }
                    else if (curr->date_end.month < 1 || curr->date_end.month > 12) {
                        printf("Error, try one more time\n");
                        curr->date_end.month = 0;
                        }
                    }
                    curr->date_end.year=0;
                while (curr->date_end.year == 0) {
                    printf("Year: ");
                    if (scanf("%d", &curr->date_end.year) != 1) {
                        printf("Error, try one more time\n");
                        fflush(stdin);
                        curr->date_end.year = 0;
                    }
                    else if (curr->date_end.year < 1) {
                        printf("Error, try one more time\n");
                        curr->date_end.year = 0;
                    }
                }break;

                case 5: printf("Enter max days of vacation :");
                while (scanf("%d", &curr->max_days) != 1 || curr->max_days < 1) {
                    printf("Error, try one more time\n");
                    fflush(stdin);
                }break;

                case 6: printf("Enter days left of vacation :");
                while (scanf("%d", &curr->days_left) != 1 || curr->days_left < 0) {
                    printf("Error, try one more time\n");
                    fflush(stdin);
                }break;

            }
            check=1;
        }
    else{
        if(curr->date_create.day!=0)printf("Vacation has already started\n");
        else printf("No request found\n");
    }
}
void editRequest() {
    check=0;
    time_t current_time;
    time(&current_time);
    struct tm *current_date = localtime(&current_time);
     if(head==NULL){
     printf("No employees found\n");
     return;
    }

    curr=head;
    int found = 0;
    while (curr != NULL) {
        if (curr->date_create.day != 0) {
            found = 1;
            break;
        }
        curr = curr->next;
    }
    if (!found) {
        printf("No requests found\n");
        return;
    }
        pendingList();
        if(check==1)return;
        check=0;
        char search[25];
        printf("Enter surname to edit request\n");
        scanf("%24s", search);
        int count=0;
        curr=head;
        while (curr != NULL){
                if(!strcmp(curr->surname, search)){
                    count++;
                }
           curr = curr->next;
        }
        curr=head;
    if(count == 1){
            curr=head;
        while (curr != NULL) {
            if (!strcmp(curr->surname, search)) {
            editing();
            return;
        }
        curr = curr->next;
        }
        printf("Employee with last name %s not found\n", search);
    }
    if (count > 1){
                curr=head;
            char searchName[25];
            printf("Write name to confirm person\n");
            scanf("%24s", &searchName);
            while (curr != NULL){
              if (strcmp(curr->surname, search)==0 && strcmp(curr->name, searchName)==0) {
                editing();
                return;
              }
              curr = curr->next;
            }
            printf("Employee: %s %s not found\n", search, searchName);
    }
}
void vacationTypeList(){
    if(head==NULL){
     printf("No employees found\n");
     return;
    }

    curr=head;
    int found = 0;
    while (curr != NULL) {
        if (curr->date_create.day != 0) {
            found = 1;
            break;
        }
        curr = curr->next;
    }
    if (!found) {
        printf("No requests found\n");
        return;
    }
    int code;
    int count=0;
    printf("Enter action code 1-paid, 2-unpaid: ");
    scanf("%d", &code);
printf("+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+\n");
printf("| Surname         | Name            | Creation date   | Vacation type   | Start date      | End date        | Max days        | Days left       |\n");
printf("+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+\n");
    switch(code){
        case 1:
            curr=head;
            while(curr!=NULL){
                if(strcmp(curr->vacation_type, "paid")==0){
                   printf("| %-15s | %-15s | %02d.%02d.%04d      | %-15s | %02d.%02d.%04d      | %02d.%02d.%04d      | %-15d | %-15d |\n", curr->surname, curr->name, curr->date_create.day, curr->date_create.month, curr->date_create.year, curr->vacation_type, curr->date_start.day, curr->date_start.month, curr->date_start.year, curr->date_end.day, curr->date_end.month, curr->date_end.year, curr->max_days, curr->days_left);
                    printf("+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+\n");
                    count = 1;
                }
                curr=curr->next;
            }
            if (count==0)printf("Requests are not found\n");break;
        case 2:
            curr=head;
            while(curr!=NULL){
                if(strcmp(curr->vacation_type, "unpaid")==0){
                    printf("| %-15s | %-15s | %02d.%02d.%04d      | %-15s | %02d.%02d.%04d      | %02d.%02d.%04d      | %-15d | %-15d |\n", curr->surname, curr->name, curr->date_create.day, curr->date_create.month, curr->date_create.year, curr->vacation_type, curr->date_start.day, curr->date_start.month, curr->date_start.year, curr->date_end.day, curr->date_end.month, curr->date_end.year, curr->max_days, curr->days_left);
                    printf("+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+\n");
                    count = 1;
                }
                curr=curr->next;
            }
            if (count==0)printf("Requests are not found\n");break;
            default:
            printf("Invalid action code\n");
            break;
        }
    }
void surnameList(){
    if(head==NULL){
     printf("No employees found\n");
     return;
    }

    curr=head;
    int found = 0;
    while (curr != NULL) {
        if (curr->date_create.day != 0) {
            found = 1;
            break;
        }
        curr = curr->next;
    }
    if (!found) {
        printf("No requests found\n");
        return;
    }
    int count=0;
    char search[25];
    printf("Enter surname to search request: ");
    scanf("%24s", &search);

    printf("+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+\n");
    printf("| Surname         | Name            | Creation date   | Vacation type   | Start date      | End date        | Max days        | Days left       |\n");
    printf("+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+\n");
            curr=head;
            while(curr!=NULL){
                if(strcmp(curr->surname, search)==0){
                    printf("| %-15s | %-15s | %02d.%02d.%04d      | %-15s | %02d.%02d.%04d      | %02d.%02d.%04d      | %-15d | %-15d |\n", curr->surname, curr->name, curr->date_create.day, curr->date_create.month, curr->date_create.year, curr->vacation_type, curr->date_start.day, curr->date_start.month, curr->date_start.year, curr->date_end.day, curr->date_end.month, curr->date_end.year, curr->max_days, curr->days_left);
                    printf("+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+\n");
                    count = 1;
                }
                curr=curr->next;
            }
            if (count==0) printf("Employee with last name %s not found\n", search);

}
void sortByDaysLeft() {
    if (head == NULL) {
        printf("No employees found\n");
        return;
    }
    curr=head;
    int count = 0;
    while (curr != NULL) {
        count++;
        curr = curr->next;
    }
    if (count <= 1) {
        printf("Not enough employees to sort\n");
        return;
    }
    int swapped;
    struct vacation *ptr1;
    struct vacation *lptr = NULL;
    do {
        swapped = 0;
        ptr1 = head;
        while (ptr1->next != lptr) {
            if (ptr1->days_left < ptr1->next->days_left) {
                struct vacation *temp = ptr1;
                struct vacation *nextTemp = ptr1->next;
                if (ptr1 == head) {
                    head = nextTemp;
                } else {
                    temp->prev->next = nextTemp;
                }
                nextTemp->prev = temp->prev;
                temp->next = nextTemp->next;

                if (nextTemp->next != NULL) {
                    nextTemp->next->prev = temp;
                }
                nextTemp->next = temp;
                temp->prev = nextTemp;
                swapped = 1;
            } else {
                ptr1 = ptr1->next;
            }
        }
        lptr = ptr1;
    } while (swapped);
}
void saveDataToBinaryFile(const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Unable to open file %s\n", filename);
        return;
    }

    curr = head;
    while (curr != NULL) {
        fwrite(curr, sizeof(struct vacation), 1, file);
        curr = curr->next;
    }

    fclose(file);
}
void saveDataToFile(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Unable to open file %s\n", filename);
        return;
    }
    saveDataToBinaryFile("load.bin");
    fprintf(file,"+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+\n");
    fprintf(file,"| Surname         | Name            | Creation date   | Vacation type   | Start date      | End date        | Max days        | Days left       |\n");
    fprintf(file,"+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+\n");
    curr = head;
    while (curr != NULL) {
        fprintf(file,"| %-15s | %-15s | %02d.%02d.%04d      | %-15s | %02d.%02d.%04d      | %02d.%02d.%04d      | %-15d | %-15d |\n", curr->surname, curr->name, curr->date_create.day, curr->date_create.month, curr->date_create.year, curr->vacation_type, curr->date_start.day, curr->date_start.month, curr->date_start.year, curr->date_end.day, curr->date_end.month, curr->date_end.year, curr->max_days, curr->days_left);
        fprintf(file,"+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+\n");
        curr = curr->next;
    }

    fclose(file);
    printf("Data saved to file %s\n", filename);
}
void loadDataFromFile(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Unable to open file %s\n", filename);
        return;
    }

    struct vacation temp;
    while (fread(&temp, sizeof(struct vacation), 1, file) == 1) {
        struct vacation* curr = (struct vacation*)malloc(sizeof(struct vacation));
        if (curr == NULL) {
            printf("Memory allocation error\n");
            fclose(file);
            return;
        }

        memcpy(curr, &temp, sizeof(struct vacation));
        curr->prev = NULL;
        curr->next = NULL;

        if (head == NULL) {
            head = curr;
            tail = curr;
        } else {
            tail->next = curr;
            curr->prev = tail;
            tail = curr;
        }
    }

    fclose(file);
    printf("Data loaded from file %s\n", filename);
}
