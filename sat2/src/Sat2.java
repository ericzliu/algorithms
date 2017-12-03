import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

public class Sat2 {
    List<Clause> clauses;

    public Sat2(List<Clause> clauses) {
        this.clauses = clauses;
    }

    public boolean solvable() {
        Digraph digraph = new Digraph();
        for (Clause c :
                clauses) {
            digraph.addEdge(-c.getP(), c.getQ());
            digraph.addEdge(-c.getQ(), c.getP());
        }
        Kosaraju kosaraju = new Kosaraju(digraph);
        for (Integer u :
                digraph.allNodes()) {
            Integer c1 = kosaraju.getComponent(u);
            Integer c2 = kosaraju.getComponent(-u);
            if (!c1.equals(0) && c1.equals(c2)) {
                return false;
            }
        }
        return true;
    }

    public static void main(String[] args) throws IOException {
        if (args.length != 1) {
            System.exit(1);
        }
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(args[0])))) {
            String line = reader.readLine();
            Integer num = Integer.valueOf(line);
            List<Clause> clauses = new ArrayList<>();
            for (int i = 0; i < num; i++) {
                String s = reader.readLine();
                String[] literals = s.split(" ");
                int i1 = Integer.parseInt(literals[0]);
                int i2 = Integer.parseInt(literals[1]);
                clauses.add(new Clause(i1, i2));
            }
            Sat2 sat2 = new Sat2(clauses);
            System.out.println(sat2.solvable());
        }
    }
}
