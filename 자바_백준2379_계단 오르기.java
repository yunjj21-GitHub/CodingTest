// 백준 2379 : 계단 오르기
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
		
		// 답안 갱신
		answer = dp[N];
		return answer;
	}
	
	public static void main(String[] args) {
		Main sol = new Main();
		
		// 입력값을 받아온다.
		Scanner scanner = new Scanner(System.in);
		int N = scanner.nextInt(); // 계단 수
		
		int[] score = new int[N + 1];
		for(int i=1; i<=N; i++) score[i] = scanner.nextInt();
		
		// 답안 출력
		int ret = sol.solution(N, score);
		System.out.println(ret);
	}
}