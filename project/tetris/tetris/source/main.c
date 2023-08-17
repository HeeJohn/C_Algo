#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>

#define LEFT 75 //�·� �̵�    //Ű���尪�� 
#define RIGHT 77 //��� �̵� 
#define UP 72 //ȸ�� 
#define DOWN 80 //soft drop
#define SPACE 32 //hard drop
#define p 112 //�Ͻ����� 
#define P 80 //�Ͻ�����
#define ESC 27 //�������� 

#define false 0
#define true 1

#define ACTIVE_BLOCK -2 // �����ǹ迭�� ����� ����� ���µ� 
#define CEILLING -1     // ����� �̵��� �� �ִ� ������ 0 �Ǵ� ���� ������ ǥ�� 
#define EMPTY 0         // ����� �̵��� �� ���� ������ ����� ǥ�� 
#define WALL 1
#define INACTIVE_BLOCK 2 // �̵��� �Ϸ�� ��ϰ� 

#define BOARD_X 11 //������ ����ũ�� 
#define BOARD_Y 23 //������ ����ũ�� 
#define BOARD_X_ADJ 3 //������ ��ġ���� 
#define BOARD_Y_ADJ 1 //������ ��ġ���� 

#define STATUS_X_ADJ BOARD_X_ADJ+BOARD_X+1 //��������ǥ�� ��ġ���� 

int STATUS_Y_GOAL; //GOAL ����ǥ����ġY ��ǥ ���� 
int STATUS_Y_LEVEL; //LEVEL ����ǥ����ġY ��ǥ ����
int STATUS_Y_SCORE; //SCORE ����ǥ����ġY ��ǥ ����

int blocks[7][4][4][4] = {
    /*------ �� ��� -----------*/
{       {0,0,0,0,
         0,1,1,0,
         0,1,1,0,
         0,0,0,0},//�� ���

        {0,0,0,0,
         0,1,1,0,
         0,1,1,0,
         0,0,0,0},

        {0,0,0,0,
        0,1,1,0,
        0,1,1,0,
        0,0,0,0},

        {0,0,0,0,
        0,1,1,0,
        0,1,1,0,
        0,0,0,0}},


        /*------ �Ѹ�� -----------*/
        {{0,0,0,0,
        0,0,0,0,
        1,1,1,1,
        0,0,0,0},//�Ѹ��

       {0,1,0,0,
        0,1,0,0,
        0,1,0,0,
        0,1,0,0},

        {0,0,0,0,
        0,0,0,0,
        1,1,1,1,
        0,0,0,0},

       {0,1,0,0,
        0,1,0,0,
        0,1,0,0,
        0,1,0,0}},

        /*------ ����� -----------*/
        {{0,0,0,0,
        1,1,0,0,
        0,1,1,0,
        0,0,0,0},//����� 

        {0,0,0,0,
        0,0,1,0,
        0,1,1,0,
        0,1,0,0},

        {0,0,0,0
        ,1,1,0,0
        ,0,1,1,0
        ,0,0,0,0},

        {0,0,0,0
        ,0,0,1,0
        ,0,1,1,0
        ,0,1,0,0}},

    /*------ ���ݴ��� -----------*/
        {{0,0,0,0,
        0,1,1,0,
        1,1,0,0,
        0,0,0,0},//���ݴ���

        {0,0,0,0,
        1,0,0,0,
        1,1,0,0,
        0,1,0,0},

        {0,0,0,0,
        0,1,1,0,
        1,1,0,0,
        0,0,0,0},

        {0,0,0,0,
        1,0,0,0,
        1,1,0,0,
        0,1,0,0}},

    /*------ ���ݴ��� -----------*/
        {{0,0,0,0,
        0,0,1,0,
        1,1,1,0,
        0,0,0,0},//���ݴ���

        {0,0,0,0,
        1,1,0,0,
        0,1,0,0,
        0,1,0,0},

        {0,0,0,0,
        0,0,0,0,
        1,1,1,0,
        1,0,0,0},

        {0,0,0,0,
        0,1,0,0,
        0,1,0,0,
        0,1,1,0}},
        /*------ ����� -----------*/

        {{0,0,0,0,
        1,0,0,0,
        1,1,1,0,
        0,0,0,0},//�����

        {0,0,0,0,
        0,1,0,0,
        0,1,0,0,
        1,1,0,0},

        {0,0,0,0,
        0,0,0,0,
        1,1,1,0,
        0,0,1,0},

        {0,0,0,0,
        0,1,1,0,
        0,1,0,0,
        0,1,0,0}},

        /*------ �Ǹ�� -----------*/
        {{0,0,0,0,
         0,1,0,0,
         1,1,1,0,
         0,0,0,0},//�Ǹ��

        {0,0,0,0,
        0,1,0,0,
        0,1,1,0,
        0,1,0,0},

        {0,0,0,0,
        0,0,0,0,
        1,1,1,0,
        0,1,0,0},

        {0,0,0,0,
        0,1,0,0,
        1,1,0,0,
        0,1,0,0}}
}; //��ϸ�� ���� 4*4������ ����� ǥ�� blcoks[b_type][b_rotation][i][j]�� ��� 

