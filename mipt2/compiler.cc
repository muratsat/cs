#include "compiler.hpp"

compiler::compiler(){

    code["halt"]    =    HALT;
    code["syscall"] = SYSCALL;
    code["add"]     =     ADD;
    code["addi"]    =    ADDI;
    code["sub"]     =     SUB;
    code["subi"]    =    SUBI;
    code["mul"]     =     MUL;
    code["muli"]    =    MULI;
    code["div"]     =     DIV;
    code["divi"]    =    DIVI;
    code["lc"]      =      LC;
    code["shl"]     =     SHL;
    code["shli"]    =    SHLI;
    code["shr"]     =     SHR;
    code["shri"]    =    SHRI;
    code["and"]     =     AND;
    code["andi"]    =    ANDI;
    code["or"]      =      OR;
    code["ori"]     =     ORI;
    code["xor"]     =     XOR;
    code["xori"]    =    XORI;
    code["not"]     =     NOT;
    code["mov"]     =     MOV;
    code["addd"]    =    ADDD;
    code["subd"]    =    SUBD;
    code["muld"]    =    MULD;
    code["divd"]    =    DIVD;
    code["itod"]    =    ITOD;
    code["dtoi"]    =    DTOI;
    code["push"]    =    PUSH;
    code["pop"]     =     POP;
    code["call"]    =    CALL;
    code["calli"]   =   CALLI;
    code["ret"]     =     RET;
    code["cmp"]     =     CMP;
    code["cmpi"]    =    CMPI;
    code["cmpd"]    =    CMPD;
    code["jmp"]     =     JMP;
    code["jne"]     =     JNE;
    code["jeq"]     =     JEQ;
    code["jle"]     =     JLE;
    code["jl"]      =      JL;
    code["jge"]     =     JGE;
    code["jg"]      =      JG;
    code["load"]    =    LOAD;
    code["store"]   =   STORE;
    code["load2"]   =   LOAD2;
    code["store2"]  =  STORE2;
    code["loadr"]   =   LOADR;
    code["loadr2"]  =  LOADR2;
    code["storer"]  =  STORER;
    code["storer2"] = STORER2;

    codeType["halt"]    = RI;
    codeType["syscall"] = RI;
    codeType["add"]     = RR;
    codeType["addi"]    = RI;
    codeType["sub"]     = RR;
    codeType["subi"]    = RI;
    codeType["mul"]     = RR;
    codeType["muli"]    = RI;
    codeType["div"]     = RR;
    codeType["divi"]    = RI;
    codeType["lc"]      = RI;
    codeType["shl"]     = RR;
    codeType["shli"]    = RI;
    codeType["shr"]     = RR;
    codeType["shri"]    = RI;
    codeType["and"]     = RR;
    codeType["andi"]    = RI;
    codeType["or"]      = RR;
    codeType["ori"]     = RI;
    codeType["xor"]     = RR;
    codeType["xori"]    = RI;
    codeType["not"]     = RI;
    codeType["mov"]     = RR;
    codeType["addd"]    = RR;
    codeType["subd"]    = RR;
    codeType["muld"]    = RR;
    codeType["divd"]    = RR;
    codeType["itod"]    = RR;
    codeType["dtoi"]    = RR;
    codeType["push"]    = RI;
    codeType["pop"]     = RI;
    codeType["call"]    = RR;
    codeType["calli"]   = J;
    codeType["ret"]     = RI;
    codeType["cmp"]     = RR;
    codeType["cmpi"]    = RI;
    codeType["cmpd"]    = RR;
    codeType["jmp"]     = J;
    codeType["jne"]     = J;
    codeType["jeq"]     = J;
    codeType["jle"]     = J;
    codeType["jl"]      = J;
    codeType["jge"]     = J;
    codeType["jg"]      = J;
    codeType["load"]    = RM;
    codeType["store"]   = RM;
    codeType["load2"]   = RM;
    codeType["store2"]  = RM;
    codeType["loadr"]   = RR;
    codeType["loadr2"]  = RR;
    codeType["storer"]  = RR;
    codeType["storer2"] = RR;

    registerInt["r0"] = 0;
    registerInt["r1"] = 1;
    registerInt["r2"] = 2;
    registerInt["r3"] = 3;
    registerInt["r4"] = 4;
    registerInt["r5"] = 5;
    registerInt["r6"] = 6;
    registerInt["r7"] = 7;
    registerInt["r8"] = 8;
    registerInt["r9"] = 9;
    registerInt["r10"] = 10;
    registerInt["r11"] = 11;
    registerInt["r12"] = 12;
    registerInt["r13"] = 13;
    registerInt["r14"] = 14;
    registerInt["r15"] = 15;
}

compiler::~compiler(){
}

int compiler::opcode(string word){
    if(code.find(word) != code.end())
        return code[word];
    
    return -1;
}

int compiler::optype(string word){
    if(codeType.find(word) != codeType.end())
        return codeType[word];
    
    return -1;
}

vector<string> compiler::readfile(const char* filename){
    FILE* f = freopen(filename, "r", stdin);

    vector<string> lines;

    string s;
    while(getline(cin, s))
        lines.push_back(s);

    fclose(f);
    return lines;
}

vector<string> compiler::split_words(string line){
    int n = line.size();

    string word;
    vector<string> words;

    for(int i = 0; i < n; i++) {
        char t = line[i];
        if(t == ';')
            break;

        else if(t == ',')
            continue;
        
        else if(t == ' ') {
            if(word.size() > 0)
                words.push_back(word);
            word = "";
        }

        else 
            word += t;
    }

    if(word.size() > 0)
        words.push_back(word);
    
    return words;
}