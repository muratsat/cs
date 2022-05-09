#include "cpu.h"

cpu::cpu() {
    code["halt"] = 0;
    code["svc"]  = 1;
    code["add"]  = 2;
    code["sub"]  = 3;
    code["mul"]  = 4;
    code["div"]  = 5;
    code["mod"]  = 6;
    code["and"]  = 7;
    code["or"]   = 8;
    code["xor"]  = 9;
    code["nand"] = 10;
    code["addd"] = 12;
    code["subd"] = 13;
    code["muld"] = 14;
    code["divd"] = 15;
    code["itod"] = 16;
    code["dtoi"] = 17;
    code["bl"]   = 20;
    code["cmp"]  = 22;
    code["cmpd"] = 23;
    code["cne"]  = 25;
    code["ceq"]  = 26;
    code["cle"]  = 27;
    code["clt"]  = 28;
    code["cge"]  = 29;
    code["cgt"]  = 30;
    code["ld"]   = 31;
    code["st"]   = 32;

    codeType[HALT] = RR;
    codeType[SVC]  = RR;
    codeType[ADD]  = RR;
    codeType[SUB]  = RR;
    codeType[MUL]  = RR;
    codeType[DIV]  = RR;
    codeType[MOD]  = RR;
    codeType[AND]  = RR;
    codeType[OR]   = RR;
    codeType[XOR]  = RR;
    codeType[NAND] = RR;
    codeType[ADDD] = RR;
    codeType[SUBD] = RR;
    codeType[MULD] = RR;
    codeType[DIVD] = RR;
    codeType[ITOD] = RR;
    codeType[DTOI] = RR;
    codeType[BL]   = B;
    codeType[CMP]  = RR;
    codeType[CMPD] = RR;
    codeType[CNE]  = RR;
    codeType[CEQ]  = RR;
    codeType[CLE]  = RR;
    codeType[CLT]  = RR;
    codeType[CGE]  = RR;
    codeType[CGT]  = RR;
    codeType[LD]   = RR;
    codeType[ST]   = RM;

    for(int r = 0; r < 32; r++) {
        string reg = "r" + to_string(r);
        regInt[reg] = r;
    }

    regInt["rz"] = 27;
    regInt["fp"] = 28;
    regInt["sp"] = 29;
    regInt["lr"] = 30;
    regInt["pc"] = 31;
}

cpu::~cpu() {

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

int cpu::strToReg(string word) {
    if(regInt.find(word) != regInt.end())
        return regInt[word];
    
    return -1;
}

vector<string> cpu::readfile() {

    vector<string> lines;

    string s;
    while(getline(cin, s)){
        s.erase(remove(s.begin(), s.end(), '\t'), s.end());
        lines.push_back(s);
    }

    return lines;
}

vector<string> cpu::split_words(string line) {
    int n = line.size();

    string word;
    vector<string> words;
    line.erase(remove(line.begin(), line.end(), '\t'), line.end());

    for(int i = 0; i < n; i++) {
        char t = line[i];
        if(t == ';')
            break;
        
        else if(t == ' ' || t == ',') {
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

void cpu::compile(){
    vector<string> lines = readfile();
    vector<vector<string>> linesWords;

    map<string, int> labelValue;
    int pc = 0;

    // set all labels
    for (auto line : lines) {
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
        if(!words.empty()){
            pc++;
            linesWords.push_back(words);
        }
    }
    for (auto &words: linesWords) {
        for (auto &word : words) {
            if(labelValue.find(word) != labelValue.end())
                word = to_string(labelValue[word]);
            // if(strToReg(word) != -1)
            //     word = "r" + to_string(strToReg(word));
        }
    }

    pc = 0;
    int lineCount = 0;
    for (auto &words: linesWords) {
        if(words.empty())
            continue;

        int cmd = opCode(words[0]);
        unsigned command = 0;
        for (auto &word : words)
            cout << word << ' ';

        switch (opType(cmd)) {
        case RR:
            command = tointRR(words);
            break;
        
        case RM:
            command = tointRM(words);
            break;
        
        case B:
            command = tointB(words);
            break;
        
        default:
            break;
        }

        printf("%08X \n", command);
        // printf("\n");
    }
}
