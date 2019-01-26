/**  最多考虑单房间多门+动态场的情况  **/
# include <iostream>
# include <queue>
# include <iomanip>
# include <memory.h>
# include <math.h>

using namespace std;
# define MIN(x,y)  ( x < y ) ? x : y;
const int LINESIZE = 30; // 房间的长
const int COLUMNSIZE = 30; // 房间的宽
const int ENTRANCE[10][2][2] = {{ {0, 14}, {0, 16} }}; // 入口位置
const int firstFzn = 1;  // firstFzn = ENTRANCE_ENERGY
int map[LINESIZE][COLUMNSIZE];
double fzn[2][LINESIZE][COLUMNSIZE]; // 定义静态场数组
queue<int> qyl, cqs; // 静态场的初始化队列

/*  int PRINT   标准输出模块
 *  string str 输出种类字段
 */

int PRINT(string str) {
    if ("fzn" == str) {
        for (int i = 0; i < LINESIZE; i++) {
            for (int j = 0; j < COLUMNSIZE; j++) {
                cout << right << setw(5) << fzn[0][i][j] << " ";
            }
            cout << endl;
        }
    }
    if ("map" == str) {
        for (int i = 0; i < LINESIZE; i++) {
            for (int j = 0; j < COLUMNSIZE; j++) {
                cout << right << setw(4) << map[i][j];
            }
            cout << endl;
        }
    }
    if ("cqs" == str) {
        while (!cqs.empty()) {
            cout << cqs.front();
            cqs.pop();
            cout << endl;
        }
    }
    return 0;
}

/*  int INIT_MAP  初始化地图
 *
 */
int INIT_MAP() {
    /**  设置墙壁和障碍物  **/
    for (int i = 0; i < LINESIZE; i++) {
        for (int j = 0; j < COLUMNSIZE; j++) {
            if (i == 0 || i == LINESIZE-1 || j == 0 || j == COLUMNSIZE-1) {
                map[i][j] = -1;
                // fzn[0][i][j] = 10000;   // 两边之和大于对角线
            }
        }
    }
    /**  设置逃生出口  **/
    for (int i = ENTRANCE[0][0][0]; i <= ENTRANCE[0][1][0]; i++) {
        for (int j = ENTRANCE[0][0][1]; j <= ENTRANCE[0][1][1]; j++) {
            map[i][j] = 0;
        }
    }
    /**  设置人群  **/
    for (int i = 10; i < 21; i++) {
        for (int j = 21; j < 25; j++) {
            map[i][j] = 1;
        }
    }
    return 0;
}

/* int INIT_STATE_FIELD 初始化静态场,静态场用于判断无人状况下的最优路径
 */
int INIT_STATE_FIELD() {
    int line, column;
    /**  初始化静态场调到最大方便后续比较  **/
    for (int i = 0; i < LINESIZE; i++) {
         for (int j = 0; j < COLUMNSIZE; j++) {
             fzn[0][i][j] = LINESIZE + COLUMNSIZE;
         }
    }
    /**  门口势能最低，设为firstFzn  **/
    for (int i = ENTRANCE[0][0][0]; i <= ENTRANCE[0][1][0]; i++) {
        for (int j = ENTRANCE[0][0][1]; j <= ENTRANCE[0][1][1]; j++) {
            fzn[0][i][j] = firstFzn;
            qyl.push(i * LINESIZE + j);      // 这个数字用来存储两个值：横纵坐标
        }
    }
    /**  再处理墙内的部分 **/
    while(!qyl.empty()) {
        line = qyl.front() / LINESIZE;
        column = qyl.front() % LINESIZE;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                /** 首先判断环绕的八个选区是否在房间内 **/
                if (( i+line > 0 && j+column > 0 && i+line < LINESIZE-1 && j+column < COLUMNSIZE-1 ) && !( i == 0 && j == 0 )) {
                    /**  其次判断该处的值是临接类型还是对角类型（影响势能的相对值）**/
                    if ( i * j == 0 ) {
                        /**  最后判断该处势能是否存在更低值的可能  **/
                        if ( 1 + fzn[0][line][column] < fzn[0][line+i][column+j] ) {
                            fzn[0][line+i][column+j] = 1 + fzn[0][line][column];
                            qyl.push((i+line) * LINESIZE + (j+column));
                        }
                    } else {
                        /**  同样判断是否存在更低值 **/
                        if ( ( 1 + fzn[0][line][column]  + 0.5 * abs(i) ) < fzn[0][line+i][column+j]) {
                            fzn[0][line+i][column+j] = 1 + fzn[0][line][column]  + 0.5 * abs(i);
                            qyl.push((i+line) * LINESIZE + (j+column));
                        }
                    }

                }
            }
        }
        /** "CHARATERISTIC"：
         *   此处有坑，如果不做这个判断，这里会出现同一格被两次计入cqs队列的可能
         *   但这个去重方法只是凭经验感觉正确，暂时还不知道怎么论证
         */
        if (cqs.empty()) {
            cqs.push(qyl.front());
        } else {
            if (cqs.back() != qyl.front()) {
                cqs.push(qyl.front());
            }
        }
        qyl.pop();
    }
//    PRINT("fzn");
    /** 设置墙壁、障碍物 **/
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
    PRINT("cqs");
    // int max = MAX(10, 9);
    // cout << max;
    return 0;
}