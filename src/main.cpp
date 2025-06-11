#include <Arduino.h>
#include "lib/wifi/wifi_custom.h"
#include "lib/mqtt/mqtt_custom.h"

#define LED_TEST 2 // petit rappel pour définir constante en C

/**
 * Fonciton pour tester l'envoie de logs
 */
void testLog();

/**
 * Fonction de setup
 * ici mettre les déclarations des PIN INPUT ET OUTPUT
 * cette fonction ne s'exécute qu'un fois au boot de l'ESP32
 */
void setup() {
  //déclaration du Serial pour init la communication série pour la sortie console
  Serial.begin(9600);
  connectWifi();
}

/**
 * Fonction loop
 * Principe de l'embarquer, cette fonction est appelé en boucle afin de récupérer les informations et d'effectuer des actions
 * Attention aux fonctions bloquantes appelées dedans
*/
void loop() {
  maintainConnectionOTA();

  testLog();
}

/**
 * Fonction pour tester l'envoi de log via le MQTT
 */
void testLog() {
  String message = "TEST DE FOU";
  logMessage("equipe de fou", message); //log sur le dash avec l'équipe en paramètre et le message, topic mqtt => logs/equipe de fou
  delay(1000);
}