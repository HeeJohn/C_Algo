#ifndef COMMON_H
#define COMMON_H

#define _CRT_SECURE_NO_WARNINGS
#include "Windows.h"

/* ---------- BOOLEAN ---------- */
#define FALSE 0
#define TRUE 1

/* ---------- 조작키 별 ASCI값 ---------- */

#define LEFT 75 //좌로 이동    //키보드값들 
#define RIGHT 77 //우로 이동 a
#define UP 72 //회전 
#define DOWN 80 //soft drop
#define SPACE 32 //hard drop
#define p 112 //일시정지 
#define P 80 //일시정지
#define ESC 27 //게임종료 

 int key; //키보드로 입력받은 키값을 저장 

/* ---------- 게임보드 배열에 저장될 블록의 상태들 ---------- */

#define ACTIVE_BLOCK -2 // 게임판배열에 저장될 블록의 상태들 
#define CEILLING -1     // 블록이 이동할 수 있는 공간은 0 또는 음의 정수료 표현 
#define EMPTY 0         // 블록이 이동할 수 없는 공간은 양수로 표현 
#define WALL 1
#define INACTIVE_BLOCK 2 // 이동이 완료된 블록값 



/* ---------- 게임 보드 크기 ---------- */

#define BOARD_X 11 //게임판 가로크기 
#define BOARD_Y 23 //게임판 세로크기 
#define BOARD_X_ADJ 3 //게임판 위치조정 
#define BOARD_Y_ADJ 1 //게임판 위치조정 
#define STATUS_X_ADJ BOARD_X_ADJ+BOARD_X+1 //게임정보표시 위치조정 

/* ------------------ 커서 ------------------ */

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE; //커서숨기는 함수에 사용되는 열거형 



#endif // !COMMON_H


