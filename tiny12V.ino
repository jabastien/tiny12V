/*
	R. J. Tidey 2017/02/22
	12V led acid battery monitor based on ATTiny85 (digispark)
	3 LEDs green, amber, red warning levels

 */

#define LED_COUNT 3
#define BATTERY A1
#define CLK_DIV 16
//time in msec for switch to trigger
#define FLASH_INTERVAL 250
#define TIME_LOOP 20

uint8_t ledPins[LED_COUNT] = {0,1,5};
int ledLevels[LED_COUNT] = {907, 888, -1};
int timeCounter = 0;

void setup(){
	cli(); // Disable interrupts
	CLKPR = (1<<CLKPCE); // Prescaler enable
	CLKPR = 4; // Clock division factor 16 1MHz
	sei(); // Enable interrupts	int i;
	int i;
	for(i = 0; i < LED_COUNT; i++) {
		pinMode(ledPins[i], OUTPUT);
	}
	analogReference(DEFAULT);
}

void flashLeds() {
	int adc = analogRead(BATTERY);
	int i;
	for(i = 0; i < LED_COUNT; i++) {
		if(adc > ledLevels[i]) {
			digitalWrite(ledPins[i], 1);	
			break;			
		}
	}
	delay(FLASH_INTERVAL / CLK_DIV);
	for(i = 0; i < LED_COUNT; i++) {
		digitalWrite(ledPins[i], 0);
	}
}

void loop(){
	if(timeCounter <= 0) {
		flashLeds();
		timeCounter = TIME_LOOP;
	}
	timeCounter--;
	delay(FLASH_INTERVAL / CLK_DIV);
}