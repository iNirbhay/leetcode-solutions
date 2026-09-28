class Solution {
public:

    vector<int> ans;
    vector<pair<int,int>> arr;

    void mergeSort(int left, int right) {

        if (left >= right)
            return;

        int mid =
            left + (right - left) / 2;

        mergeSort(left, mid);
        mergeSort(mid + 1, right);

        vector<pair<int,int>> temp;

        int i = left;
        int j = mid + 1;

        while (i <= mid && j <= right) {

            if (arr[i].first <= arr[j].first) {

                ans[arr[i].second] +=
                    j - mid - 1;

                temp.push_back(arr[i++]);
            }
            else {

                temp.push_back(arr[j++]);
            }
        }

        while (i <= mid) {

            ans[arr[i].second] +=
                j - mid - 1;

            temp.push_back(arr[i++]);
        }

        while (j <= right)
            temp.push_back(arr[j++]);

        for (int k = 0; k < temp.size(); k++)
            arr[left + k] = temp[k];
    }

    vector<int> countSmaller(vector<int>& nums) {

        int n = nums.size();

        ans.assign(n, 0);

        for (int i = 0; i < n; i++)
            arr.push_back({nums[i], i});

        mergeSort(0, n - 1);

        return ans;
    }
};