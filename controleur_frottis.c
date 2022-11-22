

/*
Conception d'un controleur factifs de frottis

Objectif    : Piloter l'indication de contamination à distance par une telecommande
Cadre       : Pedagogique
Harware     : Arduino nano / Leds (rouge & verte) / Interupteur / Buzzer actif 

modifie 10 novembre 2022

Pour la v2 : on utilise un Wemos D1 mini (probleme de recetption de MCU a Orano)
Normalement on utilise une Arduino nano, cela explique les changements de Pin

*/




#include <IRremote.h>
 

//On defini les pins LEDs et capteur IR
const int RECV_PIN  = 5;
const int redPin    = 0; 
const int greenPin  = 4;
const int buzz      = 2;

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
  pinMode(buzz,OUTPUT);

  synchronisation(); // Foction pour indiuqer la mise en place du systeme 

}
 
void loop(){

    if (irrecv.decode(&results)){

        switch(results.value){
        
        case 0xFF18E7:        //Button flecge du haut | LED vert

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

        case 0xFF4AB5:        //Button Fleche du bas | LED rouge + buzzer 
      
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
}


