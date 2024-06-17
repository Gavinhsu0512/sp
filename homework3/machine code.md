1: #include <stdio.h>       
2: 
3: int power(int a, int n) {
4:     if (n == 0) {        
    ENT  0
    LLA  2
    LI  
    PSH 
    IMM  0
    EQ  
    BZ   0
5:         return 1;        
    IMM  1
    LEV
6:     } else if (n < 0) {
    JMP  0
    LLA  2
    LI
    PSH
    IMM  0
    LT
    BZ   0
7:         return 1 / power(a, -n);
    IMM  1
    PSH
    LLA  3
    LI
    PSH
    IMM  -1
    PSH
    LLA  2
    LI
    MUL
    PSH
    JSR  -272891752
    ADJ  2
    DIV
    LEV
8:     } else {
    JMP  0
9:         return a * power(a, n - 1);
    LLA  3
    LI
    PSH
    LLA  3
    LI
    PSH
    LLA  2
    LI
    PSH
    IMM  1
    SUB
    PSH
    JSR  -272891752
    ADJ  2
    MUL
    LEV
10:     }
11: }
    LEV
12:
13: int main() {
14:   printf("power(2,31)=%d\n", power(2,31));
    ENT  0
    IMM  -272629600
    PSH
    IMM  2
    PSH
    IMM  31
    PSH
    JSR  -272891752
    ADJ  2
    PSH
    PRTF
    ADJ  2
15:   return 0;
    IMM  0
    LEV
16: }
    LEV