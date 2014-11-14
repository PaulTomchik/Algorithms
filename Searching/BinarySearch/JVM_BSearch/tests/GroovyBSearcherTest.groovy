class GroovyBSearcherTest extends GroovyTestCase {
    void testGroovySearch() {
        def arr = [0,1,2,3,4];
        def strings = ["George", "John", "Paul", "Ringo"]

        assert Groovy_BSearcher.search(0, null, null) == -1
        assert Groovy_BSearcher.search(0, [], null) == -1

        def comparator = {x,y -> x - y}
        assert Groovy_BSearcher.search(0, arr, comparator) == 0
        assert Groovy_BSearcher.search(2, arr, comparator) == 2
        assert Groovy_BSearcher.search(4, arr, comparator) == 4
        assert Groovy_BSearcher.search(-2, arr, comparator) == -1


        comparator = {a,b -> a.compareTo(b)}
        assert Groovy_BSearcher.search("George", strings, comparator) == 0
        assert Groovy_BSearcher.search("Paul", strings, comparator) == 2
        assert Groovy_BSearcher.search("Ringo", strings, comparator) == 3
        assert Groovy_BSearcher.search("Yoko", strings, comparator) == -1
    }
}
