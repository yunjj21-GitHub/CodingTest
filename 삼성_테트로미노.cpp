// 삼성 기출 : 테트로미노 (완전탐색 + DFS)
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int N, M; // 종이의 세로 크기 N, 가로 크기 M
vector<vector<int>> map; // 종이에 대한 정보를 저장
int answer = -1; // 답안

int dy[4] = { 0, 0, 1, -1 };
int dx[4] = { 1, -1, 0, 0 };
vector<vector<int>> visit; // DFS시 방문여부 체크

void getInputValue() {
	cin >> N >> M;
	map.resize(N, vector<int>(M)); // 종이의 사이즈 지정
	visit.resize(N, vector<int>(M)); // 방문여부 체크 배열 사이즈 지정
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}
}

void DFS(int y, int x, int depth, int sum) {
	if (visit[y][x]) return; // 아직 방문중인 좌표라면

	visit[y][x] = true; // 방문처리
	sum += map[y][x];

	if (++depth == 4) { // 테트로미노 모양이 만들어 졌다면
		if (sum > answer) answer = sum; // 답안 갱신
		
		visit[y][x] = false;
		return;
	}

	for (int i = 0; i < 4; i++) {
		int nxtY = y + dy[i];
		int nxtX = x + dx[i];

		if (0 > nxtY || nxtY >= N || 0 > nxtX || nxtX >= M) continue;

		DFS(nxtY, nxtX, depth, sum);
	}

	visit[y][x] = false;
}

void checkT(int y, int x) {
	if (y + 1 < N && x + 2 < M) { // ㅜ 모양 확인
		int sum = map[y][x] + map[y][x + 1] + map[y + 1][x + 1] + map[y][x + 2];
		answer = sum > answer ? sum : answer;
	}

	if (y - 1 >= 0 && y + 1 < N && x + 1 < M) { // ㅓ 모양 확인
		int sum = map[y][x] + map[y - 1][x + 1] + map[y][x + 1] + map[y + 1][x + 1];
		answer = sum > answer ? sum : answer;
	}

	if (y + 1 < N && x - 1 >= 0 && x + 1 < M) { // ㅗ 모양 확인
		int sum = map[y][x] + map[y + 1][x - 1] + map[y + 1][x] + map[y + 1][x + 1];
		answer = sum > answer ? sum : answer;
	}

	if (y + 2 < N && x + 1 < M) { // ㅏ 모양 확인
		int sum = map[y][x] + map[y + 1][x] + map[y + 2][x] + map[y + 1][x + 1];
		answer = sum > answer ? sum : answer;
	}
	return;
}

void solution() {
	// 모든 좌표를 기준으로 탐색 (완전탐색)
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			DFS(y, x, 0, 0); // 테트로미노 4개 확인 (대칭, 회전 포함)
			checkT(y, x); // 테트로미노 1개 확인 (대칭, 회전 포함, (ㅗ, ㅜ, ㅓ, ㅏ))
		}
	}
}

int main() {
	getInputValue(); // 입력값을 받아옴

	solution();
	
	cout << answer << '\n';
}