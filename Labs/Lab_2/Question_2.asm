	         AREA RESET, DATA, READONLY  
		 EXPORT __Vectors 
__Vectors 
		 DCD 0x20008000 
		 DCD Reset_Handler 
		 ALIGN 
	         AREA PowerCalculation, CODE, ReadOnly 
		 ENTRY 
		 EXPORT Reset_Handler 
   
Reset_Handler   
		 MOV R0, #7  ; R0 is xx, the base
		 MOV R1, #3  ; R1 is yy, the exponent
	         BL Power    ; Call the subroutine to calculate xx^yy
                 B End       ; The result is now in R0, can be used as needed
		 
; Subroutine to calculate power
; R0 = base, R1 = exponent, R2 = result
Power
		 MOV R2, #1  ; Initialize result to 1
		 CMP R1, #0  ; Compare exponent with 0
		 BEQ Return  ; If exponent is 0, return result as 1

PowerLoop
		 CMP R1, #0  ; Check if exponent is 0
		 BEQ Return  ; If yes, end loop
		 MUL R2, R2, R0 ; Multiply result with base
		 SUB R1, R1, #1 ; Decrement exponent
		 B PowerLoop  ; Repeat loop

Return
		 MOV R0, R2  ; Move result back to R0
		 BX LR       ; Return from subroutine

End
		 END
