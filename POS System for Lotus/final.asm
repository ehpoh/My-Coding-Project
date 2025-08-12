TITLE ASSIGNMENT  ; Subtotal = (Item1 Price * Quantity) + (Item2 Price * Quantity) + ... + (ItemN Price * Quantity)

.MODEL SMALL
.STACK 64
.DATA
	;LOGIN OR GUEST MESSAGE
	PROMPT_HEADER DB "PLEASE SELECT [1] LOGIN , [2] GUEST OR [3] NET SALES >> $"

	SAMPLE_SEP  DB "			+-----------------------------+", 0AH, 0DH, '$'		;TEACHER SAMPLE INPUT
	SAMPLE      DB "			| YOUR ID  >> HANDSOME LIANG  |", 0AH, 0DH, '$'
	SAMPLE1     DB "			| PASSWORD >> ITSYL123        |", 0AH, 0DH, '$'
	SAMPLE_SEP1 DB "			+-----------------------------+", 0AH, 0DH, '$'

	;LOGIN INPUT MESSAGE
	LOGIN_ID DB "ENTER YOUR ID  >> $"
	LOGIN_PS DB "ENTER PASSWORD >> $"
	
	BUFFER_ID DB 20
	          DB ?
	          DB 20 DUP('$')					;INPUT SIZE
	BUFFER_PS DB 20
		  DB ?
		  DB 20 DUP('$')					;INPUT SIZE

	;VALIDATE
	VALID_ID          DB '1', '$'
	VALID_PS    	  DB '1', '$'
	INVALID_MSG       DB 'Invalid ID or Password. Please try again.', 0AH, 0DH, '$'

	;LOGIN SUCCESS MESSAGE
	SUCCESS DB "LOGIN SUCCESSFULLY!", 0AH, 0DH, '$'

	MENU_SEP       DB "			+=================+================+", 0AH, 0DH, '$'		;DECLARE MENU
	MENU_HEADER    DB "			|      ITEMS      | UNIT PRICE(RM) |", 0AH, 0DH, '$'			
	MENU_SEP2      DB "			|=================+================|", 0AH, 0DH, '$'
	MENU_1	       DB "			|  [1]TABLET      |     100.00     |", 0AH, 0DH, '$'
	MENU_2	       DB "			|  [2]SMARTWATCH  |     200.00     |", 0AH, 0DH, '$'
	MENU_3	       DB "			|  [3]TELEVISION  |     200.00     |", 0AH, 0DH, '$'
	MENU_4	       DB "			|  [4]POWER BANK  |     100.00     |", 0AH, 0DH, '$'
	MENU_SEP3      DB "			+=================+================+", 0AH, 0DH, '$'

	PROMPT_ITEM DB "ENTER A ITEM(1-4) >> $"				;ENTER ITEM
	PROMPT_QUANTITY DB "ENTER QUANTITY >> $"			;ENTER QUANTITY
	PROMPT_CONTINUE DB "CONTINUE(Y/N) >> $"				;ENTER CONDITION
	PROMPT_SUBTOTAL DB "SUBTOTAL >> RM $"				;SHOW SUBTOTAL
	PROMPT_ORDER_COUNT DB "ORDER $"					;SHOW ORDER COUNT
	TAX_PERCENTAGE_MSG DB "Tax Percentage: 10% $"
	PROMPT_TAX         DB 	"AFTER TAX >> RM $", 0AH, 0DH, '$'
	PROMPT_TOTAL       DB 	"TOTAL >> RM $", 0AH, 0DH, '$'
	PROMPT_DISCOUNT	DB	"DISCOUNT >> RM $", 0AH, 0DH, '$'
	PROMPT_DISCOUNT_TOTAL	DB	"DISCOUNT_TOTAL >> RM $", 0AH, 0DH, '$'
	DISCOUNT_PERCENTAGE_MSG DB "DISCOUNT Percentage: 10% $"

    	CRLF DB 0AH, 0DH, '$'           				;CARRIAGE RETURN AND LINE FEED

	;ERROR MESSAGE
	ITEM_ERROR_MSG DB "INVALID ITEM CHOICE! PLEASE ENTER A NUMBER BETWEEN 1 AND 4.", 0AH, 0DH, '$'
	QUANTITY_ERROR_MSG DB "INVALID QUANTITY! PLEASE ENTER A DIGIT.", 0AH, 0DH, '$'
	ITEM_CHECK_ERROR_MSG DB "INVALID ITEM CHOICE! PLEASE RE-ENTER AGAIN.", 0AH, 0DH, '$'
	CONDITION_ERROR_MSG DB "INVALID INPUT! PLEASE ENTER 'Y' OR 'N'.", 0AH, 0DH, '$'
	CONT_ERROR_MSG DB "INVALID INPUT! PLEASE ENTER [1] , [2] OR [3].", 0AH, 0DH, '$'

	;PLACE TO STORE INPUT
	ITEMCHOICE DB 0                 				;STORE ITEM CHOICE
    	QUANTITY DB 0                    				;STORE QUANTITY
    	TOTAL DW 0                       				;STORE TOTAL PRICE
    	SUBTOTAL DW 0                    				;STORE SUBTOTAL
    	ORDER_COUNT DW 0						;STORE ORDER COUNT
	DISCOUNT_TOTAL	DW	0
	DISCOUNT0	DW	0
	TAX                 DW 	0                        ; Store calculated tax
    	TOTAL_WITH_TAX      DW 	0                        ; Store total after adding tax
	CONT DB 0		;CONDITION

	;NET SALES
		Gross_Sales 		DB		"Enter Gross Sales:",'$'
	Returns 	DB		"Enter Returns: $"
	Allowances	DB		"Enter Allowances:$"
	Discount	DB		"Enter Discount:$"
	Net_Sales	DB		"Net Sales =",'$'
	INVALID1	DB		"Invalid.Please Re-enter again.$"
	Choose		DB		"Please Enter 1 if you want to continue,2 if you want to end the calculation:$"
	Choice			DB		?
	Gross_Sales1		DB		?
 	Gross_Sales2		DB		?
	Gross_Sales3		DB		?
	Gross_Sales4		DB		?
	Returns1		DB		?
	Returns2		DB		?
	Returns3		DB		?
	Returns4		DB		?
	Allowances1		DB		?
	Allowances2		DB		?
	Allowances3		DB		?
 	Allowances4		DB		?
	Discount1		DB		?
	Discount2		DB		?
	Discount3		DB		?
	Discount4		DB		?
	Result1		DB		?
	Result2		DB		?
	Result3		DB		?
	Result4		DB		?
	SPACE1		DB		' '
	SPACE2		DB		' '
	SPACE3		DB		' '
	SPACE4		DB		' '
	Gross_Sales_SPACE1   	DB		' '
	Gross_Sales_SPACE2   	DB		' '
	Gross_Sales_SPACE3   	DB		' '
	Gross_Sales_SPACE4   	DB		' '
	Returns_SPACE1   	DB		' '
	Returns_SPACE2   	DB		' '
	Returns_SPACE3   	DB		' '
	Returns_SPACE4   	DB		' '
	Allowances_SPACE1   	DB		' '
	Allowances_SPACE2   	DB		' '
	Allowances_SPACE3   	DB		' '
	Allowances_SPACE4   	DB		' '
	Discount_SPACE1   	DB		' '
	Discount_SPACE2   	DB		' '
	Discount_SPACE3   	DB		' '
	Discount_SPACE4   	DB		' '
	D1			DB		?
	D2			DB		?
	RESULTE			DB		?
	RESULTF			DB		?
	RESULTG			DB		?


;----------------------------------------------------------------------------------------------------------------------------------------------------------------------
.CODE
	MAIN PROC FAR
	
	MOV AX, @DATA
	MOV DS, AX

START:
	MOV SUBTOTAL, 0							;INITIALISE SUBTOTAL WITH 0
    	MOV ORDER_COUNT, 0						;INITIALISE ORDER COUNT WITH 0

	CALL SELECTION							;CALL LOGIN UI

CONTINUE_LOOP:								;ORDERING LOOP
	MOV AH, 09H
	LEA DX, PROMPT_ITEM						
	INT 21H								;DISPLAY ITEM MESSAGE

	MOV AH, 01H
	INT 21H								;REQUEST INPUT
	SUB AL, 48							;INITIALISE AL WITH 0, CONVERT FROM ASCII
	MOV ITEMCHOICE, AL						;MOVE THE INPUT INTO ITEMCHOICE

	MOV AH, 09H
	LEA DX, CRLF
	INT 21H								;CARRIAGE RETURN AND LINE FEED

	;CHECK IF INPUT EQUAL TO 1
	MOV AL, ITEMCHOICE
	CMP AL, 1
	JL INVALID_ITEM							;IF AL LESS THAN 1 JMP TO INVALID_ITEM
	CMP AL, 4
	JG INVALID_ITEM							;IF AL GREATER THAN 4 JMP TO INVALID_ITEM

VALID_ITEM:
	JMP QUANTITY_LOOP						;IF VALID JMP TO QUANTITY_LOOP

INVALID_ITEM:
	MOV AH, 09H
	LEA DX, ITEM_ERROR_MSG
	INT 21H								;PROMPT ERROR MESSAGE
	LEA DX, CRLF
	INT 21H								;CARRIAGE RETURN AND LINE FEED
	JMP CONTINUE_LOOP						;JMP TO CONTINUE_LOOP TO RE-ENTER

