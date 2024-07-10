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
		 MOV R0, #6  ; R0 elem count  
		 MOV R1, #-14  
		 MOV R2, #5  
		 MOV R3, #32  
		 MOV R4, #-7  
		 MOV R5, #0  
		 MOV R6, #-5 
		 PUSH {R4} 
		 PUSH {R5} 
		 PUSH {R6} 
		 BL MAXMIN 
		 B FINISH 

MAXMIN   
		 POP {R6} 
		 POP {R5} 
		 POP {R4} 
		 PUSH {LR} 
		 LDR R7, =ARR 
		 STR R1, [R7] 
		 STR R2, [R7, #4] 
		 STR R3, [R7, #8] 
		 STR R4, [R7, #12] 
		 STR R5, [R7, #16] 
		 STR R6, [R7, #20] 
		 MOV R8, #0  ; INDEX COUNT 
		 LDR R9, [R7]  ; TEMP REG. WITH FIRST VALUE IN TEMP ARR. MAX TEMP 
		 LDR R12, [R7]  ; TEMP REG. WITH FIRST VALUE IN TEMP ARR MIN TEMP 

LOOP    
		 SUBS R0, #1 
		 BEQ RETURN 
		 ADD R8, R8, #1 
		 LDR R10, [R7, R8, LSL #2] 
		 CMP R10, R9  ; R10 – R9  
		 BGT GT 
		 CMP R10, R12  ; R10 – R12  
		 BLT LT 

DONE    
		 B LOOP 

RETURN   
		 POP {LR} 
		 MOV R0, R9  ; MAX 
		 MOV R1, R12  ; MIN 
		 BX LR   

GT     
		 MOV R9, R10 ; UPDATE THE VALUE TO THE BIGGER ONE, R9 CONTAIN MAX 
		 B DONE 

LT     
		 MOV R12, R10 ; UPDATE THE VALUE TO THE SMALLER ONE, R12 CONTAIN MIN 
		 B DONE   

FINISH   
		 STR R0, [R7, #24]  
		 STR R1, [R7, #28] 

		 ALIGN 
       		 AREA myVarArr, DATA, READWRITE 
ARR     	 SPACE 24

		 END
