// ���� 11726 : 2xn Ÿ�ϸ�
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
		
		// ��� ����
		answer = dp[n];
		return answer;
	}
	
	public static void main(String[] args) {
		Main sol = new Main();
		
		// �Է°��� �޾ƿ´�.
		Scanner scanner = new Scanner(System.in);
		int n = scanner.nextInt(); // Ÿ�ϸ��� ������ ����
		
		int ret = sol.solution(n);
		System.out.println(ret);
	}
}