#include <Servo.h>                            //inclusione libreria servo

Servo servohori;                              //servo orizzontale 
int servoh;                                   //valore posizione orizzontale
const int servohLimitHigh = 168;              //limite massimo 178°
const int servohLimitLow = 20;                 //limite minimo 2°
//////////////////////////////
Servo servoverti;                             //servo verticale
int servov;                                   //valore posizione verticale 
const int servovLimitHigh = 168;              //limite superiore 178°
const int servovLimitLow = 20;                 //limite superiore 2°
/////////////////////////////
const int ldrtopleft = 0;                     //fotoresistenza in alto a sinistra
const int ldrtopright = 1;                    //fotoresistenza in alto a destra
const int ldrbotleft = 2;                     //fotoresistenza in basso a sinistra
const int ldrbotright = 3;                    //fotoresistenza in basso a destra
/////////////////////////////
const int TOL = -20;                          //tolleranza per la differenza tra i valori dei fotoresistori
const unsigned long WAIT_SENSORS = 5;         //attesa tra le misurazioni dello stesso fotoresistore di cui si fa le media
const unsigned long WAIT_ACTUATORS = 1;      //attesa dopo il pilotaggio dei servomotori
const unsigned long WAIT_LOOP = 1000;            //attesa tra un ciclo e l'altro del loop


void setup () 
{
  Serial.begin(9600);  
  
  servoh = 30;                    //inizializzazione del valori del servomotore orizzontale
  servohori.attach(9);                        //esplicitazione collegamento servo orizzontale e pin 9
  servohori.write(servoh);                    //posizione di partenza servo orizzontale 
  //////////////////////////
  servov = 60;                    //inizializzazione del valori del servomotore verticale
  servoverti.attach(10);                      //esplicitazione collegamento servo verticale e pin 10
  servoverti.write(servov);                   //posizione di partenza servo verticale
  
  delay(500);
}

void loop()
{
  int topl1 = analogRead(ldrtopleft);          //creazione della variabile contenente il valore di tensione relativo alla fotoresistenza in alto a sinistra 
  delay(WAIT_SENSORS);
  int topl2 = analogRead(ldrtopleft);
  int topl = (topl1 + topl2)/2;
  ///////////////////////
  int topr1 = analogRead(ldrtopright);         //creazione della variabile contenente il valore di tensione relativo alla fotoresistenza in alto a destra
  delay(WAIT_SENSORS);
  int topr2 = analogRead(ldrtopright);
  int topr = (topr1 + topr2)/2;
  //////////////////////
  int botl1 = analogRead(ldrbotleft);          //creazione della variabile contenente il valore di tensione relativo alla fotoresistenza in basso a sinistra
  delay(WAIT_SENSORS);
  int botl2 = analogRead(ldrbotleft);
  int botl = (botl1 + botl2)/2;
  //////////////////////
  int botr1 = analogRead(ldrbotright);         //creazione della variabile contenente il valore di tensione relativo alla fotoresistenza in basso a destra
  delay(WAIT_SENSORS);
  int botr2 = analogRead(ldrbotright);
  int botr = (botr1 + botr2)/2;
  /////////////////////
  int avgtop = (topl + topr) / 2;              //calcolo del valore medio delle fotoresistenze in alto
  int avgbot = (botl + botr) / 2;              //calcolo del valore medio delle fotoresistenze in basso
  int avgleft = (topl + botl) / 2;             //calcolo del valore medio delle fotoresistenze a sinistra
  int avgright = (topr + botr) / 2;            //calcolo del valore medio delle fotoresistenze a destra

  if ((avgtop - avgbot)< TOL)                  //se la media dei valori di quelle in alto è minore di quella dei valori di quelle in basso
  {
    Serial.print(" LOW ");
    servov --;
    if (servov < servovLimitLow)               //se il valore della posizione è maggiore del limite superiore
    { 
      servov = servovLimitLow;                 //il motore assume la posizione corrispondente al limite superiore
    }
    servoverti.write(servov);                  //il motore si orienterà verso il basso
    delay(WAIT_ACTUATORS);
  }
  else if ((avgbot - avgtop)< TOL)             //se la media dei valori di quelle in basso è minore di quella dei valori di quelle in alto             
  {
    Serial.print(" HIGH ");
    servov ++;
    if (servov > servovLimitHigh)              //se il valore della posizione è minore del limite inferiore
    {
      servov = servovLimitHigh;                //il motore assume la posizione corrispondente al limite inferiore
    }
    servoverti.write(servov);                  //il motore si orienterà verso l'alto
    delay(WAIT_ACTUATORS);
  }

  if ((avgleft - avgright)< TOL)               //se la media dei valori di quelle a sinistra è maggiore di quella dei valori di quelle a destra 
  {
    Serial.print(" RIGHT ");
    servoh ++;
    if (servoh > servohLimitHigh)              //se il valore della posizione è maggiore del limite sinistro
    {
      servoh = servohLimitHigh;                //il motore assume la posizione corrispondente al limite sinistro
    }
    servohori.write(servoh);                   //il motore si orienterà verso sinistra
    delay(WAIT_ACTUATORS);
  }
  else if ((avgright - avgleft)< TOL)          //se la media dei valori di quelle a destra è maggiore di quella dei valori di quelle a sinistra 
  {
    Serial.print(" LEFT ");
    servoh --;
    if (servoh < servohLimitLow)               //se il valore della posizione è maggiore del limite destro
    {
      servoh = servohLimitLow;                 //il motore assume la posizione corrispondente al limite destro
    }
    servohori.write(servoh);                   //il motore si orienterà verso destra
    delay(WAIT_ACTUATORS);
  }
  delay(WAIT_LOOP);
  Serial.println("");
//////////////////////////////////Debug
 /*
  Serial.print("topl ");
   Serial.print(topl);
    Serial.print("  topr");
     Serial.print(topr);
  Serial.print("  botl ");
   Serial.print(botl);
    Serial.print("  botr");
     Serial.println(botr);

  Serial.print("servo vert: ");
  Serial.print(servov);
  Serial.print("  servo horiz: ");
  Serial.println(servoh); 
*/
}
