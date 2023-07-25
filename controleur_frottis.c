/*
 Conception d'un controleur factifs de frottis

 Objectif    : Piloter l'indication de contamination a distance par une telecommande
 Cadre       : Pedagogique / Formation
 Harware     : Arduino nano / Leds (red & green & white) / Interupteur / Buzzer /  Recpteur IR
 Type Carte  : Arduino nano
 Processor   : Atmega 3280 (old bootLoarder)

 modifie 20 fevrier 2023
 */

 #include <IRremote.h>


 //On defini les pins LEDs / capteur IR / Buzzer
 const int RECV_PIN  = 10;
 const int redPin    = 2; 
 const int greenPin  = 3;
 const int whitePin  = 4;
 const int buzz      = 12;

 //On defini nos variables 
 int togglestate1    = 0;   
 int togglestate2    = 0;
 int compteur;

 // On defini le recepteur IR et les objets de resultats
 IRrecv irrecv(RECV_PIN);
 decode_results results;

 void setup(){
   // Active le recpteur IR
   irrecv.enableIRIn();
   // On setup les LEDs / Buzzer en OUTPUT
   pinMode(redPin, OUTPUT);
   pinMode(greenPin, OUTPUT);
   pinMode(whitePin, OUTPUT);
   pinMode(buzz, OUTPUT);

   synchronisation();               // Foction pour indiuqer la mise en place du systeme 
   digitalWrite(whitePin, HIGH);    // Temoin Lumineux de la mise sous tension du systeme

 }

void loop(){

    if (irrecv.decode(&results)){

        switch(results.value){
        
        case 0xFF10EF:        //Button flecge de XXX | LED vert
        
        if(togglestate2==0){
        digitalWrite(greenPin, HIGH);
        delay(250);
        togglestate2=1;
        }
        else {
        digitalWrite(greenPin, LOW);
        delay(250);
        togglestate2=0;
        }
        break;

        case 0xFF5AA5:        //Button Fleche de XXX | LED rouge + buzzer 
        
        if(togglestate1==0){
        digitalWrite(redPin, HIGH);
        digitalWrite(buzz,HIGH);
        delay(250);
        togglestate1=1;
        }
        else {
        digitalWrite(redPin, LOW);
        digitalWrite(buzz,LOW);
        delay(250);
        togglestate1=0;
        }
        break;
         
        
    }
    irrecv.resume(); 
  }
}

///// Fonction  /////

void synchronisation()
{
for (compteur = 0; compteur < 5; compteur ++)
  {
    digitalWrite    (redPin,HIGH);
    digitalWrite    (greenPin,HIGH);
    digitalWrite    (buzz,HIGH);
    delay(200);
    digitalWrite    (redPin,LOW);
    digitalWrite    (greenPin,LOW);
    digitalWrite    (buzz,LOW);
    delay(150);
  }
}é
