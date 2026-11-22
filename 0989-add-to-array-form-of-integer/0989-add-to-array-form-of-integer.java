import java.util.*;

class Solution {
    public List<Integer> addToArrayForm(int[] num, int k) {

        List<Integer> ans = new ArrayList<>();

        int i = num.length - 1;
        int carry = 0;

        while(i >= 0 || k > 0 || carry > 0) {

            int sum = carry;

            if(i >= 0) {
                sum += num[i];
            }

            sum += k % 10;

            ans.add(sum % 10);

            carry = sum / 10;

            k /= 10;
            i--;
        }

        Collections.reverse(ans);

        return ans;
    }
}