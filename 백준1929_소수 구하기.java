// ���� 1929 : �Ҽ� ���ϱ�
import java.util.*;

class Main {
	public void solution(int M, int N) {
		for(int i=M; i<=N; i++) {
			boolean flag = true;
			for(int j=2; j<i; j++) {
				if(i%j == 0) {
					flag = false;
					break;
				}
			}
			
			if(flag) System.out.println(i);
		}
	}
	
	public static void main(String[] args) {
		Main sol = new Main();
		
		// �Է°��� �޾ƿ´�.
		Scanner scanner = new Scanner(System.in);
		int M = scanner.nextInt();
		int N = scanner.nextInt();
		
		// ��� ���
		sol.solution(M, N);
	}
}