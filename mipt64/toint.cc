#include "cpu.h"

// TODO

unsigned cpu::tointRR(vector<string> &words) {
    int cmd = opCode(words[0]);

    unsigned command = cmd << 26;
    int dst = strToReg(words[1]);
    int src = strToReg(words[2]);

    command |= dst << 21;
    command |= src << 16;

    if (src == RZ) {
        int imm = stoi(words[3]) & 0xffff;
        command |= imm;
    }
    else {
        int ri = strToReg(words[3]);
        int bits = stoi(words[4]);
        int im = stoi(words[5]);

        command |= ri << 11;
        command |= bits << 8;
        command |= im;
    }

    return command;
}

unsigned cpu::tointRM(vector<string> &words) {
    int cmd = opCode(words[0]);
    unsigned command = cmd << 26;

    int rd = strToReg(words[1]);
    int ra = strToReg(words[2]);

    command |= rd << 21;
    command |= ra << 16;

    if (ra == PC || ra == RZ) {
        int imm = stoi(words[3]) & 0xffff;
        command |= imm;
    }
    else if (ra == SP) {
        unsigned imm = stoul(words[3]) & 0xffff;
        command |= imm;
    }
    else {
        int ri = strToReg(words[3]), im;
        command |= ri << 11;
        if (ri == RZ) {
            im = stoi(words[4]) & 0xb;
            command |= im;
        }
        else {
            int bits = stoi(words[4]) & 0x7;
            im = stoi(words[4]) & 0xff;
            command |= bits << 8;
            command |= im;
        }
    }

    return command;
}

unsigned cpu::tointB(vector<string> &words) {
    int cmd = opCode(words[0]);
    unsigned command = cmd << 26;

    int id = 2;
    int ra = strToReg(words[id]);
    if (ra == -1) { 
        ra = PC;
        id = 1;
    }

    if (ra == PC) {
        unsigned imm = stoul(words[id]) & 0xffff;
        command |= imm;
    }
    else if (ra == RZ) {
        int imm = stoi(words[id]) & 0xffff;
        command |= imm;
    }
    else {
        int ri = strToReg(words[id]);
        int bits = stoi(words[id + 1]);
        int imm = stoi(words[id + 2]);
        command |= ri << 16;
        command |= bits << 13;
        command |= imm;
    }

    return command;
}
