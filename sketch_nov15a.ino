#define IN1  11
#define IN2  10
#define IN3 9
#define IN4 8
#define IN5 5
#define IN6 4
#define IN7 3
#define IN8 2

int Steps1 = 0; // On déclare les variables pour le sens du moteur, le nombre de pas et le temps pour lequel il va rester sur une position
int Steps2 = 0;
int Steps3 = 0;
int Steps4 = 0;

bool Direction = false;

void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(IN5, OUTPUT);
  pinMode(IN6, OUTPUT);
  pinMode(IN7, OUTPUT);
  pinMode(IN8, OUTPUT);
  }

void loop() 
{
  Pas2(700,512);
  Pas(700,512);
}


byte temps (int intervalle) // cette fonction fait passer l'état haut à l'état bas aprés un certain interval de temps
{        
  static int Time = 0; // La variable est déclaré une fois à 0

  if(Time < intervalle) // tant que le temps n'est pas dépassée
  {
    delayMicroseconds(1); // on attend une micro seconde
    Time++;               // on incrémente la variable Time de 1 quasiment toutes les microsecondes (Time se rapproche de la valeur intervalle en meme temps que le reste du progamme s'execute)
    return 1;             // on retourne 1, valeur que prendra state. A state = 1 on reste a l'état haut (la fonction temps sera rappelle)
  }
  else
  {
    Time=0;      // on remet Time à 0 pour recommencer la nouvelle boucle de temps
    return 2;    // on retourne 2, valeur que prendra state. A state = 2 on repasse à l'etat bas.
  }

}

void Pas2(int intervalle2, int borne) 
{
    static byte state = 0;
     
    if (state == 0)
    {
        switch(Steps3)
      {
        case 0:
        digitalWrite(IN8, HIGH);
        state = 1;
        break;

        case 1:
        digitalWrite (IN8, HIGH);
        digitalWrite (IN7, HIGH);
        state = 1;
        break;

        case 2:
        digitalWrite (IN7, HIGH);
        state = 1;
        break;

        case 3:
        digitalWrite(IN6, HIGH);
        digitalWrite (IN7, HIGH);
        state = 1;
        break;

        case 4:
        digitalWrite (IN6, HIGH);
        state = 1;
        break;

        case 5:
        digitalWrite (IN5, HIGH);
        digitalWrite (IN6, HIGH);  
        state = 1;
        break; 

        case 6:
        digitalWrite (IN5, HIGH);
        state = 1;
        break; 

        case 7:
        digitalWrite (IN8, HIGH);
        digitalWrite (IN5, HIGH);
        state = 1;
        break;        
      }
     direction3();   
    }

    if (state == 1)
    {
        state = temps(intervalle2);
    }

    if (state == 2){
     switch(Steps4)
      {
        case 0:
        digitalWrite (IN8, LOW);
        state = 0;
        break;

        case 1:
        digitalWrite (IN8, LOW);
        digitalWrite (IN7, LOW);
        state = 0;
        break;

        case 2:
        digitalWrite (IN7, LOW);
        state = 0;
        break;

        case 3:
        digitalWrite (IN6, LOW);
        digitalWrite (IN7, LOW);
        state = 0;
        break;

        case 4:
        digitalWrite (IN6, LOW);
        state = 0;
        break;

        case 5:
        digitalWrite (IN5, LOW);
        digitalWrite (IN6, LOW);
        state = 0;
        break;

        case 6:
        digitalWrite (IN5, LOW);
        state = 0;
        break;

        case 7:
        digitalWrite (IN8, LOW);
        digitalWrite (IN5, LOW);
        state = 0;
        break;
      }
     direction1();  
    }

}

