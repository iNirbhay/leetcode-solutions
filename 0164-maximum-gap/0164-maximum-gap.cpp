class Solution {
public:
    int maximumGap(vector<int>& nums) {

        int n = nums.size();

        if (n < 2)
            return 0;

        int mn = *min_element(nums.begin(), nums.end());
        int mx = *max_element(nums.begin(), nums.end());

        if (mn == mx)
            return 0;

        int bucketSize =
            max(1, (mx - mn) / (n - 1));

        int bucketCount =
            (mx - mn) / bucketSize + 1;

        vector<int> bucketMin(
            bucketCount,
            INT_MAX
        );

        vector<int> bucketMax(
            bucketCount,
            INT_MIN
        );

        vector<bool> used(bucketCount, false);

        for (int num : nums) {

            int index =
                (num - mn) / bucketSize;

            bucketMin[index] =
                min(bucketMin[index], num);

            bucketMax[index] =
                max(bucketMax[index], num);

            used[index] = true;
        }

        int answer = 0;
        int previous = mn;

        for (int i = 0; i < bucketCount; i++) {

            if (!used[i])
                continue;

            answer =
                max(answer,
                    bucketMin[i] - previous);

            previous = bucketMax[i];
        }

        return answer;
    }
};