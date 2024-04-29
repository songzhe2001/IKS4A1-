#include"algorithm.h"
#include"main.h"
#include <stdio.h>

//int16_t value_last=0;
//int8_t 	value_state_n=0;
//int8_t 	value_state_l=0;
//int8_t 	value_state_storage[3]={0};
//int8_t 	act=0;
//int 	value_count=0;
//uint8_t value_state_valid=0;

int 	value_last=0;
int 	value_state_n=0;
int 	value_state_l=0;
int 	value_state_storage[3]={0};
int 	act=0;
int 	value_count=0;
int 	value_state_valid=0;

int 	qvar_digital(int16_t value)
{
	int value_deviation=value-value_last;

	if (value_deviation>=54600)
		value_state_n=1;
	else if(value_deviation>=23400)
		value_state_n=value_state_l+1;
	else if(value_deviation<=-54600)
		value_state_n=-1;
	else if(value_deviation<=-23400)
		value_state_n=value_state_l-1;
	else
		value_state_n=value_state_l;

	value_last=	value_state_n * 32760;

	if (value_state_n==value_state_l)
	{
		value_count+=1;
		if	((value_count>=40)&&(value_state_n!=0)&&(value_state_n!=value_state_storage[0]))
		{
			value_count=0;
			value_state_valid=1;
			value_state_storage[2]=value_state_storage[1];
			value_state_storage[1]=value_state_storage[0];
			value_state_storage[0]=value_state_n;
		}
		else if((value_count>=120)&&(value_state_n==0))
		{
			value_count=0;
			value_state_valid=1;
			value_state_storage[2]=value_state_storage[1];
			value_state_storage[1]=value_state_storage[0];
			value_state_storage[0]=value_state_n;
		}

	}
	else
		value_count=0;

	if	(value_state_valid)
	{
		value_state_valid=0;
		if	((value_state_storage[2]==0)&&(value_state_storage[0]==0))
			act=value_state_storage[1]+value_state_storage[1];
		else if((value_state_storage[1]==-1)&&(value_state_storage[2]==1))
			act=-1;
		else if((value_state_storage[1]==1)&&(value_state_storage[2]==-1))
			act=1;
		else
			act=0;
	}
	else
		act=0;
	value_state_l=value_state_n;
	return act;
//	return value_last;
}
