// 백준 1003 : 피보나치 함수
import java.util.*;

class Main {
	public int[][] solution(int T, int[] n) {
		int[][] answer = new int[T][2];
		
		for(int i=0; i<T; i++) {
			int[][] dp = new int[45][2];
			
			dp[0][0] = 1;
			dp[0][1] = 0;
			dp[1][0] = 0;
			dp[1][1] = 1;
			
			for(int j=2; j<=n[i]; j++) {
				dp[j][0] = dp[j-1][0] + dp[j-2][0];
				dp[j][1] = dp[j-1][1] + dp[j-2][1];
			}
			
			answer[i][0] = dp[n[i]][0];
			answer[i][1] = dp[n[i]][1];
		}
		
		return answer;
	}
	
	public static void main(String[] args) {
		Main sol = new Main();
		
		// 입력값을 받아온다.
		Scanner scanner = new Scanner(System.in);
		int T = scanner.nextInt();
		int[] n = new int[T];
		for(int i=0; i<T; i++) {
			n[i] = scanner.nextInt();
		}
		
		int[][] ret = sol.solution(T, n);
		for(int i=0; i<T; i++) {
			System.out.println(ret[i][0] + " " + ret[i][1]);
		}
	}
}