/**
 * @file SensorManager.cpp
 * @brief Implementasi skeleton untuk manajemen sensor.
 */

#include "SensorManager.h"

/**
 * Mekanisme: Inisialisasi awal variabel member ke nilai nol atau false.
 */
SensorManager::SensorManager() {
  // Skeleton: Reset variabel internal.
  this->aqiScore = 0.0f;
  this->rawCO2 = 0.0f;
  this->rawSmoke = 0.0f;
  this->startTime = 0;
  this->isWarmReady = false;
}

/**
 * Mekanisme: Akses langsung (getter) ke variabel anggota raw_co2_val_.
 * @return float Nilai CO2.
 */
float SensorManager::GetCO2() {
  // Skeleton: Return raw_co2_val_.
  return this->rawCO2;
}

/**
 * Mekanisme: Akses langsung (getter) ke variabel anggota raw_smoke_val_.
 * @return float Nilai Smoke/Gas.
 */
float SensorManager::GetSmoke() {
  // Skeleton: Return raw_smoke_val_.
  return this->rawSmoke;
}

/**
 * Mekanisme: 
 * 1. Mengatur mode pin analog sesuai pinout di global_config.h.
 * 2. Mencatat millis() saat ini ke start_time_.
 */
void SensorManager::Begin() {
  // Skeleton: Konfigurasi pinMode.
  pinMode(PIN_MQ135, INPUT);
  pinMode(PIN_MQ2, INPUT);

  this->startTime = millis();
  this->isWarmReady = false;
}

/**
 * Mekanisme: 
 * 1. Verifikasi apakah waktu saat ini > SENSOR_WARMUP_TIME.
 * 2. Eksekusi analogRead pada pin sensor.
 * 3. Kalkulasi normalisasi data mentah ke skala AQI.
 */
void SensorManager::Update() {
  // Skeleton: Logika pembacaan ADC dan kalkulasi AQI.
  unsigned long elapsedTime = millis() - this->startTime;

  //cek warm up
  if (!this->isWarmReady && (elapsedTime >= SENSOR_WARMUP_TIME))  {
    this->isWarmReady = true;
  }

  //eksekusi analogRead (sensor stabil)
  if (this->isWarmReady) {
    this->rawCO2 = analogRead(PIN_MQ135);
    this->rawSmoke = analogRead(PIN_MQ2);
  }

  //kalkulasi?
  this->aqiScore = (0.7f * this->rawCO2) + (0.3f * this->rawSmoke);
}

//dummy data untuk testing
void SensorManager::SetDummyData(float co2_val, float smoke_val) {
    this->rawCO2 = co2_val;
    this->rawSmoke = smoke_val;
    
    this->aqiScore = (0.7f * this->rawCO2) + (0.3f * this->rawSmoke);
}

/**
 * Mekanisme: Mengembalikan nilai variabel aqi_score_ yang diperbarui oleh Update().
 */
float SensorManager::GetCombinedAQI() {
  // Skeleton: Return value aqi.
  return this->aqiScore;
}

/**
 * Mekanisme: Mengevaluasi variabel is_warm_ready_ yang diatur di dalam Update().
 */
bool SensorManager::IsReady() {
  // Skeleton: Return status kesiapan.
  return this->isWarmReady;
}

/**
 * Mekanisme: Kalkulasi matematis sisa waktu berdasarkan konstanta global.
 */
int SensorManager::GetWarmupCountdown() {
  // Skeleton: Perhitungan sisa waktu detik.
  // return 0;
  if (this->isWarmReady) {
    return 0;
  }

  unsigned long elapsed = millis() - this->startTime;
  
  if (elapsed >= SENSOR_WARMUP_TIME) {
    return 0;
  }
  //konversi ms ke s
  return (SENSOR_WARMUP_TIME - elapsed) / 1000;
}