// ���� 3190 : �� (�ùķ��̼�)
#include <iostream>
#include <string>
#include <vector>
#include <deque>

#define NULL 0
#define APPLE 1
#define SNACK 2

using namespace std;

int N, K, L; // ������ ũ�� N, ����� ���� K, ���� ���� ��ȯ Ƚ�� L
int map[100][100]; // ������ ���� ������ ����
deque<pair<int, char>> snackDir; // ���� ���� ��ȯ ������ ���� {sec, dir}
// ���� ������ ���� (�ð����, �� �� �� ��)
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

void getUserInput() {
    cin >> N >> K;
    for (int i = 0; i < K; i++) {
        int y, x;
        cin >> y >> x;
        y--, x--; // �ε���
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

    // ���� ��ġ������ ���� {y, x, dir}, �� ��ǥ������ ���� ��������� ����ؾ� �ϱ⿡ deque ���
    map[0][0] = SNACK;
    snack.push_front({ 0, 0, 1 });

    // 'Dummy' ���� ����
    while (true) {
        result++; // �� �ʸ��� ���� �̵��Ѵ�.

        // ���� ���� ��ǥ�� ���� ����
        int y = snack.front()[0];
        int x = snack.front()[1];
        int dir = snack.front()[2];

        // ���� �Ӹ��� �̵��� ���� Ȯ���Ѵ�.
        int nxtY = y + dy[dir];
        int nxtX = x + dx[dir];

        // ���� �Ӹ��� �̵��� �� �ִ� ������ Ȯ���Ѵ�.
        if (0 > nxtY || nxtY >= N || 0 > nxtX || nxtX >= N) break; // �Ӹ��� ���� �ε��� ���
        if (map[nxtY][nxtX] == SNACK) break; // �Ӹ��� �ڽ��� ���� �ε��� ���

        // ���� �Ӹ��� �̵��� ���� ����� �ִ��� Ȯ���Ѵ�.
        if (map[nxtY][nxtX] != APPLE) {
            map[snack.back()[0]][snack.back()[1]] = NULL;
            snack.pop_back();
        }

        // ���� �Ӹ��� �̵��Ѵ�.
        map[nxtY][nxtX] = SNACK;

        // �̵� �Ϸ� �� ������ ��ȯ�ؾ� �ϴ��� Ȯ���Ѵ�.
        int nxtDir = dir;
        if (!snackDir.empty() && result == snackDir.front().first) {
            if (snackDir.front().second == 'L') nxtDir = (nxtDir + 3) % 4; // �ݽð����� 90�� ȸ��
            else nxtDir = ++nxtDir % 4; // �ð� �������� 90�� ȸ��

            snackDir.pop_front();
        }

        // �ش� ��ǥ������ ��������� ����Ѵ�.
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