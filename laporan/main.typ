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
+ Membuat Playing Queue.
+ _Seek_ waktu musik.
+ _Skip_ musik di playing queue.
+ _Rewind_ musik yang sedang berjalan.

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


== Perancangan Proses
Hal-hal yang dituliskan pada subbab ini adalah sebagai berikut :

1. Gambarkan hirarki programnya menggunakan tools STRUCTURED CHART (penjelasan dasar dan contoh ada pada diktat DDP Bab V : Structured Programming subbab Hubungan Antar Modul, juga dapat dibaca dari file lampiran dokumen ini (StructuredChart.pdf) ).
2. Setelah itu, buat tabel penjelasan global dari setiap modul yang terdapat pada Structured Chart sebagai berikut :

// TODO: generate table dari suatu tempat, jangan langsung taroh disini
#table(
  columns: (30pt, 90pt, 70pt, 60pt, 150pt, 60pt),
  [*No*], [*Nama Modul*], [*Deskripsi*], [*Jenis*], [*Parameter*], [*Kamus Data (lokal)*],
  [1], [
    .............
    *Pembuat*
    : ...........
  ], [............], [Function atau Procedure], [
    Sebutkan, jelaskan, termasuk penjelasan IS dan FS nya !
    Sebutkan : nama, tipe data,
    passing by..
    Jelaskan : sebagai penampung nilai apa, IS & FS berupa nilai apa

  ], [] ,
  // Ilmu hitam typst.
  ..json("data/modul.json")
    .enumerate()
    .map(data => {
      let (i, v) = data
      return (str(i), [
        #v.modul
        \
        *Pembuat*:\ 
        #v.nama
        ], v.deskripsi, v.tipe, [
          #v.parameter.at(0)
          :
          #v.parameter.at(1)\
          IS:
          #v.is\
          FS:
          #v.fs
        ] , "")
    }).flatten()
)



3. Setelah itu, uraikan logika proses setiap modul yang terdapat pada Structured Chart.
{ berisi algoritma (menggunakan notasi pseudocode atau flowchart) untuk setiap modul yang dibuat (berisi logika dasar, jadi tidak termasuk layout output di layar). Yang diuraikan disini hanya modul-modul yang merupakan tambahan atau modifikasi dari program sebelumnya. KECUALI jika program dibuat dari nol, maka semua modul yang dibuat oleh kelompok ybs harus dituliskan algoritmanya.
Lengkapi algoritma dengan kamus data, untuk setiap variabel yang digunakan pada logika proses.
Jika algoritma merupakan modifikasi/copy dari algoritma/program yang dibuat oleh orang lain diluar anggota kelompok, tuliskan referensinya! }

// Just use jetbrains mono smh
Algoritma ditulis menggunakan font Courier New ukuran 10, spasi 1). Contoh :
```
    Modul UTAMA Begin
        IF True
          Then B // call modul B
        ENDIF
      WHILE True
      DO C // call modul C
      ENDWHILE
    End Modul UTAMA.
```

== Perancangan Tampilan (Output)
Sub bab ini menggambarkan rancangan/desain output/tampilan pada layar.
BUKAN hasil print screen/capture tampilan program !
Setiap perancangan tampilan harus diberi identitas dan keterangan secukupnya.


#pagebreak()
= BAB 3 KESIMPULAN

Berisi kesimpulan pencapaian tugas (apa yang sudah selesai dan apa saja yang belum / sejauh mana implementasi yang berhasil diselesaikan (versus spesifikasi yang diuraikan pada BAB I)).

#pagebreak()
= DAFTAR PUSTAKA
Berisi daftar referensi yang dijadikan acuan dalam pembuatan program ini.
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
