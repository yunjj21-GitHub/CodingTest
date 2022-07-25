// ���� 1916 : �ּҺ�� ���ϱ� (���ͽ�Ʈ�� �˰���)
#include <iostream>
#include <string>
#include <vector>
#define INF 100000000

using namespace std;

int N, M; // ������ ���� N, ������ ���� M
vector<vector<int>> bus; // ������ ���� ������ ����
int A, B; // ���ϰ��� �ϴ� ������ ����� A, ������ B
vector<bool> visit; // �� ������ �湮���θ� ����
vector<int> A_bus; // ���ͽ�Ʈ���� ����� ����

void getUserInput() {
	cin >> N >> M;
	bus.resize(N + 1, vector<int>(N + 1, INF));
	visit.resize(N + 1);
	A_bus.resize(N + 1);
	for (int i = 0; i < M; i++) {
		int x, y, cost;
		cin >> x >> y >> cost;
		// ��ߵ��ÿ� �������ð� ������ �������� ���� ������ ���� �� �ֱ� ����
		if(cost < bus[x][y]) bus[x][y] = cost;
	}
	cin >> A >> B;
}

int getSmallIndex() {
	int min = INF;
	int index = 0;
	for (int i = 1; i <= N; i++) {
		if (A_bus[i] < min && !visit[i]) {
			min = A_bus[i];
			index = i;
		}
	}
	return index;
}

void dijkstra(int start) {
	// ��� ���� �ʱ�ȭ
	for (int i = 1; i <= N; i++) {
		A_bus[i] = bus[start][i];
	}

	// ������� ���Ѵ�.
	visit[start] = true;
	for (int i = 0; i < N - 2; i++) { // ��ߵ��� start, �������� end ����
		int current = getSmallIndex(); // ���İ��� ���� current
		visit[current] = true;

		for (int end = 1; end <= N; end++) {
			if (!visit[end]) {
				if (A_bus[current] + bus[current][end] < A_bus[end]) {
					A_bus[end] = A_bus[current] + bus[current][end];
				}
			}
		}
	}
}

int main() {
	int answer;

	getUserInput();

	dijkstra(A);

	answer = A_bus[B];
	cout << answer << endl;
}