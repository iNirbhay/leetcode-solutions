import java.util.*;

class Solution {
    public List<Boolean> kidsWithCandies(int[] candies, int extraCandies) {

        int max = candies[0];

        for(int i = 0; i < candies.length; i++) {
            if(candies[i] > max) {
                max = candies[i];
            }
        }

        List<Boolean> ans = new ArrayList<>();

        for(int i = 0; i < candies.length; i++) {
            int sum = candies[i] + extraCandies;
            if(sum >= max) {
                ans.add(true);
            }
            else {
                ans.add(false);
            }
        }

        return ans;
    }
}