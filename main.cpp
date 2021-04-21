#include <iostream>
#include <thread>
#include <mutex>
#include <math.h>
#include <vector>
#include <stdio.h>
#include <string>
#include <climits>
#include <stdlib.h>
#include <fstream>

using namespace std;

std::mutex g_lock;


int bufferLength{2000000},
        threadcount{4},
        minLength{1},
        maxlength{5};

void threading(int start, vector<string> charlist) {


    //array buffer
    vector<string> finalguess(bufferLength);

    //array chars
    //all chars + words
    vector<string> chars{"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p",
                         "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I",
                         "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "0", "1",
                         "2", "3", "4", "5", "6", "7", "8", "9", "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "-",
                         "_", "+", "=", "~", "`", "[", "]", "{", "}", "|", "\\", ":", ";", "\"", "'", "<", ">", ",",
                         ".", "?", "/", " "};

    for (unsigned long long k = 0; k < charlist.size(); ++k) {
        chars.push_back(charlist[k]);
    }



    int count{0};
    unsigned long long size{chars.size()};

    string guess{""};

    clog << "[+] Thread " << start + 1 << " created!" << endl;
    //j = pw-zeichen anzahl
    for (int j = minLength; j <= maxlength; ++j) {
        //clog << "[*] Thread " << start + 1 << " now guessing " << j << " chars" << endl;

        //Guess:
        for (unsigned long long x = start; x < pow(size, j); x += threadcount) {
            //if buffer array is full:
            if (count >= bufferLength) {
                //lock stdout
                g_lock.lock();
                //print buffer array
                for (int i = 0; i < bufferLength; ++i) {
                    printf("%s\n", finalguess[i].c_str());
                }
                //unlock stdout
                g_lock.unlock();
                count = 0;
            }
            //guess:
            guess = "";
            for (int h = 1; h < j; ++h) {
                guess += chars[(int) (x / pow(size, j - h)) % size];
            }
            guess += chars[x % size];
            //add guess to buffer array
            finalguess[count] = guess;
            count++;
            //}
        }
    }
    //print buffer one more time
    //lock stdout
    g_lock.lock();
    //print buffer array
    for (int i = 0; i < bufferLength; ++i) {
        printf("%s\n", finalguess[i].c_str());
    }
    //unlock stdout
    g_lock.unlock();
}

void help() {
    cerr << endl << "CForce v2.0" << endl;
    cerr << "Written by Sebastian Hirnschall" << endl;
    cerr << "Contact - sebastian.hirnschall@gmail.com" << endl;
    cerr << endl << "Usage: ./cforce <options>" << endl;
    cerr << "Options:" << endl;
    cerr << "\t-t <value>\tNumber of threads to use" << endl;
    cerr << "\t-b <value>\tNumber of values stored in each thread (Buffer)" << endl;
    cerr << "\t-max <value>\tMaximum password length to try" << endl;
    cerr << "\t-min <value>\tMinimum password length to try" << endl;
    cerr << "\t-c <file>\tAdd words from file to use in bruteforce (like chars)" << endl;
    cerr << endl << "\t-d\tRun with default values:\n\t\t4 threads\n\t\t2000000 buffer size\n\t\t0-5 chars" << endl;
    cerr << endl << "Use another program to hash eg. jtr" << endl;
    cerr << endl << "Examples:" << endl;
    cerr << "\t./cforce -t 4 -b 2000000 -min 5 -max 6 | ./john -stdin hashlist.txt" << endl;
    cerr << "\tTrys all 5-6 chars long passwords using 4 threads and a buffer size of 2000000" << endl;
}


