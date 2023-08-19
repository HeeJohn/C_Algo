#pragma once

#ifndef CONTROL_H
#define CONTROL_H //이미 기본으로 control.h 파일이 존재함 
#include "basic.h"
#define LEFT 75 //좌로 이동    //키보드값들 
#define RIGHT 77 //우로 이동 
#define UP 72 //회전 
#define DOWN 80 //soft drop
#define SPACE 32 //hard drop
#define p 112 //일시정지 
#define P 80 //일시정지
#define ESC 27 //게임종료 

void check_key(void); //키보드로 키를 입력받음 
void drop_block(void); //블록을 아래로 떨어트림 
void move_block(int dir); //dir방향으로 블록을 움직임 

#endif
