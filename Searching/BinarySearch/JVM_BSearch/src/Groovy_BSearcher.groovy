class Groovy_BSearcher {
    public static int search(def val, def arr, Closure comparator) {
        if (arr == null || arr.size() == 0) return -1

        int left = 0
        int right = arr.size() - 1
        int p, comp

        while (left <= right) {
            p = (int)Math.ceil((right - left)/2) + left
            comp = comparator(arr[p], val)

            if (comp == 0) {
                return p
            } else if (comp > 0) {
                right = p-1
            } else {
               left = p+1
            }
        }
       return -1
    }
}