QUANTITY_LOOP:
	MOV AH, 09H
	LEA DX, PROMPT_QUANTITY
	INT 21H								;DISPLAY QUANTITY MESSAGE

	MOV AH, 01H
	INT 21H								;REQUEST INPUT

	MOV AH, 09H
	LEA DX, CRLF
	INT 21H								;CARRIAGE RETURN AND LINE FEED

	;CHECK IF BELOW '0' OR ABOVE '9'
	CMP AL, '0'
	JB INVALID_QUANTITY         					;JMP IF BELOW '0'
    	CMP AL, '9'
    	JA INVALID_QUANTITY         					;JMP IF ABOVE '9'
	CMP AL, 30H
	JLE INVALID_QUANTITY_LESS_THAN_EQUAL_0				;JMP IF LESS THAN EQUAL 0, 30H = 0
	CMP AL, 31H
	JGE QUANTITY_LOOP2						;JMP IF GREATER THAN EQUAL 1, 31H = 1

QUANTITY_LOOP2:
	SUB AL, 48                					;CONVERT TO ASCII INTEGER
    	MOV QUANTITY, AL          					;MOV INTO QUANTITY
    	JMP ITEM_CHECK       						;JMP TO ITEM CHECK

INVALID_QUANTITY:
    	MOV AH, 09H
    	LEA DX, QUANTITY_ERROR_MSG					
    	INT 21H								;PROMPT ERROR MESSAGE
	LEA DX, CRLF
	INT 21H								;CARRIAGE RETURN AND LINE FEED
    	JMP QUANTITY_LOOP     						;JMP BACK TO RE-ENTER AGAIN

INVALID_QUANTITY_LESS_THAN_EQUAL_0:
	SUB AL, 48							;CLEAR AL WITH 0, CONVERT FROM ASCII

	MOV AH, 09H
	LEA DX, QUANTITY_ERROR_MSG
	INT 21H								;PROMPT ERROR MESSAGE
	LEA DX, CRLF
	INT 21H								;CARRIAGE RETURN AND LINE FEED
	JMP QUANTITY_LOOP						;JMP BACK TO QUANTITY_LOOP RE-ENTER

ITEM_CHECK:
    	MOV AL, 0                 					;CLEAR AL FOR USE
    	MOV BL, ITEMCHOICE        					;MOV ITEMCHOICE INTO BL
    	
	CMP BL, 1
	JNE ITEM_CHECK2							;IF NOT ITEM 1 JMP TO ITEM CHECK 2
	JE ITEM_1							;IF ITEM 1 JMP TO ITEM_1

ITEM_CHECK2:
	CMP BL, 2
	JNE ITEM_CHECK3							;IF NOT ITEM 2 JMP TO ITEM CHECK 3
	JE ITEM_2							;IF ITEM 2 JMP TO ITEM_2

ITEM_CHECK3:
	CMP BL, 3
	JNE ITEM_CHECK4							;IF NOT ITEM 3 JMP TO ITEM CHECK 4
	JE ITEM_3							;IF ITEM 3 JMP TO ITEM_3

ITEM_CHECK4:
	CMP BL, 4
	JNE ITEM_CHECK5							;IF NOT ITEM 4 JMP TO ITEM CHECK 5
	JE ITEM_4							;IF ITEM 4 JMP TO ITEM_4

ITEM_CHECK5:
	MOV AH, 09H
	LEA DX, CRLF
	INT 21H								;CARRIAGE RETURN AND LINE FEED
	
	CALL DISPLAY_MENU						;CALL MENU
	
	MOV AH, 09H
	LEA DX, CRLF
	INT 21H								;CARRIAGE RETURN AND LINE FEED
	LEA DX, ITEM_CHECK_ERROR_MSG
	INT 21H								;PROMPT ERROR MESSAGE
	LEA DX, CRLF
	INT 21H								;CARRIAGE RETURN AND LINE FEED
	JMP CONTINUE_LOOP						;JMP TO CONTINUE_LOOP TO RE-ENTER

ITEM_1:									;MOV 100 INTO AL THEN JMP TO CALCULATE_TOTAL
	MOV AL, 100
	JMP CALCULATE_TOTAL

ITEM_2:									;MOV 200 INTO AL, THEN JMP TO CALCULATE_TOTAL
	MOV AL, 200
	JMP CALCULATE_TOTAL

ITEM_3:									;MOV 200 INTO AL, THEN JMP TO CALCULATE_TOTAL
	MOV AL, 200
	JMP CALCULATE_TOTAL

ITEM_4:									;MOV 100 INTO AL, THEN JMP TO CALCULATE_TOTAL
	MOV AL, 100
	JMP CALCULATE_TOTAL

CALCULATE_TOTAL:
	MOV BL, QUANTITY						;MOV QUANTITY INTO BL
    	MOV AH, 0							;CLEAR AH
    	MUL BL                  					;AL = PRICE * QUANTITY (STORE RESULT IN AX)
    	ADD SUBTOTAL, AX       						;ADD RESULT TO SUBTOTAL

    	MOV AH, 09H
	LEA DX, CRLF
	INT 21H								;CARRIAGE RETURN AND LINE FEED
    	LEA DX, PROMPT_SUBTOTAL
    	INT 21H								;DISPLAY SUBTOTAL MESSAGE
    	
	MOV AX, SUBTOTAL						;MOV SUBTOTAL RESULT INTO AX TO DISPLAY
    	CALL DISPLAY_NUMBER						;CALL DISPLAY_NUMBER

CONTINUE_ORDER_LOOP:
    	MOV AH, 09H
	LEA DX, CRLF
	INT 21H								;CARRIAGE RETURN AND LINE FEED
    	LEA DX, PROMPT_CONTINUE
    	INT 21H								;DISPLAY CONTINUE MESSAGE

    	MOV AH, 01H
    	INT 21H								;REQUEST INPUT
    	
	CMP AL, 'Y'
	JNE CONDITION_CHECK2						;IF NOT 'Y', JMP TO CONDITION_CHECK 2
    	JE CONTINUE_ORDER						;IF CONDITION = 'Y', JMP TO CONTINUE_ORDER
	
CONDITION_CHECK2:
	CMP AL, 'y'
	JNE CONDITION_CHECK3						;IF NOT 'y', JMP TO CONDITION_CHECK 3
	JE CONTINUE_ORDER						;IF CONDITION = 'y', JMP TO CONTINUE_ORDER
    	
CONDITION_CHECK3:	
	CMP AL, 'N'
    	JNE CONDITION_CHECK4						;IF NOT 'N', JMP TO CONDITION_CHECK 4
	JMP TAX_CALCULATION						;IF CONDITION = 'N', JMP TO TAX_CALCULATION
	
CONDITION_CHECK4:
	CMP AL, 'n'
	JNE SHORT_JUMP_TO_INVALID					; If not 'n', short jump to INVALID_CONDITION
	JMP TAX_CALCULATION						; If 'n', long jump to INPUT_TAX

SHORT_JUMP_TO_INVALID:
	JMP INVALID_CONDITION						; Long jump to INVALID_CONDITION
	

CONTINUE_ORDER:
	MOV AH, 09H
	LEA DX, CRLF
	INT 21H								;CARRIAGE RETURN AND LINE FEED
	LEA DX, CRLF
	INT 21H								;CARRIAGE RETURN AND LINE FEED
	
	CALL DISPLAY_MENU						;CALL MENU
	
	JMP CONTINUE_LOOP						;JMP BACK TO CONTINUE_LOOP
	

	


INVALID_CONDITION:
	MOV AH, 09H
	LEA DX, CRLF
	INT 21H								;CARRIAGE RETURN AND LINE FEED
	LEA DX, CONDITION_ERROR_MSG
	INT 21H								;PROMPT ERROR MESSAGE
	
	JMP CONTINUE_ORDER_LOOP						;JMP BACK TO RE-ENTER CONDITION

END_PROGRAM:
	MOV AX, 4C00H
	INT 21H								;END PROGRAM

;----------------------------------------------------------------------------------------------------------------------------------------------------------------------

SELECTION PROC

	CALL CLS		;CLEAR SCREEN

	SUB AL, 48		;CLEAR AL

SELECTION1:
	MOV AH, 09H
	LEA DX, PROMPT_HEADER
	INT 21H			;PROMPT HEADER MESSAGE

	MOV AH, 01H
	INT 21H			;REQUEST INPUT
	SUB AL, 48		;CONVERT FROM ASCII
	MOV CONT, AL		;MOV TO CONT

	CMP AL, 1
	JNE CHECK_CONT1		;IF NOT 1 JMP TO CHECK_CONT1
	JMP LOGIN_UI		;IF 1 CALL LOGIN_UI

CHECK_CONT1:

	CMP AL, 2
	JNE CHECK_CONT2		;IF NOT JMP CHECK_CONT2		
	JMP DISPLAY_MENU	;IF 2 JMP DISPALY MENU

CHECK_CONT2:
	
	CMP AL, 3
	JNE INVALID_CONT	;IF NOT JMP INVALID CONT
	JMP LOOP1		;IF JMP LOOP1

