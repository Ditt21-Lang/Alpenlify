# Alpenlify 🎵
*Alpenlify* adalah aplikasi pemutar musik berbasis terminal yang dikembangkan sebagai bagian dari tugas besar mata kuliah Struktur Data dan Algoritma. Program ini dirancang untuk membaca, mendekode, dan memutar file musik dari direktori lokal pengguna.

## 📌 Tujuan
Proyek ini bertujuan untuk mengimplementasikan konsep-konsep struktur data seperti queue dan list dalam konteks aplikasi nyata, serta membangun pemahaman mengenai pemrosesan input dan interaksi pengguna melalui antarmuka berbasis teks.

## ✨ Fitur-fitur
Alpenlify menyediakan berbagai fitur pemutaran musik, antara lain:

- ✅ Memutar musik dari direktori lokal
- ✅ Menambahkan musik ke dalam playing queue
- ✅ Melakukan seek ke waktu tertentu dalam lagu
- ✅ Skip ke lagu berikutnya dalam antrian
- ✅ Rewind lagu yang sedang berjalan
- ✅ Menampilkan daftar semua musik dalam folder musik
- ✅ Melihat isi antrian pemutaran (queue)
- ✅ Sistem input waktu fleksibel (detik, menit:detik, atau jam:menit:detik)

## ⚠ Batasan Program
- Hanya mendukung file musik dengan ekstensi .mp3
- Hanya dapat membaca file dari folder lokal
- Lagu hanya dapat ditambahkan satu per satu ke dalam antrian
- Tidak mendukung pencarian lagu berbasis kata kunci
- Nama file musik tidak boleh duplikat dalam direktori
- Maksimal panjang input dari pengguna adalah 1024 karakter

## 🚀 Cara Menjalankan
Pastikan Anda telah menginstal salah satu compiler berikut:

- clang
- gcc
- zig (opsional, jika ingin menggunakan Zig sebagai compiler C)

### Compile dan Jalankan
Buka file `build.sh` lalu ubah variable CC dengan compiler yang kamu gunakan. Lalu eksekusi

```sh
./main.exe
# atau beberapa compiler mengeluarkan tanpa extensi (misalnya zig)
./main

```