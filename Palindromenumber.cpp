class Solution {
public:
    bool isPalindrome(int x) {
       int current = x;
       int countd = 0;
       int digits = 0;

        do {
            current = current / 10;
            digits += 1;
        } while (current != 0);

    
        int arr[digits];
        current = x;

       if ( x < 0 ) {
        return false;
       } else if (x == 0){
        return true;
       } 
        else { 

        for (int i = 0 ; i < digits ; i++ ) {
            arr[i]  = current % 10;
            current = current / 10;
        }

        for (int i = 0 ; i < digits ; i++){
            if (*(arr + i) != *(arr + digits - i - 1)){
                return false;
            }
        }
    
    return true;    
    }
}
};