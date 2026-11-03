class Solution {
public:
    int romanToInt(string s) {
        int length = s.length() - 1;
        int integre = 0;
        int previous = 0;
        
for (int i = length ; i >= 0 ; i--) {
        int current = 0;
                if (s[i] == 'I') {
                    current = 1;
                } else if (s[i] == 'V'){
                    current = 5;
                } else if (s[i] == 'X'){
                    current = 10;
                }else if (s[i] == 'L'){
                    current = 50;
                }else if (s[i] == 'C'){
                    current = 100;
                }else if (s[i] == 'D'){
                    current = 500;
                }else if (s[i] == 'M'){
                    current = 1000;
                }

        if (current < previous){
                integre -= current;
        } else {
                integre += current;
        }
            
    
    
previous = current;

}
return integre;
            }
       
};