#set text(font: "Tinos")
#show raw.where(lang: none): raw => {
  text(font: "JetBrains Mono", raw.text)
}


#include "cover.typ"
#pagebreak()

#align(center)[
  #text(size: 14pt, weight: "bold", "TABEL REVISI")

  #let heading(body) = {
    return table.cell(
      fill: gray.lighten(20%),
      text(weight: "bold", body),
    )
  }

  #table(
    columns: (20pt, 120pt, 300pt, 60pt),
    heading("No"), heading("Tanggal"), heading("Keterangan"), heading("PIC"),
    [1], [], [], [],
    [2], [], [], [],
    [3], [], [], [],
    [4], [], [], [],
  )
]

#pagebreak()
#align(center)[
  #outline(title: text("Daftar Isi"), indent: auto)
]
#pagebreak()

// Content

#show heading.where(level: 1): it => {
  return align(
    center,
    text(
      size: 18pt,
      it.body,
    ),
  )
}

#show heading.where(level: 2): it => {
  return align(
    left,
    text(size: 14pt, it.body),
  )
}

#set par(justify: true)

= BAB 1 SPESIFIKASI PROGRAM
== 1.1 Definisi Program

Program music player adalah aplikasi perangkat lunak yang berfungsi untuk membaca, mendekode, dan memainkan file audio digital. Program ini mengimplementasikan berbagai komponen pemrosesan sinyal digital dan antarmuka pengguna untuk memungkinkan interaksi yang efisien dalam pemutaran audio.

Alpenlify adalah salah satu aplikasi pemutar musik yang dibuat untuk memenuhi tugas besar mata kuliah Struktur Data dan Algoritma. Alpenlify memiliki fitur sebagai berikut:

+ Memutar musik.
+ Membuat Playing _queue_.
+ _Seek_ waktu musik.
+ _Skip_ musik di _playing queue_.
+ _Rewind_ musik yang sedang berjalan.
+ _Search_ musik secara spesifik.
+ Lihat direktori musik.
+ Cek _queue_ musik.

Untuk memastikan pengguna dapat menjalankan program dengan benar dan memanfaatkan seluruh fitur yang tersedia, berikut ini adalah aturan-aturan penggunaan yang harus diperhatikan selama program dijalankan.

+ Pengguna dapat melihat seluruh daftar musik yang tersedia di dalam folder musik lokal. Seluruh file musik yang terdapat dalam folder tersebut akan ditampilkan secara otomatis saat program dijalankan.

+ Pengguna dapat memilih musik dari daftar dan memasukkannya ke dalam antrian pemutaran. Musik yang berada di urutan pertama antrian akan langsung dimainkan secara otomatis.

+ Apabila terdapat musik dalam antrian, pengguna dapat memilih untuk mengulang lagu yang sedang diputar tanpa menghapusnya dari antrian.

+ Pengguna dapat melewati lagu yang sedang diputar dan langsung melanjutkan ke lagu berikutnya dalam antrian, jika ada.

+ Pengguna dapat memindahkan posisi waktu pemutaran lagu dengan memasukkan nilai waktu dalam satuan waktu, yakni detik saja, menit dan detik, serta jam, menit, detik.

Selain aturan penggunaan, terdapat beberapa batasan yang perlu diketahui oleh pengguna. Batasan-batasan ini menggambarkan keterbatasan fitur dalam program dan ruang lingkup fungsionalitas yang disediakan.

+ Program hanya dapat mengakses file musik yang berada di dalam folder lokal pengguna. Musik dari sumber eksternal atau online tidak dapat digunakan.

+ Pengguna hanya dapat menambahkan satu lagu ke dalam antrian pada satu waktu. Tidak tersedia fitur untuk menambahkan banyak lagu secara bersamaan.

+ Program hanya menampilkan seluruh daftar lagu yang ada dalam folder secara keseluruhan. Pengguna tidak dapat mencari lagu secara spesifik menggunakan kata kunci atau filter tertentu.

== 1.2 Identifikasi Proses

