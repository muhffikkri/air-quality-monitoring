/**
 * @file test_main.cpp
 * @brief Integration testing antara SensorManager dan Notifier.
 */

#include <unity.h>
#include "SensorManager.h"
#include "Notifier.h"

SensorManager g_int_sensors;
Notifier g_int_notifier;

/**
 * @brief Menguji alur data dari sensor hingga ke pemicu notifikasi.
 * * **Initial State**: WiFi terhubung, sensor mensimulasikan kondisi bahaya.
 * **Final State**: Fungsi SendWhatsAppAlert terpanggil (mocked/real).
 * **Mekanisme**: 
 * 1. Simulasikan AQI > Threshold.
 * 2. Cek apakah integrasi memicu return true pada fungsi alert.
 */
void test_sensor_to_notifier_alert(void) {
  // Skeleton:
  // 1. Connect WiFi.
  // 2. Set AQI dummy > Threshold.
  // 3. TEST_ASSERT_TRUE(g_int_notifier.SendWhatsAppAlert("Integration Test"));
}

void setup() {
  delay(2000);
  UNITY_BEGIN();
  RUN_TEST(test_sensor_to_notifier_alert);
  UNITY_END();
}

void loop() {}