INVALID_CONT:
	
	MOV AH, 09H
	LEA DX, CRLF
	INT 21H			;CRLF
	LEA DX, CONT_ERROR_MSG
	INT 21H			;PROMPT ERROR MESSAGE
	LEA DX, CRLF
	INT 21H			;CRLF
	JMP SELECTION1

	RET
SELECTION ENDP

;----------------------------------------------------------------------------------------------------------------------------------------------------------------------

LOOP1:
 	MOV AH,09H			;MOV AH 09H=DISPLAY STRING
	LEA DX, CRLF
	INT 21H
	
	CALL CLS

	MOV AH, 09H
	LEA DX,Gross_Sales		;load effective address=find address of "Gross_Sales" variable 
	INT 21H

	MOV AH, 01H         		; Function to read character input
	INT 21H
	MOV Gross_Sales_SPACE1,AL	; Store input value
	SUB AL,30H			;if enter 1,store become 31H
	MOV Gross_Sales1, AL		; Store input value

	MOV AL,Gross_Sales_SPACE1
	CMP AL,0DH
        JE MIDDLE1			;IF SPACE,INVALID

		
	MOV AL,Gross_Sales1
	CMP AL,9
	JG MIDDLE1			;IF GREATER THAN 9,INVALID

	CMP AL,0
	JL MIDDLE1			;IF LESS THAN 0,INVALID

	MOV AH, 01H         		; Function to read character input
	INT 21H
	MOV Gross_Sales_SPACE2,AL	; Store input value
	SUB AL,30H			;if enter 1,store become 31H
	MOV Gross_Sales2, AL		; Store input value
	
	MOV AL,Gross_Sales_SPACE2
	CMP AL,0DH
        JE DIGIT11			;IF SPACE,INVALID

		
	MOV AL,Gross_Sales2
	CMP AL,9
	JG MIDDLE1

	CMP AL,0
	JL MIDDLE1


	MOV AH, 01H         		; Function to read character input
	INT 21H
	MOV Gross_Sales_SPACE3,AL
	SUB AL,30H			;if enter 1,store become 31H
	MOV Gross_Sales3, AL		; Store input value
	
	MOV AL,Gross_Sales_SPACE3
	CMP AL,0DH
        JE DIGIT21

		
	MOV AL,Gross_Sales3
	CMP AL,9
	JG MIDDLE1

	CMP AL,0
	JL MIDDLE1


	MOV AH, 01H         		; Function to read character input
	INT 21H
	MOV Gross_Sales_SPACE4,AL
	SUB AL,30H			;if enter 1,store become 31H
	MOV Gross_Sales4, AL			; Store input value

	MOV AL,Gross_Sales_SPACE4
	CMP AL,0DH
        JE DIGIT31

		
	MOV AL,Gross_Sales4
	CMP AL,9
	JG MIDDLE1

	CMP AL,0
	JL MIDDLE1
	JMP CONTINUE1
MIDDLE1:
	JMP INVALID

DIGIT11:
	JMP DIGIT1_CONTINUE1 

DIGIT21:
	JMP DIGIT2_CONTINUE1

DIGIT31:
	JMP DIGIT3_CONTINUE1
CONTINUE1:

DIGIT1_CONTINUE1:
DIGIT2_CONTINUE1:
DIGIT3_CONTINUE1:

	MOV AH,02H
	MOV DL,0AH			;NEW LINE
	INT 21H
	MOV DL,0DH
	INT 21H
	        		
	MOV AH,09H			;MOV AH 09H=DISPLAY STRING
	LEA DX,Returns 		;load effective address=find address of "Returns" variable
	INT 21H

	MOV AH, 01H         		; Function to read character input
	INT 21H
	MOV RETURNS_SPACE1,AL
	SUB AL,30H			;if enter 1,store become 31H
	MOV Returns1, AL			; Store input value

	MOV AL,Returns_SPACE1
	CMP AL,0DH
        JE MIDDLE2

		
	MOV AL,Returns1
	CMP AL,9
	JG MIDDLE2

	CMP AL,0
	JL MIDDLE2

	MOV AH, 01H         		; Function to read character input
	INT 21H
	MOV RETURNS_SPACE2,AL
	SUB AL,30H			;if enter 1,store become 31H
	MOV Returns2, AL       		; Store input value

	MOV AL,Returns_SPACE2
	CMP AL,0DH
        JE DIGIT12

		
	MOV AL,Returns2
	CMP AL,9
	JG MIDDLE2

	CMP AL,0
	JL MIDDLE2

	MOV AH, 01H         		; Function to read character input
	INT 21H
	MOV RETURNS_SPACE3,AL
	SUB AL,30H			;if enter 1,store become 31H
	MOV Returns3, AL			; Store input value
 	
	MOV AL,Returns_SPACE3
	CMP AL,0DH
        JE DIGIT22

		
	MOV AL,Returns3
	CMP AL,9
	JG MIDDLE2

	CMP AL,0
	JL MIDDLE2

	MOV AH, 01H         		; Function to read character input
	INT 21H
	MOV RETURNS_SPACE4,AL
	SUB AL,30H			;if enter 1,store become 31H
	MOV Returns4, AL			; Store input value
	
	MOV AL,Returns_SPACE4
	CMP AL,0DH
        JE DIGIT32

		
	MOV AL,Returns4
	CMP AL,9
	JG MIDDLE2

	CMP AL,0
	JL MIDDLE2
	JMP CONTINUE2

MIDDLE2:
	JMP INVALID

DIGIT12:
	JMP DIGIT1_CONTINUE2

DIGIT22:
	JMP DIGIT2_CONTINUE2

DIGIT32:
	JMP DIGIT3_CONTINUE2

CONTINUE2:
 
DIGIT1_CONTINUE2:
DIGIT2_CONTINUE2:
DIGIT3_CONTINUE2:

	MOV AH,02H
	MOV DL,0AH			;NEW LINE
	INT 21H
	MOV DL,0DH
	INT 21H

MOV AH,09H			;MOV AH 09H=DISPLAY STRING
	LEA DX,Allowances 		;load effective address=find address of "Allowances" variable
	INT 21H

	MOV AH, 01H         		; Function to read character input
	INT 21H
	MOV Allowances_SPACE1,AL
	SUB AL,30H			;if enter 1,store become 31H
	MOV Allowances1, AL			; Store input value

	MOV AL,Allowances_SPACE1
	CMP AL,0DH
        JE MIDDLE3

		
	MOV AL,Allowances1
	CMP AL,9
	JG MIDDLE3

	CMP AL,0
	JL MIDDLE3

	MOV AH, 01H         		; Function to read character input
	INT 21H
	MOV Allowances_SPACE2,AL
	SUB AL,30H			;if enter 1,store become 31H
	MOV Allowances2, AL       		; Store input value
	
	MOV AL,Allowances_SPACE2
	CMP AL,0DH
        JE DIGIT13

		
	MOV AL,Allowances2
	CMP AL,9
	JG MIDDLE3

	CMP AL,0
	JL MIDDLE3

	MOV AH, 01H         		; Function to read character input
	INT 21H
	MOV Allowances_SPACE3,AL
	SUB AL,30H			;if enter 1,store become 31H
	MOV AllowanceS3, AL			; Store input value
 
	MOV AL,Allowances_SPACE3
	CMP AL,0DH
        JE DIGIT23

		
	MOV AL,Allowances3
	CMP AL,9
	JG MIDDLE3

	CMP AL,0
	JL MIDDLE3

 	
	MOV AH, 01H         		; Function to read character input
	INT 21H
	MOV Allowances_SPACE4,AL
	SUB AL,30H			;if enter 1,store become 31H
	MOV Allowances4, AL			; Store input value
	
	MOV AL,Allowances_SPACE4
	CMP AL,0DH
        JE DIGIT33

		
	MOV AL,Allowances4
	CMP AL,9
	JG MIDDLE3

	CMP AL,0
	JL MIDDLE3
	JMP CONTINUE3
	
MIDDLE3:
	JMP INVALID

DIGIT13:
	JMP DIGIT1_CONTINUE3

DIGIT23:
	JMP DIGIT2_CONTINUE3

DIGIT33:
	JMP DIGIT3_CONTINUE3

CONTINUE3:
DIGIT1_CONTINUE3:
DIGIT2_CONTINUE3:
DIGIT3_CONTINUE3:

	MOV AH,02H
	MOV DL,0AH			;NEW LINE
	INT 21H
	MOV DL,0DH
	INT 21H

