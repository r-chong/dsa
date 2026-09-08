class Solution {
public:
    int getSum(int a, int b) {
        int sum = a;
        int carry = b;

        while (carry != 0) {
            // if any of a,b values are xor'able (0,1 or 1,0) then we just put 1 there
            int newSum = sum ^ carry;

            // if any of a,b values are (1,1) then we do carry which is actually a left shift
            int newCarry = (sum & carry) << 1;

            sum = newSum;
            carry = newCarry;
        }

        return sum;
    }
};