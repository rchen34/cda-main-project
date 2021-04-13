#include "spimcore.h"

//ryan
//santi
/* ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{
    printf("%c",ALUControl);

}

/* instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
    //Halt condition checks
    //Check if address is a multiple of 4


    if(PC%4!=0 || &Mem[PC]==NULL){
        return 1;
    }
    else{
        PC=PC>>2;
        instruction= &Mem[PC];
        return 0;
    }


}


/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{
    //Moving the instuction over 32-(bits wanted) is the same as isolating the bits that are necessary
    unsigned mask_six=63;
    unsigned mask_five=31;
    unsigned mask_j=

    *op=instruction>>26;
    if(*op==0){
        // the mask is 11111 so when we do and it will only extract the last 5 bits
        // so we move everything over leaving the last 11 bits and extract the last 5 using the mask and &
        *funct=instruction & mask_six;
        //shift mask 5 6 times to get shamt
        mask_five=mask_five<<6;
        *offset=instruction & mask_five;
        //shhift mask 5 to get rd
        mask_five=mask_five<<5;
        *r3=instruction & mask_five;
        //shift mask 5 to get rt
        mask_five=mask_five<<5;
        *r2=instruction& mask_five;
        // shift mask 5 to get rs
        mask_five= mask_five<<5;
        *r1=instruction& mask_five;
    }
    else if(*op==2||*op==3) {

    }
    else{

    }

    // 1111 1100 1110 1001
    // 0000 0000 0000 1111

    //Since op code is 0 it is an r type instruction
    if(op==0){

    }

}



/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{

}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{

}


/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{

}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{

}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{

}


/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{

}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{

}
int main(void){

}
