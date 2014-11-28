import java.util.Comparator;

public class MaxHeapBuilder {


    public static <T extends Comparable<T>> void toMaxHeap(T arr[], int heapSize) {
      toMaxHeap(arr, heapSize, T::compareTo);
    }

    public static <T> void toMaxHeap (T arr[], int heapSize, Comparator<T> comparator) {
        for (int i = (heapSize/2)-1; i >= 0; --i) {
            fixBrokenHeap(arr, i, heapSize, comparator);
        }
    }

    public static <T extends Comparable<T>> void fixBrokenHeap (T array[], int index, int heapSize) {
        fixBrokenHeap(array, index, heapSize, T::compareTo);
    }

    public static <T> void fixBrokenHeap (T array[], int index, int heapSize, Comparator<T> comparator) {

        int leftChildIndex;
        int rightChildIndex;
        int largest = index;

        for (;;) {
            leftChildIndex  = ((index + 1) * 2) - 1;
            rightChildIndex = (index + 1) * 2;

            if ( (leftChildIndex < heapSize) && (comparator.compare(array[index], array[leftChildIndex]) < 0)) {
                largest = leftChildIndex;
            }

            if ( (rightChildIndex < heapSize) && (comparator.compare(array[largest], array[rightChildIndex]) < 0)) {
                largest = rightChildIndex;
            }

            if (largest != index) {
                T temp = array[index];
                array[index] = array[largest];
                array[largest] = temp;
                index = largest;
            } 
            else break;
        }
    }
}
