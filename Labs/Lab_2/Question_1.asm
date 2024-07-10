        	 AREA RESET, DATA, READONLY  
		 EXPORT __Vectors 
__Vectors 
		 DCD 0x20008000 
		 DCD Reset_Handler 
		 ALIGN 
        	 AREA MatrixMultiplication, CODE, ReadOnly 
		 ENTRY 
		 EXPORT Reset_Handler 
   
Reset_Handler   
		 LDR R0, =A      ; Pointer to the start of matrix A
		 LDR R1, =Z      ; Pointer to the start of array Z
		 LDR R2, =X      ; Pointer to the start of array X
		 MOV R4, #0      ; row = 0

RowLoop
		 CMP R4, #4      ; Compare row with 4
		 BEQ End         ; If row == 4, end loop
		 MOV R5, #0      ; column = 0
		 MOV R6, #0      ; Temporary sum for Z[row] = 0

ColumnLoop
		 CMP R5, #4      ; Compare column with 4
		 BEQ UpdateZ     ; If column == 4, update Z[row]
		 LDR R7, [R0, R5, LSL #2] ; Load A[row, column]
		 LDR R8, [R2, R5, LSL #2] ; Load X[column]
		 MUL R9, R7, R8
		 ADD R6, R6, R9
		 ADD R5, R5, #1
		 B ColumnLoop

UpdateZ
		 LDR R10, [R1, R4, LSL #2]
		 ADD R10, R10, R6
		 STR R10, [R1, R4, LSL #2]
		 ADD R4, R4, #1
		 ADD R0, R0, #16 ; Move to the next row in A
		 B RowLoop

End
		 END
