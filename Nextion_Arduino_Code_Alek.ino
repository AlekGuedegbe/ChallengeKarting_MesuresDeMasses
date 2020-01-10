

/**
 *
 * HX711 library for Arduino - example file
 * https://github.com/bogde/HX711
 *
 * MIT License
 * (c) 2018 Bogdan Necula
 *
**/
#include "HX711.h"
#include <SoftwareSerial.h>
#include <Nextion.h>



SoftwareSerial nextionBroche(16,17);// RX,TX

//Composants de l'interface
NexNumber n0 = NexNumber(1,10,"n0");
NexNumber n1 = NexNumber(1,6,"n1");
NexNumber n2 = NexNumber(1,7,"n2");
NexNumber n3 = NexNumber(1,10,"n3");
NexNumber n4 = NexNumber(2,6,"n4");


// HX711 Choix des broches 
const int Horloge_SCK=2;

const int Donnee_DT_AVG =3;

const int Donnee_DT_AVD =4;

const int Donnee_DT_ARG =5;

const int Donnee_DT_ARD =6;

float   Roue_AVG=0;
float   Roue_AVD=0;
float   Roue_ARG=0;
float   Roue_ARD=0;
float   Total;




HX711 PesantAVG;
HX711 PesantAVD;
HX711 PesantARG;
HX711 PesantARD;


