#include "compiler.hpp"
using namespace std;

static double to_double(long long r1, long long r2) {
    long long res = (r2 << 32) | r1;
    return *(double*)(&res);
}

void cpu::execRM(int cmd, int r0, unsigned addr){

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
    regs[15]++;
}

void cpu::execRR(int cmd, int r1, int r2, int mod){
    long long res;
    unsigned addr;
    double d1, d2;

    switch (cmd) {
    case ADD:
        regs[r1] += regs[r2] + mod;
        break;

    case SUB:
        regs[r1] -= regs[r2] + mod;
        break;
    
    case MUL:
        res = (long long)regs[r1] * (long long)regs[r2];
        regs[r1] = res;
        regs[r1 + 1] = res >> 32;
        break;
    
    case DIV:
        res = ((long long)regs[r1 + 1] << 32) | (long long)regs[r1];
        regs[r1] = res / regs[r2];
        regs[r1 + 1] = res % regs[r2];
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
        d1 = to_double(regs[r1], regs[r1 + 1]) + to_double(regs[r2], regs[r2 + 1]);
        res = *(long long*)(&d1);
        regs[r1] = res;
        regs[r1 + 1] = res >> 32;
        break;

    case SUBD:
        d1 = to_double(regs[r1], regs[r1 + 1]) - to_double(regs[r2], regs[r2 + 1]);
        res = *(long long*)(&d1);
        regs[r1] = res;
        regs[r1 + 1] = res >> 32;
        break;

    case MULD:
        d1 = to_double(regs[r1], regs[r1 + 1]) * to_double(regs[r2], regs[r2 + 1]);
        res = *(long long*)(&d1);
        regs[r1] = res;
        regs[r1 + 1] = res >> 32;
        break;

    case DIVD:
        d1 = to_double(regs[r1], regs[r1 + 1]) / to_double(regs[r2], regs[r2 + 1]);
        res = *(long long*)(&d1);
        regs[r1] = res;
        regs[r1 + 1] = res >> 32;
        break;

    case ITOD:
        d1 = (double)regs[r2];
        res = *(long long*)(&d1);
        regs[r1] = res;
        regs[r1 + 1] = res >> 32;
        break;

    case DTOI:
        d1 = to_double(regs[r2], regs[r2 + 1]);
        regs[r1] = (int)d1;
        break;

    case CALL:
        regs[14]--;
        mem[regs[14]] = regs[15] + 1;
        addr = regs[r2] + mod;
        regs[15] = addr - 1;
        regs[r1] = addr;
        break;

    case CMP:
        flags = regs[r1] - regs[r2];
        break;

    case CMPD:
        d1 = to_double(regs[r1], regs[r1 + 1]);
        d2 = to_double(regs[r2], regs[r2 + 1]);
        flags = d1 > d2? 1 : -1;
        flags *= (d1 != d2);
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
    regs[15]++;
}

void cpu::execRI(int cmd, int r1, int imm){
    double d;
    int i;
    long long res;

    switch (cmd) {
    case HALT:
        exit(0);
        break;

    case SYSCALL:
        switch (imm) {

        case EXIT:
            exit(0);
            break;

        case SCANINT:
            res = scanf("%d", &i);
            regs[r1] = i;
            break;

        case SCANDOUBLE:
            res = scanf("%lg", &d);
            res = *(long long *)(&d);
            regs[r1] = res;
            regs[r1 + 1] = res >> 32;
            break;

        case PRINTINT:
            printf("%d", regs[r1]);
            break;

        case PRINTDOUBLE:
            d = to_double(regs[r1], regs[r1 + 1]);
            printf("%lg", d);
            break;

        case GETCHAR:
            regs[r1] = getchar();
            break;
        
        case PUTCHAR:
            putchar(regs[r1]);
            break;

        default:
            break;
        }
        break; 

    case ADDI:
        regs[r1] += imm;
        break; 

    case SUBI:
        regs[r1] -= imm;
        break; 

    case MULI:
        res = (long long)regs[r1] * (long long)imm;
        regs[r1] = res;
        regs[r1 + 1] = res >> 32;
        break; 

    case DIVI:
        res = (long long)regs[r1] / (long long)imm;
        regs[r1] = res;
        regs[r1 + 1] = res >> 32;
        break; 

    case LC:
        regs[r1] = imm;
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
        regs[14]--;
        mem[regs[14]] = regs[r1] + imm;
        break;
    
    case POP:
        regs[r1] = mem[regs[14]] + imm;
        regs[14]++;
        break;

    case RET:
        regs[15] = mem[regs[14]] - 1;
        regs[14] += imm + 1;
        break;

    case CMPI:
        flags = regs[r1] - imm;
        break;

    default:
        break;
    }
    regs[15]++;
}

void cpu::execJ(int cmd, unsigned addr){

    switch (cmd) {
    case CALLI:
        regs[14]--;
        mem[regs[14]] = regs[15] + 1;
        regs[15] = addr;
        break;
    
    case JMP:
        regs[15] = addr;
        break;

    case JNE:
        if(flags != 0)
            regs[15] = addr;
        else
            regs[15]++;
        break;

    case JEQ:
        if(flags == 0)
            regs[15] = addr;
        else
            regs[15]++;
        break;

    case JLE:
        if(flags <= 0)
            regs[15] = addr;
        else
            regs[15]++;
        break;

    case JL:
        if(flags < 0)
            regs[15] = addr;
        else
            regs[15]++;
        break;

    case JGE:
        if(flags >= 0)
            regs[15] = addr;
        else
            regs[15]++;
        break;

    case JG:
        if(flags > 0)
            regs[15] = addr;
        else
            regs[15]++;
        break;

    default:
        break;
    }
}