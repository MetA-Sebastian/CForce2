# CForce2
Fast multithreaded bruteforce tool that can use words instead of chars!

#### Compile CForce
<code>g++ main.cpp -o cforce -std=c++11 -pthread</code>

#### Usage

##### Default
<code>
./cforce -d 
</code>

##### Custom Charset

On of the key features of cforce is its ability to bruteforce using words instead of just chars. 

e.g.
if you specified "2016" in your list cforce will bruteforce with all chars and 2016
<code>
a<br />
b<br />
2016<br />
aa<br />
ab<br />
a2016<br />
aaa<br />
aab<br />
aa2016<br />
aba<br />
</code>

to use words you have to create a file with one word/line and use
<code>./cforce -c /path/to/wordlist</code
