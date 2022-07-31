// 백준 3190 : 뱀 (시뮬레이션)
#include <iostream>
#include <string>
#include <vector>
#include <deque>

#define NULL 0
#define APPLE 1
#define SNACK 2

using namespace std;

int N, K, L; // 보드의 크기 N, 사과의 개수 K, 뱀의 방향 변환 횟수 L
int map[100][100]; // 보드의 상태 정보를 저장
deque<pair<int, char>> snackDir; // 뱀의 방향 전환 정보를 저장 {sec, dir}
// 뱀의 움직임 정의 (시계방향, 상 우 하 좌)
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

void getUserInput() {
    cin >> N >> K;
    for (int i = 0; i < K; i++) {
        int y, x;
        cin >> y >> x;
        y--, x--; // 인덱싱
        map[y][x] = APPLE;
    }
    cin >> L;
    for (int i = 0; i < L; i++) {
        int sec;
        char dir;
        cin >> sec >> dir;
        snackDir.push_back({ sec, dir });
    }
}

int solution() {
    int result = 0;
    deque<vector<int>> snack;

    // 뱀의 위치정보를 저장 {y, x, dir}, 각 좌표에서의 뱀의 진행방향을 기억해야 하기에 deque 사용
    map[0][0] = SNACK;
    snack.push_front({ 0, 0, 1 });

    // 'Dummy' 게임 시작
    while (true) {
        result++; // 매 초마다 뱀이 이동한다.

        // 뱀의 현재 좌표와 진행 방향
        int y = snack.front()[0];
        int x = snack.front()[1];
        int dir = snack.front()[2];

        // 뱀의 머리가 이동할 곳을 확인한다.
        int nxtY = y + dy[dir];
        int nxtX = x + dx[dir];

        // 뱀의 머리가 이동할 수 있는 곳인지 확인한다.
        if (0 > nxtY || nxtY >= N || 0 > nxtX || nxtX >= N) break; // 머리가 벽에 부딪힌 경우
        if (map[nxtY][nxtX] == SNACK) break; // 머리가 자신의 몸에 부딪힌 경우

        // 뱀의 머리가 이동할 곳에 사과가 있는지 확인한다.
        if (map[nxtY][nxtX] != APPLE) {
            map[snack.back()[0]][snack.back()[1]] = NULL;
            snack.pop_back();
        }

        // 뱀의 머리가 이동한다.
        map[nxtY][nxtX] = SNACK;

        // 이동 완료 후 방향을 변환해야 하는지 확인한다.
        int nxtDir = dir;
        if (!snackDir.empty() && result == snackDir.front().first) {
            if (snackDir.front().second == 'L') nxtDir = (nxtDir + 3) % 4; // 반시계으로 90도 회전
            else nxtDir = ++nxtDir % 4; // 시계 방향으로 90도 회전

            snackDir.pop_front();
        }

        // 해당 좌표에서의 진행방향을 기록한다.
        snack.push_front({ nxtY, nxtX, nxtDir });
    }

    return result;
}

int main() {
    int answer = 0;

    getUserInput();

    answer = solution();

    cout << answer << endl;
}