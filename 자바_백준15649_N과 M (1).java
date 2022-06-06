// ���� 15649 : N�� M (1)
import java.util.*;

class Main {
	ArrayList<Integer[]> answer;
	int N;
	int M;
	Integer[] perm;
	boolean[] chk;
	public void makePermutation(int lev) {
		if(lev == M) {
			for(int i=0; i<M; i++) System.out.print(perm[i] + " ");
			System.out.println();
			answer.add(perm);
			return;
		}
		
		for(int i=1; i<=N; i++) {
			if(chk[i]) continue;
			perm[lev] = i;
			chk[i] = true;
			makePermutation(lev + 1);
			chk[i] = false;
		}
		return;
	}
	
	public void solution(int n, int m) {
		answer = new ArrayList<Integer[]>();
		N = n;
		M = m;
		perm = new Integer[M];
		chk = new boolean[N + 1]; // 1...N
		makePermutation(0);
	}
	
	public static void main(String[] args) {
		Main sol = new Main();
		
		// �Է°��� �޾ƿ´�.
		Scanner scanner = new Scanner(System.in);
		int n = scanner.nextInt(); // �ڿ����� ����
		int m = scanner.nextInt(); // ������ ����
		
		sol.solution(n, m);
	}
}