int b_type; //��� ������ ���� 
int b_rotation; //��� ȸ���� ���� 
int b_type_next; //���� ��ϰ� ���� 

int board_curr[BOARD_Y][BOARD_X]; //�������� ������ �����ϴ� �迭 ����Ϳ� ǥ���Ŀ� board_prev�� ����� 
int board_prev[BOARD_Y][BOARD_X]; //�� maincpy�� �������� ����Ϳ� ǥ�õǱ� ���� ������ ������ ���� 
//main�� ��ü�� ��� ����Ϳ� ǥ������ �ʰ�(�̷��� �ϸ� ����Ͱ� �����Ÿ�) 
//board_prev�� �迭�� ���ؼ� ���� �޶��� ���� ����Ϳ� ��ħ 
int bx, by; //�̵����� ����� �����ǻ��� x,y��ǥ�� ���� 

int key; //Ű����� �Է¹��� Ű���� ���� 

int speed; //��������ӵ� 
int level; //���� level 
int level_goal; //���������� �Ѿ�� ���� ��ǥ���� 
int cnt; //���� �������� ������ �� ���� ���� 
int score; //���� ���� 
int last_score = 0; //�������������� 
int best_score = 0; //�ְ�������� 

int create_nblock_on = 0; //���ο� ���� �ʿ����� �˸��� flag 
int crush_on = 0; //���� �̵����� ����� �浹�������� �˷��ִ� flag 
int level_up_on = 0; //���������� ����(���� ������ǥ�� �Ϸ�Ǿ�����) �˸��� flag 
int space_key_on = 0; //hard drop�������� �˷��ִ� flag 

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE; //Ŀ������� �Լ��� ���Ǵ� ������ 
void setcursortype(CURSOR_TYPE c);
void start_page(void); //���ӽ���ȭ�� 
void preset(void); //������ �ʱ�ȭ 
void reset_board_curr(void); //���� ������(board_curr[][]�� �ʱ�ȭ)
void reset_board_prev(void); //copy ������(board_prev[][]�� �ʱ�ȭ)
void draw_status(void); //���� ��ü �������̽��� ǥ�� 
void draw_board(void); //�������� �׸� 
void create_nblock(void); //���ο� ����� �ϳ� ���� 
void check_key(void); //Ű����� Ű�� �Է¹��� 
void drop_block(void); //����� �Ʒ��� ����Ʈ�� 
int check_crush(int bx, int by, int rotation); //bx, by��ġ�� rotationȸ������ ���� ��� �浹 �Ǵ� 
void move_block(int dir); //dir�������� ����� ������ 
void check_line(void); //���� ����á������ �Ǵ��ϰ� ���� 
void check_level_up(void); //������ǥ�� �޼��Ǿ������� �Ǵ��ϰ� levelup��Ŵ 
void check_game_over(void); //���ӿ������� �Ǵ��ϰ� ���ӿ����� ���� 
void pause(void);//������ �Ͻ�������Ŵ 
void gotoxy(int x, int y);


