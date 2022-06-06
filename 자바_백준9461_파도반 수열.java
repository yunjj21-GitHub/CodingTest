// ���� 9461 : �ĵ��� ����
import java.util.*;

class Main {
	public void solution(int T) {
		while(T-- != 0) {
			Scanner scanner = new Scanner(System.in);
			int n = scanner.nextInt();
			
			int[] dp = new int[n+1];
			dp[1] = 1;
			dp[2] = 1;
			dp[3] = 1;
			for(int i=4; i<=n; i++) {
				dp[i] = dp[i-2] + dp[i-3];
			}
			System.out.println(dp[n]);
		}
	}
	
	public static void main(String[] args) {
		Main sol = new Main();
		
		// �Է°��� �޾ƿ´�.
		Scanner scanner = new Scanner(System.in);
		int T = scanner.nextInt(); // �׽�Ʈ���̽���  ��
		sol.solution(T);
	}
}