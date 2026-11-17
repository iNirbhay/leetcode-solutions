class Solution {
    public int[] runningSum(int[] nums) {
        int[] sum = new int[nums.length];

        for (int i = 0; i < nums.length; i++) {
            sum[i] = nums[i];

            if (i > 0) {
                sum[i] += sum[i-1];
            }
        }
        return sum;
    }
}