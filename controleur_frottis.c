/*
Conception d'un controleur factifs de frottis

Objectif    : Piloter l'indication de contamination à distance par une telecommande
Cadre       : Pedagogique
Harware     : Arduino nano / Leds (rouge & verte) / Interupteur 

modifie 29 septembre 2022
*/




#include <IRremote.h>
 

//On defini les pins LEDs et capteur IR
const int RECV_PIN  = 4;
const int redPin    = 7; 
const int greenPin  = 6;

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
  // On setup les LEDs en OUTPUT
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  blink(); // Foction pour indiuqer la mise en place du systeme 

}
 
void loop(){

    if (irrecv.decode(&results)){

        switch(results.value){
          case 0xFF18E7: //Button Fleche du haut
        // Toggle LED On or Off
        if(togglestate1==0){
        digitalWrite(redPin, HIGH);
        togglestate1=1;
        }
        else {
        digitalWrite(redPin, LOW);
        togglestate1=0;
        }
        break;
      
          case 0xFF4AB5: //Button flecge du bas
        // Toggle LED On or Off
        if(togglestate2==0){
        digitalWrite(greenPin, HIGH);
        togglestate2=1;
        }
        else {
        digitalWrite(greenPin, LOW);
        togglestate2=0;
        }
        break;
        
    }
    irrecv.resume(); 
  }
}

///// Fonction  /////

void blink()
{
for (compteur = 0; compteur < 5; compteur ++)
  {
    digitalWrite (redPin,HIGH);
    digitalWrite (greenPin,HIGH);
    delay(200);
    digitalWrite (redPin,LOW);
    digitalWrite (greenPin,LOW);
    delay(150);
  }
}
