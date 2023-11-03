#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>      // ���������� ����������� ����� windows.h, ��� SetConsoleCP() �� SetConsoleOutputCP()

// ��������� �������
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


// ������� ������� ��������
int main()
{
    SetConsoleCP(1251); //������������ ��������� Windows-1251 � ���� ��������
    SetConsoleOutputCP(1251); // ������������ ��������� Windows-1251 � ���� ���������
    // ����� ������ �� ���� Lucida Console

    int kod; // ����� ��� ����� 䳿 � ����

    while (1)
    {
        // ���� ��������
        puts("���� 䳿");
        puts("1 - ��������� ��������;");
        puts("2 - ��������� ��������;");
        puts("3 - ��������� ����������� �����;");
        puts("4 - ��������� ��� �����;");
        puts("5 - ��������� ���������� ����� ��� �� ���������� � ������ �������;");
        puts("6 - ��������� ����� ��� ������ ���� ������;");
        puts("7 - ��������� ����� ��� ����������, �� �������� ��� ��������� ������;");
        puts("8 - ����� ��� ���������� � ������� �����;");
        puts("9 - ��������� ������� ������� �� ����������� �����, ������� ������, ������, ����� ����;");
        puts("10 - ���������� �� ���� ���� ������.");
        puts("0 - �����");

        // ���� ������ 䳿
        puts("������ ��� ������ 䳿");
        scanf("%d", &kod);
        printf("������� ��� %d \n", kod);
        // ������ ������� ����� ������ 䳿
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
    return EXIT_SUCCESS; // EXIT_SUCCESS - ���������, �� ������ ������ ��������� ��������}
}
// ������� �������� ������ �����
void CreateElement() // ������ ������� �����, � ������ ������� ����� �� ����������,
//��� �� ��������� ���������� ����������
{
    if (begin == NULL) {       //���� �� ������ �������

        begin = (struct sport*)malloc(sizeof(struct sport));    //�������� ���'��� � ������� ������
        if (begin == NULL) {                         //���������� ���'���
            puts("Error with allocation memory");
            return;               //���������� ������� � ��� �������
        }

        end = begin;   //������� ����� ������

        end->next = NULL;    //��������� �������� �������� �������� �� 0

        enterSport();     //�������

        return;       //���������� �������
    }


    if (begin != NULL) {  //���� �� �� ������ �������

        tt = begin;    //�����'������� �������

        begin = (struct sport*)malloc(sizeof(struct sport));    //�������� ���'��� � ������� ������
        if (begin == NULL) {                         //���������� ���'���
            puts("Error with allocation memory");
            return;               //���������� ������� � ��� �������
        }

        begin->next = tt;  //����� ������� ����� �� �������

        enterSport();    //������� ����

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
    struct sport* cur;    //��������
    struct sport* prev;    //���������

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
