
#include "common.h"


extern int STATUS_Y_GOAL; //GOAL 정보표시위치Y 좌표 저장 
extern int STATUS_Y_LEVEL; //LEVEL 정보표시위치Y 좌표 저장
extern int STATUS_Y_SCORE; //SCORE 정보표시위치Y 좌표 저장

/* ---------- 테트리스 블록 모양 4차원 배열 ( 2차원 모양 여러개 + 회전 포함 ) ---------- */
extern int blocks[7][4][4][4]; //블록모양 저장 4*4공간에 블록을 표현 blocks[b_type][b_rotation][i][j]로 사용 

/* ------------------ 블록모양 결정 변수 ------------------ */

extern int b_type; //블록 종류를 저장 
extern int b_rotation; //블록 회전값 저장 
extern int b_type_next; //다음 블록값 저장 

/* ------------------ 게임보드 정보 저장 (이전 & 현재) ------------------ */
/*
* 보드 전체를 실시간으로 변경할 경우 UI 깜빡거림
* board_prev와 배열을 비교해서 값이 달라진 곳만 모니터에 고침
*/

extern int board_curr[BOARD_Y][BOARD_X]; //현재 보드를 저장하는 배열
//모니터에 표시후에 board_prev로 복사됨

extern int board_prev[BOARD_Y][BOARD_X]; //이전 보드를 저장하는 배열
//모니터에 표시되기 전의 정보를 가지고 있음 


/* ------------------ 블록 좌표 ------------------ */

extern int bx, by; //이동중인 블록의 게임판상의 x,y좌표를 저장 

/* ------------------ 게임상태 변수 ------------------ */

extern int speed; //게임진행속도 
extern int level; //현재 level 
extern int level_goal; //다음레벨로 넘어가기 위한 목표점수 
extern int cnt; //현재 레벨에서 제거한 줄 수를 저장 
extern int score; //현재 점수 
extern int last_score; //마지막게임점수 
extern int best_score; //최고게임점수 


/* ------------------ 변화 플래그 ------------------ */

extern int create_nblock_on; //새로운 블럭이 필요함을 알리는 flag 
extern int crush_on; //현재 이동중인 블록이 충돌상태인지 알려주는 flag 
extern int level_up_on; //다음레벨로 진행(현재 레벨목표가 완료되었음을) 알리는 flag 
extern int space_key_on ; //hard drop상태임을 알려주는 flag 

/* ------------------ 커서 ------------------ */