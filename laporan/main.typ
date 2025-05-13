#set text(font: "Tinos")
#show raw.where(lang: none) : raw => {
  text(font: "JetBrains Mono", raw.text)
} 


#include "cover.typ"
#pagebreak()

#align(center)[
  #text( size: 14pt, weight: "bold", "TABEL REVISI")

  #let heading(body) = {
    
    return table.cell(
        fill: gray.lighten(20%),
        text(weight: "bold", body)
      )
  }

  #table( 
    columns: (20pt, 120pt, 300pt, 60pt),
    heading("No"), heading("Tanggal"), heading("Keterangan"), heading("PIC"),
    [1],[],[],[],
    [2],[],[],[],
    [3],[],[],[],
    [4],[],[],[],
  )
]

#pagebreak()
#align(center)[
  #outline(title: text("Daftar Isi"), indent:auto)
]
#pagebreak()

// Content

#show heading.where(
  level: 1
): it => {
  return align(center, 
  text(
    size: 18pt,
  it.body
  ) 
)}

#show heading.where(
  level: 2
): it => {
  return align(
    left, 
    text(size: 14pt, it.body) 
  )
}


= BAB 1 SPESIFIKASI PROGRAM
== 1.1 Definisi Program

Tuliskan penjelasan mengenai topik yang dibahas (definisi topik, penjelasan algoritma proses secara umum)
{tambahkan aturan2 jika ada, penulisan dapat berupa sub subbab baru sebagai bagian dari subbab 1.1 ini }

== 1.2 Identifikasi Proses

{tuliskan ada proses utama apa saja pada program dan tuliskan penjelasannya (masing-masing proses melakukan apa (apa inputnya (diketahui, apa IS nya), proses apa yang dilakukan terhadap input, dan apa outputnya (FS)))}
== 1.3 Identifikasi Data

{Sajikan ilustrasi/gambaran/reperesentasi tree atau struktur linier dari kasus yang dibahas. Dalam representasi tersebut harus tergambar juga struktur data nya (struktur data setiap node dan data dalam bentuk lain yang digunakan).
Berdasarkan representasi tersebut, tuliskan menggunakan data utama apa saja dan penjelasannya (Kamus Data).Penjelasan berupa kegunaan data (sebagai penampung nilai apa) serta tipe dataya.
}


#pagebreak()

= BAB 2 PERANCANGAN PROGRAM


== Perancangan Proses
Hal-hal yang dituliskan pada subbab ini adalah sebagai berikut :

1. Gambarkan hirarki programnya menggunakan tools STRUCTURED CHART (penjelasan dasar dan contoh ada pada diktat DDP Bab V : Structured Programming subbab Hubungan Antar Modul, juga dapat dibaca dari file lampiran dokumen ini (StructuredChart.pdf) ).
2. Setelah itu, buat tabel penjelasan global dari setiap modul yang terdapat pada Structured Chart sebagai berikut :

// TODO: generate table dari suatu tempat, jangan langsung taroh disini
#table(
  columns: (30pt, 60pt, 60pt, 60pt, 150pt, 150pt),
  [*No*], [*Nama Modul*], [*Deskripsi*], [*Jenis*], [*Parameter*], [*Kamus Data (lokal)*],
  [1],[
    .............
    *Pembuat*
    : ...........
  ],[............],[Function atau Procedure],[
Sebutkan, jelaskan, termasuk penjelasan IS dan FS nya !
Sebutkan : nama, tipe data,
passing by..
Jelaskan : sebagai penampung nilai apa, IS & FS berupa nilai apa

],[],
)

3. Setelah itu, uraikan logika proses setiap modul yang terdapat pada Structured Chart.
{ berisi algoritma (menggunakan notasi pseudocode atau flowchart) untuk setiap modul yang dibuat (berisi logika dasar, jadi tidak termasuk layout output di layar). Yang diuraikan disini hanya modul-modul yang merupakan tambahan atau  modifikasi dari program sebelumnya. KECUALI jika program dibuat dari nol, maka semua modul yang dibuat oleh kelompok ybs harus dituliskan algoritmanya.
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
  [No],[:],
  [Nama],[:],
  [Kontribusi],[:
    1. 
    2. 
    3.
  ]
)