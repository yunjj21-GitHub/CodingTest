// 백준 1002 : 터렛
import java.util.*;

class Main {
	public void solution(int T) {
		Scanner scanner = new Scanner(System.in);
		ArrayList<Integer> answer = new ArrayList<Integer>();
		while(T-- != 0) {
			int x1 = scanner.nextInt();
			int y1 = scanner.nextInt();
			int r1 = scanner.nextInt();
			int x2 = scanner.nextInt();
			int y2 = scanner.nextInt();
			int r2 = scanner.nextInt();
			
			double d = Math.sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
			int subR1R2 = Math.abs(r1- r2);
			
			if(d == 0 && r1 == r2) answer.add(-1);
			else if(r1+r2 == d || subR1R2 == d) answer.add(1);
			else if(subR1R2 < d && d < r1 + r2) answer.add(2);
			else answer.add(0);
		}
		
		for(Integer ans : answer) {
			System.out.println(ans);
		}
	}
	
	public static void main(String[] args) {
		Main sol = new Main();
		
		// 입력값을 받아온다.
		Scanner scanner = new Scanner(System.in);
		int T = scanner.nextInt(); // 테스트케이스의  수
		sol.solution(T);
	}
}