MOV AH,09H			;MOV AH 09H=DISPLAY STRING
	LEA DX,Discount 		;load effective address=find address of "Discount" variable
	INT 21H

	MOV AH, 01H         		; Function to read character input
	INT 21H
	MOV Discount_SPACE1,AL
	SUB AL,30H			;if enter 1,store become 31H
	MOV Discount1, AL			; Store input value

 	MOV AL,Discount_SPACE1
	CMP AL,0DH
        JE MIDDLE4	

	MOV AL,Discount1
	CMP AL,9
	JG MIDDLE4

	CMP AL,0
	JL MIDDLE4

	MOV AH, 01H         		; Function to read character input
	INT 21H
	MOV Discount_SPACE2,AL
	SUB AL,30H			;if enter 1,store become 31H
	MOV Discount2, AL       		; Store input value
 
	MOV AL,Discount_SPACE2
	CMP AL,0DH
        JE DIGIT14	

	MOV AL,Discount2
	CMP AL,9
	JG MIDDLE4

	CMP AL,0
	JL MIDDLE4

	MOV AH, 01H         		; Function to read character input
	INT 21H
	MOV Discount_SPACE3,AL
	SUB AL,30H			;if enter 1,store become 31H
	MOV Discount3, AL			; Store input value

	MOV AL,Discount_SPACE3
	CMP AL,0DH
        JE DIGIT24	

	MOV AL,Discount3
	CMP AL,9
	JG MIDDLE4

	CMP AL,0
	JL MIDDLE4

 	MOV AH, 01H         		; Function to read character input
	INT 21H
	MOV Discount_SPACE4,AL
	SUB AL,30H			;if enter 1,store become 31H
	MOV Discount4, AL			; Store input value
       	
	MOV AL,Discount_SPACE4
	CMP AL,0DH
        JE DIGIT34	

	MOV AL,Discount4
	CMP AL,9
	JG MIDDLE4

	CMP AL,0
	JL MIDDLE4
	JMP CONTINUE4
MIDDLE4:
	JMP INVALID

DIGIT14:
	JMP ONE_DIGIT

DIGIT24:
	JMP TWO_DIGIT

DIGIT34:
	JMP THREE_DIGIT

CONTINUE4:
	MOV AH,02H
	MOV DL,0AH			;NEW LINE
	INT 21H
	MOV DL,0DH
	INT 21H
	JMP DIGIT4


	MOV AL,Gross_Sales1
	SUB AL,Returns1
	SUB AL,Allowances1
	SUB AL,Discount1
 	MOV Result1,AL

	MOV AL,Gross_Sales2
	SUB AL,Returns2
	SUB AL,Allowances2
	SUB AL,Discount2
 	MOV Result2,AL
			 
	MOV AL,Gross_Sales3
	SUB AL,Returns3
	SUB AL,Allowances3
	SUB AL,Discount3
 	MOV Result3,AL
 	 
	MOV AL,Gross_Sales4
	SUB AL,Returns4
	SUB AL,Allowances4
	SUB AL,Discount4
 	MOV Result4,AL
	
	MOV AL, Result1
	ADD AL,30H
    	MOV DL, AL
    	MOV AH, 02H
    	INT 21H


	MOV AL, Result2
	ADD AL,30H
    	MOV DL, AL
    	MOV AH, 02H
    	INT 21H

	MOV AL, Result3
	ADD AL,30H
    	MOV DL, AL
    	MOV AH, 02H
    	INT 21H

	MOV AL, Result4
	ADD AL,30H
    	MOV DL, AL
    	MOV AH, 02H
    	INT 21H

	JMP END_PROGRAM

ONE_DIGIT:
	
	MOV AH,09H			;MOV AH 09H=DISPLAY STRING
	LEA DX,Net_Sales 		;load effective address=find address of "Net_Sales" variable
	INT 21H


	MOV AL,Gross_Sales1
	SUB AL,Returns1
	SUB AL,Allowances1
	SUB AL,Discount1
 	MOV Result1,AL

	MOV AL, Result1
	ADD AL,30H
    	MOV DL, AL
    	MOV AH, 02H
    	INT 21H

 	JMP END_PROGRAM


TWO_DIGIT:				;CALCULATE TWO DIGIT WITH TWO DIGIT
	
	MOV AH,09H			;MOV AH 09H=DISPLAY STRING
	LEA DX,Net_Sales 		;load effective address=find address of my 	"message" variable
	INT 21H

	MOV AL,Gross_Sales1		;STORE Gross_Sales1 		 
	SUB AL,Returns1			;Gross_Sales1_Returns1=Gross_Sales1-Returns1
	SUB AL,Allowances1		;Gross_Sales1-Returns1-Allowances1=Gross_Sales1_Returns1-Allowances1
	MOV AH,AL			;STORE RESULT OF Gross_Sales1-Returns1-Allowances1,AH IS FIRST DIGIT 
	
	MOV AL,Gross_Sales2		;STORE Gross_Sales2 
	SUB AL,Returns2			;Gross_Sales2_Returns2=Gross_Sales2-Returns2
	SUB AL,Allowances2		;Gross_Sales2-Returns2-Allowances2=Gross_Sales2_Returns2-Allowances2
	MOV BL,AL			;STORE RESULT OF Gross_Sales2-Returns2-Allowances2,BL IS SECOND DIGIT
	
	CMP Discount2, BL 		;COMPARED FOR Discount2 AND BL  
    	JB BORROW1       		;JUMP TO BORROW1 WHEN DISCOUNT2 < BL
	JMP CONTINUE5			;JUMP TO CONTINUE5 IF DISCOUNT2 >= BL,SO AS TO SKIP THE DISCOUNT2 < BL PROCESS


BORROW1:
	CMP Discount1, AH 		;COMPARED FOR Discount1 AND AH  
    	JB BORROW2       ;		;JUMP TO BORROW2 WHEN Discount1 < AH

BORROW2:
	JMP CONTINUE6			;DIRECTLY JUMP TO CONTINUE 6 IF DISCOUNT2 < BL AND Discount1 < AH

CONTINUE5:				
	CMP  Discount2,BL		;COMPARED FOR Discount2 AND BL
    	JG BORROW3       ;  		;UMP TO BORROW2 WHEN Discount2 > BL
	JMP CONTINUE7			;JUMP TO CONTINUE7 IF DISCOUNT2 <= BL,SO AS TO SKIP THE DISCOUNT2 > BL PROCESS

BORROW3: 				 
    	DEC AH          		; Decrease the AH digit
    	ADD BL, 10 			; Increase BL by 10

CONTINUE6:

CONTINUE7:
	MOV Result1,AH			;MOVE RESULT OF Gross_Sales1-Returns1-Allowances1 AFTER BORROW INTO AL SO AS TO CALCULATE RESULT 1
	MOV AL,Result1
	SUB AL,Discount1
 	MOV Result1,AL

	MOV AL,BL			;MOVE RESULT OF Gross_Sales2-Returns2-Allowances2 AFTER BORROW INTO AL SO AS TO CALCULATE RESULT 2
	SUB AL,Discount2		;MINUS WITH DISCOUNT2
 	MOV Result2,AL			;STORE THE RESULT OF OPERATION AFTER BORROW INTO Result2 

	MOV AL, Result1			;MOVE RESULT1 INTO AL
	ADD AL,30H			;adding 30H converts number to its corresponding ASCII character.
    	MOV DL, AL			;MOV AL TO DL
    	MOV AH, 02H			;FUNCTION OF DISPLAY CHARACTER
    	INT 21H				;Carry out the operation

	MOV AL, Result2			;MOVE RESULT2 INTO AL
	ADD AL,30H			;adding 30H converts number to its corresponding ASCII character.
    	MOV DL, AL			;MOV AL TO DL
    	MOV AH, 02H			;FUNCTION OF DISPLAY CHARACTER
    	INT 21H				;Carry out the operation
	JMP END_PROGRAM			;JUMP TO END PROGRAM

THREE_DIGIT:				;CALCULATE THREE DIGIT WITH THREE DIGIT
	
	MOV AH,09H			;MOV AH 09H=DISPLAY STRING
	LEA DX,Net_Sales 		;load effective address=find address of "Net_Sales" variable
	INT 21H				

	MOV AL,Gross_Sales1		;STORE Gross_Sales1 		 
	SUB AL,Returns1			;Gross_Sales1_Returns1=Gross_Sales1-Returns1
	SUB AL,Allowances1		;Gross_Sales1-Returns1-Allowances1=Gross_Sales1_Returns1-Allowances1
	MOV AH,AL			;STORE RESULT OF Gross_Sales1-Returns1-Allowances1,AH IS FIRST DIGIT 
	
	MOV AL,Gross_Sales2		;STORE Gross_Sales2 
	SUB AL,Returns2			;Gross_Sales2_Returns2=Gross_Sales2-Returns2
	SUB AL,Allowances2		;Gross_Sales2-Returns2-Allowances2=Gross_Sales2_Returns2-Allowances2
	MOV BL,AL			;STORE RESULT OF Gross_Sales2-Returns2-Allowances2,BL IS SECOND DIGIT
	 
	MOV AL,Gross_Sales3		;STORE Gross_Sales3 
	SUB AL,Returns3			;Gross_Sales3_Returns3=Gross_Sales3-Returns3
	SUB AL,Allowances3		;Gross_Sales3-Returns3-Allowances3=Gross_Sales3_Returns3-Allowances3
	MOV CL,AL		 	;STORE RESULT OF Gross_Sales3-Returns3-Allowances3,CL IS THIRD DIGIT

	CMP CL, Discount3		;COMPARED CL AND DISCOUNT 3
    	JE BORROW41 			;JUMP TO BORROW41

	CMP CL, Discount3
    	JB BORROW4       		; If CL  < Discount3,go to borrow,FOR THE CASE BL < Discount2
	JMP CONTINUE9
	 


BORROW41:
      	CMP BL, Discount2		;COMPARED BL AND Discount2
    	JB BORROW412 			;JUMP TO BORROW412 IF BL<Discount2
BORROW412:
	CMP AH, Discount1		;COMPARED AH AND Discount1
    	JB BORROW4121			;JUMP TO BORROW4121 IF BL<Discount2