void gotoxy(int x, int y) { //gotoxy�Լ� 
    COORD pos = { 2 * x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/*================== Ŀ�� ����� �Լ� =============== */
void setcursortype(CURSOR_TYPE c) { //Ŀ������� �Լ� 
    CONSOLE_CURSOR_INFO CurInfo;

    /*----- */
    switch (c) {
    case NOCURSOR:  // ������������������
        CurInfo.dwSize = 1; // ��������
        CurInfo.bVisible = FALSE;
        break;
    case SOLIDCURSOR:
        CurInfo.dwSize = 100;
        CurInfo.bVisible = TRUE;
        break;
    case NORMALCURSOR:
        CurInfo.dwSize = 20;
        CurInfo.bVisible = TRUE;
        break;
    }
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}
/*================== Ŀ�� ����� �Լ� =============== */
int main() {
    int i;

    srand((unsigned)time(NULL)); //����ǥ���� 
    setcursortype(NOCURSOR); //Ŀ�� ���� 
    start_page(); //����Ÿ��Ʋ ȣ�� 
    preset(); //������ ���� 

    while (1) 
    {
        for (i = 0; i < 5; i++) 
        { //����� ��ĭ�������µ��� 5�� Ű�Է¹��� �� ���� 
            check_key(); //Ű�Է�Ȯ�� 
            draw_board(); //ȭ���� �׸� 
            Sleep(speed); //���Ӽӵ����� 
            if (crush_on && check_crush(bx, by + 1, b_rotation) == false) Sleep(100);
            //����� �浹���ΰ�� �߰��� �̵��� ȸ���� �ð��� ���� 
            if (space_key_on == 1) { //�����̽��ٸ� �������(hard drop) �߰��� �̵��� ȸ���Ҽ� ���� break; 
                space_key_on = 0;
                break;
            }
        }
        drop_block(); // ����� ��ĭ ���� 
        check_level_up(); // �������� üũ 
        check_game_over(); //���ӿ����� üũ 
        if (create_nblock_on == 1) create_nblock(); // �� �� flag�� �ִ� ��� ���ο� �� ���� 
    }
}

void start_page(void) 
{
     
    // �ܼ� �ڵ��� ���ɴϴ�.
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // �ܼ� ȭ�� ���� ������ ������ ����ü�� ����
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    int consoleWidth;
    int consoleHeight;
    // �ܼ� ȭ�� ���� ���� ������
    if (GetConsoleScreenBufferInfo(hConsole, &consoleInfo)) 
    {
        // �ܼ��� ���� ũ�⸦ ���
        consoleWidth = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
        // �ܼ��� ���� ũ�⸦ ���
        consoleHeight = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;

        // ���� ���� ũ�⸦ ���
        printf("�ܼ� ���� ũ��: %d\n", consoleWidth);
        // ���� ���� ũ�⸦ ���
        printf("�ܼ� ���� ũ��: %d\n", consoleHeight);
    }
    else 
    {
        // �ܼ� ȭ�� ���� ������ ������ �� ������ ��� ���� �޽����� ���
        printf("�ܼ� ������ �����µ� �����Ͽ����ϴ�.\n");
    }

    int x = consoleWidth/10; //Ÿ��Ʋȭ���� ǥ�õǴ� x��ǥ 
    int y = (consoleHeight-17); //Ÿ��Ʋȭ���� ǥ�õǴ� y��ǥ 
    int cnt; //Ÿ��Ʋ �������� ���� ���� 

    //15x17 ������ ��ŸƮ �ȳ���
    gotoxy(x, y + 0); printf("����������������"); Sleep(100);
    gotoxy(x, y + 1); printf("�����  ����    ������"); Sleep(100);
    gotoxy(x, y + 2); printf("�����              ���  ��"); Sleep(100);
    gotoxy(x, y + 3); printf("������  ��  ��  ������"); Sleep(100);
    gotoxy(x, y + 4); printf("���  �������������"); Sleep(100);
    gotoxy(x + 5, y + 2); printf("T E T R I S"); Sleep(100);
    gotoxy(x, y + 7); printf("Please Enter Any Key to Start..");
    gotoxy(x, y + 9);  printf("   ��    : Shift");
    gotoxy(x, y + 10); printf(" ��   ��  : Left / Right");
    gotoxy(x, y + 11); printf("   ��    : Soft Drop");
    gotoxy(x, y + 12); printf(" SPACE  : Hard Drop");
    gotoxy(x, y + 13); printf("   P    : Pause");
    gotoxy(x, y + 14); printf("  ESC   : Quit");
    gotoxy(x, y + 16); printf("BONUS FOR HARD DROPS / COMBOS");

    for (cnt = 0;; cnt++) { //cnt�� 1�� ������Ű�鼭 ��� �ݺ�    //�ϳ��� ���߿��� �� ��¦�̴� �ִϸ��̼�ȿ�� 
        if (_kbhit()) break; //Ű�Է��� ������ ���ѷ��� ���� 
        if (cnt % 200 == 0) { gotoxy(x + 4, y + 1); printf("��"); }       //cnt�� 200���� ������ �������� ���� ǥ�� 
        if ((cnt % 200 - 100) == 0) { gotoxy(x + 4, y + 1); printf("  "); } //�� ī��Ʈ���� 100ī��Ʈ �������� ���� ���� 
        if ((cnt % 350) == 0) { gotoxy(x + 13, y + 2); printf("��"); } //������ ������ �ð����� ���� 
        if ((cnt % 350 - 100) == 0) { gotoxy(x + 13, y + 2); printf("  "); }
        Sleep(10); // 00.1�� ������  
    }

    while (_kbhit()) _getch(); //���ۿ� ��ϵ� Ű���� ���� 

}

void preset(void) {

    FILE* file = fopen("score.dat", "rt"); // score.dat������ ���� 
    if (file == 0) { best_score = 0; } //������ ������ �� �ְ������� 0�� ���� 
    else {
        fscanf(file, "%d", &best_score); // ������ ������ �ְ������� �ҷ��� 
        fclose(file); //���� ���� 
    }

    level = 1; //�������� �ʱ�ȭ 
    score = 0;
    level_goal = 1000;
    key = 0;
    crush_on = 0;
    cnt = 0;
    speed = 100;

    system("cls"); //ȭ������ 
    reset_board_curr(
    
    
    ); // board_curr�� �ʱ�ȭ 
    draw_status(); // ����ȭ���� �׸�
    draw_board(); // �������� �׸� 

    b_type_next = rand() % 7; //�������� ���� ��� ������ �����ϰ� ���� 
    create_nblock(); //���ο� ����� �ϳ� ����  

}

void reset_board_curr(void) { //�������� �ʱ�ȭ  
    int i, j;

    for (i = 0; i < BOARD_Y; i++) { // �������� 0���� �ʱ�ȭ  
        for (j = 0; j < BOARD_X; j++) {
            board_curr[i][j] = 0;
            board_prev[i][j] = 100;
        }
    }
    for (j = 1; j < BOARD_X; j++) { //y���� 3�� ��ġ�� õ���� ���� 
        board_curr[3][j] = CEILLING;
    }
    for (i = 1; i < BOARD_Y - 1; i++) { //�¿� ���� ����  
        board_curr[i][0] = WALL;
        board_curr[i][BOARD_X - 1] = WALL;
    }
    for (j = 0; j < BOARD_X; j++) { //�ٴں��� ���� 
        board_curr[BOARD_Y - 1][j] = WALL;
    }
}

void reset_board_prev(void) { //board_prev�� �ʱ�ȭ 
    int i, j;

    for (i = 0; i < BOARD_Y; i++) {         //�����ǿ� ���ӿ� ������ �ʴ� ���ڸ� ���� 
        for (j = 0; j < BOARD_X; j++) {  //�̴� board_curr�� ���� ���ڰ� ���� �ϱ� ���� 
            board_prev[i][j] = 100;
        }
    }
}

void draw_status(void) { //���� ���� ǥ�ø� ��Ÿ���� �Լ�  
    int y = 3;             // level, goal, score�� �����߿� ���� �ٲ�� �� ���� �� y���� ���� �����ص� 
    // �׷��� Ȥ�� ���� ���� ǥ�� ��ġ�� �ٲ� �� �Լ����� �ȹٲ㵵 �ǰ�.. 
    gotoxy(STATUS_X_ADJ, STATUS_Y_LEVEL = y); printf(" LEVEL : %5d", level);
    gotoxy(STATUS_X_ADJ, STATUS_Y_GOAL = y + 1); printf(" GOAL  : %5d", 10 - cnt);
    gotoxy(STATUS_X_ADJ, y + 2); printf("+-  N E X T  -+ ");
    gotoxy(STATUS_X_ADJ, y + 3); printf("|             | ");
    gotoxy(STATUS_X_ADJ, y + 4); printf("|             | ");
    gotoxy(STATUS_X_ADJ, y + 5); printf("|             | ");
    gotoxy(STATUS_X_ADJ, y + 6); printf("|             | ");
    gotoxy(STATUS_X_ADJ, y + 7); printf("+-- -  -  - --+ ");
    gotoxy(STATUS_X_ADJ, y + 8); printf(" YOUR SCORE :");
    gotoxy(STATUS_X_ADJ, STATUS_Y_SCORE = y + 9); printf("        %6d", score);
    gotoxy(STATUS_X_ADJ, y + 10); printf(" LAST SCORE :");
    gotoxy(STATUS_X_ADJ, y + 11); printf("        %6d", last_score);
    gotoxy(STATUS_X_ADJ, y + 12); printf(" BEST SCORE :");
    gotoxy(STATUS_X_ADJ, y + 13); printf("        %6d", best_score);
    gotoxy(STATUS_X_ADJ, y + 15); printf("  ��   : Shift        SPACE : Hard Drop");
    gotoxy(STATUS_X_ADJ, y + 16); printf("��  �� : Left / Right   P   : Pause");
    gotoxy(STATUS_X_ADJ, y + 17); printf("  ��   : Soft Drop     ESC  : Quit");
}

void draw_board(void) { //������ �׸��� �Լ� 
    int i, j;

    for (j = 1; j < BOARD_X - 1; j++) { //õ���� ��� ���ο���� �������� �������� ���� �׷��� 
        if (board_curr[3][j] == EMPTY) board_curr[3][j] = CEILLING;
    }
    for (i = 0; i < BOARD_Y; i++) {
        for (j = 0; j < BOARD_X; j++) {
            if (board_prev[i][j] != board_curr[i][j]) { //cpy�� ���ؼ� ���� �޶��� �κи� ���� �׷���.
                //�̰� ������ ��������ü�� ��� �׷��� �������� ��¦�Ÿ�
                gotoxy(BOARD_X_ADJ + j, BOARD_Y_ADJ + i);
                switch (board_curr[i][j]) {
                case EMPTY: //��ĭ��� 
                    printf("  ");
                    break;
                case CEILLING: //õ���� 
                    printf(". ");
                    break;
                case WALL: //����� 
                    printf("��");
                    break;
                case INACTIVE_BLOCK: //���� �� ���  
                    printf("��");
                    break;
                case ACTIVE_BLOCK: //�����̰��ִ� �� ���  
                    printf("��");
                    break;
                }
            }
        }
    }
    for (i = 0; i < BOARD_Y; i++) { //�������� �׸� �� board_prev�� ����  
        for (j = 0; j < BOARD_X; j++) {
            board_prev[i][j] = board_curr[i][j];
        }
    }
}

void create_nblock(void) { //���ο� ��� ����  
    int i, j;

    bx = (BOARD_X / 2) - 1; //��� ���� ��ġx��ǥ(�������� ���) 
    by = 0;  //��� ������ġ y��ǥ(���� ��) 
    b_type = b_type_next; //���������� ������ 
    b_type_next = rand() % 7; //���� ���� ���� 
    b_rotation = 0;  //ȸ���� 0������ ������ 

    create_nblock_on = 0; //create_nblock flag�� ��  

    for (i = 0; i < 4; i++) { //������ bx, by��ġ�� ������  
        for (j = 0; j < 4; j++) {
            if (blocks[b_type][b_rotation][i][j] == 1) board_curr[by + i][bx + j] = ACTIVE_BLOCK;
        }
    }
    for (i = 1; i < 3; i++) { //���ӻ���ǥ�ÿ� ������ ���ú��� �׸� 
        for (j = 0; j < 4; j++) {
            if (blocks[b_type_next][0][i][j] == 1) {
                gotoxy(STATUS_X_ADJ + 2 + j, i + 6);
                printf("��");
            }
            else {
                gotoxy(STATUS_X_ADJ + 2 + j, i + 6);
                printf("  ");
            }
        }
    }
}

void check_key(void) {
    key = 0; //Ű�� �ʱ�ȭ  

    if (_kbhit()) { //Ű�Է��� �ִ� ���  
        key = _getch(); //Ű���� ����
        if (key == 224) { //����Ű�ΰ�� 
            do { key = _getch(); } while (key == 224);//����Ű���ð��� ���� 
            switch (key) {
            case LEFT: //����Ű ��������  
                if (check_crush(bx - 1, by, b_rotation) == true) move_block(LEFT);
                break;                            //�������� �� �� �ִ��� üũ �� �����ϸ� �̵�
            case RIGHT: //������ ����Ű ��������- ���� �����ϰ� ó���� 
                if (check_crush(bx + 1, by, b_rotation) == true) move_block(RIGHT);
                break;
            case DOWN: //�Ʒ��� ����Ű ��������-���� �����ϰ� ó���� 
                if (check_crush(bx, by + 1, b_rotation) == true) move_block(DOWN);
                break;
            case UP: //���� ����Ű �������� 
                if (check_crush(bx, by, (b_rotation + 1) % 4) == true) move_block(UP);
                //ȸ���� �� �ִ��� üũ �� �����ϸ� ȸ��
                else if (crush_on == 1 && check_crush(bx, by - 1, (b_rotation + 1) % 4) == true) move_block(100);
            }                    //�ٴڿ� ���� ��� �������� ��ĭ����� ȸ���� �����ϸ� �׷��� ��(Ư������)
        }
        else { //����Ű�� �ƴѰ�� 
            switch (key) {
            case SPACE: //�����̽�Ű �������� 
                space_key_on = 1; //�����̽�Ű flag�� ��� 
                while (crush_on == 0) { //�ٴڿ� ���������� �̵���Ŵ 
                    drop_block();
                    score += level; // hard drop ���ʽ�
                    gotoxy(STATUS_X_ADJ, STATUS_Y_SCORE); printf("        %6d", score); //���� ǥ��  
                }
                break;
            case P: //P(�빮��) �������� 
            case p: //p(�ҹ���) �������� 
                pause(); //�Ͻ����� 
                break;
            case ESC: //ESC�������� 
                system("cls"); //ȭ���� ����� 
                exit(0); //�������� 
            }
        }
    }
    while (_kbhit()) _getch(); //Ű���۸� ��� 
}

void drop_block(void) {
    int i, j;

    if (crush_on && check_crush(bx, by + 1, b_rotation) == true) crush_on = 0; //���� ��������� crush flag �� 
    if (crush_on && check_crush(bx, by + 1, b_rotation) == false) { 
        //���� ��������ʰ� crush flag�� ���������� 
        for (i = 0; i < BOARD_Y; i++) { //���� �������� ���� ���� 
            for (j = 0; j < BOARD_X; j++) {
                if (board_curr[i][j] == ACTIVE_BLOCK) board_curr[i][j] = INACTIVE_BLOCK;
            }
        }
        crush_on = 0; //flag�� �� 
        check_line(); //����üũ�� �� 
        create_nblock_on = 1; //���ο� ������ flag�� ��    
        return; //�Լ� ���� 
    }

    if (check_crush(bx, by + 1, b_rotation) == true) move_block(DOWN); //���� ��������� ������ ��ĭ �̵� 
    if (check_crush(bx, by + 1, b_rotation) == false) crush_on++; //������ �̵��� �ȵǸ�  crush flag�� ��
}

int check_crush(int bx, int by, int b_rotation) { //������ ��ǥ�� ȸ�������� �浹�� �ִ��� �˻� 
    int i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) { //������ ��ġ�� �����ǰ� ������� ���ؼ� ��ġ�� false�� ���� 
            if (blocks[b_type][b_rotation][i][j] == 1 && board_curr[by + i][bx + j] > 0) return false;
        }
    }
    return true; //�ϳ��� �Ȱ�ġ�� true���� 
};

