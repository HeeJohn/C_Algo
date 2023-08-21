

#ifndef BLOCK_H
#define BLOCK_H

// 새로운 블록 생성 함수
void create_nblock(void);

// 블록 충돌 검사 함수
int check_crush(int bx, int by, int b_rotation);

// 라인이 지워지는지 검사하는 함수
void check_line(void);

#endif // !BLOCK_H


#ifndef GLOBAL_H
#define GLOBAL_H

#include"global.h"

#endif // !GLOBAL_H
