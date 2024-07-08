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
         LDR R0, =0x20000004 
         MOV R1, #0 ; j = 0 
         MOV R2, #0 ; i = 0 

Loop    
         CMP R2, #15 ; compare between i and 15 
         BGE EndLoop 
         ADD R1, R1, R2 ; j = j + i 
         ADD R2, #1 ; i++ 
         B Loop 
         
EndLoop  
         STR R1, [R0]  ;store the value of j in the memory 
         END 