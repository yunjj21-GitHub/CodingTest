// ���� 12919 : A�� B 2 (����Ž��)
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool result = false;

void solution(string S, string T);
string reverseStr(string str);

int main() {
	string S, T; // ���� ���ڿ� S, Ÿ�� ���ڿ� T
	cin >> S >> T;

	solution(S, T);
	cout << result << endl;
}

void solution(string S, string T) {
	// ��������
	if (S.size() == T.size()) { 
		if (S == T) result = true;
		return;
	}

	if (T[T.size() - 1] == 'A') { // ���ڿ��� ������ ���ڰ� A���
		solution(S, T.substr(0, T.size() - 1)); // A�� ����
	}
	
	if (T[0] == 'B') { // ���ڿ��� ���� ���ڰ� B���
		string tmp = T.substr(1); // B�� ���ŵ� ���ڿ�
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