
import java.util.*;

class Solution {
    public int smallestUniqueSubarray(int[] nums) {
        int n = nums.length;

        if (n == 1) return 1;

        int[] sorted = nums.clone();
        Arrays.sort(sorted);

        int[] s = new int[n + 1];
        int rank = 0;

        for (int i = 0; i < n; i++) {
            if (i == 0 || sorted[i] != sorted[i - 1]) {
                rank++;
            }
        }

        for (int i = 0; i < n; i++) {
            s[i] = Arrays.binarySearch(sorted, nums[i]) + 1;
        }
        s[n] = 0;

        int N = n + 1;
        int[] sa = new int[N];
        int[] c = new int[N];
        int[] pn = new int[N];
        int[] cn = new int[N];

        int alphabet = Math.max(N, rank + 1);
        int[] cnt = new int[alphabet];

        for (int x : s) cnt[x]++;
        for (int i = 1; i < alphabet; i++) {
            cnt[i] += cnt[i - 1];
        }

        for (int i = N - 1; i >= 0; i--) {
            sa[--cnt[s[i]]] = i;
        }

        c[sa[0]] = 0;
        int classes = 1;

        for (int i = 1; i < N; i++) {
            if (s[sa[i]] != s[sa[i - 1]]) classes++;
            c[sa[i]] = classes - 1;
        }

        for (int len = 1; len < N; len <<= 1) {
            for (int i = 0; i < N; i++) {
                pn[i] = sa[i] - len;
                if (pn[i] < 0) pn[i] += N;
            }

            Arrays.fill(cnt, 0, classes, 0);

            for (int x : pn) cnt[c[x]]++;
            for (int i = 1; i < classes; i++) {
                cnt[i] += cnt[i - 1];
            }

            for (int i = N - 1; i >= 0; i--) {
                int x = pn[i];
                sa[--cnt[c[x]]] = x;
            }

            cn[sa[0]] = 0;
            int newClasses = 1;

            for (int i = 1; i < N; i++) {
                int cur = sa[i];
                int prev = sa[i - 1];

                if (c[cur] != c[prev] ||
                    c[(cur + len) % N] != c[(prev + len) % N]) {
                    newClasses++;
                }

                cn[cur] = newClasses - 1;
            }

            int[] temp = c;
            c = cn;
            cn = temp;
            classes = newClasses;

            if (classes == N) break;
            if (len > N / 2) break;
        }

        int[] suffixArray = new int[n];
        for (int i = 0; i < n; i++) {
            suffixArray[i] = sa[i + 1];
        }

        int[] lcp = new int[n];
        int[] pos = new int[n];

        for (int i = 0; i < n; i++) {
            pos[suffixArray[i]] = i;
        }

        int k = 0;

        for (int i = 0; i < n; i++) {
            int r = pos[i];

            if (r == 0) continue;

            int j = suffixArray[r - 1];

            while (i + k < n && j + k < n &&
                   nums[i + k] == nums[j + k]) {
                k++;
            }

            lcp[r] = k;

            if (k > 0) k--;
        }

        int ans = n;

        for (int i = 0; i < n; i++) {
            int maxLCP = lcp[i];

            if (i + 1 < n) {
                maxLCP = Math.max(maxLCP, lcp[i + 1]);
            }

            int required = maxLCP + 1;
            int start = suffixArray[i];

            if (required <= n - start) {
                ans = Math.min(ans, required);
            }
        }

        return ans;
    }
}
