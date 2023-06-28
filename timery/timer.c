#include <LPC21xx.H>
#include "timer.h"

#define mCOUNTER_ENABLE (1<<0)
#define mCOUNTER_RESET (1<<1)
#define mRESET_ON_MR0 (1<<1)
#define mINTERRUPT_ON_MR0 (1<<0)
#define mINTERRUPT_FLAG_MR0 (1<<0)

void InitTimer0(void){
	T0TCR = mCOUNTER_ENABLE;
}

void WaitOnTimer0(unsigned int uiTime){
	T0TCR |= mCOUNTER_RESET;
	T0TCR &= (~mCOUNTER_RESET);
	while(T0TC<((uiTime)*15)){}
}

void InitTimer0Match0(unsigned int uiDelayTime){
	T0MR0 = uiDelayTime*15;
	T0MCR = T0MCR | (mINTERRUPT_ON_MR0 | mRESET_ON_MR0); // to co ma sie wydarzyc jesli TC=T0MR0 - resetuje i przerywa TC
	T0TCR|=mCOUNTER_RESET; //reset w rejestrze Timera
	T0TCR&=~mCOUNTER_RESET; //zeruje flage resetu
	T0TCR|=mCOUNTER_ENABLE; //uruchamia timer
}

void WaitOnTimer0Match0(){
	
	while((T0IR&mINTERRUPT_FLAG_MR0)==0){} // jesli nie ma przerwania (t0IR=0 & FLAG=1)=0 
	T0IR = mINTERRUPT_FLAG_MR0; //kasujemy przerwanie na odpowiednim bicie
}