#include <stdio.h>
#include <stdint.h>

#define NREG 4
#define NMEM 16

typedef union {
    struct { uint8_t rs : 2, rt : 2, op : 4; } rtype;
    struct { uint8_t addr : 4      , op : 4; } mtype;
    uint8_t inst;
}inst_t;

#define DECODE_R(inst) uint8_t rt = (inst).rtype.rt, rs = (inst).rtype.rs
#define DECODE_M(inst) uint8_t addr = (inst).mtype.addr

uint8_t pc = 0;
uint8_t R[NREG] = {};
uint8_t M[NMEM] = {
    0b11100110,
    0b00000100,
    0b11100101,
    0b00010001,
    0b11110111,
    0b00010000,
    0b00100001,
    0b00000000,
};

int halt = 0;

void exec_once() {
    inst_t this;
    this.inst = M[pc];
    switch (this.rtype.op) {
        case 0b0000: { DECODE_R(this); R[rt]    = R[rs];    break; }
        case 0b0001: { DECODE_R(this); R[rt]   += R[rs];    break; }
        case 0b1110: { DECODE_M(this); R[0]     = M[addr];  break; }
        case 0b1111: { DECODE_M(this); M[addr]  = R[0];     break; }
        default:
            printf("Invaild instruction with opcode = %x, halting...\n", this.rtype.op);
            halt = 1;
            break;
    }
    pc ++;
}

int main() {
    while(1) {
        exec_once();
        if(halt) break;
    }
    printf("The result of 16 + 33 is %d\n", M[7]);
    return 0;
}

