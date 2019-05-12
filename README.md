# FP-SISOP-D02
### FUSE-dan-Thread

### Soal:
Membuat sebuah music player dengan bahasa C yang memiliki fitur play nama_lagu,
pause, next, prev, list lagu. Selain music player juga terdapat FUSE untuk 
mengumpulkan semua jenis file yang berekstensi .mp3 kedalam FUSE yang tersebar 
pada direktori /home/user. Ketika FUSE dijalankan, direktori hasil FUSE hanya
berisi file .mp3 tanpa ada direktori lain di dalamnya. Asal file tersebut bisa
tersebar dari berbagai folder dan subfolder. program mp3 mengarah ke FUSE untuk memutar
musik.
Note: playlist bisa banyak


### Jawab:
FUSE
Untuk membuat FUSE berisi semua file berekstensi '.mp3' dari direktori /home/user dan subfoldernya, maka yang harus dilakukan adalah sebagai berikut.
1) menginstal ```pytagsfs```
   masukan command ``sudo apt-get install pytagsfs``. pytagsfs adalah FUSE file system yang menampilkan file berdasarkan tagnya.
2) membuat folder baru 
   masukan command ``mkdir musicplayer``.
3) membuat file system
   masukan command ``pytagsfs -o dstfilter='\.mp3$' /home/[user] /home/[user]/musicplayer``. 
   ``dstfilter`` digunakan untuk memfilter ekstensi file yang akan ditampilkan dalam file system dan ``'\.mp3$'`` digunakan untuk  menandakan bahwa file yang akan ditampilkan berekstensi '.mp3'
   Setelah melakukan langkah langkah tersebut, maka terbuatlah file system yang berisi file berekstensi '.mp3' pada direktori /home/user dan subfoldernya.
