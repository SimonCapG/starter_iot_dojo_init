/*
 * mqtt_custom.cpp
 */
#include "mqtt_custom.h"
#include <WiFi.h>
#include <AsyncMqttClient.h>
#include <Ticker.h>
#include <Arduino.h> // Nécessaire pour le type String

// Configuration MQTT
// const char *mqtt_server = "192.168.8.108";  //ESPAGNE
#define MQTT_HOST IPAddress(192, 168, 1, 108) // 192.168.224.194
#define MQTT_PORT 1883

const char *mqtt_topic = "esp32/logs"; // déporter en parametre
const char *mqtt_topic_sensor = "test/iot";
const char *client_id = "ESP32_Client";

AsyncMqttClient mqttClient;
Ticker mqttReconnectTimer;

bool mqttConnected = false;

/**
 * Fonction pour setup MQTT
 */
void setupMqtt()
{
    // Setup MQTT
    mqttClient.onConnect(onMqttConnect);
    mqttClient.onDisconnect(onMqttDisconnect);
    mqttClient.setServer(MQTT_HOST, MQTT_PORT);
}

/**
 * Fonction pour init la connexion au MQTT
 */
void connectMqtt()
{
    Serial.println("Connexion au MQTT...");
    mqttClient.connect();
}

/**
 * Fonction de callback lorsque la connexion au MQTT réussi
 * @param sessionPresent
 */
void onMqttConnect(bool sessionPresent)
{
    Serial.println("Connexion réussi au MQTT! ");
    // Envoyer un premier message
    String message = "[" + WiFi.localIP().toString() + "] ESP32 connecté et prêt !";
    mqttClient.publish(mqtt_topic, 0, false, message.c_str());
}

/**
 * Fonction de callback lorsqu'il y a déconnexion du MQTT
 * @param reason
 */
void onMqttDisconnect(AsyncMqttClientDisconnectReason reason)
{
    Serial.println("Déconnexté du MQTT!");

    if (WiFi.isConnected())
    {
        mqttReconnectTimer.once(2, connectMqtt);
    }
}

/**
 * Fonction pour envoyer un message
 * @param equipe
 * @param message
 */
void logMessage(String equipe, String message)
{
    String topic = "logs/" + equipe;
    unsigned long timestamp_ms = millis();
    String ip = WiFi.localIP().toString();
    message = "[" + ip + "] [" + String(timestamp_ms) + "] " + message;
    mqttClient.publish(topic.c_str(), 0, true, message.c_str());
}

/**
 * Fonction pour envoyer un message
 * @param message
 * @param equipe
 * @param valuer
 */
void sendInfoSensor(String sensor, String equipe, String value)
{
    unsigned long timestamp_ms = millis();
    String json = "{\"typeSensor\": \"" + sensor + "\",\"team\": \"" + equipe + "\", \"value\": \"" + value + "\", \"timestamp\": \"" + String(timestamp_ms) + "\"}";
    mqttClient.publish(mqtt_topic_sensor, 0, true, json.c_str());
}