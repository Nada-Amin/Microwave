//files included
#include "IO.c"
#include "stdio.h"
#include "IO.h"
#include "keypad driver.h"
#include "lcd.h"

//initialize the systic timer 
void SysTick_wait(unsigned long delay){ 
	NVIC_ST_CTRL_R = 0x00;  
	NVIC_ST_RELOAD_R = delay-1;  //Reload delay
	NVIC_ST_CURRENT_R =0; 
	NVIC_ST_CTRL_R = 0x05; 
 while((NVIC_ST_CTRL_R&0x00010000)==0){} 
 } 

//A function to make a generic delay in seconds
 void genericDelay(unsigned long time){ 
	int i;
 for(i=0;i<time ;i++) 
 SysTick_wait(16000); //one milli second delay 	
}

//function to make a delay AND update the lcd 
void statesDelay(unsigned long time){ //the function takes time in milliseconds
	int i;
	unsigned int seconds = time/1000 ; //get the time in seconds 
	unsigned int minutes = seconds/60; //get the minutes by dividing the whole seconde /60
	seconds =seconds%60; //get the remaining seconds by taking the reminder of the previous operation ###
	// now we have seconds and minutes in their variables
	for(i=0; i<time;i++){
		genericDelay(1000); //1 sec delay
		//Update lcd goes here to be updated each sec with the new seconds and minutes
		char *s ="%u : %u",minutes, seconds; //put s in the forman of min:sec in order to be printed ###
		lcd_send_string(s); //display the string 
		if(seconds>0 && minutes>=0) {seconds--;} //decrease seconds each one second
		if(seconds ==0 && minutes>0) { //If seconds reached zero, decrease the minutes 
			// After 1:00 comes 0:59
			minutes --;
			seconds =59;
		}
		if(seconds==0 && minutes==0){//we finished counting down 
			//what to do when we finish goes here ###
			}
		
		
		
	}
}

//A function to determine the delay for chicken and beef
//this function will be called inside the genericDelay function to determine the time in seconds.
unsigned long BC_delay(unsigned char state, unsigned char weight,unsigned long time ){
	switch(state) {
		case 'B': return time =30* weight*1000;       //in case of beef, delay = weight* 0.5 min
		case 'C' : return time =12*weight*1000;       //in case of corn, delay= weight * 0.2 min 
	}
	 return 0; } //if we enterd other inputs that B or C
	 
//A function to determine popcorn delay (just for further abstraction)	
unsigned long A_delay(unsigned long time){
return time=60*1000;	//60 sec dalay
} 

//A function to determine D(custom) delay 
unsigned long D_delay (unsigned long time, unsigned char seconds, unsigned char minutes){ 
	 time = 60*minutes + seconds; //times in seconds
	return time *1000; //as function takes milliseconds
}
	