void move_block(int dir) { //����� �̵���Ŵ 
    int i, j;

    switch (dir) {
    case LEFT: //���ʹ��� 
        for (i = 0; i < 4; i++) { //������ǥ�� ���� ���� 
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) board_curr[by + i][bx + j] = EMPTY;
            }
        }
        for (i = 0; i < 4; i++) { //�������� ��ĭ���� active block�� ���� 
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) board_curr[by + i][bx + j - 1] = ACTIVE_BLOCK;
            }
        }
        bx--; //��ǥ�� �̵� 
        break;

    case RIGHT:    //������ ����. ���ʹ����̶� ���� ������ ���� 
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) board_curr[by + i][bx + j] = EMPTY;
            }
        }
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) board_curr[by + i][bx + j + 1] = ACTIVE_BLOCK;
            }
        }
        bx++;
        break;

    case DOWN:    //�Ʒ��� ����. ���ʹ����̶� ���� ������ ����
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) board_curr[by + i][bx + j] = EMPTY;
            }
        }
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) board_curr[by + i + 1][bx + j] = ACTIVE_BLOCK;
            }
        }
        by++;
        break;

    case UP: //Ű���� ���� �������� ȸ����Ŵ. 
        for (i = 0; i < 4; i++) { //������ǥ�� ���� ����  
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) board_curr[by + i][bx + j] = EMPTY;
            }
        }
        b_rotation = (b_rotation + 1) % 4; //ȸ������ 1������Ŵ(3���� 4�� �Ǵ� ���� 0���� �ǵ���) 
        for (i = 0; i < 4; i++) { //ȸ���� ����� ���� 
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) board_curr[by + i][bx + j] = ACTIVE_BLOCK;
            }
        }
        break;

    case 100: //����� �ٴ�, Ȥ�� �ٸ� ��ϰ� ���� ���¿��� ��ĭ���� �÷� ȸ���� ������ ��� 
        //�̸� ���۽�Ű�� Ư������ 
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) board_curr[by + i][bx + j] = EMPTY;
            }
        }
        b_rotation = (b_rotation + 1) % 4;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) board_curr[by + i - 1][bx + j] = ACTIVE_BLOCK;
            }
        }
        by--;
        break;
    }
}

