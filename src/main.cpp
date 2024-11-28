#include <Arduino.h>

const int BUTTON_PIN = 12; // Vilken pin knappen ska vara på
const int LED_PIN = 10; // Vilken pin LED:en ska vara på
const int DEBOUNCE_DELAY = 50; // Delay för att reglera debounce

enum ButtonState { // Här skapar vi en egen datatyp som heter ButtonState. Den kan anta fyra olika värden.
  UP,
  PRESSED,
  DOWN,
  RELEASED
};

enum SystemState { // Här skapar vi en egen datatyp som heter SystemState. Den kan ha två olika värden.
  LED_ON,
  LED_OFF
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

SystemState state = LED_OFF; // Startvärde för hela systemets tillstånd

void loop() {
  delay(10);
  ButtonState buttonState = buttonRead(); // Kör funktionen som läser av knappen

  switch (buttonState) { // switch case är en kontrollstruktur i C++ som kan hantera state machines på ett bra sätt.
  // Det liknar if/else if/else
    
    case DOWN: // Om vi är i tillståndet att knappen är nedtryckt
      Serial.println("Turning on LED"); // Felsökning
      digitalWrite(LED_PIN, HIGH); // Tänd LED:en
      state = LED_ON; // Ändra tillstånd
      
      break; // I slutet av en case måste vi alltid ha en break, för annars kör den alla case
    
    case UP: // Om vi är i tillståndet att knappen är uppe
        Serial.println("Turning off LED"); // Felsökning
        digitalWrite(LED_PIN, LOW); // Släck LED:en
        state = LED_OFF; // Ändra tillstånd
      
      break;
  }
}