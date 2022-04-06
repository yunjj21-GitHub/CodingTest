// 백준 12919 : A와 B 2 (완전탐색)
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool result = false;

void solution(string S, string T);
string reverseStr(string str);

int main() {
	string S, T; // 시작 문자열 S, 타겟 문자열 T
	cin >> S >> T;

	solution(S, T);
	cout << result << endl;
}

void solution(string S, string T) {
	// 종료조건
	if (S.size() == T.size()) { 
		if (S == T) result = true;
		return;
	}

	if (T[T.size() - 1] == 'A') { // 문자열의 마지막 문자가 A라면
		solution(S, T.substr(0, T.size() - 1)); // A를 제거
	}
	
	if (T[0] == 'B') { // 문자열의 시작 문자가 B라면
		string tmp = T.substr(1); // B가 제거된 문자열
		solution(S, reverseStr(tmp));
	}
}

string reverseStr(string str) {
	for (int i = 0; i < str.size() / 2; i++) {
		char tmp = str[i];
		str[i] = str[(str.size() - 1) - i];
		str[(str.size() - 1) - i] = tmp;
	}
	return str;
}