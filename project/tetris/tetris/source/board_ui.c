#include"common.h"
#include"board_ui.h"
#include"block.h"
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<stdio.h>


/* ========== 로컬 함수 원형 선언 (board_ui.c범위) ========== */
int readBestScoreFromFile(const char* filename);
void draw_status_info(int x, int y, const char* label, int value);
void draw_status_description(int x, int y, const char* description);
void displayInstructions(int x, int y);
void find_middle(int* consoleWidth, int* consoleHeight);

/* ========== 로컬 함수 원형 선언 (board_ui.c범위) ========== */


/* ---------------- 콘솔 내 위치(커서) 이동 함수 ---------------- */
void gotoxy(int x, int y) 
{ //gotoxy함수 
    COORD pos = { 2*x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


/* ===================== 게임 안내 및 조작 설명   ===================== */

// 게임 시작 안내와 조작 설명을 출력하는 함수
void displayInstructions(int x, int y) 
{
    gotoxy(x, y + 7);  printf("아무 키나 누르세요..");
    gotoxy(x, y + 9);  printf("   △    : 모양 변경");
    gotoxy(x, y + 10); printf(" ◁   ▷  : 좌 / 우 이동");
    gotoxy(x, y + 11); printf("   ▽    : 하강");
    gotoxy(x, y + 12); printf(" SPACE  : 빠른 하강");
    gotoxy(x, y + 13); printf("   P    : 일시 정지");
    gotoxy(x, y + 14); printf("  ESC   : 종료");
    gotoxy(x, y + 16); printf("하드 드롭과 콤보에 보너스 포인트 부여");
}

// 시작 페이지를 출력하고 키 입력을 기다리는 함수
void startPage() 
{
    //int* consoleWidth, *consoleHeight;

    //find_middle(consoleWidth, consoleHeight);

    int x = 30;
    int y = 10;
    int cnt = 0;

    gotoxy(x + 5, y + 2); printf("테트리스");
    displayInstructions(x, y);

    while (!_kbhit()) 
    {
        if (cnt % 200 == 0) { gotoxy(x + 4, y + 1); printf("★"); }
        if ((cnt % 200 - 100) == 0) { gotoxy(x + 4, y + 1); printf("  "); }
        if ((cnt % 350) == 0) { gotoxy(x + 13, y + 2); printf("☆"); }
        if ((cnt % 350 - 100) == 0) { gotoxy(x + 13, y + 2); printf("  "); }
        Sleep(10);
        cnt++;
    }

    while (_kbhit()) _getch();
}

void find_middle(int * consoleWidth, int *consoleHeight) 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
  
    if (GetConsoleScreenBufferInfo(hConsole, &consoleInfo)) 
    {
        *consoleWidth = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
        *consoleHeight = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;

        printf("콘솔 가로 크기: %d\n", *consoleWidth);
        printf("콘솔 세로 크기: %d\n", *consoleHeight);

    }
    else 
    {
        fprintf(stderr, "콘솔 정보를 얻어오는데 실패하였습니다.\n");
        exit(1);
    }
}
/* ===================== 게임 안내 및 조작 설명   ===================== */



/* =========== 게임 프리셋 ( 보드, 상태표시, 최고 점수 ) =========== */

/* ------------- 게임시작 준비 (preset) ------------- */
// 게임 시작 시 초기 설정 함수
void preset(void) 
{
    system("cls"); // 화면을 지우고 게임 준비
    reset_board_curr(); // 현재 블록 배열 초기화
    draw_status(); // 상태 표시 화면 그리기
    draw_board(); // 게임 보드 그리기

    b_type_next = rand() % 7; // 다음에 나올 블록 종류 랜덤 생성
    create_nblock(); // 새로운 블록 생성
    best_score = readBestScoreFromFile("score.dat"); // 최고 점수 읽어오기
}


/* ------------- 최고 점수 ------------- */
// 최고 점수를 읽어오는 함수
int readBestScoreFromFile(const char* filename) 
{
    int bestScore = 0;
    FILE* file = fopen(filename, "rt");

    if (file != NULL) 
    {
        fscanf(file, "%d", &bestScore);
        fclose(file);
    }

    return bestScore;
}

/* ------------- 현재 보드판 ------------- */
// 현재 게임보드를 초기화하는 함수
void reset_board_curr(void) 
{
    int i, j;

    // 게임판을 0으로 초기화
    for (i = 0; i < BOARD_Y; i++) 
        for (j = 0; j < BOARD_X; j++) 
        {
            board_curr[i][j] = 0;
            board_prev[i][j] = 100;
        }

    // 천장 생성
    for (j = 1; j < BOARD_X; j++) 
        board_curr[3][j] = CEILLING;
   

    // 좌우 벽 생성
    for (i = 1; i < BOARD_Y - 1; i++) 
    {
        board_curr[i][0] = WALL;
        board_curr[i][BOARD_X - 1] = WALL;
    }

    // 바닥 벽 생성
    for (j = 0; j < BOARD_X; j++) 
        board_curr[BOARD_Y - 1][j] = WALL;
   
}

/* ------------- 이전 보드판 ------------- */
// 이전 보드판을 초기화하는 함수
void reset_board_prev(void) {
    int i, j;

    // board_prev 초기화
    for (i = 0; i < BOARD_Y; i++) {
        for (j = 0; j < BOARD_X; j++) {
            board_prev[i][j] = 100;
        }
    }
}

/* -------------------------  보드판 ------------------------- */
// 게임판을 그리는 함수
void draw_board(void) {
    int i, j;

    for (j = 1; j < BOARD_X - 1; j++) 
        // 천장은 계속 새로운 블럭이 지나가서 지워지면 새로 그려줌
        if (board_curr[3][j] == EMPTY) board_curr[3][j] = CEILLING;


    for (i = 0; i < BOARD_Y; i++) 
        for (j = 0; j < BOARD_X; j++) 
            // cpy와 비교하여 값이 달라진 부분만 새로 그려줌
            if (board_prev[i][j] != board_curr[i][j]) 
            {
                gotoxy(BOARD_X_ADJ + j, BOARD_Y_ADJ + i);
                switch (board_curr[i][j]) 
                {
                case EMPTY: // 빈 칸 모양
                    printf("  ");
                    break;
                case CEILLING: // 천장 모양
                    printf(". ");
                    break;
                case WALL: // 벽 모양
                    printf("▩");
                    break;
                case INACTIVE_BLOCK: // 굳은 블럭 모양
                    printf("□");
                    break;
                case ACTIVE_BLOCK: // 움직이고 있는 블럭 모양
                    printf("■");
                    break;
                }
            }
       
   

    // 게임판을 그린 후 board_prev에 복사
    for (i = 0; i < BOARD_Y; i++) 
        for (j = 0; j < BOARD_X; j++) 
            board_prev[i][j] = board_curr[i][j];
        
    
}

/* ----------------- 게임 상태 표시 ----------------- */

// 상태 표시 정보를 그리는 함수
void draw_status_info(int x, int y, const char* label, int value)
{
    gotoxy(x, y);
    printf(" %s : %6d", label, value);
}

// 상태 표시 설명을 그리는 함수
void draw_status_description(int x, int y, const char* description)
{
    gotoxy(x, y);
    printf(" %s", description);
}


// 게임 상태를 표시하는 함수
void draw_status(void) 
{
    int y = 3; // level, goal, score만 게임 중에 값이 바뀔 수 있으므로 y 값을 저장

    draw_status_info(STATUS_X_ADJ, STATUS_Y_LEVEL = y, "LEVEL", level);
    draw_status_info(STATUS_X_ADJ, STATUS_Y_GOAL = y + 1, "GOAL", 10 - cnt);

    // NEXT 블록 표시
    for (int i = 0; i < 5; i++)
    {
        if (i == 2) draw_status_description(STATUS_X_ADJ, y + 3 + i, "|             |");
        else draw_status_description(STATUS_X_ADJ, y + 3 + i, "|             |");
    }

    draw_status_info(STATUS_X_ADJ, y + 8, "YOUR SCORE", score);
    draw_status_info(STATUS_X_ADJ, STATUS_Y_SCORE = y + 9, "LAST SCORE", last_score);
    draw_status_info(STATUS_X_ADJ, y + 12, "BEST SCORE", best_score);

    // 조작 설명 표시
    draw_status_description(STATUS_X_ADJ, y + 15, "  △   : Shift        SPACE : Hard Drop");
    draw_status_description(STATUS_X_ADJ, y + 16, "◁   ▷ : Left / Right   P   : Pause");
    draw_status_description(STATUS_X_ADJ, y + 17, "  ▽   : Soft Drop     ESC  : Quit");
}


/* =========== 게임 프리셋 ( 보드, 상태표시, 최고 점수 ) =========== */


/* ==================== 게임 오버 처리 ==================== */

// 게임 오버 상황을 체크하고 처리하는 함수
void check_game_over(void) {
    int i;
    int x = 5;
    int y = 5;

    for (i = 1; i < BOARD_X - 2; i++) {
        if (board_curr[3][i] > 0) { // 천장(위에서 세번째 줄)에 inactive 블록이 생성되면 게임 오버
            print_game_over_message(x, y); // 게임 오버 메세지 출력
            last_score = score; // 게임 점수를 저장
            update_best_score(); // 최고 점수 갱신 여부 확인 및 처리
            Sleep(1000);
            while (_kbhit()) _getch();
            key = _getch();
            preset(); // 게임 재시작을 위한 초기화
        }
    }
}

// 게임 오버 메세지 출력 함수
void print_game_over_message(int x, int y) {
    gotoxy(x, y + 0); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
    gotoxy(x, y + 1); printf("▤                              ▤");
    gotoxy(x, y + 2); printf("▤  +-----------------------+   ▤");
    gotoxy(x, y + 3); printf("▤  |  G A M E  O V E R..   |   ▤");
    gotoxy(x, y + 4); printf("▤  +-----------------------+   ▤");
    gotoxy(x, y + 5); printf("▤   YOUR SCORE: %6d         ▤", score);
    gotoxy(x, y + 6); printf("▤                              ▤");
    gotoxy(x, y + 7); printf("▤  Press any key to restart..  ▤");
    gotoxy(x, y + 8); printf("▤                              ▤");
    gotoxy(x, y + 9); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
}

// 최고 점수 갱신 및 파일 저장 함수
void update_best_score() {
    if (score > best_score) { // 최고 기록 갱신 시
        FILE* file = fopen("score.dat", "wt"); // score.dat에 점수 저장

        print_best_score_message(); // 최고 점수 메세지 출력

        if (file != NULL) {
            fprintf(file, "%d", score);
            fclose(file);
        }
        else {
            gotoxy(0, 0);
            printf("FILE ERROR: SYSTEM CANNOT WRITE BEST SCORE ON \"SCORE.DAT\"");
        }
    }
}

// 최고 점수 메세지 출력 함수
void print_best_score_message() {
    int x = 5;
    int y = 11;

    gotoxy(x, y + 6); printf("▤  ★★★ BEST SCORE! ★★★   ▤  ");
}



/* ==================== 게임 오버 처리 ==================== */


/* ==================== 게임 일시 정지 ==================== */
// 게임 일시정지 함수
void pause(void) 
{
    display_pause_message(); // 일시정지 메세지 출력
    _getch(); // 키 입력 대기

    clear_and_redraw(); // 화면 초기화 및 재그리기
    draw_next_block(); // 다음 블록 그리기
}

// 일시정지 메세지 출력 함수
void display_pause_message()
{
    int x = 5;
    int y = 5;

    gotoxy(x, y + 0); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
    gotoxy(x, y + 1); printf("▤                              ▤");
    gotoxy(x, y + 2); printf("▤  +-----------------------+   ▤");
    gotoxy(x, y + 3); printf("▤  |       P A U S E       |   ▤");
    gotoxy(x, y + 4); printf("▤  +-----------------------+   ▤");
    gotoxy(x, y + 5); printf("▤  Press any key to resume..   ▤");
    gotoxy(x, y + 6); printf("▤                              ▤");
    gotoxy(x, y + 7); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
}

// 화면 초기화 및 재그리기 
// 함수
void clear_and_redraw() {
    system("cls"); // 화면 지우기

    reset_board_prev(); // 이전 블록 배열 초기화
    draw_board(); // 게임 보드 그리기
    draw_status(); // 상태 표시 그리기
}

// 다음 블록 그리기 함수
void draw_next_block()
{
    for (int i = 1; i < 3; i++) 
     // 다음 블록 그리기
        for (int j = 0; j < 4; j++) 
        {
            int x = BOARD_X + BOARD_X_ADJ + 3 + j;
            int y = i + 6;

            if (blocks[b_type_next][0][i][j] == 1) 
            {
                gotoxy(x, y);
                printf("■");
            }
            else 
            {
                gotoxy(x, y);
                printf("  ");
            }
        }
}

/* ==================== 게임 일시 정지 ==================== */



void check_level_up(void) {
    int i, j;

    if (cnt >= 10) { //레벨별로 10줄씩 없애야함. 10줄이상 없앤 경우 
        draw_board();
        level_up_on = 1; //레벨업 flag를 띄움 
        level += 1; //레벨을 1 올림 
        cnt = 0; //지운 줄수 초기화   

        for (i = 0; i < 4; i++) {
            gotoxy(BOARD_X_ADJ + (BOARD_X / 2) - 3, BOARD_Y_ADJ + 4);
            printf("             ");
            gotoxy(BOARD_X_ADJ + (BOARD_X / 2) - 2, BOARD_Y_ADJ + 6);
            printf("             ");
            Sleep(200);

            gotoxy(BOARD_X_ADJ + (BOARD_X / 2) - 3, BOARD_Y_ADJ + 4);
            printf("☆LEVEL UP!☆");
            gotoxy(BOARD_X_ADJ + (BOARD_X / 2) - 2, BOARD_Y_ADJ + 6);
            printf("☆SPEED UP!☆");
            Sleep(200);
        }
        reset_board_prev(); //텍스트를 지우기 위해 board_prev을 초기화.
        //(board_prev와 board_curr가 전부 다르므로 다음번 draw()호출시 게임판 전체를 새로 그리게 됨) 

        for (i = BOARD_Y - 2; i > BOARD_Y - 2 - (level - 1); i--) { //레벨업보상으로 각 레벨-1의 수만큼 아랫쪽 줄을 지워줌 
            for (j = 1; j < BOARD_X - 1; j++) {
                board_curr[i][j] = INACTIVE_BLOCK; // 줄을 블록으로 모두 채우고 
                gotoxy(BOARD_X_ADJ + j, BOARD_Y_ADJ + i); // 별을 찍어줌.. 이뻐보이게 
                printf("★");
                Sleep(20);
            }
        }
        Sleep(100); //별찍은거 보여주기 위해 delay 
        check_line(); //블록으로 모두 채운것 지우기
        //.check_line()함수 내부에서 level up flag가 켜져있는 경우 점수는 없음.         
        switch (level) { //레벨별로 속도를 조절해줌. 
        case 2:
            speed = 50;
            break;
        case 3:
            speed = 25;
            break;
        case 4:
            speed = 10;
            break;
        case 5:
            speed = 5;
            break;
        case 6:
            speed = 4;
            break;
        case 7:
            speed = 3;
            break;
        case 8:
            speed = 2;
            break;
        case 9:
            speed = 1;
            break;
        case 10:
            speed = 0;
            break;
        }
        level_up_on = 0; //레벨업 flag꺼줌

        gotoxy(STATUS_X_ADJ, STATUS_Y_LEVEL); printf(" LEVEL : %5d", level); //레벨표시 
        gotoxy(STATUS_X_ADJ, STATUS_Y_GOAL); printf(" GOAL  : %5d", 10 - cnt); // 레벨목표 표시 

    }
}