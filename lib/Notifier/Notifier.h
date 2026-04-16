/**
 * @file Notifier.h
 * @brief Header file untuk abstraksi layanan komunikasi WiFi dan Cloud.
 */

#ifndef LIB_NOTIFIER_NOTIFIER_H_
#define LIB_NOTIFIER_NOTIFIER_H_

#include <Arduino.h>
#include "secrets.h"
#include "global_config.h"

/**
 * @class Notifier
 * @brief Mengelola seluruh protokol komunikasi eksternal (WiFi, WhatsApp, ThingSpeak).
 * * Kelas ini bertugas sebagai jembatan antara data lokal di ESP32 dengan 
 * layanan internet pihak ketiga.
 */
class Notifier {
 public:
  /**
   * @brief Konstruktor untuk inisialisasi modul Notifier.
   * * @details 
   * **Initial State**: Objek Notifier diinstansiasi di memori.
   * **Final State**: Timestamp pengiriman internal di-reset ke 0; objek siap digunakan.
   * **Mekanisme**: Menyetel nilai awal pada variabel privat pelacak waktu (timing tracker).
   */
  Notifier();

  /**
   * @brief Melakukan prosedur autentikasi dan koneksi ke jaringan WiFi.
   * * @details 
   * **Initial State**: Modul WiFi dalam keadaan idle atau terputus.
   * **Final State**: ESP32 mendapatkan alamat IP dan status WL_CONNECTED aktif.
   * **Mekanisme**: Mengambil kredensial dari secrets.h, memanggil WiFi.begin(), 
   * dan melakukan polling status koneksi secara serial.
   * * @return void
   */
  void ConnectWiFi();

  /**
   * @brief Mengirimkan pesan peringatan bahaya ke nomor WhatsApp yang terdaftar.
   * * @details 
   * **Initial State**: Kondisi ambang batas (threshold) terlampaui dan pesan siap dikirim.
   * **Final State**: HTTP GET Request dikirim ke server CallMeBot; timestamp diperbarui.
   * **Mekanisme**: 
   * 1. Mengecek cooldown interval agar tidak terjadi spamming API.
   * 2. Melakukan URL Encoding pada string pesan.
   * 3. Menginisialisasi HTTPClient untuk melakukan request ke gateway.
   * * @param message String berisi konten pesan alert yang akan dikirim.
   * @return bool True jika request berhasil dikirim dan diterima oleh gateway (HTTP 200).
   */
  bool SendWhatsAppAlert(String message);

  /**
   * @brief Melakukan sinkronisasi dan logging data sensor ke dashboard ThingSpeak.
   * * @details 
   * **Initial State**: Data AQI, CO2, dan Gas tersedia di memori lokal.
   * **Final State**: Data terunggah ke Field 1, 2, dan 3 pada channel ThingSpeak terkait.
   * **Mekanisme**: 
   * 1. Mengecek batas interval pengiriman (default 15 detik untuk ThingSpeak).
   * 2. Menyusun query string URL dengan menyertakan API Key dan nilai sensor.
   * 3. Melakukan eksekusi HTTP GET.
   * * @param aqi Nilai gabungan indeks kualitas udara.
   * @param co2 Nilai konsentrasi CO2 hasil pembacaan SensorManager.
   * @param smoke Nilai konsentrasi gas/asap hasil pembacaan SensorManager.
   * @return void
   */
  void LogToThingSpeak(float aqi, float co2, float smoke);

 private:
  unsigned long last_wa_attempt_ms_; ///< Timestamp terakhir kali pesan WA dikirim.
  unsigned long last_ts_attempt_ms_; ///< Timestamp terakhir kali logging cloud dilakukan.
};

#endif  // LIB_NOTIFIER_NOTIFIER_H_