// 백준 11726 : 2xn 타일링
import java.util.*;

class Main {
	public int solution(int n) {
		int answer = 0;
		
		int[] dp = new int[1005];
		dp[1] = 1;
		dp[2] = 2;
		dp[3] = 3;
		for(int i=4; i<=n; i++) {
			dp[i] = dp[i-1] + dp[i- 2];
 		}
		
		// 답안 갱신
		answer = dp[n];
		return answer;
	}
	
	public static void main(String[] args) {
		Main sol = new Main();
		
		// 입력값을 받아온다.
		Scanner scanner = new Scanner(System.in);
		int n = scanner.nextInt(); // 타일링할 가로의 길이
		
		int ret = sol.solution(n);
		System.out.println(ret);
	}
}