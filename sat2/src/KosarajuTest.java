import org.junit.Test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotEquals;

public class KosarajuTest {
    @Test
    public void two_components() {
        Digraph digraph = new Digraph();
        digraph.addEdge(1, 2);
        digraph.addEdge(2, 3);
        digraph.addEdge(3, 1);
        digraph.addEdge(4, 5);
        digraph.addEdge(5, 6);
        digraph.addEdge(6, 4);
        digraph.addEdge(4, 1);
        Kosaraju kosaraju = new Kosaraju(digraph);
        Integer a = kosaraju.getComponent(1);
        Integer b = kosaraju.getComponent(2);
        Integer c = kosaraju.getComponent(3);
        assertEquals(a, b);
        assertEquals(a, c);
        a = kosaraju.getComponent(4);
        assertNotEquals(a, b);
        b = kosaraju.getComponent(5);
        c = kosaraju.getComponent(6);
        assertEquals(a, b);
        assertEquals(a, c);
    }
}
