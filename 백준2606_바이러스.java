package kyoboCodingTestPractice;
// 백준 2606 : 바이러스
import java.util.*;

class Main {
	public int solution(int N, int M, ArrayList<Integer>[] graph) {
		int answer = -1; // 1번 컴퓨터 미포함
		
		Queue<Integer> q = new LinkedList<Integer>();
		boolean[] visit = new boolean[N+1];
		q.add(1);
		visit[1] = true;
		while(!q.isEmpty()) {
			answer++;
			ArrayList<Integer> node = graph[q.peek()];
			q.remove();
			
			for(int i=0; i<node.size(); i++) {
				if(visit[node.get(i)]) continue;
					
				q.add(node.get(i));
				visit[node.get(i)] = true;
			}
		}
		
		return answer;
	}
	
	public static void main(String[] args) {
		Main sol = new Main();
		
		// 입력값을 받아온다.
		Scanner scanner = new Scanner(System.in);
		int N = scanner.nextInt(); // 노드의 개수
		int M = scanner.nextInt(); // 간선의 개수
		
		// 2차원 ArrayList 선언 방법 (^^,,,)
		ArrayList<Integer>[] graph = new ArrayList[N+1];
		for(int i=1; i<=N; i++) {
			graph[i] = new ArrayList<Integer>();
		}
		
		for(int i=0; i<M; i++) {
			int a = scanner.nextInt();
			int b = scanner.nextInt();
			
			graph[a].add(b);
			graph[b].add(a);
		}
		
		// 답안 출력
		int ret = sol.solution(N, M, graph);
		System.out.println(ret);
	}
}