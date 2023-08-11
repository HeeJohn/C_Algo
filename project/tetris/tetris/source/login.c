
/*
void loaddata(Person* parr, int* pnum)
{
    FILE* file = fopen("랭킹.dat", "r");
    if (file == NULL)
    {
        return;
    }

    while (1)
    {
        fscanf(file, "%s %d %s", parr[*pnum].name, &parr[*pnum].score, parr[*pnum].password);
        if (feof(file) != 0)
            break;
        (*pnum)++;
    }
    fclose(file);
}

void signup(Person* parr, int* person)
{

    int i;

    while (1)
    {
        printf("회원가입");
        gotoxy(2, 4); printf("아이디를 적어주세요 : ");
        gotoxy(2, 5); printf("비밀번호 적어주세요 (영어로 적어주세요) :");
        gotoxy(14, 4); scanf("%s", parr[*person].name);
        for (i = 0; i < *person; i++)
            if (strcmp(parr[i].name, parr[*person].name) == 0)
            {
                printf("\n이미 존재하는 아이디입니다. 첫번째 화면으로 돌아갑니다."); Sleep(2000); system("cls");
                return;
            }
        gotoxy(25, 5); get_pw(parr[*person].password);
        break;

    }
    printf("\n\n%s님의 회원가입을 완료했습니다.", parr[*person].name);
    parr[*person].score = 0;
    (*person)++;
    peopleplus(parr, *person);
    Sleep(1500); system("cls");
}
void peopleplus(Person* parr, int people)
{
    Person* arr;
    if (people + 2 == sum)
    {
        sum += 3;
        arr = (Person*)realloc(parr, sizeof(Person) * (sum));
        if (arr != NULL)parr = arr;
    }
}
void get_pw(char* buf)
{
    int cnt = 0, key;  // 입력 받은 글자 수와 키

    while (1)
    {
        key = _getch();  // 한 글자 입력받음

        if (key == ENTER_KEY)  // 엔터 또는 탭 키면 종료
            break;
        if (key == BACKSPACE && cnt > 0)
        {
            buf[cnt] = NULL;
            cnt--;
            putchar('\b'); putchar(' '); putchar('\b');
            continue;
        }
        else if (key == BACKSPACE && cnt == 0)continue;
        buf[cnt++] = (char)key;   // 버퍼에 글자 저장하고 카운트 1 증가
        putchar('*');  // 화면에 별 표시

        if (cnt == P_SIZE - 1)  // 최대 크기를 넘어가면 종료
            break;
    }

    buf[cnt] = '\0';    // 문자열로 만들기 위해 널 문자 마무리
}
int login(Person* parr, int* person)
{
    while (1)
    {
        int retry = 0;

        int i, choice;
        char name[NAME_LEN];
        gotoxy(2, 4); printf("아이디를 적어주세요 : ");
        gotoxy(2, 5); printf("비밀번호 적어주세요 : ");
        gotoxy(15, 4); scanf("%s", name); fflush(stdin);
        for (i = 0; i < *person; i++)
        {
            if (strcmp(name, parr[i].name) == 0)
            {
                retry = pw_conf(parr, i); system("cls"); if (retry == 1)break;
                return i;
            }
        }
        if (retry == 1) { system("cls"); continue; }
        gotoxy(2, 8); printf("이름이 존재하지 않습니다 \n 1.다시   2.회원가입");
        gotoxy(20, 8); scanf("%d", &choice); fflush(stdin);
        switch (choice)
        {
        case 1:gotoxy(10, 4); system("cls");; continue;
        case 2:system("cls"); signup(parr, person); return -1;
        }
    }
}
int pw_conf(Person* parr, int i)
{
    char password[P_SIZE]; int choice;
    while (1)
    {
        gotoxy(15, 5); get_pw(password);
        if (strcmp(password, parr[i].password) == 0)
            return 2;
        else
        {
            printf("\n1. 이름 다시 입력하기    2. 비밀번호 다시 입력하기 -> "); scanf("%d", &choice);
            switch (choice)
            {
            case 1: system("cls"); return 1;
            case 2:gotoxy(15, 5); printf("                       "); continue;
            }
        }
    }
}

void scorecompare(Person* parr, int person, int people)
{
    Person temp;
    int i, j;
    if (people == 1)return;
    else
        for (i = 0; i < people - 1; i++)
            for (j = i + 1; j < people; j++)
                if (parr[i].score < parr[j].score)
                {
                    temp = parr[i];
                    parr[i] = parr[j];
                    parr[j] = temp;
                }
}
void printranking(Person* parr, int people)
{
    int i = 0;
    gotoxy(7, 0); printf("랭킹!!"); gotoxy(0, 1); printf("등수  이름"); gotoxy(10, 1); printf("점수");
    if (people < 5)
        for (i = 0; i < people; i++)
        {
            gotoxy(0, 2 + i); printf("%d.    %s", i + 1, parr[i].name);
            gotoxy(15, 2 + i); printf("%d", parr[i].score);
        }
    else
        for (i = 0; i < 5; i++)
        {
            gotoxy(0, 2 + i); printf("%d.    %s", i + 1, parr[i].name);
            gotoxy(15, 2 + i); printf("%d", parr[i].score);
        }Sleep(4000);
        system("cls");
}*/