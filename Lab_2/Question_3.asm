         AREA RESET, DATA, READONLY  
         EXPORT __Vectors 
__Vectors 
         DCD 0x20008000 
         DCD Reset_Handler 
         ALIGN 
         AREA myCode, CODE, ReadOnly 
         ENTRY 
         EXPORT Reset_Handler 
 
Reset_Handler    

ARR_SIZE  EQU  10 

          MOV R0, #0 ; initialize array index -i- to 0 
          MOV R1, #0 ; initialize sum to 0 
          LDR R2, =Arr ; load the base address of the array in R2 
          LDR R3, =0x20000000 ; storing the address sum will be stored in it in R3 

LOOP  
          CMP R0, #ARR_SIZE ; check loop condition i < array size 
          BEQ STORING  
          LDR R4, [R2, R0, LSL #2] ; load data of Arr[i] 
          ADD R1, R1, R4 ; sum = sum + Arr[i] 
          ADD R0, R0, #1; increment of i 
          B LOOP 
 
STORING  
          STR R1, [R3] ; storing sum in the memory address stored in R3 

         ALIGN 
         AREA myData, DATA, READONLY 
Arr      DCD 1,2,3,4,5,6,7,8,9,10 

         END