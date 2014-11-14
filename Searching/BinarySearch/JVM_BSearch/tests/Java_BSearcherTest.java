import org.junit.Test;

public class Java_BSearcherTest {

    @Test
    public void testSearch() throws Exception {
        Integer[] arr = {0,1,2,3,4};
        String[] strings = {"George", "John", "Paul", "Ringo"};

        assert Java_BSearcher.search(0, null, null) == -1;
        assert Java_BSearcher.search(0, new Integer[0], null) == -1;

        Java_BSearcher.Comparator <Integer>integerComparator = (a,b) -> a - b;
        assert Java_BSearcher.search(0, arr, integerComparator) == 0;
        assert Java_BSearcher.search(2, arr, integerComparator) == 2;
        assert Java_BSearcher.search(4, arr, integerComparator) == 4;
        assert Java_BSearcher.search(5, arr, integerComparator) == -1;

        Java_BSearcher.Comparator <String> stringComparator = (a,b) -> a.compareTo(b);
        assert Java_BSearcher.search("George", strings, stringComparator) == 0;
        assert Java_BSearcher.search("Paul", strings, stringComparator) == 2;
        assert Java_BSearcher.search("Ringo", strings, stringComparator) == 3;
        assert Java_BSearcher.search("Yoko", strings, stringComparator) == -1;
    }
}