int main(int argc, char *argv[]) {


    vector<string> charlist{};
    string line;
    ifstream charfile;

    //commandline arguments
    //-- Menu --//
    if (argc < 2) {
        help();
        return 0;
    }
    for (int i = 1; i < argc; i++) {
        string arg{argv[i]};
        if ((arg == "-t") || (arg == "-T")) {
            i++;
            threadcount = atoi(argv[i]);
        }
        else if ((arg == "-b") || (arg == "-B")) {
            i++;
            bufferLength = atoi(argv[i]);
        }
        else if ((arg == "-max") || (arg == "-Max") || (arg == "-MAX")) {
            i++;
            maxlength = atoi(argv[i]);
        }
        else if ((arg == "-min") || (arg == "-Min") || (arg == "-MIN")) {
            i++;
            minLength = atoi(argv[i]);
        }
        else if ((arg == "-c") || (arg == "-C")) {
            i++;
            charfile.open(argv[i]);
        }
        else if ((arg == "-d") || (arg == "-D")) {
            threadcount = 4;
            bufferLength = 2000000;
            minLength = 1;
            maxlength = 5;
            break;
        }
    }

    while (getline(charfile, line)) {
        if (line != "") {
            charlist.push_back(line);
        }
    }



    //how many threads?
    std::thread t1(threading, 0, charlist);
    if (threadcount >= 2) {
        std::thread t2(threading, 1, charlist);
        if (threadcount >= 3) {
            std::thread t3(threading, 2, charlist);
            if (threadcount >= 4) {
                std::thread t4(threading, 3, charlist);
                if (threadcount >= 5) {
                    std::thread t5(threading, 4, charlist);
                    if (threadcount >= 6) {
                        std::thread t6(threading, 5, charlist);
                        if (threadcount >= 7) {
                            std::thread t7(threading, 6, charlist);
                            if (threadcount >= 8) {
                                std::thread t8(threading, 7, charlist);
                                if (threadcount >= 9) {
                                    std::thread t9(threading, 8, charlist);
                                    if (threadcount >= 10) {
                                        std::thread t10(threading, 9, charlist);
                                        if (threadcount >= 11) {
                                            std::thread t11(threading, 10, charlist);
                                            if (threadcount >= 12) {
                                                std::thread t12(threading, 11, charlist);
                                                if (threadcount >= 13) {
                                                    std::thread t13(threading, 12, charlist);
                                                    if (threadcount >= 14) {
                                                        std::thread t14(threading, 13, charlist);
                                                        if (threadcount >= 15) {
                                                            std::thread t15(threading, 14, charlist);
                                                            if (threadcount >= 16) {
                                                                std::thread t16(threading, 15, charlist);
                                                                if (threadcount >= 17) {
                                                                    std::thread t17(threading, 16, charlist);
                                                                    if (threadcount >= 18) {
                                                                        std::thread t18(threading, 17, charlist);
                                                                        if (threadcount >= 19) {
                                                                            std::thread t19(threading, 18, charlist);
                                                                            if (threadcount >= 20) {
                                                                                std::thread t20(threading, 19,
                                                                                                charlist);
                                                                                if (threadcount >= 21) {
                                                                                    std::thread t21(threading, 20,
                                                                                                    charlist);
                                                                                    if (threadcount >= 22) {
                                                                                        std::thread t22(threading, 21,
                                                                                                        charlist);
                                                                                        if (threadcount >= 23) {
                                                                                            std::thread t23(threading,
                                                                                                            22,
                                                                                                            charlist);
                                                                                            if (threadcount >= 24) {
                                                                                                std::thread t24(
                                                                                                        threading,
                                                                                                        23, charlist);
                                                                                                if (threadcount >= 25) {
                                                                                                    std::thread t25(
                                                                                                            threading,
                                                                                                            24,
                                                                                                            charlist);
                                                                                                    if (threadcount >=
                                                                                                        26) {
                                                                                                        std::thread t26(
                                                                                                                threading,
                                                                                                                25,
                                                                                                                charlist);
                                                                                                        if (threadcount >=
                                                                                                            27) {
                                                                                                            std::thread t27(
                                                                                                                    threading,
                                                                                                                    26,
                                                                                                                    charlist);
                                                                                                            if (threadcount >=
                                                                                                                28) {
                                                                                                                std::thread t28(
                                                                                                                        threading,
                                                                                                                        27,
                                                                                                                        charlist);
                                                                                                                if (threadcount >=
                                                                                                                    29) {
                                                                                                                    std::thread t29(
                                                                                                                            threading,
                                                                                                                            28,
                                                                                                                            charlist);
                                                                                                                    if (threadcount >=
                                                                                                                        30) {
                                                                                                                        std::thread t30(
                                                                                                                                threading,
                                                                                                                                29,
                                                                                                                                charlist);
                                                                                                                        if (threadcount >=
                                                                                                                            31) {
                                                                                                                            std::thread t31(
                                                                                                                                    threading,
                                                                                                                                    30,
                                                                                                                                    charlist);
                                                                                                                            if (threadcount >=
                                                                                                                                32) {
                                                                                                                                std::thread t32(
                                                                                                                                        threading,
                                                                                                                                        31,
                                                                                                                                        charlist);
                                                                                                                                t32.join();
                                                                                                                            }
                                                                                                                            t31.join();
                                                                                                                        }
                                                                                                                        t30.join();
                                                                                                                    }
                                                                                                                    t29.join();
                                                                                                                }
                                                                                                                t28.join();
                                                                                                            }
                                                                                                            t27.join();
                                                                                                        }
                                                                                                        t26.join();
                                                                                                    }
                                                                                                    t25.join();
                                                                                                }
                                                                                                t24.join();
                                                                                            }
                                                                                            t23.join();
                                                                                        }
                                                                                        t22.join();
                                                                                    }
                                                                                    t21.join();
                                                                                }
                                                                                t20.join();
                                                                            }
                                                                            t19.join();
                                                                        }
                                                                        t18.join();
                                                                    }
                                                                    t17.join();
                                                                }
                                                                t16.join();
                                                            }
                                                            t15.join();
                                                        }
                                                        t14.join();
                                                    }
                                                    t13.join();
                                                }
                                                t12.join();
                                            }
                                            t11.join();
                                        }
                                        t10.join();
                                    }
                                    t9.join();
                                }
                                t8.join();
                            }
                            t7.join();
                        }
                        t6.join();
                    }
                    t5.join();
                }
                t4.join();
            }
            t3.join();
        }
        t2.join();
    }
    t1.join();

    return 0;
}

