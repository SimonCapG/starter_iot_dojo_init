/*
 * mqtt_custom.h
 */
#ifndef MQTT_CUSTOM_H
#define MQTT_CUSTOM_H

#include <Arduino.h>  // Nécessaire pour le type String
#include <AsyncMqttClient.h>

void connectMqtt();

void setupMqtt();

void onMqttConnect(bool sessionPresent);

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason);

void logMessage(String equipe, String message);

void sendInfoSensor(String sensor, String equipe, String value);

#endif