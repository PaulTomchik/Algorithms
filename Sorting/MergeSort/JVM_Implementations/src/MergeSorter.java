import java.util.ArrayList;

public interface MergeSorter {
    public interface Comparator<T> {
        int compare(T a, T b);
    }

    public <T> void sort(ArrayList<T> arr, Comparator<T> comparator);
}
