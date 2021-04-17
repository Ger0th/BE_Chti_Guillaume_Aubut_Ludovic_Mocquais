	PRESERVE8
	THUMB   
		
		
;code C		
;void timer_callback(void)
;{
;	if (FlagCligno==1)
;	{
;		FlagCligno=0;
;		GPIOB_Set(1);
;	}
;	else
;	{
;		FlagCligno=1;
;		GPIOB_Clear(1);
;	}
;		
;}

	include Driver/DriverJeuLaser.inc
	export timer_callback
	
; ====================== zone de r�servation de donn�es,  ======================================
;Section RAM (read only) :
	area    mesdata,data,readonly


;Section RAM (read write):
	area    maram,data,readwrite
		

FlagCligno dcb 0	
; ===============================================================================================
	


		
;Section ROM code (read only) :		
	area    moncode,code,readonly
; �crire le code ici		
	
; Algo C
;void Timer_callback(void)
;{
;	if (FlagCligno==1)
;	{
;		FlagCligno=0;
;		GPIOB_Set(1);
;	}
;	else
;	{
;		FlagCligno=1;
;		GPIOB_CLear(1);
;	}
;}

timer_callback proc
Si
	ldr r1, =FlagCligno
	ldrb r0, [r1]
	adds r0, r0
	beq Sinon
Alors
	mov r0, #0
	strb r0, [r1]
	mov r0, #1
	bl GPIOB_Clear
	b FinSi
Sinon
	mov r0, #1
	strb r0, [r1]
	bl GPIOB_Set
FinSi
	bx lr
	endp
	end	