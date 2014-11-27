import java.util.Arrays;

public class RadixSortTest {
  
  static final int ARRSZ = 100000000;
  static final int NUM_TRIALS = 5;

  public static void main (String args[]) {

    int array[] = new int[ARRSZ];
    long startTime, endTime;
    long javaTotalTime = 0;
    long nativeTotalTime = 0;

    for (int t=0; t < NUM_TRIALS; ++t) {
    
      System.out.println("Trial: " + t);

      for (int i=0; i < array.length; ++i) { array[i] = (int)(Math.random() * 100000); }

      System.out.print("Java sort.... ");
      startTime = System.nanoTime();
      Arrays.sort(array);
      endTime = System.nanoTime();
      javaTotalTime += endTime - startTime;
      System.out.println("done. Time: " + (endTime - startTime)/100000);

      for (int i=0; i < array.length; ++i) { array[i] = (int)(Math.random() * 100000); }

      System.out.print("Native sort.... ");
      startTime = System.nanoTime();
      RadixSorter.sort(array);
      endTime = System.nanoTime();
      System.out.println("done. Time: " + (endTime - startTime)/100000);

      for (int i=1; i < array.length; ++i) { assert array[i-1] <= array[i]; }
      nativeTotalTime += endTime - startTime;
    }

    System.out.println("Average  Java  time: " + (javaTotalTime/NUM_TRIALS)/1000000 + "ms.");
    System.out.println("Average Native time: " + (nativeTotalTime/NUM_TRIALS)/1000000 + "ms.");
  }
}