void Pas(int intervalle1, int borne) // la fonction pour controler le premier moteur 
{
    static byte state = 0; // on declare une premiere fois state a 0
  // La fonction est divisé en 3, sois state est à 0, et on enverra du courant dans une ou deux bobines (état haut), soit state est à 1 et on attendra, soit state est à 2 
  // et on arrête d'envoyer le courant. Une fois le cycle fait (etat haut, attente, etat bas) on recommence.   
    if (state == 0) // etat haut
    {
        switch(Steps1) // en fonction de la valeur de Steps1 on active tel ou tel bobine
      {
        case 0:
        digitalWrite(IN4, HIGH);
        state = 1; //apres l'avoir active on passe a state = 1 
        break; // on sort du switch, on tombe sur direction

        case 1:
        digitalWrite (IN4, HIGH);
        digitalWrite (IN3, HIGH);
        state = 1;
        break;

        case 2:
        digitalWrite (IN3, HIGH);
        state = 1;
        break;

        case 3:
        digitalWrite(IN2, HIGH);
        digitalWrite (IN3, HIGH);
        state = 1;
        break;

        case 4:
        digitalWrite (IN2, HIGH);
        state = 1;
        break;

        case 5:
        digitalWrite (IN1, HIGH);
        digitalWrite (IN2, HIGH);  
        state = 1;
        break; 

        case 6:
        digitalWrite (IN1, HIGH);
        state = 1;
        break; 

        case 7:
        digitalWrite (IN4, HIGH);
        digitalWrite (IN1, HIGH);
        state = 1;
        break;        
      }
      direction1();
    }

    if (state == 1)
    {
        state = temps(intervalle1);
    }

    if (state == 2){
     switch(Steps2)
      {
        case 0:
        digitalWrite (IN4, LOW);
        state = 0;
        break;

        case 1:
        digitalWrite (IN4, LOW);
        digitalWrite (IN3, LOW);
        state = 0;
        break;

        case 2:
        digitalWrite (IN3, LOW);
        state = 0;
        break;

        case 3:
        digitalWrite (IN2, LOW);
        digitalWrite (IN3, LOW);
        state = 0;
        break;

        case 4:
        digitalWrite (IN2, LOW);
        state = 0;
        break;

        case 5:
        digitalWrite (IN1, LOW);
        digitalWrite (IN2, LOW);
        state = 0;
        break;

        case 6:
        digitalWrite (IN1, LOW);
        state = 0;
        break;

        case 7:
        digitalWrite (IN4, LOW);
        digitalWrite (IN1, LOW);
        state = 0;
        break;
      }
     direction2();      
    }    
    }
 
    
void direction3(){ // direction (1,2,3 ou 4) incremente Steps(1,2,3 ou 4) pour respecter la sequence d'allumage des bobines  
  if(Direction==1){
        Steps3++;
    }
    if(Direction==0){
        Steps3--;
    }
    if(Steps3>7){
        Steps3=0;
    }
    if(Steps3<0){
        Steps3=7;       
    }
}

void direction4(){
  if(Direction==1){
        Steps4++;
    }
    if(Direction==0){
        Steps4--;
    }
    if(Steps4>7){
        Steps4=0;
    }
    if(Steps4<0){
        Steps4=7;       
    }
}
void direction2(){
  if(Direction==1){
        Steps3++;
        Steps4++;
    }
    if(Direction==0){
        Steps3--;
        Steps4--;
    }
    if(Steps1>7){
        Steps3=0;
        Steps4=0;
    }
    if(Steps1<0){
        Steps3=7;   
        Steps4=7;     
    }
}
//void direction1(){
//  if(Direction==1){
//        Steps1++;
//    }
//    if(Direction==0){
//        Steps1--;
//    }
//    if(Steps1>7){
//        Steps1=0;
//    }
//    if(Steps1<0){
//        Steps1=7;       
//    }
//}
//
//void direction2(){
//  if(Direction==1){
//        Steps4++;
//    }
//    if(Direction==0){
//        Steps4--;
//    }
//    if(Steps4>7){
//        Steps4=0;
//    }
//    if(Steps4<0){
//        Steps4=7;       
//    }
//}

