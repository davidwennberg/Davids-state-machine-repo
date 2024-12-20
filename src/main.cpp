#include <Arduino.h>

const int button_pin = 12;
const int LED_pin = 10;
const int pot_pin = 8;


int last_button_state = HIGH;
int LED_state = LOW;

void setup() {
  Serial.begin(115200);
  pinMode(button_pin, INPUT_PULLUP);
  pinMode(pot_pin, INPUT);
  ledcAttach(LED_pin, 5000, 8);
  analogReadResolution(12);
}

void loop() {

  int pot_reading = analogRead(pot_pin);
  
  int output = map(pot_reading, 0, 4095, 0, 255);

  int button_state = digitalRead(button_pin);

  if(button_state == LOW and last_button_state == HIGH) { //Debouncing
    Serial.println("Knapptryck registrerad, debouncing"); //Felsökning
    
    delay(20);

    button_state = digitalRead(button_pin);

    if (button_state != last_button_state) {

      Serial.println("Knapptryck confirmed"); //Felsökning
      Serial.println(output);
      ledcWrite(LED_pin, output);
      last_button_state = button_state;
      LED_state = !LED_state;
      Serial.println(LED_state);
      
    }
    
  }
  delay(10);
}



































/*
const int BUTTON_PIN = 12; // Vilken pin knappen ska vara på
const int LED_PIN = 10; // Vilken pin LED:en ska vara på
const int DEBOUNCE_DELAY = 50; // Delay för att reglera debounce
const int BLINK_TIME = 250;
int LAST_LED_UPDATE = 0;
int LED_STATE = LOW;
int TIMEOUT_TIME = 5000;
unsigned long TIME_STATE_CHANGE;

enum ButtonState { // Här skapar vi en egen datatyp som heter ButtonState. Den kan anta fyra olika värden.
  UP,
  PRESSED,
  DOWN,
  RELEASED
};

enum SystemState { // Här skapar vi en egen datatyp som heter SystemState. Den kan ha tre olika värden.
  LED_ON,
  LED_OFF,
  LED_BLINK
};

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Vilken slags pin knappen ska vara
  pinMode(LED_PIN, OUTPUT); // Vilken slags pin LED:en ska vara
}

int lastButtonState = HIGH; // En variabel som håller reda på senaste buttonstate. Från början uppsläppt.

ButtonState buttonRead() { // En funktion som läser av knappen och returnerar i vilket state den är.
// Funktionen är av typen ButtonState, vilket ju är vår egna datatyp
  
  int reading = digitalRead(BUTTON_PIN); // Läser av knappens värde

  if (reading != lastButtonState) { // Om värdet är annorlunda från senaste state
    delay(DEBOUNCE_DELAY); // Vänta för att säkerställa att knappstatus är stabil
    reading = digitalRead(BUTTON_PIN); // Läs knappstatus igen

    if (reading != lastButtonState) { // Om den fortfarande är annorlunda än senaste state
      lastButtonState = reading; // Uppdatera buttonstate
      if (lastButtonState == LOW) { // Om knappen är nedtryckt
        Serial.println("PRESSED"); // Felsökning
        return PRESSED; // Returnerar PRESSED, eftersom att vi är i det tillfälle då knappen precis trycks ner
      }
      else { // Om knappen är uppsläppt
        Serial.println("RELEASED"); // Felsökning
        return RELEASED; // Returnerar RELEASED, eftersom att vi är i det tillfälle då knappen precis släpps upp
      }
    }
  }

  if (lastButtonState == LOW) { // Om buttonstate inte har ändrats och den är nedtryckt
    return DOWN; // Returnera att knappen är i stabilt nedtryckt tillstånd
  }
  else { // Om buttonstate inte har ändrats och den är uppsläppt
    return UP; // Returnera att knappen är i stabilt uppsläppt läge
  }
}

void BLINK_LED() { //Funktion för att blinka LEDen
  int reading = millis();
      if (reading - LAST_LED_UPDATE >= BLINK_TIME) {
        LAST_LED_UPDATE = reading;
        LED_STATE = !LED_STATE;
        digitalWrite(LED_PIN,LED_STATE);
      }
}
SystemState state = LED_OFF; // Startvärde för hela systemets tillstånd

void loop() {
  ButtonState buttonState = buttonRead(); // Kör funktionen som läser av knappen

  switch (state) { // switch case är en kontrollstruktur i C++ som kan hantera state machines på ett bra sätt.
  // Det liknar if/else if/else
    
    case LED_OFF: // Om vi är i tillståndet att LED är av
      digitalWrite(LED_PIN, LOW); //Om ingen knapp trycks ned ska LEDen fortsätta vara släckt
      if (buttonState==PRESSED) { //Om vi fick tillbaka att knappen precis trycks ner
        Serial.println("Turning on LED"); // Felsökning
        digitalWrite(LED_PIN, HIGH); // Tänd LED:en
        TIME_STATE_CHANGE = millis(); //Starta klockan för timeout när tillståndet ändras
        state = LED_ON; // Ändra tillstånd
      }

      break; // I slutet av en case måste vi alltid ha en break, för annars kör den alla case
    
    case LED_ON: // Om vi är i tillståndet att LED är på
      digitalWrite(LED_PIN, HIGH); //Om ingen knapp trycks ned ska LEDen fortsätta vara tänd
      if (buttonState==PRESSED) { // Om vi fick tillbaka att knappen precis trycks ner
        Serial.println("Starting LED blink"); // Felsökning
        TIME_STATE_CHANGE = millis(); //Starta klockan för timeout när tillståndet ändras
        state = LED_BLINK; // Ändra tillstånd
      }
      else if (millis() - TIME_STATE_CHANGE >= TIMEOUT_TIME) { //Stäng av LEDen om knappen ej rörts på 5 sekunder
        state = LED_OFF;
      }
      break;
    
    case LED_BLINK: //Om vi är i tillståndet att LEDen blinkar
      BLINK_LED();
      if (buttonState==PRESSED) { //Om vi fick tillbaka att knappen precis trycks ner
        Serial.println("Turning off LED"); // Felsökning
        digitalWrite(LED_PIN, LOW); // Släck LED:en
        TIME_STATE_CHANGE = millis(); //Starta klockan för timeout när tillståndet ändras
        state = LED_OFF; // Ändra tillstånd
      }
      else if (millis() - TIME_STATE_CHANGE >= TIMEOUT_TIME) { //Stäng av LEDen om knappen ej rörts på 5 sekunder
        state = LED_OFF;
      }
      break;
  }   
}

*/