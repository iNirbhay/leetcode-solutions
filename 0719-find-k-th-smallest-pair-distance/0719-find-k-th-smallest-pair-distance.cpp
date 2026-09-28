class Solution {
public:

    int countPairs(
        vector<int>& nums,
        int distance) {

        int left = 0;
        int count = 0;

        for (int right = 0;
             right < nums.size();
             right++) {

            while (
                nums[right] - nums[left]
                > distance
            ) {
                left++;
            }

            count += right - left;
        }

        return count;
    }

    int smallestDistancePair(
        vector<int>& nums,
        int k) {

        sort(nums.begin(), nums.end());

        int left = 0;

        int right =
            nums.back() - nums.front();

        while (left < right) {

            int mid =
                left + (right - left) / 2;

            if (countPairs(nums, mid) >= k)
                right = mid;
            else
                left = mid + 1;
        }

        return left;
    }
};