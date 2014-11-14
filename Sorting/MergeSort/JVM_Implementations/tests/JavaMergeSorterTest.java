import org.junit.Test;

import java.util.ArrayList;
import java.util.Arrays;

public class JavaMergeSorterTest {

    @Test
    public void testNullArraySort() throws Exception {
        new JavaMergeSorter().sort(null, null);
    }

    @Test
    public void testEmptyArraySort() throws Exception {
        new JavaMergeSorter().sort(new ArrayList<>(Arrays.asList(new Integer[]{})), null);
    }

    @Test
    public void testIntegerSort() throws Exception {
        ArrayList<Integer> arr;
        MergeSorter.Comparator<Integer> intComparator = (a,b) -> a-b;

        MergeSorter mergeSorter = new JavaMergeSorter();

        arr =  new ArrayList<>(Arrays.asList(new Integer[]{1,2,3}));
        mergeSorter.sort(arr, intComparator);
        for (int i = 1; i < arr.size(); ++i) {
            assert arr.get(i-1) < arr.get(i);
        }

        arr =  new ArrayList<>(Arrays.asList(new Integer[]{3,2,1}));
        mergeSorter.sort(arr, intComparator);
        for (int i = 1; i < arr.size(); ++i) {
            assert arr.get(i-1) < arr.get(i);
        }
    }

    @Test
    public void testStringSort() throws Exception {
        ArrayList<String> arr;
        MergeSorter.Comparator<String> strComparator = (a,b) -> a.compareTo(b);

        MergeSorter mergeSorter = new JavaMergeSorter();

        arr =  new ArrayList<>(Arrays.asList(new String[]{"Curly", "Larry", "Moe"}));
        mergeSorter.sort(arr, strComparator);
        for (int i = 1; i < arr.size(); ++i) {
            assert arr.get(i-1).compareTo(arr.get(i)) < 0;
        }

        arr =  new ArrayList<>(Arrays.asList(new String[]{"Moe", "Larry", "Curly"}));
        mergeSorter.sort(arr, strComparator);
        for (int i = 1; i < arr.size(); ++i) {
            assert arr.get(i-1).compareTo(arr.get(i)) < 0;
        }

        arr =  new ArrayList<>(Arrays.asList(new String[]{"Darryl", "Darryl", "Larry"}));
        mergeSorter.sort(arr, strComparator);
        for (int i = 1; i < arr.size(); ++i) {
            assert arr.get(i-1).compareTo(arr.get(i)) <= 0;
        }
    }
}