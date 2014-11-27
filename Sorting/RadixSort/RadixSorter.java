public class RadixSorter {

  static {
    System.load(System.getProperty("user.dir") + "/RadixSort.so");
  }

  /**
   *  ASSUMES: Non-negative integers.
   *           Large N.
   *
   */
  public static native void sort(int arr[]);

}
