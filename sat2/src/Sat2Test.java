import org.junit.Test;

import java.util.Arrays;

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

public class Sat2Test {
    @Test
    public void always_true() {
        Clause c = new Clause(1, -1);
        Sat2 sat2 = new Sat2(Arrays.asList(c));
        boolean solvable = sat2.solvable();
        assertTrue(solvable);
    }

    @Test
    public void no_assignment() {
        Clause c1 = new Clause(1, 2);
        Clause c2 = new Clause(-1, 3);
        Clause c3 = new Clause(-2, 3);
        Clause c4 = new Clause(-3, -3);
        Sat2 sat2 = new Sat2(Arrays.asList(c1, c2, c3, c4));
        boolean solvable = sat2.solvable();
        assertFalse(solvable);
    }
}
