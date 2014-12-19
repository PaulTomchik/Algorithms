import java.util.ArrayList;

public class MatrixChainMultiplication {

    public static int MatrixChainOrder(int[] dimensionSeq, ArrayList<Integer> solution) {
        int n = dimensionSeq.length - 1;
        int[] table = new int[n*n];

        solution.ensureCapacity(n);

        //FIXME: INDEXING IS OFF
        for (int len = 2; len < n; ++len) {
            for (int i = 1; i < (n - len + 1); ++i) {

                int j = i + len - 1;

                table[(i/n) + j-1] = Integer.MAX_VALUE;

                for (int k = i; k < j; ++j) {
                    int q = table[i/n + k-1]

                }
            }
        }

    }
}
