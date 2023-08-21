/* ============== 보드 UI 그리는 함수  ============== */
#ifndef BOARD_UI
#define BOARD_UI


/* ---------- 게임 프리셋 ---------- */

// 시작 페이지를 출력하고 콘솔 창 크기를 설정하는 함수
void startPage(int* consoleWidth, int* consoleHeight);

// 게임 오버 상황을 체크하고 처리하는 함수
void check_game_over(void);

// 게임 시작 시 초기 설정 함수
void preset(void);

// 현재 게임판을 초기화하는 함수
void reset_board_curr(void);

// 이전 게임판을 초기화하는 함수
void reset_board_prev(void);

// 게임판을 그리는 함수
void draw_board(void);

// 상태 정보를 그리는 함수
void draw_status(void);

/* ---------- 게임 오버 처리 ---------- */

// 게임을 일시정지시키고 일시정지 메세지를 출력하는 함수
void pause(void);

// 게임 오버 상황을 체크하고 처리하는 함수
void check_game_over(void);

// 게임 오버 메세지 출력 함수
void print_game_over_message(int x, int y);

// 최고 점수 갱신 및 파일 저장 함수
void update_best_score();

// 최고 점수 메세지 출력 함수
void print_best_score_message();


/* ---------- 게임 일시 정지 ---------- */
// 게임 일시정지 함수
void pause(void);
// 일시정지 메세지 출력 함수
void display_pause_message();
// 화면 초기화 및 재그리기 함수
void clear_and_redraw();
// 다음 블록 그리기 함수
void draw_next_block();


#endif // BOARD_UI

/* ============== 보드 UI 그리는 함수  ============== */