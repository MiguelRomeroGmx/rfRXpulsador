#include <VirtualWire.h>

unsigned long last = millis();
int ledPin = 13;

void setup()
{
    Serial.begin(9600);	// Debugging only
    Serial.println("setup");

    // Se inicializa el RF
    vw_setup(2000);	 // velocidad: Bits per segundo
    vw_set_rx_pin(2);  //Pin 2 como entrada del RF
    vw_rx_start();       // Se inicia como receptor
    
    pinMode(ledPin, OUTPUT);    //Configuramos el pin del Led como entrada
    digitalWrite(ledPin, false);
}

void loop()
{

    boolean ledState = digitalRead(ledPin);//check if the LED is turned on or off. Returns 1 or 0
    uint8_t dato;
    uint8_t datoleng=1;
    //verificamos si hay un dato valido en el RF
    if (vw_get_message(&dato,&datoleng))
    {

            Serial.print(dato);
            if(millis() - last > 250){//if time now is 250 milliseconds greater than last time
                if(ledState == 0 && (char)dato=='a'){//if LED is off and button code is ok
                 digitalWrite(ledPin, HIGH);
                }else if(ledState == 1 && (char)dato=='a'){//if LED is on and button code is ok
                   digitalWrite(ledPin, LOW);
                    }
      
                    }
    last = millis();//reset timer              
    }
    delay(80);
}
