Tentu, ini adalah draf **README.md** profesional yang disusun untuk keperluan repositori GitHub proyek Tugas Akhir kamu. Dokumentasi ini mencakup visi proyek, aspek teknis, hingga prosedur pengujian dengan standar industri.

---

# 🌬️ Air Quality Monitoring Briefcase (AQM-BIFCAS-001)

Sistem monitoring kualitas udara portabel berbasis IoT yang dirancang untuk mendeteksi kadar CO2 dan gas berbahaya secara _real-time_ dengan fitur peringatan dini melalui WhatsApp.

---

## 📌 1. Ikhtisar Proyek

Proyek ini dikembangkan sebagai tugas akhir kuliah untuk menjawab kebutuhan akan alat pemantau kualitas udara yang portabel dan mampu memberikan notifikasi instan. Menggunakan **ESP32** sebagai otak sistem, alat ini menggabungkan sensor gas seri MQ dengan layanan _cloud_ untuk pemantauan berkelanjutan.

### **Fitur Utama:**

- **Real-Time Monitoring:** Memantau CO2 (MQ-135) dan Gas/Asap (MQ-2) setiap detik.
- **Edge Processing:** Menghitung skor AQI (_Air Quality Index_) langsung di perangkat.
- **WhatsApp Alert:** Mengirimkan peringatan otomatis ke ponsel jika udara dalam kondisi bahaya.
- **Cloud Logging:** Sinkronisasi data ke ThingSpeak untuk analisis historis.
- **Portable Design:** Desain berbentuk _briefcase_ dengan casing 3D-printed yang kokoh.

---

## 🛠️ 2. Metode Pendekatan & Arsitektur

Proyek ini menggunakan pendekatan **Modular Development** dan **Object-Oriented Programming (OOP)** untuk memastikan pengerjaan tim dapat berjalan secara paralel.

### **Alur Data (Data Flow):**

1.  **Acquisition:** Sensor membaca sinyal analog dari udara.
2.  **Processing:** ESP32 menormalisasi data (12-bit ADC) dan menghitung bobot AQI (70% CO2, 30% Smoke).
3.  **Communication:** Data dikirim via WiFi menggunakan protokol HTTP GET.
4.  **Action:** Pengguna menerima notifikasi WA melalui CallMeBot API dan visualisasi data di ThingSpeak.

---

## 📦 3. Komponen & Briefcase

### **Hardware:**

| Komponen            | Fungsi                                               |
| :------------------ | :--------------------------------------------------- |
| **ESP32 DevKit V1** | Mikrokontroler utama dengan modul WiFi terintegrasi. |
| **Sensor MQ-135**   | Deteksi CO2 dan kualitas udara umum.                 |
| **Sensor MQ-2**     | Deteksi LPG, Asap, dan gas mudah terbakar.           |
| **Buzzer/LED**      | Indikator bahaya lokal pada perangkat.               |
| **3D Printed Case** | Casing khusus dengan optimasi sirkulasi udara.       |

### **Software:**

- **Framework:** Arduino Core for ESP32.
- **Environment:** PlatformIO (VS Code).
- **Testing:** Unity Test Framework.
- **API:** ThingSpeak & CallMeBot (WhatsApp Gateway).

---

## 📂 4. Struktur Repositori

Repositori ini mengikuti standar struktur proyek PlatformIO:

```text
├── include/
│   ├── global_config.h       # Konstanta pin, threshold, dan timing.
│   ├── secrets.h             # Kredensial WiFi & API (Private).
│   └── secrets.example.h     # Template kredensial untuk tim.
├── lib/
│   ├── SensorManager/        # Modul manajemen sensor (Anggota A).
│   └── Notifier/             # Modul WiFi & Cloud API (Anggota B).
├── src/
│   └── main.cpp              # Orchestrator utama sistem (Anggota C).
├── test/                     # Unit & Integration testing (Unity).
├── platformio.ini            # Konfigurasi environment & library.
└── README.md
```

---

## 🚀 5. Cara Penggunaan

### **Persiapan Awal:**

1.  **Clone Repositori:**
    ```bash
    git clone https://github.com/username/air-quality-monitoring.git
    ```
2.  **Konfigurasi Kredensial:**
    - Salin `include/secrets.example.h` menjadi `include/secrets.h`.
    - Isi `WIFI_SSID`, `WIFI_PASS`, `WA_API_KEY`, dan `TS_API_KEY` sesuai akunmu.
3.  **Build & Upload:**
    - Buka proyek di VS Code (dengan ekstensi PlatformIO).
    - Klik **Build** (ikon centang) lalu **Upload** (ikon panah).

### **Kalibrasi:**

- Saat pertama kali dinyalakan, alat akan memasuki fase **Warm-up** selama 2 menit.
- Pastikan alat berada di udara terbuka (fresh air) selama proses pemanasan untuk akurasi maksimal.

---

## 🧪 6. Skema Pengujian (Testing)

Proyek ini dilengkapi dengan suite pengujian otomatis di folder `test/`:

1.  **Unit Testing:** Memastikan logika kalkulasi AQI di `SensorManager` akurat secara matematis.
2.  **Integration Testing:** Memastikan modul `Notifier` dapat mengirim data saat dipicu oleh `SensorManager`.
3.  **System Testing:** Pengujian _end-to-end_ dengan memberikan polutan asap nyata untuk melihat respon sistem.

**Cara menjalankan test:**

```bash
pio test -e esp32dev
```

---

## 👥 7. Tim Pengembang

- **Anggota A:** Firmware Developer (Logic Sensor & Kalibrasi).
- **Anggota B:** Cloud & Integration Developer (WiFi, WhatsApp, ThingSpeak).
- **Anggota C:** System Orchestrator & Mechanical Designer (Main Loop & 3D Design).

---

_Dibuat untuk memenuhi Tugas Akhir Informatika - Universitas Diponegoro._
