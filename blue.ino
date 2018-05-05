#include<avr/io.h>
#define F_CPU 8000000UL
#include<util/delay.h>
#define lcd PORTB

 void lcd_cmd(int cmd) 
 { 
 lcd=((cmd&0xf0)/4);
 lcd += 0x02;
 _delay_ms(2);
 lcd=lcd- 0x02;
 lcd=((cmd & 0x0f)*4);
 lcd += 0x02;
 _delay_ms(2);
 lcd=lcd-0x02;}

void lcd_begin()
{
lcd_cmd(0x02);
lcd_cmd(0x0C);
lcd_cmd(0x28);
lcd_cmd(0x06);
lcd_cmd(0x01);}

void lcd_data (int data)
{
lcd=((data & 0xf0)/4);
lcd+=0x03;
_delay_ms(2);
lcd=lcd-0x02;
lcd=((data&0x0f)*4);
lcd+=0x03;
_delay_ms(2);
lcd=lcd-0x02;}
	
void lcd_num(int n)
{ 
if(n<10)
{
lcd_data(n+48);
}
else
{
lcd_num(n/10);
lcd_data((n%10)+48);
}
}

void lcd_string(char a[])
{
	int i=0;
	while(a[i]!='\0')
	{
		lcd_data(a[i]);
		i++;
	}
}



 void serialbegin(unsigned long BR)
 {
 UCSRB=(1<<RXEN)+(1<<TXEN);
 UCSRC=(1<<URSEL)+(1<<USBS)+(1<<UCSZ1)+(1<<UCSZ0);
 UBRRL=((F_CPU/(BR*16))-1);
 UBRRH=(((F_CPU/(BR*16))-1)>>8);
 }

 void txdata(char data)
 {
  while((UCSRA&(1<<UDRE))==0);
  UDR=data;
  }

  int serialavailable()
  {
  if(UCSRA&(1<<RXC))
  {
   return 1;
   }
   return 0;
   }

   char rxdata()
   {
    return UDR;
	}


 int main()
  {
  	DDRB=0xff;
	DDRD=0xff;
	TCCR0=0b01101010;
    TCCR2=0b01101010;
	DDRC=0xff;
  
	   char ch;
	   serialbegin(9600);
	   while(1)
	   {
	    if(serialavailable())
		{
			ch=rxdata();
	      	{
				if(ch==70)
				{
					OCR0=245;
					OCR2=255;
					PORTC=0b00001010;
				}
		  		else if(ch==66)
				{
					OCR0=245;
					OCR2=255;
					PORTC=0b00000101;
				}
				else if(ch==76)
				{
					OCR0=245;
					OCR2=255;
					PORTC=0b00000110;
				}
				else if(ch==82)
				{
					OCR0=245;
					OCR2=255;
					PORTC=0b00001001;
				}
				else if(ch==71)
				{
					OCR0=245;
					OCR2=200;
					PORTC=0b00001010;
				}
				else if(ch==73)
				{
					OCR0=190;
					OCR2=255;
					PORTC=0b00001010;
				}
				else if(ch==72)
				{
					OCR0=245;
					OCR2=200;
					PORTC=0b00000101;
				}
				else if(ch==74)
				{
					OCR0=190;
					OCR2=255;
					PORTC=0b00000101;
				}
				else
				{
					PORTC=0;
				}
	  	
	  
		  	}
	  }
	  }
	  }
