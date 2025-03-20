#include <Wire.h>
#include <LiquidCrystal_I2C_Hangul.h>

// Define pins for IR sensors and Relay module
#define IR1pin 2
#define IR2pin 3
#define Relay1pin 8

// Debounce delay for sensor triggering (in milliseconds)
const int IR_TRIGGER_DELAY = 100;

// Variables for tracking room occupancy and sensor trigger timings
int count = 0;
bool inRoom = false;
unsigned long lastIR1triggerTime = 0;
unsigned long lastIR2triggerTime= 0;
bool lastTriggerWasIR1 = false;

// Initialize LCD displays for status output
LiquidCrystal_I2C_Hangul lcd(0x27, 16, 2);
LiquidCrystal_I2C_Hangul lcd2(0x20, 16, 2);

void setup() {
  // Initialize LCDs with startup messages (including project title and author info)
  initLCD(lcd);
  lcd.print("Power off. Code");
  lcd.setCursor(0, 1);
  lcd.print("by Solso.");

  initLCD(lcd2);
  lcd2.print("Room is vacant.");
  delay(10);

  // Configure IR sensor pins as INPUT_PULLUP for reliable readings
  pinMode(IR1pin, INPUT_PULLUP);
  pinMode(IR2pin, INPUT_PULLUP);

  // Attach ISR for IR sensor 1 (entry detection)
  attachInterrupt(digitalPinToInterrupt(IR1pin), IR1_ISR, FALLING);

  // Attach ISR for IR sensor 2 (exit detection)
  attachInterrupt(digitalPinToInterrupt(IR2pin), IR2_ISR, FALLING);

  // Configure Relay pin as OUTPUT and set to LOW (off) by default
  pinMode(Relay1pin, OUTPUT);
  digitalWrite(Relay1pin, LOW); 
}

void loop() {
  // If both IR sensors trigger within debounce time, determine entry/exit based on trigger order
  if (millis() - lastIR1triggerTime < IR_TRIGGER_DELAY && millis() - lastIR2triggerTime < IR_TRIGGER_DELAY) {
	if (lastTriggerWasIR1) {
	  count--;
	} else {
	  count++;
	}
	if (count < 0){
	  count = 0;
	  digitalWrite(Relay1pin, LOW);
	}
	updateDisplay();
	// Update the LCD screens
	lastIR1triggerTime = 0;
	lastIR2triggerTime = 0;
  } 
else if (millis() - lastIR1triggerTime >= IR_TRIGGER_DELAY && millis() - lastIR2triggerTime >= IR_TRIGGER_DELAY && inRoom) {
	
	updateDisplay();
	// Update the LCD screens
	
	inRoom = false;
	
  }

  delay(10);
  if (count < 0){
	  count = 0;
	  digitalWrite(Relay1pin, LOW);
  } 
}

// ISR for IR sensor 1: Handles entry detection when IR1 triggers
void IR1_ISR() {
  if (!digitalRead(IR2pin) && millis() - lastIR1triggerTime >= IR_TRIGGER_DELAY) {
	// If IR1 is triggered and IR2 has not been triggered recently, set the trigger time and mark last trigger as IR1
	lastIR1triggerTime = millis();
	lastTriggerWasIR1 = true;
	inRoom = true;
  }
}

// ISR for IR sensor 2: Handles exit detection when IR2 triggers
void IR2_ISR() {
  if (!digitalRead(IR1pin) && millis() - lastIR2triggerTime >= IR_TRIGGER_DELAY) {
	// If IR2 is triggered and IR1 has not been triggered recently, set the trigger time and mark last trigger as IR2
	lastIR2triggerTime = millis();
	lastTriggerWasIR1 = false;
	inRoom = true;
  }
}

// Update LCD displays to show current occupancy and power status
void updateDisplay() {
  lcd.clear();
  lcd2.clear();
  if (count == 0) {
	// If no one is in the room, display the appropriate message on both LCD screens and turn off the device
	lcd.setCursor(0, 0);
	lcd.print("Power is off.");
	lcd.setCursor(0, 1);
	lcd.print("No one inside.");
	
	lcd2.setCursor(0, 0);
	lcd2.print("Room is vacant.");
	lcd2.setCursor(0,1);
	lcd2.print("No one inside.");
	
	digitalWrite(Relay1pin, LOW);
  } 
  else if (count > 0 && count < 5) {
	// If there are people in the room but less than 5, display the appropriate message on both LCD screens and turn on the device
	lcd.setCursor(0, 0);
	lcd.print("Power on.");
	
	lcd2.setCursor(0, 0);
	lcd2.print("May be available"); 
		if (count == 1) {
		lcd.setCursor(0, 1);
		lcd.print("1 person in.");
		
		lcd2.setCursor(0, 1);
		lcd2.print("1 person in."); 
	}
	
	 else {
		lcd.setCursor(0, 1);
		lcd.print(count);
		lcd.print(" persons in.");
		
		lcd2.setCursor(0, 1);
		lcd2.print(count);
		lcd2.print(" persons in."); 
	 }
	
	digitalWrite(Relay1pin, HIGH); 

	if (count < 0){
	  count = 0;
	  digitalWrite(Relay1pin, LOW);  
	}   
  }
  else {
	// If there are 5 or more people in the room, display the appropriate message on both LCD screens and turn on the device
	lcd.setCursor(0, 0);
	lcd.print("Power on.");
	lcd.setCursor(0, 1);
	lcd.print(count);
	lcd.print(" persons in."); 
	
	lcd2.setCursor(0, 0);
	lcd2.print("Room is occupied");
	lcd2.setCursor(0, 1);
	lcd2.print(count);
	lcd2.print(" persons in.");  
	digitalWrite(Relay1pin, HIGH);
		}
	}

// Initialize LCD: Set up I2C communication, backlight, and display configuration 
void initLCD(LiquidCrystal_I2C_Hangul & lcd) {
  lcd.init();
  lcd.backlight();
  lcd.begin(16, 2);
}
