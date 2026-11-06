class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int size = strs.size();
        string common = "";
        int y = 0;
        bool keepgoing = true;;

        do {
            if (y >= strs[0].length()) {
                return common;
            }

        char current = strs[0][y];
        
        for (int i = 1 ; i < size ; i++) {
            if (y  >= strs[i].length() || strs[i][y] != current) {
                return common;
                keepgoing = false;
            }
        }                   

        common.push_back(current);
        y++;
        } while (keepgoing);
        return common;
    }
};