void check_line(void) {
    int i, j, k, l;

    int    block_amount; //������ ��ϰ����� �����ϴ� ���� 
    int combo = 0; //�޺����� �����ϴ� ���� ������ �ʱ�ȭ 

    for (i = BOARD_Y - 2; i > 3;) { //i=BOARD_Y-2 : ���ʺ��� ��ĭ����,  i>3 : õ��(3)�Ʒ����� �˻� 
        block_amount = 0; //��ϰ��� ���� ���� �ʱ�ȭ 
        for (j = 1; j < BOARD_X - 1; j++) { //���� �������� ��ϰ����� �� 
            if (board_curr[i][j] > 0) block_amount++;
        }
        if (block_amount == BOARD_X - 2) { //����� ���� �� ��� 
            if (level_up_on == 0) { //���������°� �ƴ� ��쿡(�������� �Ǹ� �ڵ� �ٻ����� ����) 
                score += 100 * level; //�����߰� 
                cnt++; //���� �� ���� ī��Ʈ ���� 
                combo++; //�޺��� ����  
            }
            for (k = i; k > 1; k--) { //������ ��ĭ�� ��� ����(������ õ���� �ƴ� ��쿡��) 
                for (l = 1; l < BOARD_X - 1; l++) {
                    if (board_curr[k - 1][l] != CEILLING) board_curr[k][l] = board_curr[k - 1][l];
                    if (board_curr[k - 1][l] == CEILLING) board_curr[k][l] = EMPTY;
                    //������ õ���� ��쿡�� õ���� ��ĭ ������ �ȵǴϱ� ��ĭ�� ���� 
                }
            }
        }
        else i--;
    }
    if (combo) { //�� ������ �ִ� ��� ������ ���� ��ǥ�� ���� ǥ����  
        if (combo > 1) { //2�޺��̻��� ��� ��� ���ʽ��� �޼����� �����ǿ� ����ٰ� ���� 
            gotoxy(BOARD_X_ADJ + (BOARD_X / 2) - 1, BOARD_Y_ADJ + by - 2); printf("%d COMBO!", combo);
            Sleep(500);
            score += (combo * level * 100);
            reset_board_prev(); //�ؽ�Ʈ�� ����� ���� board_prev�� �ʱ�ȭ.
            //(board_prev�� board_curr�� ���� �ٸ��Ƿ� ������ draw()ȣ��� ������ ��ü�� ���� �׸��� ��) 
        }
        gotoxy(STATUS_X_ADJ, STATUS_Y_GOAL); printf(" GOAL  : %5d", (cnt <= 10) ? 10 - cnt : 0);
        gotoxy(STATUS_X_ADJ, STATUS_Y_SCORE); printf("        %6d", score);
    }
}

