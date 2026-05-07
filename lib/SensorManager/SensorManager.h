/**
 * @file SensorManager.h
 * @brief Header file untuk manajemen akuisisi data sensor gas dan udara.
 */

#ifndef LIB_SENSORMANAGER_SENSORMANAGER_H_
#define LIB_SENSORMANAGER_SENSORMANAGER_H_

#include <Arduino.h>
#include "global_config.h"

/**
 * @class SensorManager
 * @brief Kelas untuk menangani pembacaan, kalibrasi, dan kalkulasi AQI dari sensor MQ.
 */
class SensorManager {
 private:
     //ATRIBUT
     float aqiScore;
     float rawCO2;
     float rawSmoke;
     unsigned long startTime;
     bool isWarmReady;
     
 public:
  /**
   * @brief Konstruktor untuk inisialisasi awal objek SensorManager.
   * * @details 
   * **Initial State**: Objek dibuat, variabel data (_aqi, _co2) bernilai 0.
   * **Final State**: Objek siap digunakan; variabel internal diatur ke nilai default.
   * **Mekanisme**: Mengatur flag kesiapan sensor ke false dan me-reset timer.
   * * @return Instance of SensorManager.
   */
  SensorManager();

  /**
   * @brief Mengambil nilai konsentrasi gas CO2 terbaru.
   * @details 
   * **Initial State**: Fungsi dipanggil untuk kebutuhan logging atau display.
   * **Final State**: Mengembalikan nilai mentah atau PPM CO2 hasil pembacaan terakhir.
   * **Mekanisme**: Mengambil data dari variabel privat raw_co2_val_.
   * @return float Nilai CO2 dalam satuan raw ADC atau PPM (tergantung implementasi).
   */
  float GetCO2();

  /**
   * @brief Mengambil nilai konsentrasi asap/gas (smoke) terbaru.
   * @details 
   * **Initial State**: Fungsi dipanggil oleh modul eksternal (main/notifier).
   * **Final State**: Mengembalikan nilai konsentrasi gas/asap terbaru.
   * **Mekanisme**: Mengambil data dari variabel privat raw_smoke_val_.
   * @return float Nilai gas/asap dalam satuan raw ADC atau PPM.
   */
  float GetSmoke();
  
  /**
   * @brief Konfigurasi perangkat keras dan pin sensor.
   * * @details 
   * **Initial State**: Pin mikrokontroler dalam status default (floating).
   * **Final State**: Pin didefinisikan sebagai INPUT; waktu mulai (start_time) dicatat.
   * **Mekanisme**: Memanggil pinMode() untuk sensor MQ-135 dan MQ-2.
   * * @return void.
   */
  void Begin();

  /**
   * @brief Melakukan pengambilan data dan perhitungan berkala.
   * * @details 
   * **Initial State**: Menggunakan data dari siklus sebelumnya.
   * **Final State**: Data analog terbaru dibaca; nilai AQI terbaru dihitung dan disimpan.
   * **Mekanisme**: Membaca nilai ADC, mengecek durasi warm-up, dan menghitung bobot AQI.
   * * @return void.
   */
  void Update();

  /**
   * @brief Mengambil hasil perhitungan indeks kualitas udara (AQI) gabungan.
   * * @details 
   * **Initial State**: Fungsi dipanggil oleh orchestrator.
   * **Final State**: Mengembalikan nilai AQI hasil kalkulasi terakhir.
   * **Mekanisme**: Akses langsung ke variabel privat aqi_score_.
   * * @return float Nilai AQI dalam rentang skala yang ditentukan (0.0 - 500.0).
   */
  float GetCombinedAQI();

  /**
   * @brief Mengecek apakah sensor sudah melewati masa pemanasan (warm-up).
   * * @details 
   * **Initial State**: Status kesiapan diminta untuk pengecekan logika.
   * **Final State**: Mengembalikan status boolean kesiapan hardware.
   * **Mekanisme**: Membandingkan uptime sistem dengan ambang batas SENSOR_WARMUP_TIME.
   * * @return bool True jika sensor sudah stabil dan siap memberikan data akurat.
   */
  bool IsReady();

  /**
   * @brief Mendapatkan estimasi waktu sisa pemanasan sensor.
   * * @details 
   * **Initial State**: Sensor dalam fase awal penyalaan.
   * **Final State**: Memberikan angka sisa waktu dalam detik.
   * **Mekanisme**: Pengurangan (Target Time - Current Time).
   * * @return int Sisa waktu warm-up (detik).
   */
  int GetWarmupCountdown();

  //dummy untuk testing
  void SetDummyData(float co2_val, float smoke_val);

//  private:
//   float aqi_score_;           ///< Skor AQI gabungan hasil perhitungan.
//   float raw_co2_val_;         ///< Nilai ADC mentah dari sensor CO2.
//   float raw_smoke_val_;       ///< Nilai ADC mentah dari sensor Gas/Asap.
//   unsigned long start_time_;  ///< Waktu saat Begin() dipanggil.
//   bool is_warm_ready_;        ///< Status kestabilan sensor.
};

#endif  // LIB_SENSORMANAGER_SENSORMANAGER_H_