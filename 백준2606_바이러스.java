package kyoboCodingTestPractice;
// ���� 2606 : ���̷���
import java.util.*;

class Main {
	public int solution(int N, int M, ArrayList<Integer>[] graph) {
		int answer = -1; // 1�� ��ǻ�� ������
		
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
		
		// �Է°��� �޾ƿ´�.
		Scanner scanner = new Scanner(System.in);
		int N = scanner.nextInt(); // ����� ����
		int M = scanner.nextInt(); // ������ ����
		
		// 2���� ArrayList ���� ��� (^^,,,)
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
		
		// ��� ���
		int ret = sol.solution(N, M, graph);
		System.out.println(ret);
	}
}