void check_level_up(void) {
    int i, j;

    if (cnt >= 10) { //�������� 10�پ� ���־���. 10���̻� ���� ��� 
        draw_board();
        level_up_on = 1; //������ flag�� ��� 
        level += 1; //������ 1 �ø� 
        cnt = 0; //���� �ټ� �ʱ�ȭ   

        for (i = 0; i < 4; i++) {
            gotoxy(BOARD_X_ADJ + (BOARD_X / 2) - 3, BOARD_Y_ADJ + 4);
            printf("             ");
            gotoxy(BOARD_X_ADJ + (BOARD_X / 2) - 2, BOARD_Y_ADJ + 6);
            printf("             ");
            Sleep(200);

            gotoxy(BOARD_X_ADJ + (BOARD_X / 2) - 3, BOARD_Y_ADJ + 4);
            printf("��LEVEL UP!��");
            gotoxy(BOARD_X_ADJ + (BOARD_X / 2) - 2, BOARD_Y_ADJ + 6);
            printf("��SPEED UP!��");
            Sleep(200);
        }
        reset_board_prev(); //�ؽ�Ʈ�� ����� ���� board_prev�� �ʱ�ȭ.
        //(board_prev�� board_curr�� ���� �ٸ��Ƿ� ������ draw()ȣ��� ������ ��ü�� ���� �׸��� ��) 

        for (i = BOARD_Y - 2; i > BOARD_Y - 2 - (level - 1); i--) { //�������������� �� ����-1�� ����ŭ �Ʒ��� ���� ������ 
            for (j = 1; j < BOARD_X - 1; j++) {
                board_curr[i][j] = INACTIVE_BLOCK; // ���� ������� ��� ä��� 
                gotoxy(BOARD_X_ADJ + j, BOARD_Y_ADJ + i); // ���� �����.. �̻����̰� 
                printf("��");
                Sleep(20);
            }
        }
        Sleep(100); //�������� �����ֱ� ���� delay 
        check_line(); //������� ��� ä��� �����
        //.check_line()�Լ� ���ο��� level up flag�� �����ִ� ��� ������ ����.         
        switch (level) { //�������� �ӵ��� ��������. 
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
        level_up_on = 0; //������ flag����

        gotoxy(STATUS_X_ADJ, STATUS_Y_LEVEL); printf(" LEVEL : %5d", level); //����ǥ�� 
        gotoxy(STATUS_X_ADJ, STATUS_Y_GOAL); printf(" GOAL  : %5d", 10 - cnt); // ������ǥ ǥ�� 

    }
}

void check_game_over(void) {
    int i;

    int x = 5;
    int y = 5;

    for (i = 1; i < BOARD_X - 2; i++) {
        if (board_curr[3][i] > 0) { //õ��(������ ����° ��)�� inactive�� �����Ǹ� ���� ���� 
            gotoxy(x, y + 0); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�"); //���ӿ��� �޼��� 
            gotoxy(x, y + 1); printf("��                              ��");
            gotoxy(x, y + 2); printf("��  +-----------------------+   ��");
            gotoxy(x, y + 3); printf("��  |  G A M E  O V E R..   |   ��");
            gotoxy(x, y + 4); printf("��  +-----------------------+   ��");
            gotoxy(x, y + 5); printf("��   YOUR SCORE: %6d         ��", score);
            gotoxy(x, y + 6); printf("��                              ��");
            gotoxy(x, y + 7); printf("��  Press any key to restart..  ��");
            gotoxy(x, y + 8); printf("��                              ��");
            gotoxy(x, y + 9); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");
            last_score = score; //���������� �ű� 

            if (score > best_score) { //�ְ��� ���Ž� 
                FILE* file = fopen("score.dat", "wt"); //score.dat�� ���� ����                

                gotoxy(x, y + 6); printf("��  �ڡڡ� BEST SCORE! �ڡڡ�   ��  ");

                if (file == 0) { //���� �����޼���  
                    gotoxy(0, 0);
                    printf("FILE ERROR: SYSTEM CANNOT WRITE BEST SCORE ON \"SCORE.DAT\"");
                }
                else {
                    fprintf(file, "%d", score);
                    fclose(file);
                }
            }
            Sleep(1000);
            while (_kbhit()) _getch();
            key = _getch();
            preset();
        }
    }
}

void pause(void) { //���� �Ͻ����� �Լ� 
    int i, j;

    int x = 5;
    int y = 5;

    for (i = 1; i < BOARD_X - 2; i++) { //���� �Ͻ����� �޼��� 
        gotoxy(x, y + 0); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");
        gotoxy(x, y + 1); printf("��                              ��");
        gotoxy(x, y + 2); printf("��  +-----------------------+   ��");
        gotoxy(x, y + 3); printf("��  |       P A U S E       |   ��");
        gotoxy(x, y + 4); printf("��  +-----------------------+   ��");
        gotoxy(x, y + 5); printf("��  Press any key to resume..   ��");
        gotoxy(x, y + 6); printf("��                              ��");
        gotoxy(x, y + 7); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");
    }
    _getch(); //Ű�Է½ñ��� ��� 

    system("cls"); //ȭ�� ����� ���� �׸� 
    reset_board_prev();
    draw_board();
    draw_status();

    for (i = 1; i < 3; i++) { // ������� �׸� 
        for (j = 0; j < 4; j++) {
            if (blocks[b_type_next][0][i][j] == 1) {
                gotoxy(BOARD_X + BOARD_X_ADJ + 3 + j, i + 6);
                printf("��");
            }
            else {
                gotoxy(BOARD_X + BOARD_X_ADJ + 3 + j, i + 6);
                printf("  ");
            }
        }
    }
} //��! 


void draw_next_block() {

    for (int i = 1; i < 3; i++) { // ������� �׸� 
        for (int j = 0; j < 4; j++) {
            if (blocks[b_type_next][0][i][j] == 1) {
                gotoxy(BOARD_X + BOARD_X_ADJ + 3 + j, i + 6);
                printf("��");
            }
            else {
                gotoxy(BOARD_X + BOARD_X_ADJ + 3 + j, i + 6);
                printf("  ");
            }
        }
    }
}