void setup() {
  Serial.begin(9600);
  Serial.println("");

  //Verification du bon fonctionnement de l'ecran
  if(nexInit()) {
    Serial.println("setup ok");
  } else {
    Serial.println("Setup error !!! ");
    while(1){;}
  }

  Serial.println("Démarrage du processus de calibrage\n");

  // Initialize library with data output pin, clock input pin and gain factor.
  // Channel selection is made by passing the appropriate gain:
  // - With a gain factor of 64 or 128, channel A is selected
  // - With a gain factor of 32, channel B is selected
  // By omitting the gain factor parameter, the library
  // default "128" (Channel A) is used here.
 
 PesantAVG.begin(Donnee_DT_AVG,Horloge_SCK);
  PesantAVD.begin(Donnee_DT_AVD,Horloge_SCK);
   PesantARG.begin(Donnee_DT_ARG,Horloge_SCK);
    PesantARD.begin(Donnee_DT_ARD,Horloge_SCK);
  
  Serial.println("_____________________________________Informations Brutes sans calibrage___________________________"); //Cette rubrique n'est nécéssaire que pour trouver l'échelle et la tare 
  
    Serial.print("Lecture Brute: \t\t\n\n"); // Mesure unique sans aucun parametrage , mesure brute 
  
                     Serial.print("ROUE AVANT GAUCHE: \t\t");
                         Serial.println( PesantAVG.read());  // afficher la sortie brute 
                         Serial.print("\n");

                    Serial.print("ROUE AVANT DROITE: \t\t");
                        Serial.println( PesantAVD.read());  // afficher la sortie brute 
                        Serial.print("\n");

                   Serial.print("ROUE ARRIERE GAUCHE: \t\t");
                        Serial.println( PesantARG.read());  // afficher la sortie brute 
                        Serial.print("\n");

                  Serial.print("ROUE ARRIERE DROITE: \t\t");
                        Serial.println( PesantARD.read());  // afficher la sortie brute 
                        Serial.print("\n\n");

    Serial.print("Lecture moyenne: \t\t\n\n");
  
           Serial.print("ROUE AVANT GAUCHE: \t\t");
                Serial.println( PesantAVG.read_average(5));    // Moyenne de 20 lectures
                Serial.print("\n");

          Serial.print("ROUE AVANT DROITE: \t\t");
                Serial.println( PesantAVD.read_average(5));    // Moyenne de 20 lectures
                Serial.print("\n");

          Serial.print("ROUE ARRIERE GAUCHE: \t\t");
                Serial.println( PesantARG.read_average(5));    // Moyenne de 20 lectures
                Serial.print("\n");

            Serial.print("ROUE ARRIERE DROITE: \t\t");
                Serial.println( PesantARD.read_average(5));    // Moyenne de 20 lectures
                Serial.print("\n");
  
  
  
  
  Serial.print(" Lecture moyenne moins la tare : \t\t\n\n");
            
             Serial.print("ROUE AVANT GAUCHE: \t\t");    
                Serial.println( PesantAVG.get_value(1));    //Moyenne moins la tare (Une seule mesure pour l'instant)
                Serial.print("\n");
             
             Serial.print("ROUE AVANT DROITE: \t\t");    
                Serial.println( PesantAVD.get_value(1));   //Moyenne moins la tare (Une seule mesure pour l'instant)
                Serial.print("\n");  

            Serial.print("ROUE ARRIERE GAUCHE: \t\t");    
                Serial.println( PesantARG.get_value(1));    //Moyenne moins la tare (Une seule mesure pour l'instant)
                Serial.print("\n");

             Serial.print("ROUE ARRIERE DROITE: \t\t");    
                Serial.println( PesantARD.get_value(1));    //Moyenne moins la tare (Une seule mesure pour l'instant)
                Serial.print("\n");

               
   
  Serial.print("Lecture Finale: \t\t\n\n");
          
          Serial.print("ROUE AVANT GAUCHE: \t\t");   
                Serial.println( PesantAVG.get_units(5), 1); // Mesure finale de la masse brute sans application de l'échelle et sans enlever la tare 
                Serial.print("\n");

          Serial.print("ROUE AVANT DROITE: \t\t");   
                Serial.println( PesantAVD.get_units(5), 1);  // Mesure finale de la masse brute sans application de l'échelle et sans enlever la tare 
                Serial.print("\n");

          Serial.print("ROUE ARRIERE GAUCHE: \t\t");   
                Serial.println( PesantARG.get_units(5), 1);  // Mesure finale de la masse brute sans application de l'échelle et sans enlever la tare 
                Serial.print("\n");

         Serial.print("ROUE ARRIERE DROITE: \t\t");   
                Serial.println( PesantARD.get_units(5), 1);  // Mesure finale de la masse brute sans application de l'échelle et sans enlever la tare 
                Serial.print("\n");
   
   
   
   
   PesantAVG.set_scale(48765);                      // Valeur obtenue grace a la masse  brute obtenue plus haut  (Ici on a fait Masse moyenne brute / Masse réelle de l'objet)
   PesantAVG.tare(109022);                // La tare correspond a la valeur de la masse brute obtenue sans aucun objet sur la balance  
   
   PesantAVD.set_scale(39377);                      // Valeur obtenue grace a la masse  brute obtenue plus haut  (Ici on a fait Masse moyenne brute / Masse réelle de l'objet)
   PesantAVD.tare(127567);               // La tare correspond a la valeur de la masse brute obtenue sans aucun objet sur la balance 

   PesantARG.set_scale(45828);                      // Valeur obtenue grace a la masse  brute obtenue plus haut  (Ici on a fait Masse moyenne brute / Masse réelle de l'objet)
   PesantARG.tare(16017);               // La tare correspond a la valeur de la masse brute obtenue sans aucun objet sur la balance  

   PesantARD.set_scale(39600);                      // Valeur obtenue grace a la masse  brute obtenue plus haut  (Ici on a fait Masse moyenne brute / Masse réelle de l'objet)
   PesantARD.tare(64896);               // La tare correspond a la valeur de la masse brute obtenue sans aucun objet sur la balance  
   
   
   
 Serial.println("_________________________________ Réglages de l'échelle et de la tare:____________________________"); // Cette partie permet de vérifier que les paramètres de calibrages ( échelle et tarage ) sont bons 

       Serial.print("Lecture unique: \t\n");
                 
          Serial.print("ROUE AVANT GAUCHE: \t");  
                  Serial.println( PesantAVG.read());                 // affichage d'une mesure de masse avec application de l'échelle
                  Serial.print("\n");
                  
           Serial.print("ROUE AVANT DROITE: \t");
                  Serial.println( PesantAVD.read());                 // affichage d'une mesure de masse avec application de l'échelle
                  Serial.print("\n");
                  
           Serial.print("ROUE ARRIERE GAUCHE: \t");     
                  Serial.println( PesantARG.read());                 // affichage d'une mesure de masse avec application de l'échelle
                  Serial.print("\n");

           Serial.print("ROUE ARRIERE DROITE: \t");
                  Serial.println( PesantARD.read());                 // affichage d'une mesure de masse avec application de l'échelle
                  Serial.print("\n\n");
   
   
   
  Serial.print("Lecture moyenne:\t\t\n");

  Serial.print("ROUE AVANT GAUCHE: \t");
          Serial.println( PesantAVG.read_average(5));       //moyenne de 20 mesures , pour améliorer la précision de notre mesure 
          Serial.print("\n");

   Serial.print("ROUE AVANT DROITE: \t\t");
          Serial.println( PesantAVD.read_average(5));       //moyenne de 20 mesures , pour améliorer la précision de notre mesure 
          Serial.print("\n");

   Serial.print("ROUE ARRIERE GAUCHE: \t");
          Serial.println( PesantARG.read_average(5));       //moyenne de 20 mesures , pour améliorer la précision de notre mesure 
          Serial.print("\n");

    Serial.print("ROUE ARRIERE DROITE: \t");
          Serial.println( PesantARD.read_average(5));       //moyenne de 20 mesures , pour améliorer la précision de notre mesure 
          Serial.print("\n\n");
   
  
  Serial.print("Lecture moyenne moins la tare : \t\t\n");
 
    Serial.print("ROUE AVANT GAUCHE: \t");
                Serial.println( PesantAVG.get_value(5));    // Moyenne de 5 mesure avec la tare en moins 
                Serial.print("\n");

    Serial.print("ROUE AVANT DROITE: \t");
                Serial.println( PesantAVD.get_value(5));    // Moyenne de 5 mesure avec la tare en moins 
                Serial.print("\n");

    Serial.print("ROUE ARRIERE GAUCHE: \t");
                Serial.println( PesantARG.get_value(5));    // Moyenne de 5 mesure avec la tare en moins 
                Serial.print("\n");

     Serial.print("ROUE AVANT DROITE: \t");
                Serial.println( PesantARD.get_value(5));    // Moyenne de 5 mesure avec la tare en moins 
                Serial.print("\n\n");

 
   
  Serial.print("Lecture finale: \t\t\n");
   
    Serial.print("ROUE AVANT GAUCHE: \t"); 
          Serial.println( PesantAVG.get_units(5), 1);        // Moyenne de 5 mesures finales avec application de tous les paramètres,tares et échelle
          Serial.print("\n");

    Serial.print("ROUE AVANT DROITE: \t"); 
          Serial.println( PesantAVD.get_units(5), 1);        // Moyenne de 5 mesures finales avec application de tous les paramètres,tares et échelle
          Serial.print("\n");

    Serial.print("ROUE ARRIERE GAUCHE: \t"); 
          Serial.println( PesantARG.get_units(5), 1);        // Moyenne de 5 mesures finales avec application de tous les paramètres,tares et échelle
          Serial.print("\n");

     Serial.print("ROUE ARRIRE DROITE: \t"); 
          Serial.println( PesantARD.get_units(5), 1);        // Moyenne de 5 mesures finales avec application de tous les paramètres,tares et échelle
          Serial.print("\n\n");



  Serial.println("___________________________________Fin du Processus de calibrage___________________________________________ \n\n\n");
 
  
  Serial.println("_________________________________Mesure de la masse sur la balance______________________________________________\n\n");
}


