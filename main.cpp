// 最多考虑单房间多门+动态场的情况
# include <iostream>
# include <queue>
# include <memory.h>
# include <math.h>

using namespace std;
# define MIN(x,y)  ( x < y ) ? x : y;
const int LINESIZE = 30; // 房间的长
const int COLUMNSIZE = 30; // 房间的宽
const int ENTRANCE[10][2][2] = {{ {0, 14}, {0, 16} }}; // 入口位置
const int firstFzn = 1;  // firstFzn = ENTRANCE_ENERGY
int map[LINESIZE][COLUMNSIZE];
int fzn[3][LINESIZE][COLUMNSIZE]; // 定义静态场数组
queue<int> qyl, cqs;

int PRINT(string str) {
    if ("fzn" == str) {
        for (int i = 0; i < LINESIZE; i++) {
            for (int j = 0; j < COLUMNSIZE; j++) {
                cout << fzn[0][i][j] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}

/* 
 *
 */ 
int INIT_MAP() {
    for (int i = 0; i < LINESIZE; i++) {
        for (int j = 0; j < COLUMNSIZE; j++) {
            if (i == 0 || i == LINESIZE || j == 0 || j == COLUMNSIZE) {
                map[i][j] = -1;  // 两边之和大于对角线
                // fzn[0][i][j] = 10000;
            }
        }
    }
    for (int i = ENTRANCE[0][0][0]; i <= ENTRANCE[0][1][0]; i++) {
        for (int j = ENTRANCE[0][0][1]; j <= ENTRANCE[0][1][1]; j++) {
            map[i][j] = 0;
        }
    }
    for (int i = 10; i < 21; i++) {
        for (int j = 21; j < 25; j++) {
            map[i][j] = 1;
        }
    }
    return 0;
}

/* int INIT_STATE_FIELD 沿入口向内初始化静态场数组
 * 
 */
int INIT_STATE_FIELD() {
    int line, column;
    // 遍历建立静态场
    // 先单独处理门的部分
    for (int i = 0; i < LINESIZE; i++) {
        for (int j = 0; j < COLUMNSIZE; j++) {
            fzn[0][i][j] = 1000;
        }
    }
    for (int i = ENTRANCE[0][0][0]; i <= ENTRANCE[0][1][0]; i++) {
        for (int j = ENTRANCE[0][0][1]; j <= ENTRANCE[0][1][1]; j++) {
            qyl.push(i * LINESIZE + j);      // 这个数字用来存储两个值：横纵坐标
        }
    }
    for (int i = ENTRANCE[0][0][0]; i <= ENTRANCE[0][1][0]; i++) {
        for (int j = ENTRANCE[0][0][1]; j <= ENTRANCE[0][1][1]; j++) {
            line = qyl.front() / LINESIZE;
            column = qyl.front() % LINESIZE;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (( i > 0 && j > 0 && i < LINESIZE-1 && j < COLUMNSIZE-1 ) && !( i == 0 && j == 0 )) {
                        if ( ( 1 + fzn[0][line][column]  + 0.5 * abs(i) ) < fzn[0][line+i][column+j]) {
                            fzn[0][line+i][column+j] = 1 + fzn[0][line][column]  + 0.5 * abs(i);
                            qyl.push((i+line) * LINESIZE + (j+column));
                            cout << "hhh" << endl;
                        }
                    }
                }
            }
            cqs.push(qyl.front());
            qyl.pop();
        }
    }
    // 再处理墙内的部分
    // while(!qyl.empty()) {
    //     column = qyl.front() / LINESIZE;
    //     line = qyl.front() % LINESIZE;
    //     for (int i = -1 + column; i <= 1 + column; i++) {
    //         for (int j = -1 + line; j <= 1 + line; j++) {
    //             if (( i > 0 && j > 0 && i < LINESIZE-1 && j < COLUMNSIZE-1 ) && !( i == 0 && j == 0 )) {
    //                 if ( ( 1 + fzn[0][line][column]  + 0.5 * abs(i) ) < fzn[0][line+i][column+j]) {
    //                     fzn[0][line+i][column+j] = 1 + fzn[0][line][column]  + 0.5 * abs(i);
    //                     qyl.push((i+line) * LINESIZE + (j+column));
    //                     cout << qyl.front() << endl;
    //                 }
    //             }
    //         }
    //     }
    //     cqs.push(qyl.front());
        
    //     qyl.pop();
    // }
    // PRINT("fzn");

    // 设置墙壁、障碍物
    for (int i = 0; i < LINESIZE; i++) {
        for (int j = 0; j < COLUMNSIZE; j++) {
            if (-1 == map[i][j]) {
                fzn[0][i][j] = LINESIZE + COLUMNSIZE;  // 两边之和大于对角线
                // fzn[0][i][j] = 10000;
            }
        }
    }
    for (int i = ENTRANCE[0][0][0]; i <= ENTRANCE[0][1][0]; i++) {
        for (int j = ENTRANCE[0][0][1]; j <= ENTRANCE[0][1][1]; j++) {
            fzn[0][i][j] = firstFzn;
        }
    }

    return 0;
}

int INIT_ALL() {
    INIT_MAP();
    
    INIT_STATE_FIELD();
    // cout << fzn[0][20][20];
    return 0;
}

int main() {
    INIT_ALL();
    // PRINT("fzn");
    // int max = MAX(10, 9);
    // cout << max;

    getchar();
    return 0;
}