Program ini memiliki penggunaan utama sebagai berikut.

1. Membuka program.
2. Muncul menu dengan pilihan sebagai berikut

#set enum(numbering: "a)")
+ Lihat Musik

Fitur ini akan menampilkan musik dalam bentuk hirarki direktori yang berada di device pengguna yang berada di folder Music. Contoh tampilan outputnya seperti di bawah ini.
```sh
Music/
  Rock/
     KingSlayer.mp3

  Dangdut/
    CintaSatuMalam.mp3
    KeretaMalam.mp3
    Bergadang.mp3
```
b) Tambahkan music ke queue.

Fitur ini akan menambahkan lagu yang dipilih ke dalam queue music. berikut adalah contoh proses pemilihan lagu untuk dimasukan ke Queue menggunakan contoh direktori sebelumnya.

```sh

Rock/
Dangdut/

> Dangdut

CintaSatuMalam.mp3
KeretaMalam.mp3
Bergadang.mp3

> Bergadang.mp3

```

c) Skip

Memungkinkan musik yang sedang berjalan dilewati dan memulai lagu berikutnya yang di dalam queue jika ada.

d) Rewind

Mengulang musik yang sedang berjalan ke awal.

e) Seek

Memungkinkan user untuk mencari detik lagu secara spesifik. Contoh dibawah ini akan memindahkan musik ke detik ke-120.

```sh
Pindah waktu ke detik berapa?

> 120
```


== 1.3 Identifikasi Data

#image("media/Tree.png")
Saat program dijalankan akan dibuat sebuah tree berdasarkan direktori. Gambar di atas adalah contoh visualisasi dari direktori tersebut.

#pagebreak()

Untuk masing - masing node, diberikan struktur data seperti gambar di bawah ini.
#image("media/MusicNode.png")

Untuk Queue musik akan digunakan sebuah queue yang infonya berisi pointer menuju node musik yang ada di dalam tree
#image("media/qyu.png")

Setiap queue, berisi pointer yang menunjuk ke bagian depan dan belakang queue. Untuk queue-nya sendiri akan diimplementasikan menggunakan linked list dengan struktur info yang merupakan pointer ke musik node dan next
#image("media/QueueNode.png")

Untuk mendapatkan _full path_ dari musik sedangkan queue hanya memiliki pointer ke musik node yang kemungkinan merupakan _leaf_ perlu digunakan stack untuk mendapatkan _full path_ dari musik.
#image("media/stak.png")

Setiap stack, berisi pointer yang menunjuk ke bagian atas stack. Untuk stack-nya sendiri akan diimplementasikan menggunakan linked list dengan struktur info yang merupakan pointer ke musik node dan next
#image("media/StakNode.png")



#pagebreak()

= BAB 2 PERANCANGAN PROGRAM

== 2.1 Chart
=== 2.1.1 Strucuted chart 1
#image("media/structured-chart-1.png")
=== 2.1.2 Strucuted chart 2
#image("media/structured-chart-2.png")
=== 2.1.3 Strucuted chart 3
#image("media/structured-chart-3.png")


== 2.2 Tabel Prosedur

// TODO: generate table dari suatu tempat, jangan langsung taroh disini
// #table(
//   columns: (30pt, 90pt, 70pt, 60pt, 150pt, 60pt),
//   [*No*], [*Nama Modul*], [*Deskripsi*], [*Jenis*], [*Parameter*], [*Kamus Data (lokal)*],
//   // Ilmu hitam typst.
//   ..json("data/modul.json")
//     .enumerate()
//     .map(data => {
//       let (i, v) = data
//       return (str(i + 1), [
//         #v.modul
//         \
//         *Pembuat*:\ 
//         #v.nama
//         ], v.deskripsi, v.tipe, [
          
//           #let n = 0
//           #while (n < v.parameter.len()) {
//             [
//               #v.parameter.at(n) 
//               :
//               #v.parameter.at(n + 1) \ ]
//             n = n + 2
//           } 
          