BORROW4121:
	DEC AH          		; Decrease AH BY 1
    	ADD BL, 10 			; Increase BL by 10
	JMP CONTINUE9			;JUMP TO CONTINUE 9 AFTER FINISH BORROW OPERATION

BORROW4:
	CMP BL, Discount2		;COMPARED BL AND Discount2
    	JB BORROW13			;JUMP TO  BORROW13 IF BL < Discount2

	CMP BL, Discount2		;COMPARED BL AND Discount2
    	JG BORROW5			;JUMP TO  BORROW5 IF BL > Discount2
BORROW5:
	CMP AH, Discount1		;COMPARED AH AND Discount1
    	JG BORROW6			;JUMP TO  BORROW6 IF AH > Discount1
BORROW6:
	JMP CONTINUE9			;JUMP TO CALCULATE OPERATION

 
	CMP CL, Discount3		;COMPARED CL AND Discount3
    	JB BORROW7        		; If CL < Discount3,go to borrow 

	CMP CL, Discount3
    	JE BORROW7       		; If CL = Discount3,go to borrow 
	
	CMP CL, Discount3
    	JB BORROW8       		; If CL < Discount3,go to borrow 
	CMP CL, Discount3
    	JE BORROW8       		; If CL = Discount3,go to borrow 

BORROW13:
	CMP AH,DISCOUNT1
	JG BORROW130
BORROW130:
	DEC AH          		; Decrease AH
    	ADD BL, 10 			; Increase BL by 10
	DEC BL				;DEC BL BY 1
	ADD CL, 10 			; Increase CL by 10

	JMP CONTINUE9

BORROW7:
	CMP BL, Discount2 		 
    	JG BORROW9			;If BL > Discount2,go to borrow
	CMP BL, Discount2 
    	JE BORROW12			;If BL = Discount2,go to borrow

	CMP BL, Discount2 
    	JB BORROW11       		; If BL < Discount2 , go to borrow

	JMP CONTINUE9			;END OF THE BORROW

BORROW8:
	DEC BL				;DEC BL BY 1
	ADD CL, 10 			; Increase CL by 10
	
	JMP CONTINUE9			;END OF THE BORROW

BORROW9:
 	DEC BL				;DEC BL BY 1
	ADD CL, 10 			; Increase CL by 10
	
	JMP CONTINUE9			;END OF THE BORROW
BORROW11:
	CMP AH, Discount1 
    	JB MIDDLE5       		; If AH < Discount1 , INVALID

	CMP AH, Discount1  
    	JG BORROW12       		; If AH > Discount2 , go to borrow

BORROW12:
   	DEC BL				; Decrease BL BY 1
	ADD CL, 10			; Increase CL by 10
    	DEC AH       			; Decrease AH BY 1
    	ADD BL, 10 			; Increase BL by 10
	JMP CONTINUE9

CONTINUE9:
	MOV AL,AH			;STORE THR CHANGE OF AH INTO AL
	SUB AL,Discount1		;AH,THAT IS FIRST DIGIT - Discount1
 	MOV Result1,AL			;STORE THE RESULT OF BORROW FOR FIRST DIGIT

	MOV AL,BL			;STORE THR CHANGE OF BL INTO AL
	SUB AL,Discount2		;BL,THAT IS SECOND DIGIT - Discount2
 	MOV Result2,AL			;STORE THE RESULT OF BORROW FOR SECOND DIGIT


	MOV AL,CL			;STORE THR CHANGE OF CL INTO AL
	SUB AL,Discount3		;AL,THAT IS THIRD DIGIT - Discount3
 	MOV Result3,AL			;STORE THE RESULT OF BORROW FOR THIRD DIGIT

	MOV AL, Result1			;MOVE RESULT1 INTO AL
	ADD AL,30H			;adding 30H converts number to its corresponding ASCII character.
    	MOV DL, AL			;MOV AL TO DL
    	MOV AH, 02H			;FUNCTION OF DISPLAY CHARACTER
    	INT 21H				;Carry out the operation

	MOV AL, Result2			;MOVE RESULT2 INTO AL
	ADD AL,30H			;adding 30H converts number to its corresponding ASCII character.
    	MOV DL, AL			;MOV AL TO DL
    	MOV AH, 02H			;FUNCTION OF DISPLAY CHARACTER
    	INT 21H				;Carry out the operation
	 

	MOV AL, Result3			;MOVE RESULT3 INTO AL
	ADD AL,30H			;adding 30H converts number to its corresponding ASCII character.
    	MOV DL, AL			;MOV AL TO DL
    	MOV AH, 02H			;FUNCTION OF DISPLAY CHARACTER
    	INT 21H				;Carry out the operation
	JMP END_PROGRAM			;JUMP TO END PROGRAM
 
MIDDLE5:
	JMP INVALID			; AS A TRANSFER SECTION SO THAT AS TO AVOID OUT OF RANGE,EVENRUALLU JUMP TO INVALID
 
	

DIGIT4:					;CALCULATE THE FOUR DIGIT
	MOV AH,09H			;MOV AH 09H=DISPLAY STRING
	LEA DX,Net_Sales 		;load effective address=find address of "Net_Sales" variable
	INT 21H				

	MOV AL,Gross_Sales1		;STORE Gross_Sales1 		 
	SUB AL,Returns1			;Gross_Sales1_Returns1=Gross_Sales1-Returns1
	SUB AL,Allowances1		;Gross_Sales1-Returns1-Allowances1=Gross_Sales1_Returns1-Allowances1
	MOV AH,AL			;STORE RESULT OF Gross_Sales1-Returns1-Allowances1,AH IS FIRST DIGIT 
	SUB AL,Discount1
	MOV RESULTE,AL

	MOV AL,Gross_Sales2		;STORE Gross_Sales2 
	SUB AL,Returns2			;Gross_Sales2_Returns2=Gross_Sales2-Returns2
	SUB AL,Allowances2		;Gross_Sales2-Returns2-Allowances2=Gross_Sales2_Returns2-Allowances2
	MOV BL,AL			;STORE RESULT OF Gross_Sales2-Returns2-Allowances2,BL IS SECOND DIGIT
	SUB AL,Discount2
	MOV RESULTF,AL
 	SUB AL,Discount2
	MOV RESULTF,AL	

	MOV AL,Gross_Sales3		;STORE Gross_Sales3 
	SUB AL,Returns3			;Gross_Sales3_Returns3=Gross_Sales3-Returns3
	SUB AL,Allowances3		;Gross_Sales3-Returns3-Allowances3=Gross_Sales3_Returns3-Allowances3
	MOV CL,AL		 	;STORE RESULT OF Gross_Sales3-Returns3-Allowances3,CL IS THIRD DIGIT
	SUB AL,Discount3
	MOV RESULTG,AL

	MOV AL,Gross_Sales4		;STORE Gross_Sales4
	SUB AL,Returns4			;Gross_Sales4_Returns4=Gross_Sales4-Returns4
	SUB AL,Allowances4		;Gross_Sales4-Returns4-Allowances4=Gross_Sales4_Returns4-Allowances4
	MOV DL,AL		 	;STORE RESULT OF Gross_Sales4-Returns4-Allowances4,AH IS FOUR DIGIT		 


	
	CMP DL, Discount4
    	JB borrow16      		; If DL < Discount4 , go to borrow
	CMP DL, Discount4
    	JB borrow98       		; If DL < Discount4 , go to borrow
	CMP DL, Discount4
    	JB borrow99      		; If DL < Discount4 , go to borrow 
	CMP DL,Discount4
	JG borrow35			; If DL > Discount4 , go to borrow 
	JMP CONTINUE11			;JUMP TO THE CALCULATION IF NO BORROW
BORROW35:  
	CMP CL, Discount3
	JG borrow90			;If CL < Discount3 , go to borrow
	CMP RESULTG, 1
	JB borrow36			;If CL < Discount3 , go to borrow
	CMP RESULTG, 0
	JE borrow36 
BORROW90:
	CMP BL,Discount2 
    	JG borrow91 			;If BL > Discount2 , go to borrow
borrow91:
	CMP AH,Discount1 		;If AH > Discount1 , go to borrow
    	JG borrow92
borrow92:
	JMP CONTINUE11			;JUMP TO THE OPERATION AFTER FINSIH THECALCULATION
borrow36:
	 
	CMP CL, Discount3
    	JB borrow37       		; If CL < Discount3 , go to borrow
	CMP CL, Discount3 
    	JE borrow37       		; If CL < Discount3 , go to borrow
    
borrow37:
	CMP BL,Discount2 
    	JB borrow38      		; If BL < Discount2 , go to borrow

	CMP RESULTF, 1 			;RESULTF THAT IS RESULT 2
	JG borrow38			;RESULTF >1,JUMP TO BORROW

BORROW16:  
	CMP RESULTG, 1			;RESULTG THAT IS RESULT 3
	JG borrow22			;RESULTG >1,JUMP TO BORROW
	CMP RESULTG, 1			;RESULTG THAT IS RESULT 3
	JB borrow60			;RESULTG  <1,JUMP TO BORROW
borrow98:

	CMP RESULTE, 2 			;RESULTE THAT IS RESULT 1
    	JB borrow121      		; If BL < Discount2 , go to borroW
	CMP BL,Discount2 
    	JG borrow50      		; If BL > Discount2 , go to borrow

