//
// Created by ZNSY on 2020/5/19.
//

#include "board.h"
#include <iostream>
#include <string>
using namespace std;

//��������
int Board::place(int x, int y, int color) {
    if (!this->board[x][y]) {
        this->board[x][y] = color;
        return 1;
    }
    else
        return 0;
}

//����ʤ�����ʱlength = 0
int Board::check(int x, int y, int color, int length, int directX, int directY) {
    int nowLength;
//    ��ʤ���
    if (length == CHESS) {
        this->win = color;
        return CHESS;
    }
//    δ��ʤ������Ǽ��ĵ�һ�����ӣ�������Χ�����ݹ���
    else if (directX == 0 && directY == 0){
//        ������������Χ
        for (int i=-1; i<2; i++){
            for (int j=-1; j<2; j++){
//                �������Լ���������ɫ��һ�µ����ӣ�����
                if ((i == 0 && j == 0) || (this->board[x+i][y+j] != color))
                    continue;
//                ����ݹ����¼��
                else {
                    nowLength = this->check(x+directX, y+directY, color, length+1, i, j);
                    if (nowLength == CHESS) return 5;
                }
            }
        }
    }
//    δ��ʤ������Ǽ����;�����Ӳ���û��ʤ�������ݹ�
    else {
        if (this->board[x+directX][y+directY] == color)
            return this->check(x+directX, y+directY, color, length+1, directX, directY);
        else
            return 0;
    };
    return 0;
}

void Board::print(bool cur) {
    const string white=" �� ", black =" �� ", cursor = " + ";
    const string LT   =" �� ", TOP   =" �� ", RT   =" �� ";
    const string LEFT =" �� ", CENTER =" �� ", RIGHT=" �� ";
    const string LF   =" �� ", FOOT  =" �� ",  RF   =" �� ";
    const string SPACE="   ";

//    ���̻��Ƴ�ʼ��
    string display[2*SIZE+1][2*SIZE+1];
    for (int i = 0; i < 2 * SIZE + 1; i ++)
        for (int j = 0; j < 2 * SIZE + 1; j ++)
            display[i][j] = SPACE;

    display[0][0] = LT, display[0][2*SIZE] = RT, display[2*SIZE][0] = LF, display[2*SIZE][2*SIZE] = RF;
    for (int i = 2; i < 2 * SIZE; i += 2){
        display[0][i] = TOP, display[i][0] = LEFT, display[2*SIZE][i] = FOOT, display[i][2*SIZE] = RIGHT;
        for (int j = 2; j < 2 * SIZE; j += 2){
            display[i][j] = CENTER;
        }
    }
//    ��������
    for (int i = 0; i < SIZE; i ++){
        for (int j = 0; j < SIZE; j ++){
            int piece = this->board[i][j];
            if (!piece) continue;
            else if (piece == WHITE) display[2*i+1][2*j+1] = white;
            else if (piece == BLACK) display[2*i+1][2*j+1] = black;
        }
    }

//    �L�u���
    if (cur) {
        int row = this->cursorPos[0], col = this->cursorPos[1];
        display[2 * row + 1][2 * col + 1] = cursor;
    }
//    ���
    for (int i = 0; i < 2 * SIZE + 1; i ++) {
        for (int j = 0; j < 2 * SIZE + 1; j++) {
            cout << display[i][j];
        }
        cout << endl;
    }
}

