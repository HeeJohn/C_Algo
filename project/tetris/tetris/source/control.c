#include <control_h.h>


void check_key(void) {
    key = 0; //키값 초기화  

    if (_kbhit()) { //키입력이 있는 경우  
        key = _getch(); //키값을 받음
        if (key == 224) { //방향키인경우 
            do { key = _getch(); } while (key == 224);//방향키지시값을 버림 
            switch (key) {
            case LEFT: //왼쪽키 눌렀을때  
                if (check_crush(bx - 1, by, b_rotation) == true) move_block(LEFT);
                break;                            //왼쪽으로 갈 수 있는지 체크 후 가능하면 이동
            case RIGHT: //오른쪽 방향키 눌렀을때- 위와 동일하게 처리됨 
                if (check_crush(bx + 1, by, b_rotation) == true) move_block(RIGHT);
                break;
            case DOWN: //아래쪽 방향키 눌렀을때-위와 동일하게 처리됨 
                if (check_crush(bx, by + 1, b_rotation) == true) move_block(DOWN);
                break;
            case UP: //위쪽 방향키 눌렀을때 
                if (check_crush(bx, by, (b_rotation + 1) % 4) == true) move_block(UP);
                //회전할 수 있는지 체크 후 가능하면 회전
                else if (crush_on == 1 && check_crush(bx, by - 1, (b_rotation + 1) % 4) == true) move_block(100);
            }                    //바닥에 닿은 경우 위쪽으로 한칸띄워서 회전이 가능하면 그렇게 함(특수동작)
        }
        else { //방향키가 아닌경우 
            switch (key) {
            case SPACE: //스페이스키 눌렀을때 
                space_key_on = 1; //스페이스키 flag를 띄움 
                while (crush_on == 0) { //바닥에 닿을때까지 이동시킴 
                    drop_block();
                    score += level; // hard drop 보너스
                    gotoxy(STATUS_X_ADJ, STATUS_Y_SCORE); printf("        %6d", score); //점수 표시  
                }
                break;
            case P: //P(대문자) 눌렀을때 
            case p: //p(소문자) 눌렀을때 
                pause(); //일시정지 
                break;
            case ESC: //ESC눌렀을때 
                system("cls"); //화면을 지우고 
                exit(0); //게임종료 
            }
        }
    }
    while (_kbhit()) _getch(); //키버퍼를 비움 
}

void move_block(int dir) { //블록을 이 동시킴 
    int i, j;

    switch (dir) {
    case LEFT: //왼쪽방향 
        for (i = 0; i < 4; i++) { //현재좌표의 블럭을 지움 
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) board_curr[by + i][bx + j] = EMPTY;
            }
        }
        for (i = 0; i < 4; i++) { //왼쪽으로 한칸가서 active block을 찍음 
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) board_curr[by + i][bx + j - 1] = ACTIVE_BLOCK;
            }
        }
        bx--; //좌표값 이동 
        break;

    case RIGHT:    //오른쪽 방향. 왼쪽방향이랑 같은 원리로 동작 
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

    case DOWN:    //아래쪽 방향. 왼쪽방향이랑 같은 원리로 동작
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

    case UP: //키보드 위쪽 눌렀을때 회전시킴. 
        for (i = 0; i < 4; i++) { //현재좌표의 블럭을 지움  
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) board_curr[by + i][bx + j] = EMPTY;
            }
        }
        b_rotation = (b_rotation + 1) % 4; //회전값을 1증가시킴(3에서 4가 되는 경우는 0으로 되돌림) 
        for (i = 0; i < 4; i++) { //회전된 블록을 찍음 
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) board_curr[by + i][bx + j] = ACTIVE_BLOCK;
            }
        }
        break;

    case 100: //블록이 바닥, 혹은 다른 블록과 닿은 상태에서 한칸위로 올려 회전이 가능한 경우 
        //이를 동작시키는 특수동작 
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) board_curr[by + i][bx + j] = EMPTY;
            }//원래 있던
        }
        b_rotation = (b_rotation + 1) % 4;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) board_curr[by + i - 1][bx + j] = ACTIVE_BLOCK;
            }
        }//한칸 위로 올림
        by--;
        break;
    }
}
void drop_block(void) {
    int i, j;

    if (crush_on && check_crush(bx, by + 1, b_rotation) == true) crush_on = 0; //밑이 비어있으면 crush flag 끔 
    if (crush_on && check_crush(bx, by + 1, b_rotation) == false) { 
        //밑이 비어있지않고 crush flag가 켜저있으면 
        for (i = 0; i < BOARD_Y; i++) { //현재 조작중인 블럭을 굳힘 
            for (j = 0; j < BOARD_X; j++) {
                if (board_curr[i][j] == ACTIVE_BLOCK) board_curr[i][j] = INACTIVE_BLOCK;
            }
        }
        crush_on = 0; //flag를 끔 
        check_line(); //라인체크를 함 
        create_nblock_on = 1; //새로운 블럭생성 flag를 켬    
        return; //함수 종료 
    }

    if (check_crush(bx, by + 1, b_rotation) == true) move_block(DOWN); //밑이 비어있으면 밑으로 한칸 이동 
    if (check_crush(bx, by + 1, b_rotation) == false) crush_on++; //밑으로 이동이 안되면  crush flag를 켬
}