void loop() {
        
        
       delay(50);   
      Serial.print("\t||Masses Actuelles sur la balance :\t\n");

    Roue_AVG=PesantAVG.get_units(5), 1;//( moyenne de 20 mesure );
       Serial.print("ROUE AVANT GAUCHE: \t");
               Serial.print(abs(Roue_AVG));
               Serial.print("Kg\n");
               n0.setValue(Roue_AVG);
              
               

                           
               delay(50);
               

   Roue_AVD=PesantAVD.get_units(5), 1;//( moyenne de 20 mesure );
        Serial.print("ROUE AVANT DROITE: \t");
               Serial.print(abs(Roue_AVD));
               Serial.print("Kg\n");
               n2.setValue(Roue_AVD);

                        
                delay(50);
               

  Roue_ARG=PesantARG.get_units(5), 1;//( moyenne de 20 mesure );
         Serial.print("ROUE ARRIERE GAUCHE: \t");
               Serial.print(abs(Roue_ARG));
               Serial.print("Kg\n");
               n1.setValue(Roue_ARG);

                         
               delay(50);
              

   Roue_ARD=PesantARD.get_units(5), 1;//( moyenne de 20 mesure );
         Serial.print("ROUE ARRIERE DROITE: \t");
               Serial.print(abs(Roue_ARD));
               Serial.print("Kg\n");
                n3.setValue(Roue_ARD);

                 delay(50);
               

                
               
               Total=abs(Roue_ARD)+abs(Roue_ARG)+abs(Roue_AVD)+abs(Roue_AVG);
         Serial.print("Total\t");
               Serial.print(Total);
               Serial.print("Kg\n");
                n4.setValue(Total);
       
               
               

          



}