//           IS:
//           #v.is\
//           FS:
//           #v.fs
//         ] , "")
//     }).flatten()
// )
#for module in json("data/modul_future.json").enumerate() [
  #let (i, modules) = module;
  
  == 2.2.#(i + 1) #modules.at("modul_name")

  #table(
  columns: (30pt, 90pt, 70pt, 60pt, 150pt, 60pt),
  [*No*], [*Nama Modul*], [*Deskripsi*], [*Jenis*], [*Parameter*], [*Kamus Data (lokal)*],
    ..modules.at("modules")
    .enumerate()
    .map(data => {
      let (i, v) = data

      return (str(i + 1), [
        #v.modul
        \
        *Pembuat*: \ 
        #v.nama
      ]
      , v.deskripsi, v.tipe, [
         #let n = 0
        #while (n < v.parameter.len()) {
            [
              #v.parameter.at(n) 
              :
              #v.parameter.at(n + 1) \ ]
            n = n + 2
        } 
          
          IS:
          #v.is\
          FS:
          #v.fs
      ], [
        #let n = 0
        #while (n < v.lokal.len()) {
            [
              #v.lokal.at(n) 
              :
              #v.lokal.at(n + 1) \ ]
            n = n + 2
        } 
      ])
    }).flatten()
  )
]

== 2.3 Algoritma

#let pseudocode = read("data/pseudocode.pas")
#raw(pseudocode, lang: "pas")

== 2.4 Perancangan Tampilan (Output)

#image("media/tampilan-menu.png")

Tampilan diatas adalah tampilan yang akan muncul saat awal masuk program

#image("media/tampilan-lihat-musk.png")

Tampilan diatas adalah tampilan yang akan muncul pada memasuki menu "Lihat Musik"

#image("media/tampilan-masukan-musik.png")

Tampilan diatas adalah tampilan yang akan muncul pada memasuki menu "Tambahkan musik ke queue". Tampilan ini akan muncul sampai pengguna menginputkan sebuah file

#image("media/tampilan-seek.png")

Tampilan diatas adalah tampilan yang akan muncul saat pengguna memasuki menu "Seek"


#pagebreak()

= BAB 3 HASIL AKHIR PROGRAM

== 3.1. Pembahasan Hasil Implementasi
#for module in json("data/test.json").enumerate() [
  #let (i, data) = module
  #(i + 1). Fitur #data.fitur \
  - #data.penjelasan
  #image("test/" + data.screenhoot)
  #table(
     columns: (30pt, 70pt, 80pt, 80pt, 150pt, 70pt),
    [No], [Data Input], [Hasil yang diharapkan], [Hasil Keluaran Program], [Screen Capture], [Hasil \ Pengujian], 
    ..data.data
    .enumerate()
    .map(data => {
      let (i, test) = data
      return (str(i + 1), test.data_input, test.expected, test.actual, image("test/"+test.ss), test.result)
    }).flatten()
  )
]

#pagebreak()
= BAB 4 KESIMPULAN

Berisi kesimpulan pencapaian tugas (apa yang sudah selesai dan apa saja yang belum / sejauh mana implementasi yang berhasil diselesaikan (versus spesifikasi yang diuraikan pada BAB I)).

#pagebreak()
= DAFTAR PUSTAKA
Berisi daftar referensi yang dijadikan acuan dalam pembuatan program ini. \
https://stackoverflow.com/questions/1981459/using-threads-in-c-on-windows-simple-example \ 
https://learn.microsoft.com/en-us/windows/win32/procthread/creating-threads?redirectedfrom=MSDN \
https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-createthread \
https://github.com/mackron/miniaudio/tree/master \
#pagebreak()
= DAFTAR KONTRIBUSI ANGGOTA KELOMPOK
Berisi daftar keterangan kontribusi setiap anggota kelompok pada pengerjaan pembuatan program ini.

// TODO: Sama, generate dari suatu data source. Jangan langsung taruh
#table(
  columns: (100pt, 400pt),
  [No], [:],
  [Nama], [:],
  [Kontribusi],
  [:
    1.
    2.
    3.
  ],
)
