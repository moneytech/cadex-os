/**
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
*/

/**
 * A Brainf**k interpreter. 
 * This is the only interpreter that I could run in Cadex OS
*/
#include <stdio.h>

#define PRG1\
	    "++++++++++        initializes cell zero to 10\
         [\
         >+++++++>++++++++++>+++>+<<<<-\
		 ]                 this loop sets the next four cells to 70/100/30/10 \
         >++.              print   'H'\
         >+.               print   'e'\
         +++++++.                  'l'\
         .                         'l'\
         +++.                      'o'\
         >++.                      space\
         <<+++++++++++++++.        'W'\
         >.                        'o'\
         +++.                      'r'\
         ------.                   'l'\
         --------.                 'd'\
         >+.                       '!'\
         >.                        newline"

#define ADD ",>++++++[<-------->-],[<+>-]<."
#define MUL ",>,>++++++++[<------<------>>-]<<[>[>+>+<<-]>>[<<+>>-]<<<-]>>>++++++[<++++++++>-],<.>.";

#define FIZZBUZZ\
	">++++++++++[<++++++++++>-]>>>+++>+++++>+<<<<<<\
[\
 >>>+\
 >- [<<+>>-]<<<+>[<[-]>>>+<<-]<[>>>+++>>[-]<<<<<- +++++++[>++++++++++<-]>.<+++++++[>+++++<-]>.<++++[>++++<-]>+..[-]<]>>\
 >>- [<<<+>>>-]<<<<+>[<[-]>>>>+<<<-]<[>>>>+++++>[-]<<<<<- +++++++++++[>++++++<-]>.<+++++++[>+++++++<-]>++.+++++..[-]<]>>\
 >>>\
 [-\
  <<<[<+>>>>+<<<-]<[>+<-]>>>>\
  [\
   >++++++++++<\
   [>-[>+>+<<-]>[<+>-] +>[<[-]>-]< [>>+<<<++++++++++>-]<<-]\
   >---------- >>>[<<<<+>>>>-] <<<<\
   >>>>>+> >>[-] <[>+<-] <[>+<-] <<<<< [>>>>>+<<<<<+] <\
  ]\
  >>>>>\
  [ <++++++[>>++++++++<<-]>> . [-] >[<+>-] >[<+>-] <<<-]\
  <<<<<\
 ]+\
 <<<<<\
 +++++++++++++.---.[-]\
<-]"\

char cells[100] = {0};
void interpret(char* program)
{
	int cnt;	           // cnt is a counter that is going to be used
	                       //     only when parsing 0-loops
	int stack[100] = {0};  // create a stack, 100 levels deep - modeled
	                       //     using a simple array - and initialized to 0
	int sp = 0;			   // sp is going to be used as a 'stack pointer'
	char* ip = program;    // ip is going to be used as instruction pointer
	char* cell = cells;    // cell is the pointer to the 'current' memory cell
	                       //      and as such, it is initialized to the first
	                       //      memory cell
	
	while(*ip)			   // as long as ip point to 'valid code' keep going
	{
		if(*ip == ',')
			read_object(0, &cell, 1);
		else if(*ip == '.')
			printf("%c", *cell);
		else if(*ip == '>')
			cell++;
		else if(*ip == '<')
			cell--;
		else if(*ip == '+')
			*cell = *cell + 1;
		else if(*ip == '-')
			*cell = *cell - 1;
		else if(*ip == '[')
		{			
			
			if(stack[sp] != ip - program)
				stack[++sp] = ip - program;					
			
			*ip++;
			
			if(*cell != 0)
				continue;
			else
			{					
				cnt = 1;
				while((cnt > 0) || *ip != ']')
				{
					*ip++;
					if(*ip == '[')
						cnt++;
					else if(*ip == ']')
						cnt--;
				}
				sp--;
			}
		}else if(*ip == ']')
		{				
			ip = program + stack[sp];
				continue;
		}
		*ip++;
	}
}

int main(int argc, char* argv[])
{	
	char *prg = ADD;
		
	interpret(prg);
	return 0;
}