borrow121:
	CMP CL, Discount3
    	JB borrow131       		; If CL < Discount3 , go to borrow
	CMP CL, Discount3 
    	JE borrow131       		; If CL < Discount3 , go to borrow

borrow38: 
	CMP BL, Discount2 
    	JB borrow39     		 ; If BL < Discount2 , go to borrow
	CMP BL, Discount2 		
    	JE borrow39     		 ; If BL = Discount2 , go to borrow

borrow39:
	CMP RESULTE, 1 			;RESULTE THAT IS RESULT 1
    	JG borrow40      		; If RESULTE  > 1 , go to borrow
	
borrow99:
	CMP RESULTE, 2 			;RESULTE THAT IS RESULT 1
    	JB borrow15     		; If RESULTE < 1 , go to borrow
	CMP RESULTF, 2			;RESULTF THAT IS RESULT 2
    	JB borrow15      		; If RESULTF < 2 , go to borrow

borrow40:

	DEC BL				; Decrease BL BY 1
	ADD CL, 10 			; Increase CL by 10
    	DEC AH        			; Decrease AH BY 1
    	ADD BL, 10 			; Increase BL by 10
	JMP CONTINUE11			;END OF THE BORROW 

borrow60:
	CMP BL, Discount2
    	JG borrow50       		; If BL > Discount2 , go to borrow 


borrow50:
	DEC CL				; Decrease CL BY 1
	ADD DL, 10 			; Increase DL by 10
	DEC BL				; Decrease BL BY 1
	ADD CL, 10 			; Increase CL by 10    
	JMP CONTINUE11			;JUMP TO OPERATION AT THE NED OF BORROW

borrow22:
	CMP CL, Discount3
    	JG borrow70      		 ; If CL < Discount3 , go to borrow
	CMP CL, Discount3
    	JB borrow96      		 ; If CL < Discount3 , go to borrow
	CMP CL, Discount3 
    	JE borrow96       		 ; If CL < Discount3 , go to borrow
borrow70:
	CMP BL, Discount2
    	JB borrow80       		; If BL < Discount2 , go to borrow 
borrow131:
	CMP BL, Discount2 
    	JB borrow14      		; If BL < Discount2 , go to borrow
	CMP BL, Discount2 
    	JE borrow14     		 ; If BL = Discount2 , go to borrow
borrow80: 
	CMP RESULTE, 1 			;RESULTE THAT IS RESULT 1
    	JG borrow81      		; If RESULTE >1 , go to borrow

borrow81:
	DEC AH         			 ; Decrease AH BY 1
    	ADD BL, 10			 ; Increase BL by 10
	DEC CL				; Decrease CL BY 1
	ADD DL, 10 			; Increase DL by 10  
	JMP CONTINUE11			;JUMP TO OPERATION AT THE  ERD OF BORROW

borrow15:
	CMP RESULTE, 1 			;RESULTE THAT IS RESULT 1
    	JG borrow18      		; If RESULTE >1 , go to borrow
	DEC CL				;DECREASE CL BY 1
	ADD DL, 10 			; Increase DL by 10
	JMP CONTINUE11			;JUMP TO OPERATION AT THE  ERD OF BORROW

borrow96:
	CMP RESULTF, 1 			;RESULTE THAT IS RESULT 1
	JG borrow24			 ; If RESULTE >1 , go to borrow
	 
borrow24:
	 
	CMP BL, Discount2 
    	JB borrow97     		 ; If BL < Discount2 , go to borrow
	CMP BL, Discount2 
    	JE borrow97      		; If BL = Discount2 , go to borrow

borrow97:
	CMP RESULTE, 1 			;RESULTE THAT IS RESULT 1
    	JG borrow111      		; If RESULTE  > 1 , go to borrow
	
borrow111:
	DEC CL				; DECREASE CL by 1
	ADD DL, 10			; Increase DL by 10
	DEC BL				; Decrease BL BY 1
	ADD CL, 10 			; Increase CL by 10
    	DEC AH          		; Decrease AH BY 1
    	ADD BL, 10 			; Increase BL by 10
	JMP CONTINUE11			;JUMP TO OPERATION AT THE  ERD OF BORROW
	 

	
borrow14:
	DEC CL				; DECREASE CL by 1
	ADD DL, 10			 ; Increase DL by 10
	DEC BL				; Decrease BL BY 1
	ADD CL, 10 			; Increase CL by 10
    	DEC AH        			 ; Decrease SH BY 1
    	ADD BL, 10			 ; Increase BL by 10
	JMP CONTINUE11			;JUMP TO OPERATION AT THE  ERD OF BORROW

borrow18:
	DEC CL				; DECREASE CL by 1
	ADD DL, 10			 ; Increase DL by 10
	DEC BL				; Decrease BL BY 1
	ADD CL, 10 			; Increase CL by 10
    	DEC AH        			 ; Decrease SH BY 1
    	ADD BL, 10			 ; Increase BL by 10
	JMP CONTINUE11			;JUMP TO OPERATION AT THE  ERD OF BORROW

CONTINUE11:


   	MOV AL,AH			;STORE THR CHANGE OF AH INTO AL
	SUB AL,Discount1		;AH,THAT IS FIRST DIGIT - Discount1
 	MOV Result1,AL			;STORE THE RESULT OF BORROW FOR FIRST DIGIT

	MOV AL,BL			;STORE THR CHANGE OF BL INTO AL
	SUB AL,Discount2		;BL,THAT IS SECOND DIGIT - Discount2
 	MOV Result2,AL			;STORE THE RESULT OF BORROW FOR SECOND DIGIT


	MOV AL,CL			;STORE THR CHANGE OF CL INTO AL
	SUB AL,Discount3		;AL,THAT IS THIRD DIGIT - Discount3
 	MOV Result3,AL			;STORE THE RESULT OF BORROW FOR THIRD DIGIT


	MOV AL,DL			;STORE THR CHANGE OF CL INTO AL
	SUB AL,Discount4		;AL,THAT IS FOUR DIGIT - Discount4
 	MOV Result4,AL			;STORE THE RESULT OF BORROW FOR FOUR DIGIT

	MOV AL, Result1			;MOVE RESULT1 INTO AL
	ADD AL,30H			;adding 30H converts number to its corresponding ASCII character.
    	MOV DL, AL			;MOV AL TO DL
    	MOV AH, 02H			;FUNCTION OF DISPLAY CHARACTER
    	INT 21H				;Carry out the operation

	MOV AL, Result2			;MOVE RESULT2 INTO AL
	ADD AL,30H			;adding 30H converts number to its corresponding ASCII character.
    	MOV DL, AL			;MOV AL TO DL
    	MOV AH, 02H			;FUNCTION OF DISPLAY CHARACTER
    	INT 21H				;Carry out the operation
	 

	MOV AL, Result3			;MOVE RESULT3 INTO AL
	ADD AL,30H			;adding 30H converts number to its corresponding ASCII character.
    	MOV DL, AL			;MOV AL TO DL
    	MOV AH, 02H			;FUNCTION OF DISPLAY CHARACTER
    	INT 21H				;Carry out the operation

	MOV AL, Result4			;MOVE RESULT4 INTO AL
	ADD AL,30H			;adding 30H converts number to its corresponding ASCII character.
    	MOV DL, AL			;MOV AL TO DL
    	MOV AH, 02H			;FUNCTION OF DISPLAY CHARACTER
    	INT 21H				;Carry out the operation

	JMP NET_END_PROGRAM			;JUMP TO END PROGRAM




INVALID:
	MOV AH,02H
	MOV DL,0AH			;NEW LINE
	INT 21H
	MOV DL,0DH
	INT 21H


	MOV AH,09H			;MOV AH 09H=DISPLAY STRING
	LEA DX,INVALID1 		;load effective address=find address of my "message" variable
	INT 21H

LOOP2:
	MOV AH,02H
	MOV DL,0AH			;NEW LINE
	INT 21H
	MOV DL,0DH
	INT 21H


	MOV AH,09H			;MOV AH 09H=DISPLAY STRING
	LEA DX,Choose 			;load effective address=find address of  "Choose" variable
	INT 21H

	MOV AH, 01H         		; Function to read character input
	INT 21H
	SUB AL,30H			;if enter 1,store become 31H
	MOV Choice, AL			; Store input value
	
	MOV AH,02H
	MOV DL,0AH			;NEW LINE
	INT 21H
	MOV DL,0DH
	INT 21H

	MOV AH,02H
	MOV DL,0AH			;NEW LINE
	INT 21H
	MOV DL,0DH
	INT 21H


	MOV AL,Choice
	CMP AL,1
	JE LOOPING			;IF ENTER 1 FOR CHOICE,LOOPING

	MOV AL,Choice
	CMP AL,2
	JE NET_END_PROGRAM			;IF ENTER 1 FOR CHOICE,END OF PROGRAM
	
	MOV AL,Choice
	CMP AL,1
	JNE LOOPING2			;IF NO EQAUL 1,REPEAT FOR CHOICE

	MOV AL,Choice
	CMP AL,2
	JNE LOOPING2			;IF NO EQAUL 2,REPEAT FOR CHOICE

