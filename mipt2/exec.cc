#include "compiler.hpp"
using namespace std;

void cpu::execRM(int cmd, int r0, unsigned addr){
    string word = code_word[cmd];

    switch (cmd) {
    case LOAD:
        regs[r0] = mem[addr];
        break;

    case STORE:
        mem[addr] = regs[r0];
        break;

    case LOAD2:
        regs[r0] = mem[addr];
        regs[r0 + 1] = mem[addr + 1];
        break;

    case STORE2:
        mem[addr] = regs[r0];
        mem[addr + 1] = regs[r0 + 1];
        break;

    default:
        break;
    }
}

void cpu::execRR(int cmd, int r1, int r2, int mod){
    string word = code_word[cmd];
    long long res;
    unsigned addr;

    switch (cmd) {
    case ADD:
        regs[r1] += regs[r2] + mod;
        break;

    case SUB:
        regs[r1] -= r2 + mod;
        break;
    
    case MUL:
        res = (long long)regs[r1] * (long long)regs[r2];
        regs[r1] = res;
        regs[r1 + 1] = res;
        // TODO
        break;
    
    case DIV:
        // TODO
        break;

    case SHL:
        regs[r1] = regs[r1] << regs[r2];
        break;

    case SHR:
        regs[r1] = regs[r1] >> regs[r2];
        break;
    
    case AND:
        regs[r1] = regs[r1] & regs[r2];
        break;

    case OR:
        regs[r1] = regs[r1] | regs[r2];
        break;
    
    case XOR:
        regs[r1] = regs[r1] ^ regs[r2];
        break;
    
    case MOV:
        regs[r1] = regs[r2] + mod;
        break;

    case ADDD:
        // TODO
        break;

    case SUBD:
        // TODO
        break;

    case MULD:
        // TODO
        break;

    case DIVD:
        // TODO
        break;

    case ITOD:
        // TODO
        break;

    case DTOI:
        // TODO
        break;

    case CALL:
        addr = regs[r2] + mod;
        // TODO
        // push stack
        break;

    case CMP:
        flags = regs[r1] - regs[r2];
        break;

    case CMPD:
        // TODO
        break;

    case LOADR:
        addr = regs[r2] + mod;
        regs[r1] = mem[addr];
        break;

    case LOADR2:
        addr = regs[r2] + mod;
        regs[r1] = mem[addr];
        regs[r1 + 1] = mem[addr + 1];
        break;

    case STORER:
        addr = regs[r2] + mod;
        mem[addr] = regs[r1];
        break;

    case STORER2:
        addr = regs[r2] + mod;
        mem[addr] = regs[r1];
        mem[addr + 1] = regs[r1 + 1];
        break;

    default:
        break;
    }
}

void cpu::execRI(int cmd, int r1, int imm){
    string word = code_word[cmd];

    switch (cmd) {
    case HALT:
        exit(0);
        break;

    case SYSCALL:
        // TODO
        break; 

    case ADDI:
        regs[r1] += imm;
        break; 

    case SUBI:
        regs[r1] -= imm;
        break; 

    case MULI:
        // TODO
        break; 

    case DIVI:
        // TODO
        break; 

    case LC:
        // if(imm > 1048576)
        // TODO
        break; 

    case SHLI:
        regs[r1] = regs[r1] << imm;
        break;

    case SHRI:
        regs[r1] = regs[r1] >> imm;
        break;

    case ANDI:
        regs[r1] = regs[r1] & imm;
        break;

    case ORI:
        regs[r1] = regs[r1] | imm;
        break;

    case XORI:
        regs[r1] = regs[r1] ^ imm;
        break;

    case NOT:
        regs[r1] = ~regs[r1];
        break;

    case PUSH:
        mem[regs[14]] = regs[r1] + imm;
        regs[14]++;
        break;
    
    case POP:
        regs[r1] = mem[regs[14]] + imm;
        regs[14]--;
        break;

    case RET:
        // TODO
        // regs[14] 
        // regs[15] = 
        break;

    case CMPI:
        flags = regs[r1] - imm;
        break;

    default:
        break;
    }
}

void cpu::execJ(int cmd, unsigned addr){
    string word = code_word[cmd];

    switch (cmd) {
    case CALLI:
        // regs[15] = mem[addr];
        // TODO
        break;
    
    case JMP:
        regs[15] = addr;
        break;

    case JNE:
        if(flags != 0)
            regs[15] = addr;
        break;

    case JEQ:
        if(flags != 0)
            regs[15] = addr;
        break;

    case JLE:
        if(flags <= 0)
            regs[15] = addr;
        break;

    case JL:
        if(flags < 0)
            regs[15] = addr;
        break;

    case JGE:
        if(flags >= 0)
            regs[15] = addr;
        break;

    case JG:
        if(flags > 0)
            regs[15] = addr;
        break;

    default:
        break;
    }
}