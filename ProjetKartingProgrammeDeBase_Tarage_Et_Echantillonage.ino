   // Programme permettant de mesurer une masse avec etape de tarage et d'etalonnage 
#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

//Définition Variables 
float MasseBrute=0;
float Scale=0;
float Etalon=17.8;
float offset=0;

HX711 scale; // Test sur un seul pesons 

//Ici dans le void setup la difference avec notre premier programme est qu'on saute de nombreuses etapes intermédiaires qui ne sont 
//pas vraiment nécéssaire losqu'on effectue un bon tarage
void setup() {
  Serial.begin(57600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  //Calibrating (Etapes proposées sur le github de bogde)
  scale.set_scale();
  scale.tare(); /* C'est la procedure dont on a rééllement besoin pour effectuer un tarage il suffit de l'appeler sans argument et
                  elle permet de tarer le pesant correspondant ici "scale"*/ 
  
  Serial.println("________Place a Known weight (delais de 10s)______\n") ;/*En fait ici il s'agit de l'etape de l'etalonnage en principe il est prévu de avec le nextion de choisir le pesons de poser une 
  une masse etalon dont on connait la masse , d'entrer cette masse puis de lancer l'etalonnage afin d'obtenir notre échelle .Vu qu'ici on utilise pas l'écran et que le serial.read ne fonctionne 
  pas du tout pour simuler un bouton on a instauré un délais de 10s en attendant d'autoriser l'echantillonnage avec notre nextion.Donc ici après que le programme nous ait demander de placer notre masse  etalon on a un délais de 10s pour le mettre sur le pesons
  Notez qu'ici on a préalablement enregistrer la masse de l'etalon dans la variable Etalon qui est au début de notre programme*/
  delay(10000);
  MasseBrute=scale.get_units(10);
  Scale=MasseBrute/Etalon;
  scale.set_scale(Scale);

}

void loop() 
{
 
  Serial.print("Weight: ");
  Serial.println(scale.get_units(10), 2); /*Ici on a plus grand chose a faire puisque notre tarage est fait et notre etalonnage aussi il suffit maintenant de poser la masse a mesurer sur le pesons 
  et on l'a affiché a l'écran toute les 3s et avec ce programme on a testé sur plusieurs objet et on a leurs masses exactes avec une erreur quasi nulle*/ 
  delay(3000);
  
}