LOOPING2:
	

	MOV AH,09H			;MOV AH 09H=DISPLAY STRING
	LEA DX,INVALID1 		;load effective address=find address of "INVALID" variable
	INT 21H

	

	JMP LOOP2			;LOOP FOR THE INVALID
LOOPING:
	JMP LOOP1			;LOOP FOR WHOLE PROGRAM

NET_END_PROGRAM:
 
	MOV AX,4C00H			;END OF YHE PROGRAM 
	INT 21H				;USE "AX" 2 BYTE

;----------------------------------------------------------------------------------------------------------------------------------------------------------------------

LOGIN_UI PROC
	
	CALL CLS
	
	MOV AH, 09H
	LEA DX, SAMPLE_SEP
	INT 21H						;DISPLAY SEPARATER
	LEA DX, SAMPLE
	INT 21H						;DISPLAY FIRST SAMPLE
	LEA DX, SAMPLE1
	INT 21H						;DISPLAY SECOND SAMPLE
	LEA DX, SAMPLE_SEP1
	INT 21H						;DISPLAY SEPARATER
	LEA DX, CRLF
	INT 21H						;CARRIAGE RETURN AND LINE FEED

LOGIN_FIELD:	
	MOV AH, 09H
	LEA DX, LOGIN_ID
	INT 21H						;DISPLAY LOGIN MESSAGE

	MOV AH, 0AH
	LEA DX, BUFFER_ID
	INT 21H						;REQUEST INPUT

	MOV AH, 02H
	MOV DL, 0AH
	INT 21H
	MOV DL, 0DH
	INT 21H						;CARRIAGE RETURN AND LINE FEED

	MOV AH, 09H
	LEA DX, LOGIN_PS
	INT 21H						;DISPLAY LOGIN MESSAGE

	MOV AH, 0AH
	LEA DX, BUFFER_PS
	INT 21H						;REQUEST INPUT

	MOV AH, 02H
	MOV DL, 0AH
	INT 21H
	MOV DL, 0DH
	INT 21H						;CARRIAGE RETURN AND LINE FEED

    	CALL DISPLAY_MENU              ; If valid, call menu

	RET
LOGIN_UI ENDP

;----------------------------------------------------------------------------------------------------------------------------------------------------------------------

DISPLAY_MENU PROC			;DISPLAY MENU
	
  	CALL CLS                        ;CLEAR SCREEN
	MOV AH, 09H
	LEA DX, SUCCESS
	INT 21H
    	LEA DX, MENU_SEP
	INT 21H				;DISPLAY SEPARATER
	LEA DX, MENU_HEADER
	INT 21H				;DISPLAY HEADER
    	LEA DX, MENU_SEP2
	INT 21H				;DISPLAY SEPARATER
	LEA DX, MENU_1
	INT 21H				;DISPLAY ITEM 1
	LEA DX, MENU_2
	INT 21H				;DISPLAY ITEM 2
	LEA DX, MENU_3
	INT 21H				;DISPLAY ITEM 3
	LEA DX, MENU_4
	INT 21H				;DISPLAY ITEM 4
    	LEA DX, MENU_SEP3
	INT 21H				;DISPLAY SEPARATER
	LEA DX, CRLF
	INT 21H				;DISPLAY ITEM 5
    	LEA DX, PROMPT_ORDER_COUNT	
	INT 21H				;SHOW ORDER COUNT
	INC ORDER_COUNT                 ;INCREMENT THE ORDER COUNT
	CALL DISPLAY_ORDER_COUNT        ;CALL DISPLAY ORDER COUNT
	
	MOV AH, 09H
	LEA DX, CRLF
	INT 21H				;CARRIAGE RETURN AND LINE FEED
	LEA DX, CRLF
	INT 21H				;CARRIAGE RETURN AND LINE FEED

	RET				;RETURN FROM PROCEDURE
DISPLAY_MENU ENDP

;----------------------------------------------------------------------------------------------------------------------------------------------------------------------

DISPLAY_ORDER_COUNT PROC		;DISPLAY ORDER COUNT                
    	MOV AX, ORDER_COUNT             ;MOV ORDER COUNT VALUE INTO AX  
    	CALL DISPLAY_COUNT		;CALL DISPLAY COUNT
               
    	RET                             ;RETURN FROM PROCEDURE  
DISPLAY_ORDER_COUNT ENDP

;----------------------------------------------------------------------------------------------------------------------------------------------------------------------
DISPLAY_COUNT PROC            		;DISPLAY COUNT

    	PUSH AX                     	;SAVE AX ON THE STACK TO PRESERVE ITS VALUE
    	PUSH BX                     	;SAVE BX ON THE STACK TO PRESERVE ITS VALUE
    	PUSH CX                     	;SAVE CX ON THE STACK TO PRESERVE ITS VALUE
    	PUSH DX                     	;SAVE DX ON THE STACK TO PRESERVE ITS VALUE

   	; IF ORDER COUNT EQUAL TO 0
    	MOV AX, ORDER_COUNT         	;MOV ORDER COUNT INTO AX
    	CMP AX, 0                   	;COMPARE AX WITH 0
    	JE DISPLAY_ZERO_COUNT           ;IF AX = 0, JMP TO DISPLAY_ZERO_COUNT

    	; CALCULATE NUMBER OF DIGITS AND PREPARE TO DISPLAY
    	MOV CX, 0                   	;INITIALIZE DIGIT COUNTER TO 0

    	; CALCULATE NUMBER OF DIGITS IN AX
   	MOV BX, 10                  	;SET BX TO 10, FOR DIVISOR DECIMAL CALCULATION

COUNT_ORDER_DIGITS:
    	XOR DX, DX                  	;CLEAR DX
    	DIV BX                      	;DIVIDE AX BY 10, QUOTIENT IN AX, REMAINDER IN DX
    	INC CX                      	;INCREMENT DIGIT COUNT
    	CMP AX, 0                   	;CHECK IF AX IS 0
    	JNZ COUNT_ORDER_DIGITS      	;IF AX NOT EQUAL TO 0, JMP BACK TO COUNT_ORDER_DIGITS TO REPEAT DIGITS COUNTING

    	MOV AX, ORDER_COUNT         	;MOV ORDER_COUNT INTO AX
    	MOV BX, 10                  	;SET BX TO 10, FOR DIVISOR DECIMAL CALCULATION
    	MOV DX, 0                   	;CLEAR DX

PRINT_DIGITS:
    	XOR DX, DX                  	;CLEAR DX
    	DIV BX                      	;DIVIDE AX BY 10
    	PUSH DX                     	;PUSH REMAINDER ON STACK
    	CMP AX, 0                   	;CHECK IF AX IS 0
    	JNZ PRINT_DIGITS            	;IF AX NOT EQUAL TO 0, JMP BACK TO PRINT_DIGITS

PRINT_LOOP:
    	POP DX                      	;POP VALUE FROM STACK INTO DX
    	ADD DL, '0'                 	;CONVERT DIGIT TO ASCII
    	MOV AH, 02H                 	
    	INT 21H                     	;DISPLAY CHARACTER
    	LOOP PRINT_LOOP             	;LOOP UNTIL ALL DIGITS ARE PRINTED

    	JMP DONE_DISPLAY            	;JMP TO DONE_DISPLAY

DISPLAY_ZERO_COUNT:
    	MOV AH, 02H                 	
    	MOV DL, '0'                 	;LOAD ASCII ZERO INTO DL
    	INT 21H                     	;DISPLAY CHARACTER

DONE_DISPLAY:
    	POP DX                      	;POP DX FROM STACK
    	POP CX                      	;POP CX FROM STACK
    	POP BX                      	;POP BX FROM STACK
    	POP AX                      	;POP AX FROM STACK

    	RET                         	;RETURN FROM PROCEDURE
DISPLAY_COUNT ENDP

;----------------------------------------------------------------------------------------------------------------------------------------------------------------------

CLS PROC
    	
	MOV AX, 0600h          		;FUNCTION TO SCROLL ENTIRE SCREEN
    	MOV BH, 07h            		;SET BACKGROUND COLOUR TO BLACK
    	MOV CX, 0              		;UPPER LEFT CORNER
    	MOV DX, 184Fh          		;LOWER RIGHT CORNER (80 X 25)
    	INT 10h                		;CALL BIOS TO CLS
    
    	;MOVE CURSOR TO TOP LEFT
    	MOV AX, 0200h          		;FUNCTION SET CURSOR POSITION
    	XOR BX, BX             		;COLUMN = 0 (LEFT MOST)
    	XOR DX, DX             		;ROW = 0 (TOP MOST)
    	INT 10h                		;CALL BIOS TO SET CURSOR POSITION
	
    	RET
CLS ENDP

