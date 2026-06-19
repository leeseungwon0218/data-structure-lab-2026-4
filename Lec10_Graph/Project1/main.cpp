#include "Location2D.h"
#include <stack>
#include <deque>
#include <iostream> 
#include <queue>
//한글 x 
using namespace std;

const int MAZE_SIZE = 6;

char map[MAZE_SIZE][MAZE_SIZE] = {
    {'1','1','1','1','1','1'},
    {'0','0','1','0','0','1'},
    {'1','0','0','0','1','1'},
    {'1','0','1','0','1','1'},
    {'1','0','1','0','0','x'},
    {'1','1','1','1','1','1'}
};




bool isValidLoc(int r, int c) {
    if (r < 0 || c < 0 || r >= MAZE_SIZE || c >= MAZE_SIZE) return false;
    else return map[r][c] == '0' || map[r][c] == 'x';
}

int main() {
    int ds_num;
    printf("Select DFS data structure library : 1)stack, 2)deque \n");
    scanf_s("%d", &ds_num);
    

    switch (ds_num) {
    case 1: {

        stack<Location2D> locStack;
        Location2D entry(1, 0);
        locStack.push(entry);

        while (locStack.empty() == false) {
            Location2D here = locStack.top();
            locStack.pop();

            int r = here.row, c = here.col;
            printf("(%d,%d) ", r, c);

            if (map[r][c] == 'x') {
                printf("\nSuccess\n");
                break;
            }
            else {
                map[r][c] = '.';

                if (isValidLoc(r - 1, c)) locStack.push(Location2D(r - 1, c));
                if (isValidLoc(r + 1, c)) locStack.push(Location2D(r + 1, c));
                if (isValidLoc(r, c - 1)) locStack.push(Location2D(r, c - 1));
                if (isValidLoc(r, c + 1)) locStack.push(Location2D(r, c + 1));
            }
        }
       
    }



    case 2: {
        //덱
        deque<Location2D> locDeque;  // 위치 덱 객체 생성
        Location2D entry(1, 0);      //입구 
        locDeque.push_front(entry);     //덱에 입구 위치 삽입

        while (locDeque.empty() == false) {   //덱이 비어있지 않은동안
            Location2D here = locDeque.front(); //덱의 front 상단 객체 복사
            locDeque.pop_front();

            int r = here.row, c = here.col;
            printf("(%d,%d) ", r, c);

            if (map[r][c] == 'x') {
                printf("\nSuccess\n");
                break;
            }
            else {
                map[r][c] = '.';

                if (isValidLoc(r - 1, c)) locDeque.push_front(Location2D(r - 1, c));
                if (isValidLoc(r + 1, c)) locDeque.push_front(Location2D(r + 1, c));
                if (isValidLoc(r, c - 1)) locDeque.push_front(Location2D(r, c - 1));
                if (isValidLoc(r, c + 1)) locDeque.push_front(Location2D(r, c + 1));
            }
        }
    }
    }
    //bfs
    char initMap[MAZE_SIZE][MAZE_SIZE] = {
        {'1','1','1','1','1','1'},
        {'0','0','1','0','0','1'},
        {'1','0','0','0','1','1'},
        {'1','0','1','0','1','1'},
        {'1','0','1','0','0','x'},
        {'1','1','1','1','1','1'}

    };
    for (int i = 0; i < MAZE_SIZE; i++) {
        for (int j = 0; j < MAZE_SIZE; j++) {
            map[i][j] = initMap[i][j];
        }
    }
    printf("\n--- BFS Result ---\n");
    queue<Location2D> locQueue;
    Location2D entryBFS(1, 0);
    locQueue.push(entryBFS);

    while (locQueue.empty() == false) {
        Location2D here = locQueue.front();
        locQueue.pop();

        int r = here.row, c = here.col;
        printf("(%d,%d) ", r, c);

        if (map[r][c] == 'x') {
            printf("\nSuccess\n");
            return 0; 
        }
        else {
            map[r][c] = '.';

            if (isValidLoc(r - 1, c)) locQueue.push(Location2D(r - 1, c));
            if (isValidLoc(r + 1, c)) locQueue.push(Location2D(r + 1, c));
            if (isValidLoc(r, c - 1)) locQueue.push(Location2D(r, c - 1));
            if (isValidLoc(r, c + 1)) locQueue.push(Location2D(r, c + 1));
        }
    }

    return 0;



}
    


