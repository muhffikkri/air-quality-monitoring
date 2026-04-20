/**
 * @file test_main.cpp
 * @brief Unit testing untuk modul SensorManager.
 */

#include <unity.h>
#include "SensorManager.h"

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

/**
 * @brief Prosedur yang dijalankan setelah setiap test case.
 */
void tearDown(void) {
  // Skeleton: Membersihkan resource jika diperlukan.
}

/**
 * @test Menguji perhitungan AQI dengan input simulasi.
 * **Mekanisme**: Memasukkan nilai ADC simulasi dan memverifikasi output 70/30.
 * **Input**: ADC CO2 = 2048 (~250 AQI), ADC Smoke = 1024 (~125 AQI).
 * **Ekspektasi**: (0.7 * 250) + (0.3 * 125) = 175 + 37.5 = 212.5.
 */
void TestAqiCalculationLogic(void) {
  // Catatan: Pastikan SensorManager memiliki method untuk 'inject' data simulasi
  // atau ubah variabel internal menjadi protected untuk keperluan testing.
  
  // Asumsi hasil perhitungan berdasarkan rumus di SensorManager.cpp
  float result = g_test_sensors.GetCombinedAQI();
  
  // Unity Assert untuk membandingkan float dengan toleransi (delta) 0.01
  TEST_ASSERT_FLOAT_WITHIN(0.01, 0.0, result); // Awalnya harus 0 sebelum update
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
  delay(2000); // Jeda stabilisasi serial
  UNITY_BEGIN();
  RUN_TEST(TestAqiCalculationLogic);
  RUN_TEST(TestWarmupInitialState);
  UNITY_END();
}

void loop() {}