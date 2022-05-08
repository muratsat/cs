#include "compiler.hpp"
using namespace std;

cpu::cpu(){

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

    codeType[HALT]    = RI;
    codeType[SYSCALL] = RI;
    codeType[ADD]     = RR;
    codeType[ADDI]    = RI;
    codeType[SUB]     = RR;
    codeType[SUBI]    = RI;
    codeType[MUL]     = RR;
    codeType[MULI]    = RI;
    codeType[DIV]     = RR;
    codeType[DIVI]    = RI;
    codeType[LC]      = RI;
    codeType[SHL]     = RR;
    codeType[SHLI]    = RI;
    codeType[SHR]     = RR;
    codeType[SHRI]    = RI;
    codeType[AND]     = RR;
    codeType[ANDI]    = RI;
    codeType[OR]      = RR;
    codeType[ORI]     = RI;
    codeType[XOR]     = RR;
    codeType[XORI]    = RI;
    codeType[NOT]     = RI;
    codeType[MOV]     = RR;
    codeType[ADDD]    = RR;
    codeType[SUBD]    = RR;
    codeType[MULD]    = RR;
    codeType[DIVD]    = RR;
    codeType[ITOD]    = RR;
    codeType[DTOI]    = RR;
    codeType[PUSH]    = RI;
    codeType[POP]     = RI;
    codeType[CALL]    = RR;
    codeType[CALLI]   = J;
    codeType[RET]     = RI;
    codeType[CMP]     = RR;
    codeType[CMPI]    = RI;
    codeType[CMPD]    = RR;
    codeType[JMP]     = J;
    codeType[JNE]     = J;
    codeType[JEQ]     = J;
    codeType[JLE]     = J;
    codeType[JL]      = J;
    codeType[JGE]     = J;
    codeType[JG]      = J;
    codeType[LOAD]    = RM;
    codeType[STORE]   = RM;
    codeType[LOAD2]   = RM;
    codeType[STORE2]  = RM;
    codeType[LOADR]   = RR;
    codeType[LOADR2]  = RR;
    codeType[STORER]  = RR;
    codeType[STORER2] = RR;

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

cpu::~cpu(){
}

int cpu::opCode(string word){
    if(code.find(word) != code.end())
        return code[word];
    
    return -1;
}

int cpu::opType(int cmd){
    if(codeType.find(cmd) != codeType.end())
        return codeType[cmd];
    
    return -1;
}


int cpu::isRegister(string word) {
    if(registerInt.find(word) != registerInt.end())
        return registerInt[word];
    
    return -1;
}

void cpu::error(int line) {
    cerr << "error in line " << line << '\n';
    exit(0);
}

vector<string> cpu::readfile(){

    vector<string> lines;

    string s;
    while(getline(cin, s)){
        s.erase(remove(s.begin(), s.end(), '\t'), s.end());
        lines.push_back(s);
    }

    return lines;
}

vector<string> cpu::split_words(string line){
    int n = line.size();

    string word;
    vector<string> words;
    line.erase(remove(line.begin(), line.end(), '\t'), line.end());

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

static bool isNumber(string s){
    for(char c : s)
        if(!isdigit(c)) return false;
    return true;
}

static void print_bin(unsigned int x) {
    for (int i = 1; i <= 32; i++) {
        printf("%d", (x >> (32 - i))&1);
        if(i%8 == 0)
            printf(" ");
    }
    printf("\n");
}

void cpu::assemble(){
    vector<string> lines = readfile();

    vector<vector<string>> linesWords;

    map<string, int> labelValue;
    int pc = 0;
    for(auto line : lines){
        auto words = split_words(line);
        for(auto it = words.begin(); it != words.end(); it++){
            string word = *it;
            if (word.back() == ':'){
                words.erase(it);
                it--;
                word.pop_back();
                labelValue[word] = pc;
            }
        }
        if(!words.empty())
            pc++;
        linesWords.push_back(words);
    }

    pc = 0;
    int lineCount = 0;

    for (auto &words: linesWords) {
        for (auto &word : words) {
            if(labelValue.find(word) != labelValue.end())
                word = to_string(labelValue[word]);
        }
    }

    for (auto &words: linesWords) {

        lineCount++;
        if(words.empty())
            continue;;

        if (words[0] == "end") {
            regs[15] = stoul(words[1]);
            break;
        }
        else if (words[0] == "word") {
            mem[pc] = stoi(words[1]);
            pc++;
        }
        else if (words[0] == "double") {
            float x = stod(words[1]);
            long long res = *(unsigned*)(&x);
            mem[pc] = res;
            mem[pc + 1] = (res >> 32);
            pc += 2;
        }
        else {
            unsigned command = 0;
            int cmd = opCode(words[0]), cmdType = opType(cmd);
            int r1 = -1, r2 = -1;
            unsigned addr = 0;
            int mod = 0, imm = 0;

            switch (cmdType) {

            case RM:
                r1 = isRegister(words[1]);
                addr = stoul(words[2]);
                command |= (cmd & 0xff) << 24;
                command |= (r1 & 0xf) << 20;
                command |= addr & 0xfffff;
                break;

            case RR:
                r1 = isRegister(words[1]);
                r2 = isRegister(words[2]);
                mod = stoi(words[3]);
                command |= (cmd & 0xff) << 24;
                command |= (r1 & 0xf) << 20;
                command |= (r2 & 0xf) << 16;
                command |= mod & 0xffff;
                break;

            case RI:
                r1 = isRegister(words[1]);
                if(r1 == -1){
                    r1 = 0;
                    imm = stoi(words[1]);
                }
                else
                    imm = stoi(words[2]);
                command |= (cmd & 0xff) << 24;
                command |= (r1 & 0xf) << 20;
                command |= (imm & 0xfffff);
                break;

            case J:
                addr = stoul(words[1]);
                command |= (cmd & 0xff) << 24;
                command |= addr & 0xfffff;
                break;

            default:
                break;
            }
            mem[pc] = command;
            pc++;
        }
    }
}

void cpu::run() {

    regs[14] = 1024*1024 - 1;
    unsigned command = mem[regs[15]];
    unsigned cmd = (command >> 24);

    while (cmd != HALT) {
        command = mem[regs[15]];
        cmd = (command >> 24);

        int r1 = 0, r2 = 0;
        unsigned addr = 0;
        int mod = 0, imm = 0;

        switch (opType(cmd)) {
        
        case RM: 
            r1 = (command >> 20) & 0xf;
            addr = command & 0xfffff;
            execRM(cmd, r1, addr);
            break;

        case RR: 
            r1  = (command >> 20) & 0xf;
            r2  = (command >> 16) & 0xf;
            mod = command & 0xffff;
            execRR(cmd, r1, r2, mod);
            break;

        case RI:
            r1  = (command >> 20) & 0xf;
            imm = command & 0xfffff;
            execRI(cmd, r1, imm);
            break;

        case J:
            addr = command & 0xfffff;
            execJ(cmd, addr);
            break;

        default:
            break;
        }
    }
}


void cpu::load() {
    FILE *fp = fopen("input.bin", "rb");
    fseek(fp, 0L, SEEK_END);
    size_t count = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    char *byte = (char*)malloc(count);
    int bytes = fread(byte, 1, count, fp);

    int pc = 0;
    for (int i = 512; i + 3 < count; i += 4) {
        unsigned command = 0;
        command |= ((unsigned)(char)byte[i + 3] & 0xff) << 24;
        command |= ((unsigned)(char)byte[i + 2] & 0xff) << 16;
        command |= ((unsigned)(char)byte[i + 1] & 0xff) << 8;
        command |= (unsigned)(char)byte[i] & 0xff;
        mem[pc] = command;
        pc++;
    }


    unsigned addr = 0; // 28 - 31
    addr |= (unsigned)byte[28];
    addr |= (unsigned)byte[29] << 8;
    addr |= (unsigned)byte[30] << 16;
    addr |= (unsigned)byte[31] << 24;
    regs[15] = addr;
    regs[14] = 1024*1024 - 1;
    mem[pc] = 0;

    fclose(fp);
    free(byte);
}
