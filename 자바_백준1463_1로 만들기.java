// 백준 1463 : 1로 만들기
import java.util.*;

class Main {
	public int solution(int n) {
		int answer = 0;
		
		int[] dp = new int[n + 1];
		int INF = 10000000; // 임의의 큰 값
		Arrays.fill(dp, INF);
		dp[n] = 0;
		for(int i=n; i>=1; i--) {
			if(i % 3 == 0) { // 3으로 나누는 경우
				dp[i / 3] = Math.min(dp[i / 3], dp[i] + 1);	
			}
			if(i % 2 == 0) { // 2로 나누는 경우
				dp[i / 2] = Math.min(dp[i / 2], dp[i] + 1);
			}
			// 1을 빼는 경우
			dp[i - 1] = Math.min(dp[i-1], dp[i]  + 1);
		}
		
		answer = dp[1];
		return answer;
	}
	
	public static void main(String[] args) {
		Main sol = new Main();
		
		// 입력값을 받아온다.
		Scanner scanner = new Scanner(System.in);
		int input = scanner.nextInt();
		int ret = sol.solution(input);
		
		System.out.println(ret);
	}
}
