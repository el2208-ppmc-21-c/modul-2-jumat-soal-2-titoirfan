/*
ASCII (dibaca as-key) merupakan singkatan dari American Standard Code for Information Interexchange, ASCII merupakan standar yang mengasosiasikan huruf, angka, dan beberapa karakter lainnya pada sebuah data 8-bit. Sebagai contoh, huruf A (a kapital) bila disimpan pada variabel bertipe data char, maka akan disimpan sebagai ‘A’. Jika direpresentasikan dalam bilangan Decimal, maka akan bernilai 65, jika direpresentasikan dalam bilangan Hexadecimal, maka akan bernilai 41. https://www.rapidtables.com/code/text/ascii-table.html https://www.computerhope.com/jargon/a/ascii.htm
Buatlah sebuah program yang menerima nama file eksternal beserta extension-nya sebagai masukan. Lakukan validasi terhadap nama file tersebut dengan pesan error seperti pada contoh eksekusi program. Program akan meminta masukan nama file hingga nama file tersebut valid. (Ketika terdapat file dengan nama file tersebut, maka nama file tersebut valid)
Setiap file eksternal memiliki dua buah line yang harus dibaca dengan line pertama hanya terdiri dari kata Char atau Hexa. Line kedua memiliki informasi yang harus dikonversi. Jika line pertama merupakan Char, maka line kedua memiliki informasi karakter ASCII yang harus dikonversi menjadi hexadecimal. Jika line pertama merupakan Hexa, maka line kedua memiliki informasi hexadecimal yang harus dikonversi menjadi karakter ASCII. Hasil konversi dapat langsung ditampilkan dan diikuti oleh informasi yang dimiliki file eksternal seperti pada contoh.
- David Khowanto
- Usulan Soal Modul 2
*/
#include <stdio.h>
#include <string.h>

void main() {
  FILE* fp;                         // file pointer untuk menampung file external
  char file_content[256 * 2] = "";  // isi dari file keseluruhan
  char filename[20] = "";           // nama file
  char file_type[15] = "";          // tipe file, char atau hexa

  // melakukan validasi nama file yang diinput
  do {
    printf("Nama file: ");
    scanf("%s", &filename);
    fp = fopen(filename, "r");
    if (fp == NULL) {
      printf("Error membuka file, silahkan input ulang nama file\n\n");
    }
  } while (fp == NULL);

  // mengambil tipe file, char atau hexa pada line pertama file external
  char input_type[15];
  fgets(input_type, 15, fp);
  
  // melakukan konversi pada line kedua file external bergantung dari tipe file, char atau hexa
  printf("\nHasil konversi:\n");
  // jika tipe file hexa, ubah hex string pada file eksternal menjadi hex int sehingga dapat menampilkan karakter ascii
  if (strcmp(input_type, "Hexa\r\n") == 0) {
    char file_buff[3];
    strcat(file_type, "hexadecimal");         // untuk display output file_type nantinya
    while (fgets(file_buff, 3, fp) != NULL) { // mengambil 2 karakter hex dan null terminating character \0 hingga EOF
      int hex;
      strcat(file_content, file_buff);        // menyimpan data asli file eksternal untuk display output file_content nantinya
      sscanf(file_buff, "%x", &hex);          // mengubah hex string menjadi hex int
      printf("%c", hex);                      // menampilkan karakter ascii dari hex int
    }
  }
  // jika tipe file char, ubah karakter ascii pada file eksternal menjadi hex string/int
  else if (strcmp(input_type, "Char\r\n") == 0) {
    strcat(file_type, "character");           // untuk display output file_type nantinya
    char c = fgetc(fp);                       // mengambil karakter paling 'ujung'
    int i = 0;
    while (c != EOF) {                        // mengambil setiap karakter hingga EOF 
      file_content[i] = c;                    // menyimpan data asli file eksternal untuk display output file_content nantinya
      printf("%02x ", c);                     // menampilkan hex string/int
      c = fgetc(fp);                          // mengambil karakter paling 'ujung'
      i++;                                    // iterasi untuk array karakter data asli file eksternal
    }
  }
  // jika tipe file bukan char ataupun hexa
  else {
    strcat(file_type, "None");
    printf("Isi file tidak didukung");
  }

  // jika tipe file merupakan char ataupun hexa, mengeluarkan konten asli dari file eksternal
  if (strcmp(file_type, "None") != 0) {
    printf("\n\nHasil didapatkan dari input %s dengan nilai:\n%s", file_type, file_content);
  }

  fclose(fp);
}
