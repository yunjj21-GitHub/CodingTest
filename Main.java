// [����������� �ڵ��׽�Ʈ ����] ���� 1463 : 1�� �����
package kyoboCodingTestPractice;
import java.util.*;

class Main {
	public int solution(int n) {
		int answer = 0;
		
		int[] dp = new int[n + 1];
		int INF = 10000000; // ������ ū ��
		Arrays.fill(dp, INF);
		dp[n] = 0;
		for(int i=n; i>=1; i--) {
			if(i % 3 == 0) { // 3���� ������ ���
				dp[i / 3] = Math.min(dp[i / 3], dp[i] + 1);	
			}
			if(i % 2 == 0) { // 2�� ������ ���
				dp[i / 2] = Math.min(dp[i / 2], dp[i] + 1);
			}
			// 1�� ���� ���
			dp[i - 1] = Math.min(dp[i-1], dp[i]  + 1);
		}
		
		answer = dp[1];
		return answer;
	}
	
	public static void main(String[] args) {
		Main sol = new Main();
		
		// �Է°��� �޾ƿ´�.
		Scanner scanner = new Scanner(System.in);
		int input = scanner.nextInt();
		int ret = sol.solution(input);
		
		System.out.println(ret);
	}
}
