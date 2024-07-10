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
		 LDR R0, =0x20000000 ; Address of n
		 LDR R1, =0x20000004 ; Address of sum
		 MOV R2, #0          ; Initialize sum to 0
		 STR R2, [R1]        ; Store 0 in sum
		 LDR R3, [R0]        ; Load the value of n into R3

WhileLoop
		 CMP R3, #0          ; Compare n with 0
		 BLE EndLoop         ; If n <= 0, exit loop
		 ADD R2, R2, R3      ; sum = sum + n
		 STR R2, [R1]        ; Store the updated sum
		 SUB R3, R3, #1      ; n = n - 1
		 STR R3, [R0]        ; Store the updated n
		 B WhileLoop         ; Repeat the loop

EndLoop
		 END
