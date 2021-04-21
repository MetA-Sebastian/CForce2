# CForce
Designed to aid in targeted brute force password cracking attacks.       
Use information that is known about a password to significantly (exponentially) reduce the time it takes to crack the password.


Fast multithreaded bruteforce tool that can use words instead of chars!

#### Compile CForce
<code>g++ main.cpp -o cforce -std=c++11 -pthread</code>

#### Usage

###### Options

    -t <value>\tNumber of threads to use
    -b <value>\tNumber of values stored in each thread (Buffer)
    -max <value>\tMaximum password length to try
    -min <value>\tMinimum password length to try
    -c <file>\tAdd words from file to use in bruteforce (like chars)
    -d\tRun with default values: 4 threads, 2000000 buffer size, 0-5 chars

###### Examples:
<code>
    ./cforce -t 4 -b 2000000 -min 5 -max 6 | ./john -stdin -format=NT hashlist.txt
</code>    
    Trys all 5-6 chars long passwords using 4 threads and a buffer size of 2000000 and pipes the output to John    


###### How it works

The key features of cforce is its ability to bruteforce using words instead of just chars.  
E.g.:    
If you suspect the target to use the current year anywhere in the password you can add it to be used as a char. If the assumption is correct, the 4 char long year (e.g. 2016) will be used as a single char, therefor reducing the password length by 3. Thus the password can be cracked significantly faster if some parts of the password are known even if the erxact position is unknown.

e.g.
if you specified "2016" in your list cforce will bruteforce with all chars and 2016   
a   
b   
2016   
aa   
ab   
a2016   
aaa   
aab   
aa2016   
aba     

to use words you have to create a file with one word/line and use
<code>./cforce -c /path/to/wordlist</code>
