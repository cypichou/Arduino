#include <Adafruit_NeoPixel.h> // le programme doit inclure la librairie qui permet de contrôler la matrice led
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN    13 // on connecte la matrice sur la pin led 13 de l'arduino
#define NUMPIXELS 64 // le nombre de led dela matrice
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500
#include <SoftwareSerial.h>
SoftwareSerial mySerial(3, 2); // RX, TX on a change le port RX et TX pour ne pas géner la communication série entre l'arduino et la matrice
char data = 0;
String s_data = "";
String s_previousdata = "255/255/255/030/";
bool etat;
void setup()
{
  Serial.begin(38400);      
  pinMode(13, OUTPUT);
  pixels.begin();
  for(int i=0; i<NUMPIXELS; i++)
  {
  pixels.setPixelColor(i, pixels.Color(255, 255,255));
  pixels.show();                                                              
  }  
}
void loop()
{
  if(Serial.available() > 0)  // Si une information est détectée sur le port RX de l'arduino envoyé par l'arduino
  { 
   data = Serial.read();      // on initialise la variable data à l'information détecté par l'arduino
   if( data == '+')           // dès que le dernier caractères de la commande est détectée (le dernier caractère sera toujours un plus)
    {
    etat = true;              // on active la recherche de type de data qui va faire tel ou                                                               
    }                         // tel action sur la matrice led
    else
    {
    s_data += String(data);   // tant qu'on a pas le dernier caractère on continue à ajouter les informations 
    Serial.print(s_data);     // dans data pour avoir la commande au complet      
    } 
  }   
                                                              
if (etat){                                                    
  
   if( s_data == "ledON" )
   {
  s_data = "255/255/255/30";       // on rédefini le data pour donner une valeur à la couleur à laquelle va s'allumer la matrice led
  couleurLed();                    // cette fonction allume la led     
   }
  
   if( s_data == "ledOFF" )
   {
  s_data = "0/0/0/0";
  couleurLed();     
   }
   else
  {
   couleurLed(); 
  }
  s_data="";                        // On réinitialise le data
  etat =  false;                    // On arrête le bloc du programme qui analyse le data
 }
}

void couleurLed(){

  int seperateur1 = s_data.indexOf('/');                      // On obtient l'index de chaque / dans la chaîne de valeurs
  int seperateur2 = s_data.indexOf('/', seperateur1+1);
  int seperateur3 = s_data.indexOf('/', seperateur2+1); 
  int seperateur4 = s_data.indexOf('/', seperateur3+1);
 
  String rouge = s_data.substring(0, seperateur1);             // on sépare la chaine de caractere en 4 valeurs pour obtenir la valeur                                                              
  String vert = s_data.substring(seperateur1+1, seperateur2);  // de rouge, de bleu, de vert et de la luminosité
  String bleu = s_data.substring(seperateur2+1, seperateur3);
  String luminosite = s_data.substring(seperateur3+1, seperateur4);
 
  for(int i=0; i<NUMPIXELS; i= i + 1) {
 
  pixels.setPixelColor(i, pixels.Color(rouge.toInt()*luminosite.toInt()/255, vert.toInt()*luminosite.toInt()/255, bleu.toInt()*luminosite.toInt()/255)); 
  pixels.show();                                          // ici la commande de la bibliotheque avec les bonnes valeurs de couleur pour allumer les led                                                              
  }
}
