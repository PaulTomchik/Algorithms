import java.util.Comparator;

public class Heapsort {

    public static <T extends Comparable<T>> void sort (T array[]) {
        sort(array, T::compareTo);
    }

    public static <T> void sort (T array[], Comparator<T> comparator) {

        T temp;

        MaxHeapBuilder.toMaxHeap(array, array.length, comparator);

        for (int i = array.length-1; i > 0; --i) {
            temp = array[i];
            array[i] = array[0];
            array[0] = temp;

            MaxHeapBuilder.fixBrokenHeap(array, 0, i, comparator);
        }
    }
}
