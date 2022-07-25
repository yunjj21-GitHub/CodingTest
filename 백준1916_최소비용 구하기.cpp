// 백준 1916 : 최소비용 구하기 (다익스트라 알고리즘)
#include <iostream>
#include <string>
#include <vector>
#define INF 100000000

using namespace std;

int N, M; // 도시의 개수 N, 버스의 개수 M
vector<vector<int>> bus; // 도시의 버스 정보를 저장
int A, B; // 구하고자 하는 도시의 출발지 A, 도착지 B
vector<bool> visit; // 각 도시의 방문여부를 저장
vector<int> A_bus; // 다익스트라의 결과를 저장

void getUserInput() {
	cin >> N >> M;
	bus.resize(N + 1, vector<int>(N + 1, INF));
	visit.resize(N + 1);
	A_bus.resize(N + 1);
	for (int i = 0; i < M; i++) {
		int x, y, cost;
		cin >> x >> y >> cost;
		// 출발도시와 도착도시가 동일한 여러개의 버스 정보가 들어올 수 있기 때문
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
	// 결과 벡터 초기화
	for (int i = 1; i <= N; i++) {
		A_bus[i] = bus[start][i];
	}

	// 결과값을 구한다.
	visit[start] = true;
	for (int i = 0; i < N - 2; i++) { // 출발도시 start, 도착도시 end 제외
		int current = getSmallIndex(); // 거쳐가는 도시 current
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