#include <Servo.h>                            //inclusione libreria servo
Servo servohori;                              //servo orizzontale 
int servoh = 0;                               //valore iniziale 0° 
int servohLimitHigh = 178;                    //limite massimo 160°
int servohLimitLow = 2;                       //limite minimo 20°
Servo servoverti;                             //servo verticale
int servov = 0;                               //valore iniziale 0° 
int servovLimitHigh = 178;                    //limite superiore 160°
int servovLimitLow = 2;                       //limite superiore 20°
int ldrtopl = 2;                              //fotoresistenza in alto a sinistra
int ldrtopr = 1;                              //fotoresistenza in alto a destra
int ldrbotl = 3;                              //fotoresistenza in basso a sinistra
int ldrbotr = 0;                              //fotoresistenza in basso a destra

 void setup () 
 {
  Serial.begin(9600);                          
  servohori.attach(9);                        //esplicitazione collegamento servo orizzontale e pin 9
  servohori.write(0);                         //posizione di partenza servo orizzontale = 0°
  servoverti.attach(10);                      //esplicitazione collegamento servo verticale e pin 10
  servoverti.write(0);                        //posizione di partenza servo verticale = 0°
  delay(500);
 }

void loop()
{
  servoh = servohori.read();                   //viene rilevato il valore della posizione del servo orizzontale 
  servov = servoverti.read();                  //viene rilevato il valore della posizione del servo orizzontale 
  int topl = analogRead(ldrtopl);              //creazione della variabile contenente il valore di tensione relativo alla fotoresistenza in alto a sinistra 
  int topr = analogRead(ldrtopr);              //creazione della variabile contenente il valore di tensione relativo alla fotoresistenza in alto a destra
  int botl = analogRead(ldrbotl);              //creazione della variabile contenente il valore di tensione relativo alla fotoresistenza in basso a sinistra
  int botr = analogRead(ldrbotr);              //creazione della variabile contenente il valore di tensione relativo alla fotoresistenza in basso a destra
  int avgtop = (topl + topr) / 2;              //calcolo del valore medio delle fotoresistenze in alto
  int avgbot = (botl + botr) / 2;              //calcolo del valore medio delle fotoresistenze in basso
  int avgleft = (topl + botl) / 2;             //calcolo del valore medio delle fotoresistenze a sinistra
  int avgright = (topr + botr) / 2;            //calcolo del valore medio delle fotoresistenze a destra

  if ((avgtop - avgbot)< -40)                  //se la media dei valori di quelle in alto è minore di quella dei valori di quelle in basso
  {
    servoverti.write(servov -1);               //il motore si orienterà verso il basso
    if (servov > servovLimitHigh)              //se il valore della posizione è maggiore del limite superiore
     { 
      servov = servovLimitHigh;                //il motore assume la posizione corrispondente al limite superiore
     }
    delay(10);
  }
  else if ((avgbot - avgtop)< -40)             //se la media dei valori di quelle in basso è minore di quella dei valori di quelle in alto             
  {
    servoverti.write(servov +1);               //il motore si orienterà verso l'alto
    if (servov < servovLimitLow)               //se il valore della posizione è minore del limite inferiore
    {
    servov = servovLimitLow;                   //il motore assume la posizione corrispondente al limite inferiore
    }
    delay(10);
  }
  else 
  {
    servoverti.write(servov);                  //se il valore di luminosità è uguale in prossimità delle resistenze controllate il motore mantiene la sua posizione 
  }
  
  if ((avgleft - avgright)>40)                 //se la media dei valori di quelle a sinistra è maggiore di quella dei valori di quelle a destra 
  {
    servohori.write(servoh -1);                //il motore si orienterà verso sinistra
    if (servoh > servohLimitHigh)              //se il valore della posizione è maggiore del limite sinistro
    {
    servoh = servohLimitHigh;                  //il motore assume la posizione corrispondente al limite sinistro
    }
    delay(10);
  }
  else if ((avgright - avgleft)>40)            //se la media dei valori di quelle a destra è maggiore di quella dei valori di quelle a sinistra 
  {
    servohori.write(servoh +1);                //il motore si orienterà verso destra
    if (servoh < servohLimitLow)               //se il valore della posizione è maggiore del limite destro
     {
     servoh = servohLimitLow;                  //il motore assume la posizione corrispondente al limite destro
     }
    delay(10);
  }
  else 
  {
    servohori.write(servoh);                   //se il valore di luminosità è uguale in prossimità delle resistenze controllate il motore mantiene la sua posizione
  }
  delay(10);
  Serial.print("topl ");
   Serial.print(topl);
    Serial.print("  topr");
     Serial.print(topr);
  Serial.print("  botl ");
   Serial.print(botl);
    Serial.print("  botr");
     Serial.println(botr);     
}
