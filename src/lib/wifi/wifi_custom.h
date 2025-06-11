/*
 * wifi_custom.h
 */
#ifndef WIFI_CUSTOM_H
#define WIFI_CUSTOM_H

#include <WiFi.h>

void connectWifi();

void wifiEvent(WiFiEvent_t event);

void maintainConnectionOTA();

#endif