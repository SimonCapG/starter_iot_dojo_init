/*
 * wifi_custom.cpp
 */
#include "wifi_custom.h"
#include <ArduinoOTA.h>
#include <WiFi.h>
#include <Ticker.h>
#include <lib/mqtt/mqtt_custom.h>

const char *ssid = "SSID_WIFI";
const char *password = "xxxxxxx";

WiFiClient espClient;
Ticker wifiMqttReconnectTimer;

/**
 * Fonction pour la connexion au wifi et au mqtt
 */
void connectWifi()
{
    WiFi.onEvent(wifiEvent); // config du callback pour gérer les event de Wifi.begin
    WiFi.begin(ssid, password);
}

/**
 * Fonction pour gérer les event de Wifi.begin
 * SYSTEM_EVENT_STA_START    <== 	Le mode station a démarré (WiFi.begin() a été appelé)
 * SYSTEM_EVENT_STA_CONNECTED   <==  Connexion au réseau établie (mais pas encore d’IP)
 * SYSTEM_EVENT_STA_GOT_IP   <==  L’ESP32 a obtenu une adresse IP (connexion réussie)
 * SYSTEM_EVENT_STA_DISCONNECTED  <== Déconnexion du réseau Wi-Fi
 *
 */
void wifiEvent(WiFiEvent_t event)
{
    switch (event)
    {
    case SYSTEM_EVENT_STA_START:
        Serial.println("Wi-Fi connexion start");
        break;
    case SYSTEM_EVENT_STA_CONNECTED:
        Serial.println("Connecté au Wi-Fi mais pas encore d'IP");
        break;
    case SYSTEM_EVENT_STA_GOT_IP:
        Serial.print("Connecté + IP : " + WiFi.localIP().toString() + "   ");
        //Connexion au MQTT
        setupMqtt();
        connectMqtt();
        // Initialisation OTA
        ArduinoOTA.begin();
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        Serial.println("Déconnecté. Tentative de reconnexion...");
        wifiMqttReconnectTimer.detach(); // on s'assure de ne pas se reconnecter au MQTT pendant la reconnexion au wifi
        WiFi.begin();
        delay(3000);
        break;
    }
}

/**
 * Fonction piur maintenir la connexion OTA
 */
void maintainConnectionOTA()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        // Serial.println("Toujours connecté au Wi-Fi!");
        ArduinoOTA.handle(); // Gère les mises à jour OTA
    }
}