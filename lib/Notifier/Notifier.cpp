/**
 * @file Notifier.cpp
 * @brief Implementasi kerangka (skeleton) fungsi komunikasi Notifier.
 */

#include "Notifier.h"

/**
 * Mekanisme: Inisialisasi variabel timestamp ke 0 agar pengiriman pertama 
 * dapat langsung dilakukan tanpa menunggu delay interval.
 */
Notifier::Notifier() {
  // Skeleton: Penentuan nilai awal variabel privat.
}

/**
 * Mekanisme: 
 * 1. Set WiFi mode ke WIFI_STA.
 * 2. Menggunakan variabel WIFI_SSID dan WIFI_PASS untuk koneksi.
 * 3. Output progres koneksi ke Serial Monitor untuk mempermudah debugging.
 */
void Notifier::ConnectWiFi() {
  // Skeleton: Implementasi logika WiFi.begin() dan pengecekan status.
}

/**
 * Mekanisme: 
 * 1. Pengecekan durasi millis() vs WHATSAPP_ALERT_DELAY.
 * 2. Mengganti karakter spasi dengan '+' agar kompatibel dengan format URL.
 * 3. Menggunakan class HTTPClient untuk transmisi data.
 * * @param message Teks berita yang ingin dikirimkan.
 */
bool Notifier::SendWhatsAppAlert(String message) {
  // Skeleton: Implementasi pembentukan URL dan HTTP GET request.
  return false; 
}

/**
 * Mekanisme: 
 * 1. Verifikasi koneksi WiFi aktif.
 * 2. Menghindari pengiriman data yang terlalu cepat (rate limiting).
 * 3. Mengirimkan data sensor ke endpoint ThingSpeak API.
 * * @param aqi Input Field 1.
 * @param co2 Input Field 2.
 * @param smoke Input Field 3.
 */
void Notifier::LogToThingSpeak(float aqi, float co2, float smoke) {
  // Skeleton: Implementasi sinkronisasi cloud dengan data 3 field.
}