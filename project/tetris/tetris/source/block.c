#include "common.h"
#include "board_ui.h"
#include<stdlib.h>
#include<stdio.h>


/* ------------------- 새로운 블록 생성 함수 ------------------- */
void create_nblock(void)
{
    int i, j;

    bx = (BOARD_X / 2) - 1; //블록 생성 위치x좌표(게임판의 가운데) 
    by = 0;  //블록 생성위치 y좌표(제일 위) 

    b_type = b_type_next; //다음블럭값을 가져옴 
    b_type_next = rand() % 7; //다음 블럭을 만듦

    b_rotation = 0;  //회전은 0번으로 가져옴 
    create_nblock_on = 0; //create_nblock flag를 끔  

    for (i = 0; i < 4; i++)
    { /* 게임판 bx, by위치에 블럭생성 */
        for (j = 0; j < 4; j++)
        {
            if (blocks[b_type][b_rotation][i][j] == 1)
                board_curr[by + i][bx + j] = ACTIVE_BLOCK;
        }
    }
    for (i = 1; i < 3; i++)
    { /* 게임상태표시에 다음에 나올블럭을 그림 */
        for (j = 0; j < 4; j++)
        {
            if (blocks[b_type_next][0][i][j] == 1)
            {
                gotoxy(STATUS_X_ADJ + 2 + j, i + 6);
                printf("■");
            }
            else
            {
                gotoxy(STATUS_X_ADJ + 2 + j, i + 6);
                printf("  ");
            }
        }
    }
}

/* ------------------- 블록 충돌 검사 함수 ------------------- */
int check_crush(int bx, int by, int b_rotation)
{ /* 지정된 좌표와 회전값으로 충돌이 있는지 검사 */
    int i, j;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        { /* 지정된 위치의 게임판과 블럭모양을 비교해서 겹치면 FALSE를 리턴 */
            if (blocks[b_type][b_rotation][i][j] == 1 && board_curr[by + i][bx + j] > 0)
                return FALSE;
        }
    }
    return TRUE; //하나도 안겹치면 TRUE리턴 
};


/* ----------  라인이 지워지는지 검사하는 함수  ---------- */
void check_line(void)
{
    int i, j, k, l;

    int block_amount; //한줄의 블록개수를 저장하는 변수 
    int combo = 0; //콤보개수 저장하는 변수 지정및 초기화 

    for (i = BOARD_Y - 2; i > 3;)
    { /* i = BOARD_Y - 2 : 밑쪽벽의 윗칸부터, i>3 : 천장(3)아래까지 검사 */
        block_amount = 0; //블록개수 저장 변수 초기화 

        for (j = 1; j < BOARD_X - 1; j++)
        { /* 벽과 벽사이의 블록개수를 셈 */
            if (board_curr[i][j] > 0)
                block_amount++;
        }

        if (block_amount == BOARD_X - 2) //블록이 가득 찬 경우 
        {
            if (level_up_on == 0) //레벨업상태가 아닌 경우에(레벨업이 되면 자동 줄삭제가 있음)
            {
                score += 100 * level; //점수추가 
                cnt++; //지운 줄 개수 카운트 증가 
                combo++; //콤보수 증가  
            }
            for (k = i; k > 1; k--)
            { /* 윗줄을 한칸씩 모두 내림(윗줄이 천장이 아닌 경우에만) */
                for (l = 1; l < BOARD_X - 1; l++)
                {
                    if (board_curr[k - 1][l] != CEILLING)
                        board_curr[k][l] = board_curr[k - 1][l];
                    if (board_curr[k - 1][l] == CEILLING)
                        board_curr[k][l] = EMPTY; //윗줄이 천장인 경우에는 천장을 한칸 내리면 안되니까 빈칸을 넣음 
                }
            }
        }
        else i--;
    }
    if (combo) //콤보가 있는 경우 점수와 레벨 목표를 새로 표시함 
    {
        if (combo > 1) //2콤보이상인 경우 경우 보너스및 메세지를 게임판에 띄웠다가 지움 
        {
            gotoxy(BOARD_X_ADJ + (BOARD_X / 2) - 1, BOARD_Y_ADJ + by - 2);
            printf("%d COMBO!", combo);
            Sleep(500);
            score += (combo * level * 100);
            reset_board_prev(); //텍스트를 지우기 위해 board_prev을 초기화.
            //(board_prev와 board_curr가 전부 다르므로 다음번 draw()호출시 게임판 전체를 새로 그리게 됨) 
        }
        gotoxy(STATUS_X_ADJ, STATUS_Y_GOAL);
        printf(" GOAL  : %5d", (cnt <= 10) ? 10 - cnt : 0);
        gotoxy(STATUS_X_ADJ, STATUS_Y_SCORE);
        printf("        %6d", score);
    }
}