;----------------------------------------------------------------------------------------------------------------------------------------------------------------------
TAX_CALCULATION PROC
    MOV CX, 10               ; Store the fixed tax percentage (10%)

    ; Multiply SUBTOTAL by tax percentage (stored in CX)
    MOV AX, [SUBTOTAL]        ; Load SUBTOTAL into AX
    MOV BX, CX                ; Move tax percentage into BX (CX contains the tax rate, e.g., 6 for 6%)
    MUL BX                    ; AX = SUBTOTAL * tax percentage

    ; Divide by 100 to convert percentage into a decimal
    MOV BX, 100               ; Prepare BX with the divisor 100 (for percentage calculation)
    DIV BX                    ; AX = (SUBTOTAL * tax percentage) / 100

    ; Store the tax amount
    MOV [TAX], AX             ; Store the tax amount in TAX

    ; Add tax to subtotal to get the total
    MOV AX, [SUBTOTAL]        ; Reload SUBTOTAL into AX
    ADD AX, [TAX]             ; AX = SUBTOTAL + TAX
    MOV [TOTAL_WITH_TAX], AX  ; Store the result as TOTAL_WITH_TAX
    
    ; Display subtotal
    MOV AH, 09H
    LEA DX, CRLF
    INT 21H
    LEA DX, PROMPT_SUBTOTAL
    INT 21H
    MOV AX, [SUBTOTAL]        ; Move SUBTOTAL into AX
    CALL DISPLAY_NUMBER    ; Display SUBTOTAL
	
    ; Display tax percentage
    MOV AH, 09H
    LEA DX, CRLF
    INT 21H
    LEA DX, TAX_PERCENTAGE_MSG ; Load the tax percentage message
    INT 21H                    ; Display the tax percentage message

    ; Display tax
    MOV AH, 09H
    LEA DX, CRLF
    INT 21H
    LEA DX, PROMPT_TAX
    INT 21H
    MOV AX, [TAX]             ; Move TAX into AX
    CALL DISPLAY_T      ; Display TAX

    ; Display total with tax
    MOV AH, 09H
    LEA DX, CRLF
    INT 21H
    LEA DX, PROMPT_TOTAL
    INT 21H
    MOV AX, [TOTAL_WITH_TAX]  ; Move TOTAL_WITH_TAX into AX
    CALL DISPLAY_T      ; Display TOTAL_WITH_TAX
    
    JMP DISCOUNT_CALCULATION

    ; Exit program
    MOV AH, 4CH
    INT 21H 
	
TAX_CALCULATION ENDP

;----------------------------------------------------------------------------------------------------------------------------------------------------------------------

DISCOUNT_CALCULATION PROC
    MOV CX, 10               ; Store the fixed discount percentage (10%)


    MOV AX, [TOTAL_WITH_TAX]        	; Load TOTAL into AX
    MOV BX, CX                	; Move discount percentage into BX 
    MUL BX                    	; AX = TOTAL * discount percentage


    MOV BX, 100               ; Prepare BX with the divisor 100 (for percentage calculation)
    DIV BX                    ; AX = (TOTAL * discount percentage) / 100


    MOV [DISCOUNT0], AX             ; Store the discount amount in DISCOUNT


    MOV AX, [TOTAL_WITH_TAX]        ; Reload TOTAL into AX
    SUB AX, [DISCOUNT0]             ; AX = TOTAL - DISCOUNT
    MOV [DISCOUNT_TOTAL], AX  ; Store the result as DISCOUNT_TOTAL


    MOV AH, 09H
    LEA DX, CRLF
    INT 21H
    LEA DX, DISCOUNT_PERCENTAGE_MSG ; Load the discount percentage message
    INT 21H                    ; Display the discount percentage message


    MOV AH, 09H
    LEA DX, CRLF
    INT 21H
    LEA DX, PROMPT_DISCOUNT
    INT 21H
    MOV AX, [DISCOUNT0]             ; Move DISCOUNT into AX
    CALL DISPLAY_T      ; Display DISCOUNT

    MOV AH, 09H
    LEA DX, CRLF
    INT 21H
    LEA DX, PROMPT_TOTAL
    INT 21H
    MOV AX, [DISCOUNT_TOTAL]  ; Move DISCOUNT_TOTAL into AX
    CALL DISPLAY_T     ; Display DISCOUNT_TOTAL
    

    MOV AH, 4CH
    INT 21H 
	
DISCOUNT_CALCULATION ENDP

;----------------------------------------------------------------------------------------------------------------------------------------------------------------------

DISPLAY_NUMBER PROC			;DISPLAY NUMBER

    	PUSH AX                    	;SAVE AX ON THE STACK TO PRESERVE IT'S VALUE
    	PUSH BX                    	;SAVE BX ON THE STACK TO PRESERVE IT'S VALUE
    	PUSH CX                    	;SAVE CX ON THE STACK TO PRESERVE IT'S VALUE
    	PUSH DX                    	;SAVE DX ON THE STACK TO PRESERVE IT'S VALUE

    	;IF SUBTOTAL EQUAL TO 0
    	MOV AX, SUBTOTAL           	;MOV SUBTOTAL INTO AX
    	CMP AX, 0                  	
    	JE DISPLAY_ZERO            	;IF AX = 0, JMP TO DISPLAY_ZERO

    	;CALCULATE NUMBER OF DIGITS AND PREPARE TO DISPLAY
    	MOV CX, 0                  	;INITIALISE DIGIT COUNTER TO 0

    	;CALCULATE NUMBER OF DIGITS IN AX
    	MOV BX, 10                 	;SET BX TO 10, FOR DIVISOR DECIMAL CALCULATION

COUNT_DIGITS:
        XOR DX, DX             		;CLEAR DX
        DIV BX                 		;DIVIDE AX BY 10, QUOTIENT IN AX, REMAINDER IN DX
        PUSH DX                		;PUSH REMAINDER TO STACK
        INC CX                 		;INCREMENT DIGIT COUNT
        CMP AX, 0              		
        JNZ COUNT_DIGITS      		;IF AX NOT EQUAL TO 0, JMP BACK TO COUNT_DIGITS TO REPEAT DIGIT COUNTING

    	;DISPLAY EACH DIGITS
DISPLAY_DIGITS:
        POP DX                 		;POP THE LAST DIGIT IN THE STACK OF DX
        ADD DL, '0'            		;CONVERT TO ASCII
        MOV AH, 02H            		
        INT 21H                		;DISPLAY CHARACTER
        LOOP DISPLAY_DIGITS    		;LOOP UNTIL ALL DIGITS DISPLAYED

    	;DISPLAY DECIMAL POINT
    	MOV DL, '.'                	;MOV DECIMAL POINT INTO DL
    	MOV AH, 02H                	
    	INT 21H                    	;DISPLAY DECIMAL POINT

   	;DISPLAY TWO ZERO FOR DECIMAL PLACE
    	MOV DL, '0'                
    	INT 21H                    	;DISPLAY FIRST ZERO
    	MOV DL, '0'                
    	INT 21H                    	;DISPLAY SECOND ZERO

    	JMP DONE                  	;JMP TO DONE

DISPLAY_ZERO:
    	;HANDLE CASE WHERE SUBTOTAL = 0
    	MOV DL, '0'                	
    	MOV AH, 02H                	
    	INT 21H                    	;DISPLAY A ZERO

    	;DISPLAY DECIMAL POINT WITH TWO ZERO
    	MOV DL, '.'                	
    	MOV AH, 02H                	
    	INT 21H                    	;DISPLAY DECIMAL POINT
    	MOV DL, '0'                	
    	INT 21H                    	;DISPLAY FIRST ZERO
    	MOV DL, '0'                	
    	INT 21H                    	;DISPLAY SECOND ZERO

DONE:
    	MOV AH, 09H                	
    	LEA DX, CRLF               	
    	INT 21H                    	;CARRIAGE RETURN AND LINE FEED

    	POP DX                     	;RESTORE ORIGINAL VALUE OF DX FROM STACK
    	POP CX                     	;RESTORE ORIGINAL VALUE OF CX FROM STACK
    	POP BX                     	;RESTORE ORIGINAL VALUE OF BX FROM STACK
    	POP AX                     	;RESTORE ORIGINAL VALUE OF AX FROM STACK

    	RET                        	;RETURN FROM PROCEDURE
DISPLAY_NUMBER ENDP

;----------------------------------------------------------------------------------------------------------------------------------------------------------------------

;display the tax and total
DISPLAY_T PROC
    ; Convert the number in AX to a string and display it
    PUSH AX                ; Preserve AX (Stack)
    MOV CX, 0              ; Counter for digits
    MOV BX, 10             ; Divisor for decimal conversion
    MOV DX, 0              ; Clear DX (to prepare for division)

    ; Convert number to digits (reverse order)
    .CONVERT_LOOP:
        XOR DX, DX         ; Clear DX before division
        DIV BX             ; AX = AX / 10, AX = quotient, DX = remainder
        PUSH DX            ; Store the remainder (digit)
        INC CX             ; Increment digit count
        TEST AX, AX        ; Check if AX is zero
        JNZ .CONVERT_LOOP  ; Repeat until AX is zero

    ; Print the digits in reverse order
    .PRINT_LOOP:
        POP DX             ; Get the last stored digit
        ADD DL, '0'        ; Convert digit to ASCII
        MOV AH, 02H        ; DOS function to write a character
        INT 21H            ; Call DOS
        LOOP .PRINT_LOOP   ; Repeat for all digits

    ; Add decimal point and two zeroes for .00
    MOV DL, '.'           ; Move decimal point into DL
    MOV AH, 02H
    INT 21H               ; Display the decimal point

    MOV DL, '0'           ; Display first zero
    INT 21H

    MOV DL, '0'           ; Display second zero
    INT 21H

    POP AX                 ; Restore AX
    RET                    ; Return from the function
DISPLAY_T ENDP

;----------------------------------------------------------------------------------------------------------------------------------------------------------------------

	MAIN ENDP
END MAIN
