// 백준 9005 : 1, 2, 3 더하기
import java.util.*;

class Main {
	public int[] solution(int T, int[] n) {
		int[] answer = new int[T];
		
		for(int i=0; i<T; i++) {
			int[] dp = new int[15];
			dp[1] = 1;
			dp[2] = dp[1] + 1;
			dp[3] = dp[1] + dp[2] + 1;
			
			for(int j=4; j<=n[i]; j++) {
				dp[j] = dp[j-3] + dp[j-2] + dp[j-1];
			}
			
			answer[i] = dp[n[i]];
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
		
		// 답안 출력
		int[] ret = sol.solution(T, n);
		for(int i=0; i<T; i++) {
			System.out.println(ret[i]);
		}
	}
}
