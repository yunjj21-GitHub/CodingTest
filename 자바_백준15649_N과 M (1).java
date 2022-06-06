// 백준 15649 : N과 M (1)
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
		
		// 입력값을 받아온다.
		Scanner scanner = new Scanner(System.in);
		int n = scanner.nextInt(); // 자연수의 범위
		int m = scanner.nextInt(); // 수열의 길이
		
		sol.solution(n, m);
	}
}