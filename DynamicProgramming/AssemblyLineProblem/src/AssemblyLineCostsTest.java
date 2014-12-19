import java.util.ArrayList;

public class AssemblyLineCostsTest {

    @org.junit.Test
    public void testSolveAssemblyLineProblem() throws Exception {
        ArrayList<Integer> solution = new ArrayList<Integer>();

        AssemblyLineCosts.CostPair enter;
        AssemblyLineCosts.CostPair[] stations  = new AssemblyLineCosts.CostPair[6];
        AssemblyLineCosts.CostPair[] transfers = new AssemblyLineCosts.CostPair[5];
        AssemblyLineCosts.CostPair exit;

        enter = new AssemblyLineCosts.CostPair(2, 4);

        stations[0] = new AssemblyLineCosts.CostPair(7,8);
        stations[1] = new AssemblyLineCosts.CostPair(9,5);
        stations[2] = new AssemblyLineCosts.CostPair(3,6);
        stations[3] = new AssemblyLineCosts.CostPair(4,4);
        stations[4] = new AssemblyLineCosts.CostPair(8,5);
        stations[5] = new AssemblyLineCosts.CostPair(4,7);

        transfers[0] = new AssemblyLineCosts.CostPair(2,2);
        transfers[1] = new AssemblyLineCosts.CostPair(3,1);
        transfers[2] = new AssemblyLineCosts.CostPair(1,2);
        transfers[3] = new AssemblyLineCosts.CostPair(3,2);
        transfers[4] = new AssemblyLineCosts.CostPair(4,1);

        exit = new AssemblyLineCosts.CostPair(3,2);

//        System.out.println(AssemblyLineCosts.solveAssemblyLineProblem(stations, transfers, enter, exit, solution));
//        System.out.println(solution);
        assert(AssemblyLineCosts.solveAssemblyLineProblem(stations, transfers, enter, exit) == 38);
    }
}