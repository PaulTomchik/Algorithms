import java.security.InvalidParameterException;
import java.util.ArrayList;

public class AssemblyLineCosts {
  static class CostPair {
     private double top;
     private double bottom;

    public CostPair (double topCost, double bottomCost) {
      this.top = topCost;
      this.bottom = bottomCost;
    }

    public double getTopCost() {
      return top;
    }

    public double getBottomCost() {
      return bottom;
    }
  }

  public static double solveAssemblyLineProblem ( CostPair stations[],
                                                  CostPair transfers[],
                                                  CostPair enter,
                                                  CostPair exit,
                                                  ArrayList<Integer> solution)
  {
    ArrayList<Integer> topSolution    = new ArrayList<Integer>();
    ArrayList<Integer> bottomSolution = new ArrayList<Integer>();

    if ((stations == null) || (transfers == null) || (enter == null) || (exit == null)) {
      throw new InvalidParameterException("Null argument passed.");
    }

    if (stations.length != (transfers.length + 1)) {
      throw new InvalidParameterException("Inconsistent numbers for stations and transfers.");
    }

    double topBest = enter.getTopCost();
    double bottomBest = enter.getBottomCost();

    double tempBest;

    if (stations.length > 0) {
      topBest += stations[0].getTopCost();
      topSolution.add(0);

      bottomBest += stations[0].getBottomCost();
      bottomSolution.add(1);

      for (int i=1; i < stations.length; ++i) {
        tempBest = bottomBest + transfers[i-1].getBottomCost();
        if ( topBest > tempBest ) {
          topBest = tempBest;
          topSolution.add(1);
        } else {
          topSolution.add(0);
        }

        tempBest = topBest + transfers[i-1].getTopCost();
        if ( bottomBest > tempBest ) {
          bottomBest = tempBest;
          bottomSolution.add(0);
        } else {
          bottomSolution.add(1);
        }

        topBest    += stations[i].getTopCost();
        bottomBest += stations[i].getBottomCost();
      }
    }

    topBest    += exit.getTopCost();
    bottomBest += exit.getBottomCost();

    if (solution != null) {
      if (topBest < bottomBest) {
        solution.addAll(topSolution);
      } else {
        solution.addAll(bottomSolution);
      }
    }

    return Math.min(topBest, bottomBest);
  }
}

