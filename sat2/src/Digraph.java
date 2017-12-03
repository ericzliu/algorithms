import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;

public class Digraph {

    HashMap<Integer, List<Integer>> adjencencyLists = new HashMap<>();

    public void addEdge(Integer u, Integer v) {
        if (adjencencyLists.containsKey(u)) {
        }
        else {
            adjencencyLists.put(u, new ArrayList<>());
        }
        adjencencyLists.get(u).add(v);
    }

    Iterable<Integer> allNodes() {
        return adjencencyLists.keySet();
    }

    Iterable<Integer> getEdges(Integer u) {
        if (adjencencyLists.containsKey(u)) {
            return adjencencyLists.get(u);
        }
        return Collections.emptyList();
    }

    Digraph transpose() {
        Digraph digraph = new Digraph();
        for (Integer u :
                allNodes()) {
            for (Integer v :
                    getEdges(u)) {
                digraph.addEdge(v, u);
            }
        }
        return digraph;
    }

}
