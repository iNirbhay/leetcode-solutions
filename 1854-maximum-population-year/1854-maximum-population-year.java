
class Solution {
    public int maximumPopulation(int[][] logs) {

        int[] population = new int[101];

        for (int i = 0; i < logs.length; i++) {

            int birth = logs[i][0];
            int death = logs[i][1];

            for (int year = birth; year < death; year++) {
                population[year - 1950]++;
            }
        }

        int max = 0;
        int ans = 1950;

        for (int i = 0; i < 101; i++) {

            if (population[i] > max) {
                max = population[i];
                ans = i + 1950;
            }
        }

        return ans;
    }
}
