/**
 * @file test_main.cpp
 * @brief Unit testing untuk modul SensorManager.
 */

#include <unity.h>
#include "SensorManager.h"
#include "global_config.h"

SensorManager g_test_sensors;

/**
 * @brief Prosedur yang dijalankan sebelum setiap test case.
 * **Initial State**: Objek dalam kondisi mentah.
 * **Final State**: Objek diinisialisasi ulang.
 * **Mekanisme**: Memanggil konstruktor atau Begin().
 */
void setUp(void) {
  g_test_sensors = SensorManager();
  g_test_sensors.Begin();
}

void tearDown(void) {}

/**
 * @test Memverifikasi state awal SensorManager setelah Begin().
 * **Mekanisme**: Mengecek nilai default, status kesiapan, dan countdown warm-up.
 * **Ekspektasi**: Semua nilai sensor masih nol, belum siap, dan countdown tidak negatif.
 */
void TestInitialSensorManagerState(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.0001, 0.0, g_test_sensors.GetCombinedAQI());
  TEST_ASSERT_FLOAT_WITHIN(0.0001, 0.0, g_test_sensors.GetCO2());
  TEST_ASSERT_FLOAT_WITHIN(0.0001, 0.0, g_test_sensors.GetSmoke());
  TEST_ASSERT_FALSE(g_test_sensors.IsReady());
  TEST_ASSERT_GREATER_OR_EQUAL_INT(0, g_test_sensors.GetWarmupCountdown());
  TEST_ASSERT_LESS_OR_EQUAL_INT(SENSOR_WARMUP_TIME / 1000,
                                g_test_sensors.GetWarmupCountdown());
}

/**
 * @test Verifikasi status warm-up sensor.
 * **Mekanisme**: Memastikan IsReady() mengembalikan false saat awal dinyalakan.
 */
void TestWarmupInitialState(void) {
  TEST_ASSERT_FALSE(g_test_sensors.IsReady());
  TEST_ASSERT_GREATER_OR_EQUAL_INT(0, g_test_sensors.GetWarmupCountdown());
}

/**
 * @brief Entry point untuk Unity test runner di ESP32.
 */
void setup() {
  delay(2000); 
  UNITY_BEGIN();

  RUN_TEST(TestInitialSensorManagerState);
  RUN_TEST(TestWarmupInitialState);

  UNITY_END();
}

void loop() {}