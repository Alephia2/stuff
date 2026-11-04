class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string common = "";
int y = 0;

while (true) {
    if (y >= strs[0].length()) break;
    
    char currentChar = strs[0][y];

    
    for (int i = 1; i < strs.size(); i++) {
        if (y >= strs[i].length() || strs[i][y] != currentChar) {
            return common;
        }
    }

    common.push_back(currentChar);
    y++;
}

return common;
    }
        };