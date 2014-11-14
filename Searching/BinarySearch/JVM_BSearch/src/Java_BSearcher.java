public class Java_BSearcher {

    public interface Comparator<T> {
        public int compare (T arg1, T arg2);
    }

    public static <T> int search (T val, T arr[], Comparator<T> comparator) {
        if (arr == null || arr.length == 0) return -1;

        int left = 0;
        int right = arr.length - 1;

        int ptr, comp;

        while (left <= right) {
            ptr = (int)Math.ceil((right - left) / 2) + left;
            comp = comparator.compare(arr[ptr], val);

            if (comp == 0) {
                return ptr;
            } else if (comp > 0) {
                right = ptr - 1;
            } else {
                left = ptr + 1;
            }
        }
       return -1;
    }
}

