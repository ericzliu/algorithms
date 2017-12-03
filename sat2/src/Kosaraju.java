import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.Stack;

public class Kosaraju {

    private Map<Integer, Integer> scc;

    public Kosaraju(Digraph digraph) {
        Set<Integer> visited = new HashSet<>();
        List<Integer> finished = new ArrayList<>();
        for (Integer u : digraph.allNodes()) {
            if (!visited.contains(u)) {
                dfs(digraph, u, visited, finished);
            }
        }
        int length = finished.size();
        int num = 0;
        Digraph transGraph = digraph.transpose();
        Map<Integer, Integer> cc = new HashMap<>();
        for (int i = length - 1; i > -1 ; i--) {
            Integer u = finished.get(i);
            if (!cc.containsKey(u)) {
                num += 1;
                dfs2(transGraph, u, num, cc);
            }
        }
        scc = cc;
    }

    private static void dfs(Digraph digraph, Integer s, Set<Integer> visited, List<Integer> finished) {
        Stack<Integer> pile = new Stack<>();
        visited.add(s);
        pile.push(s);
        while (!pile.empty()) {
            Integer u = pile.peek();
            boolean allVisited = true;
            for (Integer v :
                    digraph.getEdges(u)) {
                if (!visited.contains(v)) {
                    allVisited = false;
                    pile.push(v);
                    visited.add(v);
                }
            }
            if (allVisited) {
                finished.add(u);
                pile.pop();
            }
        }
    }

    private static void dfs2(Digraph digraph, Integer s, Integer num, Map<Integer, Integer> cc) {
        Stack<Integer> pile = new Stack<>();
        pile.push(s);
        cc.put(s, num);
        while (!pile.empty()) {
            Integer u = pile.pop();
            for (Integer v :
                    digraph.getEdges(u)) {
                if (!cc.containsKey(v)) {
                    cc.put(v, num);
                    pile.push(v);
                }
            }
        }
    }

    public Integer getComponent(Integer u) {
        if (scc.containsKey(u)) {
            return scc.get(u);
        }
        return 0;
    }
}
