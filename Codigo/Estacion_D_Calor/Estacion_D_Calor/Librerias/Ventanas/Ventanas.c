/*
 * Ventanas.c
 *
 * Created: 28/7/2025 15:40:08
 *  Author: Alvaro
 */ 
#include "Ventanas.h"

void Ventana_Principal(){
	
	unsigned char Grado[8] = { 0b00110,0b01001,0b01001,0b00110,0b00000,0b00000,0b00000,0b00000};
	unsigned char Fan[8] = { 0b00000,0b10001,0b11011,0b01110,0b01110,0b11011,0b10001,0b00000};
	unsigned char Power[8] = { 0b00011,0b00110,0b01100,0b11111,0b00110,0b01100,0b01000,0b10000};
	
	char str[5];
	
	lcd_clear();
	lcd_gotorc(1,1);
	lcd_puts("Set:");
	
	lcd_gotorc(1,5);
	sprintf(str, "%i", SeletTEMP);
	lcd_puts(str);
	
	lcd_custom_char(0, Grado);
	lcd_gotorc(1,8);
	lcd_data(0);
	
	lcd_gotorc(2,1);
	lcd_puts("T:");
	
	lcd_gotorc(2,3);
	sprintf(str, "%i", TEMP);
	lcd_puts(str);
	
	
	lcd_custom_char(0, Grado);
	lcd_gotorc(2,6);
	lcd_data(0);
	
	
	lcd_custom_char(1, Fan);
	lcd_gotorc(2,16);
	lcd_data(1);
	
	lcd_gotorc(2,17);
	sprintf(str, "%i", SeletAire);
	lcd_puts(str);
	
	lcd_gotorc(2,20);
	lcd_puts("%");

	if(!Banderas.Estado){
		lcd_gotorc(1,17);
		lcd_puts("OFF");
	}else{
		lcd_gotorc(1,18);
		lcd_puts("ON");
	}
	
	_delay_ms(100);
}