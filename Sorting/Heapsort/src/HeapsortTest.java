import java.util.UUID;


public class HeapsortTest {

    @org.junit.Test
    public void testSortWithDoubles() throws Exception {
        Double arr[] = new Double[1000];
        int numberOfTrials = 100;

        for (int i=0; i < numberOfTrials; ++i) {
            for (int j=0; j < 1000; ++j) arr[j] = Math.random() * 1000;

            Heapsort.sort(arr);

            for (int j=1; j < 1000; ++j) { assert arr[j-1] <= arr[j]; }
        }
    }

    @org.junit.Test
    public void testSortWithRecords() throws Exception {

        class Record {
            String lName;
            double salary;

            Record(String lName) {
                this.lName = lName;
                salary = 250000 * Math.random();
            }
        }

        Record recs[] = new Record[1000];
        String str;

        for (int i=0; i < 1000; ++i) {
            str = UUID.randomUUID().toString();
            recs[i] = new Record(str.substring(0, (int) (Math.random() * str.length() + 1)) );
        }

        Heapsort.sort(recs, (rec1, rec2) -> rec1.lName.compareTo(rec2.lName));

        for (int j=1; j < 1000; ++j) { assert recs[j-1].lName.compareTo(recs[j].lName) <= 0; }

    }
}