void direction(){
  if(Direction==1){
        Steps1++;
    }
    if(Direction==0){
        Steps1--;
    }
    if(Steps1>7){
        Steps1=0;
    }
    if(Steps1<0){
        Steps1=7;     
    }
}

void pas(int DELAY, int borne){
  for ( int n=0; n < borne; n++ ) // boucle pour compter le nombre de pas
    {
      for ( int p=0; p < 9; p++ ) // boucle pour faire toutes les sequences qui font un pas
    {
      switch(Steps1)
      {
        case 0:
        digitalWrite(IN4, HIGH);
        delayMicroseconds (DELAY);
        digitalWrite (IN4, LOW);
        break;

      case 1:
        digitalWrite (IN4, HIGH);
        digitalWrite (IN3, HIGH);
        delayMicroseconds (DELAY);
        digitalWrite (IN4, LOW);
        digitalWrite (IN3, LOW);
        break;

      case 2:
        digitalWrite (IN3, HIGH);
        delayMicroseconds (DELAY);
        digitalWrite (IN3, LOW);
        break;

      case 3:
        digitalWrite(IN2, HIGH);
        digitalWrite (IN3, HIGH);
        delayMicroseconds (DELAY);
        digitalWrite (IN2, LOW);
        digitalWrite (IN3, LOW);
        break;

      case 4:
        digitalWrite (IN2, HIGH);
        delayMicroseconds (DELAY);
        digitalWrite (IN2, LOW);
        break;

      case 5:
        digitalWrite (IN1, HIGH);
        digitalWrite (IN2, HIGH);
        delayMicroseconds (DELAY);
        digitalWrite (IN1, LOW);
        digitalWrite (IN2, LOW);
        break;

      case 6:
        digitalWrite (IN1, HIGH);
        delayMicroseconds (DELAY);
        digitalWrite (IN1, LOW);
        break;

      case 7:
        digitalWrite (IN4, HIGH);
        digitalWrite (IN1, HIGH);
        delayMicroseconds (DELAY);
        digitalWrite (IN4, LOW);
        digitalWrite (IN1, LOW);
        break;
      }
      direction();
    }
      
   }
}

void pas2(int DELAY, int borne){
  for ( int n=0; n < borne; n++ )
    {
      for ( int p=0; p < 9; p++ )
    {
      switch(Steps1)
      {
        case 0:
        digitalWrite(IN8, HIGH);
        delayMicroseconds (DELAY);
        digitalWrite (IN8, LOW);
        break;

      case 1:
        digitalWrite (IN8, HIGH);
        digitalWrite (IN7, HIGH);
        delayMicroseconds (DELAY);
        digitalWrite (IN8, LOW);
        digitalWrite (IN7, LOW);
        break;

      case 2:
        digitalWrite (IN7, HIGH);
        delayMicroseconds (DELAY);
        digitalWrite (IN7, LOW);
        break;

      case 3:
        digitalWrite(IN6, HIGH);
        digitalWrite (IN7, HIGH);
        delayMicroseconds (DELAY);
        digitalWrite (IN6, LOW);
        digitalWrite (IN7, LOW);
        break;

      case 4:
        digitalWrite (IN6, HIGH);
        delayMicroseconds (DELAY);
        digitalWrite (IN6, LOW);
        break;

      case 5:
        digitalWrite (IN5, HIGH);
        digitalWrite (IN6, HIGH);
        delayMicroseconds (DELAY);
        digitalWrite (IN5, LOW);
        digitalWrite (IN6, LOW);
        break;

      case 6:
        digitalWrite (IN5, HIGH);
        delayMicroseconds (DELAY);
        digitalWrite (IN5, LOW);
        break;

      case 7:
        digitalWrite (IN8, HIGH);
        digitalWrite (IN5, HIGH);
        delayMicroseconds (DELAY);
        digitalWrite (IN8, LOW);
        digitalWrite (IN5, LOW);
        break;
      }
//      direction();
    }
    }
      
    }
