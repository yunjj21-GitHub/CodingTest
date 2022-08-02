// ���� 14499 : �ֻ��� ������
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

int N, M; // ������ ���� ũ�� N, ���� ũ�� M
vector<vector<int>> map; // ������ ������ ����
int y, x; // �ֻ����� �ʱ� ��ǥ
int K; // ����� ����
queue<int> order; // ����� ������ ����
Dice dice = { 0, 0, 0, 0, 0, 0 }; // �ֻ����� ���� ������ ����
// �ֻ����� �������� ���� {��, ��, ��, ��}
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
    if (dir == 0) { // ����
        tmp.west = dice.btm;
        tmp.north = dice.north;
        tmp.east = dice.top;
        tmp.south = dice.south;
        tmp.top = dice.west;
        tmp.btm = dice.east;
    }
    else if (dir == 1) { // ����
        tmp.west = dice.top;
        tmp.north = dice.north;
        tmp.east = dice.btm;
        tmp.south = dice.south;
        tmp.top = dice.east;
        tmp.btm = dice.west;
    }
    else if (dir == 2) { // ����
        tmp.west = dice.west;
        tmp.north = dice.top;
        tmp.east = dice.east;
        tmp.south = dice.btm;
        tmp.top = dice.south;
        tmp.btm = dice.north;
    }
    else { // dir == 3, ����
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

        // �ֻ����� �̵��� �� �ִ��� Ȯ���Ѵ�.
        if (0 > nxtY || nxtY >= N || 0 > nxtX || nxtX >= M) continue;

        // �ֻ����� ������.
        rollDice(dir);

        // �ֻ����� �̵��� ĭ�� ���� �ִ� ���� Ȯ���Ѵ�.
        if (map[nxtY][nxtX] == 0) {
            map[nxtY][nxtX] = dice.btm;
        }
        else {
            dice.btm = map[nxtY][nxtX];
            map[nxtY][nxtX] = 0;
        }

        // �ֻ��� �� �鿡 ���� �ִ� ���� ����Ѵ�.
        cout << dice.top << endl;

        // �ֻ����� ������ġ�� �����Ѵ�.
        y = nxtY, x = nxtX;
    }
}

int main() {
    getUserInputValue();

    solution();
}