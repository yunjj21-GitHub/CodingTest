// ���� 2379 : ��� ������
import java.util.*;

class Main {
	public int solution(int N, int[] score) {
		int answer = 0;
		
		int[] dp = new int[N+1];
		dp[1] = score[1];
		dp[2] = score[2] + score[1]; 
		for(int i=3; i<=N; i++) {
			dp[i] = Math.max(score[i] + dp[i-2], score[i] + score[i-1] + dp[i-3]);
		}
		
		// ��� ����
		answer = dp[N];
		return answer;
	}
	
	public static void main(String[] args) {
		Main sol = new Main();
		
		// �Է°��� �޾ƿ´�.
		Scanner scanner = new Scanner(System.in);
		int N = scanner.nextInt(); // ��� ��
		
		int[] score = new int[N + 1];
		for(int i=1; i<=N; i++) score[i] = scanner.nextInt();
		
		// ��� ���
		int ret = sol.solution(N, score);
		System.out.println(ret);
	}
}