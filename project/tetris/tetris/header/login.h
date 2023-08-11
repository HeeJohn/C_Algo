#pragma once
#ifndef LOGIN
#define LOGIN // 로그인, 정렬 헤더파일

//랭킹, 계정 코딩
#define NAME_LEN 20
#define PERSON_NUM 1
#define P_SIZE 21
#define ENTER_KEY 13
#define TAB_KEY 9
#define BACKSPACE 8


typedef struct _Person
{
    char name[NAME_LEN];
    int score;
    char password[20];
} Person;

int sum = 7;



/*함수 원형 선언*/

//Person* perArr = (Person*)malloc(sizeof(Person));
void loaddata(Person*, int*);
void signup(Person*, int*);
void peopleplus(Person*, int);
void get_pw(char*);
int login(Person*, int*);
int pw_conf(Person*, int);

#endif