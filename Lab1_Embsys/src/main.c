#include <asf.h>
#include <stdio.h>

static char strbuf[128];

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */

	//init board
	board_init();

	//init lcd
	gfx_mono_init();

	//set background lcd on
	gpio_set_pin_high(LCD_BACKLIGHT_ENABLE_PIN);
	
	//toggle flag 1=low, 0=high
	int flagLed0=1;
	int flagLed1=1;

	uint64_t counter = 0;
	
	gfx_mono_draw_string("Spinning...",0, 0, &sysfont);
	gfx_mono_draw_string("UwU OwO",0, 8, &sysfont);
	
	for (int ii = 0; ii < 18; ii++) {
		if (ii % 3 == 0) {
			gpio_toggle_pin(LED0);
		} else if (ii % 3 == 1) {
			gpio_toggle_pin(LED1);
		} else if (ii % 3 == 2) {
			gpio_toggle_pin(LED2);
		}
		delay_ms(250);
	}
	
	//set display - output lcd
	gfx_mono_draw_string("Praktik Embsys 1: IO",0, 0, &sysfont);
	gfx_mono_draw_string("Genap = Buzz",0, 8, &sysfont);
	gfx_mono_draw_string("Steven - 1906293322",8, 16, &sysfont);
	
	//set J1 Pin 0 to output
	ioport_set_pin_dir(J1_PIN0, IOPORT_DIR_OUTPUT);

	//forever loop
	while(1){
 		if(ioport_get_pin_level(GPIO_PUSH_BUTTON_1)==0){
 			flagLed1 = (flagLed1==0) ? 1 : 0;
		}
		
		if(ioport_get_pin_level(GPIO_PUSH_BUTTON_2)==0){
			counter = counter+1;
		}
		
		// Hold untuk menyalakan LED0
		ioport_set_pin_level(LED0_GPIO,ioport_get_pin_level(GPIO_PUSH_BUTTON_0));
		
		// Menyalakan LED1 sesuai flag (toggle)
		ioport_set_pin_level(LED1_GPIO,flagLed1);

		snprintf(strbuf, sizeof(strbuf), "Counter : %3d",counter); // Show counter to lcd
		gfx_mono_draw_string(strbuf,24, 24, &sysfont);
		
		
		
		// Toggle J1 PIN 0 (Buzzer) menyala / mati
		if (counter % 2 == 0){
			ioport_set_pin_level(J1_PIN0, 1);		} else {
			ioport_set_pin_level(J1_PIN0, 0);
		}
		
		delay_ms(50);
	}	
}