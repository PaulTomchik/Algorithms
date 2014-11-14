/**
 * Created by paul on 9/10/14.
 */
class GroovyMergeSorter implements MergeSorter {

    public void sort (ArrayList arr, MergeSorter.Comparator comparator) {
        if (arr == null || arr.size() < 2) return;

        sorter(arr, 0, arr.size()-1, comparator)
    }

    /**
     * @param arr: arraylist to sort
     * @param p: base of the left partition to merge
     * @param q: end of the left partition (inclusive)
     * @param r: end of the right partition
     * @param comparator: lambda that compares the arraylist elements
     *
     * NOTE: No null checks within method. Assumed to have been done by the public method.
     *
     */
    private static void sorter (arr, p, q, comparator) {
        if (q == p) return

        int m = ((q - p)/2) + p

        sorter(arr, p, m, comparator)
        sorter(arr, m+1, q, comparator)
        merge(arr, p, m, q, comparator)
    }


    /**
     *
     * @param arr: arraylist to sort
     * @param p: base of the left partition to merge
     * @param q: end of the left partition (inclusive)
     * @param r: end of the right partition
     * @param comparator: lambda that compares the arraylist elements
     *
     * NOTE: No null checks within method. Assumed to have been done by the public method.
     *
     */
    private static void merge (arr, p, q, r, comparator) {

        ArrayList left = arr[p..q]
        ArrayList right = arr[(q+1)..r]

        int i = 0;
        int j = 0;

        for (def k = p; k < r+1; ++k) {
            if (i == left.size()) {
                arr[k] = right[j++]
            } else if (j == right.size()) {
                arr[k] = left[i++]
            } else if (comparator.compare(left[i], right[j]) <= 0) {
                arr[k] = left[i++]
            } else {
                arr[k] = right[j++]
            }
        }
    }
}
