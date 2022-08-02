// 백준 14499 : 주사위 굴리기
#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

struct Dice {
    int west = 0;
    int north = 0;
    int east = 0;
    int south = 0;
    int top = 0;
    int btm = 0;
};

int N, M; // 지도의 세로 크기 N, 가로 크기 M
vector<vector<int>> map; // 지도의 정보를 저장
int y, x; // 주사위의 초기 좌표
int K; // 명령의 개수
queue<int> order; // 명령의 정보를 저장
Dice dice = { 0, 0, 0, 0, 0, 0 }; // 주사위의 상태 정보를 저장
// 주사위의 움직임을 정의 {동, 서, 북, 남}
int dy[4] = { 0, 0, -1, 1 };
int dx[4] = { 1, -1, 0, 0 };

void getUserInputValue() {
    cin >> N >> M >> y >> x >> K;
    map.resize(N, vector<int>(M));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> map[i][j];
        }
    }
    for (int i = 0; i < K; i++) {
        int dir;
        cin >> dir;
        dir--;
        order.push(dir);
    }
}

void rollDice(int dir) {
    Dice tmp = { 0, 0, 0, 0, 0, 0 };
    if (dir == 0) { // 동쪽
        tmp.west = dice.btm;
        tmp.north = dice.north;
        tmp.east = dice.top;
        tmp.south = dice.south;
        tmp.top = dice.west;
        tmp.btm = dice.east;
    }
    else if (dir == 1) { // 서쪽
        tmp.west = dice.top;
        tmp.north = dice.north;
        tmp.east = dice.btm;
        tmp.south = dice.south;
        tmp.top = dice.east;
        tmp.btm = dice.west;
    }
    else if (dir == 2) { // 북쪽
        tmp.west = dice.west;
        tmp.north = dice.top;
        tmp.east = dice.east;
        tmp.south = dice.btm;
        tmp.top = dice.south;
        tmp.btm = dice.north;
    }
    else { // dir == 3, 남쪽
        tmp.west = dice.west;
        tmp.north = dice.btm;
        tmp.east = dice.east;
        tmp.south = dice.top;
        tmp.top = dice.north;
        tmp.btm = dice.south;
    }
    dice = tmp;
}

void solution() {
    while (!order.empty()) {
        int dir = order.front();
        order.pop();
        
        int nxtY = y + dy[dir];
        int nxtX = x + dx[dir];

        // 주사위가 이동할 수 있는지 확인한다.
        if (0 > nxtY || nxtY >= N || 0 > nxtX || nxtX >= M) continue;

        // 주사위를 굴린다.
        rollDice(dir);

        // 주사위가 이동한 칸에 쓰여 있는 수를 확인한다.
        if (map[nxtY][nxtX] == 0) {
            map[nxtY][nxtX] = dice.btm;
        }
        else {
            dice.btm = map[nxtY][nxtX];
            map[nxtY][nxtX] = 0;
        }

        // 주사위 윗 면에 쓰여 있는 수를 출력한다.
        cout << dice.top << endl;

        // 주사위의 현재위치를 갱신한다.
        y = nxtY, x = nxtX;
    }
}

int main() {
    getUserInputValue();

    solution();
}