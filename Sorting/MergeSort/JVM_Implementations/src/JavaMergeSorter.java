import java.util.ArrayList;

public class JavaMergeSorter implements MergeSorter {

    public <T> void sort (ArrayList<T> arr, Comparator<T> comparator) {
        if (arr == null || arr.size() < 2) return;

        sort(arr, 0, arr.size(), comparator);
    }

    /**
     * @param arr: array to sort
     * @param p: base index
     * @param r: end of array (non-inclusive)
     * @param comparator: comparator for elems
     * @param <T>: Type of elems
     */
    private <T> void sort (ArrayList<T> arr, int p, int r, Comparator<T> comparator) {
        if ((r - p) < 2) return;

        int q = ((r - p)/2) + p;

        sort(arr, p, q, comparator);
        sort(arr, q, r, comparator);
        merge(arr, p, q, r, comparator);
    }

    /**
     *
     * @param arr: array to sort
     * @param p: base index
     * @param q: the end of the first partition to merge (Non-inclusive)
     * @param r: end of array (non-inclusive)
     * @param comparator: comparator for elems
     * @param <T>: Type of elems
     */
    private <T> void merge (ArrayList<T> arr, int p, int q, int r, Comparator<T> comparator) {
        ArrayList<T> left = new ArrayList<>(arr.subList(p,q));
        ArrayList<T> right = new ArrayList<>(arr.subList(q,r));

        int i = 0;
        int j = 0;

        for (int k = p; k < r; ++k) {
            if (i == left.size()) {
                while(k < r)  arr.set(k++, right.get(j++));
                return;
            } else if (j == right.size()) {
                arr.set(k, left.get(i++));
            } else if (comparator.compare(left.get(i), right.get(j)) <= 0) {
                arr.set(k, left.get(i++));
            } else {
                arr.set(k, right.get(j++));
            }
        }
    }
}
