/**
 * @file test_main.cpp
 * @brief Realisasi Integration Testing antara SensorManager dan Notifier.
 * @author Tim Capstone - Kelompok Briefcase
 */

#include <Arduino.h>
#include <WiFi.h>
#include <unity.h>
#include "SensorManager.h"
#include "Notifier.h"
#include "global_config.h"

// ==========================================
// INSTANSI GLOBAL
// ==========================================
SensorManager g_int_sensors;
Notifier g_int_notifier;

/**
 * @brief Prosedur persiapan sebelum setiap test case.
 * **Mekanisme**: Memastikan hardware sensor siap dan WiFi terkoneksi.
 */
void setUp(void) {
  g_int_sensors.Begin();
  if (WiFi.status() != WL_CONNECTED) {
    g_int_notifier.ConnectWiFi();
  }
}

void tearDown(void) {}

/**
 * @brief Menguji alur data terintegrasi dari deteksi hingga pengiriman.
 * * @details
 * **Initial State**: WiFi terhubung, sistem siap melakukan pembacaan.
 * **Final State**: Pesan peringatan terkirim saat kondisi ambang batas terlampaui.
 * **Mekanisme**:
 * 1. Melakukan update sensor (mengambil data real/simulasi).
 * 2. Mengecek apakah nilai AQI saat ini > AQI_THRESHOLD_WARNING.
 * 3. Jika ya, memicu fungsi SendWhatsAppAlert() dan memvalidasi nilai baliknya.
 * **Input**: Data real dari sensor atau simulasi lingkungan.
 * **Output**: Status keberhasilan integrasi (Boolean).
 */
void TestSensorToNotifierAlert(void) {
  // 1. Jalankan siklus update sensor
  g_int_sensors.Update();

  // 2. Simulasikan pengecekan logika seperti pada main.cpp
  float aqi = g_int_sensors.GetCombinedAQI();
  
  // Karena ini integration test, kita menguji apakah alur pemicu notifikasi valid
  if (aqi > AQI_THRESHOLD_WARNING) {
    String test_msg = "INTEGRATION TEST: High AQI detected (" + String(aqi) + ")";
    bool is_notified = g_int_notifier.SendWhatsAppAlert(test_msg);
    
    // Verifikasi: Jika AQI tinggi, maka notifier HARUS berhasil dipanggil
    TEST_ASSERT_TRUE_MESSAGE(is_notified, "Failed to trigger WhatsApp alert on high AQI");
  } else {
    // Jika AQI rendah, kita uji pengiriman manual untuk memastikan API Notifier hidup
    bool status = g_int_notifier.SendWhatsAppAlert("INTEGRATION TEST: System Normal");
    TEST_ASSERT_TRUE_MESSAGE(status, "Notifier API is unreachable even in normal condition");
  }
}

/**
 * @brief Entry point untuk menjalankan integration test.
 */
void setup() {
  delay(2000);

  UNITY_BEGIN();

  RUN_TEST(TestSensorToNotifierAlert);

  UNITY_END();
}

void loop() {}