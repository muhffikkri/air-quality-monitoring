/**
 * @file main.cpp
 * @brief Orchestrator utama sistem Monitoring Kualitas Udara.
 * @author Capstone Project - Air Quality Smart Monitoring System 
 * @version 1.0
 * @date 16-04-2026
 * * @details
 * **Mekanisme Kerja**:
 * 1. Melakukan inisialisasi seluruh modul (Sensor dan Notifier).
 * 2. Menjalankan siklus pemutakhiran data sensor secara non-blocking.
 * 3. Mengevaluasi kondisi udara berdasarkan ambang batas (threshold).
 * 4. Memicu notifikasi WhatsApp dan logging Cloud jika prasyarat terpenuhi.
 */

#include <Arduino.h>
#include "global_config.h"
#include "secrets.h"
#include "SensorManager.h"
#include "Notifier.h"

// ==========================================
// INSTANSI OBJEK (Global Instances)
// ==========================================
/** @brief Objek global untuk manajemen sensor */
SensorManager g_sensors;  

/** @brief Objek global untuk layanan komunikasi */
Notifier g_notifier;      

// ==========================================
// VARIABEL PENGENDALI (Timing Control)
// ==========================================
/** @brief Menyimpan timestamp terakhir sampling dilakukan */
unsigned long g_last_sampling_time_ms = 0;

/**
 * @brief Fungsi inisialisasi awal sistem.
 * * @details
 * **Initial State**: Perangkat baru dinyalakan, pin dalam status default, WiFi mati.
 * **Final State**: Serial monitor aktif, perangkat keras terkonfigurasi, WiFi terhubung.
 * **Mekanisme**:
 * 1. Memulai komunikasi Serial untuk debugging.
 * 2. Memanggil metode Begin() dari SensorManager untuk inisialisasi pin.
 * 3. Memanggil metode ConnectWiFi() dari Notifier untuk akses internet.
 * * @return void
 */
void setup() {
  Serial.begin(115200);
  Serial.println("\n[SYSTEM] Booting Air Quality Smart Monitoring...");

  // Inisialisasi LED Indikator
  pinMode(PIN_LED_STATUS, OUTPUT);
  digitalWrite(PIN_LED_STATUS, HIGH);

  // Inisialisasi Modul-Modul
  g_sensors.Begin();
  g_notifier.ConnectWiFi();

  Serial.println("[SYSTEM] Hardware and Network Ready.");
  digitalWrite(PIN_LED_STATUS, LOW);
}

/**
 * @brief Loop utama pemrosesan data dan logika keputusan.
 * * @details
 * **Initial State**: Menunggu interval sampling atau status kesiapan sensor.
 * **Final State**: Data terkirim ke Cloud/WhatsApp jika kondisi terpenuhi.
 * **Mekanisme**:
 * 1. Memanggil g_sensors.Update() secara kontinu untuk memantau status warm-up.
 * 2. Melakukan pengecekan g_sensors.IsReady() sebelum mengolah data.
 * 3. Jika durasi SAMPLING_INTERVAL tercapai:
 * - Ambil nilai AQI, CO2, dan Smoke.
 * - Bandingkan AQI dengan AQI_THRESHOLD_WARNING.
 * - Jika melampaui, panggil g_notifier.SendWhatsAppAlert().
 * - Selalu panggil g_notifier.LogToThingSpeak() untuk data logging.
 * * @return void
 */
void loop() {
  // 1. Selalu perbarui status internal sensor (termasuk timer warm-up)
  g_sensors.Update();

  // 2. Jalankan logika hanya jika hardware sudah stabil (Warm-up selesai)
  if (g_sensors.IsReady()) {
    
    // Eksekusi berdasarkan interval sampling (Non-blocking)
    if (millis() - g_last_sampling_time_ms >= SAMPLING_INTERVAL) {
      
      // Ambil data dari SensorManager
      float current_aqi = g_sensors.GetCombinedAQI();
      float current_co2 = g_sensors.GetCO2(); // Raw/PPM data
      float current_smoke = g_sensors.GetSmoke(); // Raw/PPM data

      // Tampilkan data ke Serial Monitor
      Serial.printf("[DATA] AQI: %.2f | CO2: %.2f | Smoke: %.2f\n", 
                    current_aqi, current_co2, current_smoke);

      // 3. Logika Ambang Batas (Alert System)
      if (current_aqi > AQI_THRESHOLD_WARNING) {
        String alert_content = "WARNING! Air quality at " + String(LOKASI) + 
                               " is POOR. AQI: " + String(current_aqi);
        
        g_notifier.SendWhatsAppAlert(alert_content);
        digitalWrite(PIN_LED_STATUS, HIGH); // Indikator visual bahaya
      } else {
        digitalWrite(PIN_LED_STATUS, LOW);
      }

      // 4. Sinkronisasi Data ke Cloud
      g_notifier.LogToThingSpeak(current_aqi, current_co2, current_smoke);

      g_last_sampling_time_ms = millis();
    }

  } else {
    // Memberikan informasi progres pemanasan sensor 
    static unsigned long last_print_ms = 0;
    if (millis() - last_print_ms >= 5000) {
      Serial.printf("[SYSTEM] Sensor warming up... %d s remaining.\n", 
                    g_sensors.GetWarmupCountdown());
      last_print_ms = millis();
    }
  }
}