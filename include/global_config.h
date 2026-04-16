#ifndef GLOBAL_CONFIG_H
#define GLOBAL_CONFIG_H

#include <Arduino.h>

// ==========================================
// PIN MAPPING (ESP32)
// ==========================================
// Sensor Analog
#define PIN_MQ135      34  // GPIO34 (ADC1)
#define PIN_MQ2        32  // GPIO32 (ADC1)

// Output Lokal
#define PIN_BUZZER     25  // GPIO25
#define PIN_LED_STATUS 2   // Built-in LED

// I2C untuk OLED (Default ESP32)
#define OLED_SDA       21
#define OLED_SCL       22

// ==========================================
// AMBANG BATAS (THRESHOLDS)
// ==========================================
#define AQI_THRESHOLD_WARNING  100
#define AQI_THRESHOLD_DANGER   200
#define CO2_PPM_THRESHOLD      1000

// ==========================================
// TIMING & INTERVALS (ms)
// ==========================================
#define SENSOR_WARMUP_TIME     120000 // 2 Menit pemanasan sensor
#define SAMPLING_INTERVAL      10000   // Baca sensor tiap 10 detik
#define THINGSPEAK_INTERVAL    15000  // Batas limit ThingSpeak
#define WHATSAPP_ALERT_DELAY   60000  // Jeda antar notifikasi (agar tidak spam)

// ==========================================
// DEVICE INFO
// ==========================================
#define DEVICE_ID "AQM-BIFCAS-001"
#define LOKASI    "Departemen-Informatika-Undip"

#endif