/***********************************************************************
*  Program to alternate between 20 10-led sequences with two buttons,
*  and to change between 10 velocities with two buttons
*  Micro: Atmega328P
*  Date: 8-03-2022
***********************************************************************/

/***************************** Libraries ******************************/
#include <avr/io.h>
#include <util/delay.h>  //delay library
/***************************** Macros *********************************/
#define F_CPU 16000000UL // 16 MHz clock speed

/***********************************************************************
*  Pin-reading definition through a macro #define
*  PDx depict pin Dx
*  #define <nameMacro> (port & (1<<portPin))>>portPin
***********************************************************************/
#define seqUp (PINC & (1<<PC5))>>PC5
#define seqDown (PINC & (1<<PC4))>>PC4
#define velUp (PINC & (1<<PC3))>>PC3
#define velDown (PINC & (1<<PC2))>>PC2

/******************* Global Variables Definition **********************/
short seqID; 	// Sequence Identifier 
short velID;	// Velocity Identifier					   
int velocities[] = {3000,2000,1000,700,600,500,400,300,200,100};
short nVel = (&velocities)[1] - velocities; //number of velocities

// Array of 20 x 10 (20 sequences, with 10  different sparkles each one)
int seqArray[][10] =
{
	{0},
	{1,2,4,8,16,32,64,128,256,512},					//1
	{512,256,128,64,32,16,8,4,2,1},
	{1,2,0x204,0x109,0x92,0x124,0x242,0x81,0x100,0x200},											
	{0x200,0x100,0x81,0x242,0x124,0x92,0x109,0x204,2,1},
	{0x201,0x303,0x387,0x3CF,0x3FF,0x3FF,0x3CF,0x387,0x303,0x201},  //5
	{1,3,7,15,31,63,127,255,511,1023},
	{1023,511,255,127,63,31,15,7,3,1},
	{0,0x200,0x201,0x301,0x303,0x383,0x387,0x3C7,0x3CF,0x3EF},
	{0x3EF,0x3CF,0x3C7,0x387,0x383,0x303,0x301,0x201,0x200,0},	
	{0x3FF,0,0x2AA,0,0x249,0,0x222,0,0x210,0},			//10
	{0,0x210,0,0x222,0,0x249,0,0x2AA,0,0x3FF},	
	{0x20,0x30,0x70,0x78,0xF8,0xFA,0x1FA,0x1FE,0x3FE,0x3FF},
	{0x3FF,0x3FE,0x1FA,0xFA,0xF8,0x78,0x70,0x30,0x20},	
	{0x201,0x102,0x84,0x48,0x30,0x30,0x48,0x84,0x102,0x201},
	{0x1FE,0x2FD,0x37B,0x3B7,0x3CF,0x3CF,0x3B7,0x37B,0x2FD,0x1FE},	//15
	{0x200,0x200,0x200,0x200,0x200,0x2AA,0x155,0x2AA,0x155,0x2AA},
	{0x108,0x84,0x42,0x21,0x21,0x42,0x84,0x108,0x108,0x84},	
	{15,189,257,380,504,647,728,882,913,944},
	{30,161,232,330,431,517,529,544,672,713},
	{13,21,34,55,89,144,233,377,610,987}				//20
};												
short nSeq = (&seqArray)[1] - seqArray; // Number of sequences
/********************* Functions and subroutines **********************/	
void indexSelector (short *x,short MAX, int UP, int DOWN){
	/*
	x   : variable that depicts an index of an array
	MAX : size of the array
	UP  : button to move from 0 to MAX-1 in the array
	DOWN: button to move from MAX-1 to 0 in the array
	*/
	// Avoid index to exceed the limits
	if ((*x) < 0) (*x) = 0;				
	if ((*x) > MAX-1) (*x) = MAX-1;
	// Increase or decrease counting according to the button
	if (UP)        {(*x)++; _delay_ms(250);}
	else if (DOWN) {(*x)--; _delay_ms(250);}
}
void delayms(int n){
	while(n--)
	{
		_delay_ms(1);
	}
}
void setSeq(int vec[]){
	PORTD = 0x00;
	PORTB = 0x00;
	for (int i = 0;i<10; i++)
	{
		// if any button to change sequence is pressed, 
		// end sequence execution (to check the new value of seqID)
		if (seqUp || seqDown) break;
		else
		{	
			// if any button to change velocity is pressed, 
			// change value of velID according to the button
			if (velUp || velDown) 
			{
				indexSelector(&velID,nVel,velUp,velDown);
			}
			// Assign i-th element of a sequence to ports D
			// (first 8 LSB) and B (the MSB ones)
			PORTD = vec[i] & 0xFF;
			PORTB = vec[i] >> 8;
			delayms(velocities[velID]);
		}
	}
}
 
/************************** Main Program ******************************/
int main(void)
{
	/*************** variable initialization **************************/
	seqID = 0;
	velID = 0;
	//*******************Ports Setting ********************************/
	// Port D as output
	// 0xFF = 0b11111111
	// PORT B as output
	// 0xFF = 0b11111111
	// PORT C as input
	// 0x00 = 0b00000000
	DDRD |= 0xFF;
	DDRB |= 0xFF;
	DDRC |= 0x00;
	
	PORTD = 0x00;
	PORTB = 0x00;
	while (1)
	{
		PORTC = 0x00;
		indexSelector(&seqID,nSeq,seqUp,seqDown);
		/*********** Selection and Execution of Sequences **********/
		switch(seqID)
		{
			case 0:		   	      break;
			case 1:setSeq(seqArray[1]);   break;
			case 2:setSeq(seqArray[2]);   break;
			case 3:setSeq(seqArray[3]);   break;
			case 4:setSeq(seqArray[4]);   break;
			case 5:setSeq(seqArray[5]);   break;
			case 6:setSeq(seqArray[6]);   break;
			case 7:setSeq(seqArray[7]);   break;
			case 8:setSeq(seqArray[8]);   break;
			case 9:setSeq(seqArray[9]);   break;
			case 10:setSeq(seqArray[10]); break;
			case 11:setSeq(seqArray[11]); break;
			case 12:setSeq(seqArray[12]); break;
			case 13:setSeq(seqArray[13]); break;
			case 14:setSeq(seqArray[14]); break;
			case 15:setSeq(seqArray[15]); break;
			case 16:setSeq(seqArray[16]); break;
			case 17:setSeq(seqArray[17]); break;
			case 18:setSeq(seqArray[18]); break;
			case 19:setSeq(seqArray[19]); break;
			case 20:setSeq(seqArray[20]); break;
		}
	}
	return 0;
}//** End of Program
