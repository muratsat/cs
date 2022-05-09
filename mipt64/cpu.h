#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#pragma once

typedef long long unsigned llu;
typedef long long ll;

using namespace std;

enum type {
    RR, // 6b[code] 5b[dst] 5b[src] 16[imm]
    RM,
    B
};

enum registers {
    RZ = 27,
    FP = 28,
    SP = 29,
    LR = 30,
    PC = 31
};

enum syscalls {
    EXIT = 0,
    SCANINT = 100,
    SCANDOUBLE = 101,
    PRINTINT = 102,
    PRINTDOUBLE = 103,
    GETCHAR = 104,
    PUTCHAR = 105
};

enum code_e {
    HALT = 0,
    SVC = 1,
    ADD = 2,
    SUB = 3,
    MUL = 4,
    DIV = 5,
    MOD = 6,
    AND = 7,
    OR = 8,
    XOR = 9,
    NAND = 10,
    ADDD = 12,
    SUBD = 13,
    MULD = 14,
    DIVD = 15,
    ITOD = 16,
    DTOI = 17,
    BL = 20,
    CMP = 22,
    CMPD = 23,
    CNE = 25,
    CEQ = 26,
    CLE = 27,
    CLT = 28,
    CGE = 29,
    CGT = 30,
    LD = 31,
    ST = 32,
};

class cpu {
    ll regs[32] = {};
    unsigned mem[2097152];
    int flags = 0;

    map<string, int> code;

    map<int, int> codeType;

    map<string, int> regInt;


    // read and return vector of lines
    // from FILENAME in stdin
    vector<string> readfile();

    // split string into 
    // separate words
    vector<string> split_words(string line);

    // operation code
    // returns -1 if doesn't exist
    int opCode(string word);

    // operation type(RM, RR, B)
    // returns -1 if doesn't exist
    int opType(int cmd);

    // return register number
    // or -1 if word is not register
    int strToReg(string word);

    unsigned tointRR(vector<string> &words);
    unsigned tointRM(vector<string> &words);
    unsigned tointB(vector<string> &words);

    public:
    cpu();
    ~cpu();

    // assemble file input.fasm
    // from stdin
    void compile();

    // run the assembled program
    void run();
};