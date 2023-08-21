//
////��ŷ, ���� �ڵ�
//#define NAME_LEN 20
//#define PERSON_NUM 1
//#define P_SIZE 21
//#define ENTER_KEY 13
//#define TAB_KEY 9
//#define BACKSPACE 8
//
//
//typedef struct _Person
//{
//    char name[NAME_LEN];
//    int score;
//    char password[20];
//} Person;
//
//int sum = 7;
//
//
//
//#include<windows.h>
//#include<conio.h>
//#include<time.h>
//#include<stdlib.h>
//#include<stdio.h>
////
////Person* perArr = (Person*)malloc(sizeof(Person));
//void loaddata(Person*, int*);
//void signup(Person*, int*);
//void peopleplus(Person*, int);
//void get_pw(char*);
//int login(Person*, int*);
//int pw_conf(Person*, int);
//
//void loaddata(Person* parr, int* pnum)
//{
//    FILE* file = fopen("��ŷ.dat", "r");
//    if (file == NULL)
//    {
//        return;
//    }
//
//    while (1)
//    {
//        fscanf(file, "%s %d %s", parr[*pnum].name, &parr[*pnum].score, parr[*pnum].password);
//        if (feof(file) != 0)
//            break;
//        (*pnum)++;
//    }
//    fclose(file);
//}
//
//void signup(Person* parr, int* person)
//{
//
//    int i;
//
//    while (1)
//    {
//        printf("ȸ������");
//        gotoxy(2, 4); printf("���̵� �����ּ��� : ");
//        gotoxy(2, 5); printf("��й�ȣ �����ּ��� (����� �����ּ���) :");
//        gotoxy(14, 4); scanf("%s", parr[*person].name);
//        for (i = 0; i < *person; i++)
//            if (strcmp(parr[i].name, parr[*person].name) == 0)
//            {
//                printf("\n�̹� �����ϴ� ���̵��Դϴ�. ù��° ȭ������ ���ư��ϴ�."); Sleep(2000); system("cls");
//                return;
//            }
//        gotoxy(25, 5); get_pw(parr[*person].password);
//        break;
//
//    }
//    printf("\n\n%s���� ȸ�������� �Ϸ��߽��ϴ�.", parr[*person].name);
//    parr[*person].score = 0;
//    (*person)++;
//    peopleplus(parr, *person);
//    Sleep(1500); system("cls");
//}
//
//void peopleplus(Person* parr, int people)
//{
//    Person* arr;
//    if (people + 2 == sum)
//    {
//        sum += 3;
//        arr = (Person*)realloc(parr, sizeof(Person) * (sum));
//        if (arr != NULL)parr = arr;
//    }
//}
//
//void get_pw(char* buf)
//{
//    int cnt = 0, key;  // �Է� ���� ���� ���� Ű
//
//    while (1)
//    {
//        key = _getch();  // �� ���� �Է¹���
//
//        if (key == ENTER_KEY)  // ���� �Ǵ� �� Ű�� ����
//            break;
//        if (key == BACKSPACE && cnt > 0)
//        {
//            buf[cnt] = NULL;
//            cnt--;
//            putchar('\b'); putchar(' '); putchar('\b');
//            continue;
//        }
//        else if (key == BACKSPACE && cnt == 0)continue;
//        buf[cnt++] = (char)key;   // ���ۿ� ���� �����ϰ� ī��Ʈ 1 ����
//        putchar('*');  // ȭ�鿡 �� ǥ��
//
//        if (cnt == P_SIZE - 1)  // �ִ� ũ�⸦ �Ѿ�� ����
//            break;
//    }
//
//    buf[cnt] = '\0';    // ���ڿ��� ����� ���� �� ���� ������
//}
//int login(Person* parr, int* person)
//{
//    while (1)
//    {
//        int retry = 0;
//
//        int i, choice;
//        char name[NAME_LEN];
//        gotoxy(2, 4); printf("���̵� �����ּ��� : ");
//        gotoxy(2, 5); printf("��й�ȣ �����ּ��� : ");
//        gotoxy(15, 4); scanf("%s", name); fflush(stdin);
//        for (i = 0; i < *person; i++)
//        {
//            if (strcmp(name, parr[i].name) == 0)
//            {
//                retry = pw_conf(parr, i); system("cls"); if (retry == 1)break;
//                return i;
//            }
//        }
//        if (retry == 1) { system("cls"); continue; }
//        gotoxy(2, 8); printf("�̸��� �������� �ʽ��ϴ� \n 1.�ٽ�   2.ȸ������");
//        gotoxy(20, 8); scanf("%d", &choice); fflush(stdin);
//        switch (choice)
//        {
//        case 1:gotoxy(10, 4); system("cls");; continue;
//        case 2:system("cls"); signup(parr, person); return -1;
//        }
//    }
//}
//int pw_conf(Person* parr, int i)
//{
//    char password[P_SIZE]; int choice;
//    while (1)
//    {
//        gotoxy(15, 5); get_pw(password);
//        if (strcmp(password, parr[i].password) == 0)
//            return 2;
//        else
//        {
//            printf("\n1. �̸� �ٽ� �Է��ϱ�    2. ��й�ȣ �ٽ� �Է��ϱ� -> "); scanf("%d", &choice);
//            switch (choice)
//            {
//            case 1: system("cls"); return 1;
//            case 2:gotoxy(15, 5); printf("                       "); continue;
//            }
//        }
//    }
//}
//
//void scorecompare(Person* parr, int person, int people)
//{
//    Person temp;
//    int i, j;
//    if (people == 1)return;
//    else
//        for (i = 0; i < people - 1; i++)
//            for (j = i + 1; j < people; j++)
//                if (parr[i].score < parr[j].score)
//                {
//                    temp = parr[i];
//                    parr[i] = parr[j];
//                    parr[j] = temp;
//                }
//}
//void printranking(Person* parr, int people)
//{
//    int i = 0;
//    gotoxy(7, 0); printf("��ŷ!!"); gotoxy(0, 1); printf("���  �̸�"); gotoxy(10, 1); printf("����");
//    if (people < 5)
//        for (i = 0; i < people; i++)
//        {
//            gotoxy(0, 2 + i); printf("%d.    %s", i + 1, parr[i].name);
//            gotoxy(15, 2 + i); printf("%d", parr[i].score);
//        }
//    else
//        for (i = 0; i < 5; i++)
//        {
//            gotoxy(0, 2 + i); printf("%d.    %s", i + 1, parr[i].name);
//            gotoxy(15, 2 + i); printf("%d", parr[i].score);
//        }Sleep(4000);
//        system("cls");
//}