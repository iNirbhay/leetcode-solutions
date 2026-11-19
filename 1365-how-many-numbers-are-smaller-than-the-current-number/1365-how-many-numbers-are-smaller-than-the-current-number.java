class Solution {
    public int[] smallerNumbersThanCurrent(int[] nums) {
        int[] ans = new int[nums.length];
        int count = 0;
        for (int i = 0; i < nums.length; i++) {
            for(int n = 0; n < nums.length; n++) {
                if (nums[i] > nums[n] && n!=i) {
                    count++;
                    ans[i] += count;
                }
                count = 0;
            }
        }
        return ans;
    }
}