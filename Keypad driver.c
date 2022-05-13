#include "IO.h"
# include "stdint.h"
unsigned char noPressed=0xFF;
unsigned char  array [4][4]={{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};
void Port_Init(unsigned char portname);
unsigned char ReadPin (unsigned char portName,unsigned pinNum);
void Set_portDir(unsigned char port_name,unsigned char dierction);
void enable_PullUP (unsigned char port_name ,unsigned char pin_number);
void write_lownibble(unsigned char port_name,unsigned char data);
void writePin(unsigned char portName,unsigned char pinNumber,unsigned char data);

	
void Keypad_init(unsigned char portName)
{ 
	Port_Init('A');
	Set_portDir('A',0x0F);
	enable_PullUP ('A', 4);
	enable_PullUP ('A', 5);
	enable_PullUP ('A', 6);
	enable_PullUP ('A', 7);
	
}

unsigned char KeypadScan()
{
    unsigned char x,y,i;
	while(1)
	for (x=0;x<4;x++)
		{ 	 write_lownibble('A',0x0F);
					writePin('A',x,0);
		
			for (y=0;y<4;y++)
		{
				i=ReadPin ('A',y+4);
					if(i==0) 
					{return array[x][y];
								break;}
					if(i==0)break;
						return noPressed;
						 
		 }	
	 }
}		