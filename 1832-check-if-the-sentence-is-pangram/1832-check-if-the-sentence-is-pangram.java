class Solution {
    public boolean checkIfPangram(String sentence) {
        boolean[] seen = new boolean[26];

        for(int i = 0; i < sentence.length(); i++) {
            int index = sentence.charAt(i) - 'a';
            seen[index] = true;
        }
        
        for(int i = 0; i < 26; i++) {
            if(!seen[i]) {
                return false;
            }
        }
        return true;
    }
}