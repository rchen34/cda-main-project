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
    // this is a test
}
/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{

    unsigned mask_six=63; // 63 == 11 1111
    unsigned mask_five=31; // 31 == 1 1111
    unsigned mask_sixteen = 65535; // == 1111 1111 1111 1111
    unsigned mask_j= 67108863; // this big number is the decimal value of  28 1's
                               // in binary notation, 11111111111111111111111111,
                               // since the JUMP address is 28 bits long

    *op=instruction>>26;
    if(*op==0){ // if R-format
        // the mask is 11111 so when we do AND operation it will only extract the last 5 bits
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
    else if(*op==2||*op==3) { // if J-format
        *jsec = instruction & mask_j;
    }
    else{ // if I-format
        // immediate value needs to be taken in. 16 bit number
        *offset = instruction & mask_sixteen;
        // rt needs to be taken in. mask shifted 16 bits left past immediate
        mask_five = mask_five<<16;
        *r2 = instruction & mask_five;
        // rs needs to be taken in. mask shifted 5 more bits to left
        mask_five = mask_five<<5;
        *r1 = instruction & mask_five;
    }

    return;
}



/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{
    if(op == 0) { // R-type instruction
      controls->RegDst = '1';
    	controls->Jump = '0';
    	controls->Branch = '0';
    	controls->MemRead = '0';
    	controls->MemtoReg = '0';
    	controls->ALUOp = '7';
    	controls->MemWrite = '0';
    	controls->ALUSrc = '0';
    	controls->RegWrite = '1';
    }else if(op == 2) {// jump
      controls->RegDst = '2';
    	controls->Jump = '1';
    	controls->Branch = '0';
    	controls->MemRead = '0';
    	controls->MemtoReg = '2';
    	controls->ALUOp = '0';
    	controls->MemWrite = '0';
    	controls->ALUSrc = '2';
    	controls->RegWrite = '0';
    }else if(op == 4) { // branch on equal
      controls->RegDst = '0';
      controls->Jump = '0';
      controls->Branch = '1';
      controls->MemRead = '0';
      controls->MemtoReg = '0';
      controls->ALUOp = '1';
      controls->MemWrite = '0';
      controls->ALUSrc = '2';
      controls->RegWrite = '0';
    }else if(op == 8) {//add immediate
      controls->RegDst = '0';
    	controls->Jump = '0';
    	controls->Branch = '0';
    	controls->MemRead = '0';
    	controls->MemtoReg = '0';
    	controls->ALUOp = '0';
    	controls->MemWrite = '0';
    	controls->ALUSrc = '2';
    	controls->RegWrite = '1';
    }else if(op == 10) {//set less than immediate
      controls->RegDst = '0';
    	controls->Jump = '0';
    	controls->Branch = '0';
    	controls->MemRead = '0';
    	controls->MemtoReg = '0';
    	controls->ALUOp = '2';
    	controls->MemWrite = '0';
    	controls->ALUSrc = '2';
    	controls->RegWrite = '1';
    }
}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{
    // point data1 and data2 to the value of Reg at r1 and r2
    *data1=Reg[r1];
    *data2=Reg[r2];

}


/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{
    // assign the sign-extended value of 'offset' to 'extended_value'
    //according to lecture, we get passed 16 bits and we make it into 32
    //To check if the offset is negative we shift it 15 bits to the right leaving the largest bit, if its 1 its negative
    //otherwise its positive
    unsigned neg_num=4294901760;
    //this number is 11111111111111110000000000000000
    if(offset>>15==1){
        // for negative we use a neg_num which has all ones in the leftmost 16 positions and zeros for the remaining ones
        // doing an or operation on this allows us to keep the integrity of the leftmost 16 bits while making the rest of
        // them 1s
        *extended_value= neg_num|offset;
    }
    else{
        // Here you would add 16 0s to the right of offset but in C it doesn't make a difference so we just set extend value
        // equal to offset
        *extended_value= neg_num|offset;

    }


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
    // check for Halt
    if( (ALUResult % 4) != 0) {
      Halt = 1;
      return Halt;
    }

    if(MemWrite == '1') { // memory write operation
      // write data2 to memory location addressed by ALUResult
      Mem[ALUResult >> 2} = data2;
    } else if(MemRead == '1') { // memory read operation
      // Read content of ALUResult's memory location to memdata
      *memdata = Mem[ALUResult >> 2];
    }//end if else

    return 0;
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
