/*
David Fauzi, Usulan Soal M2
*/
#include <stdio.h>
#include <stdlib.h> // For exit() function
#include <string.h>

int main()
{
    char str[1000], fileName[20];
    FILE *fptr;
    int count = 0, price, qty, waktu;
    float bunga;
    double totalPinjaman, angsuranPokok, sisaAngsuran, angsuranBulan, totalAngsuran;
    printf("Nama file: ");
    scanf("%s", fileName);
    printf("Bunga per tahun: ");
    scanf(" %f", &bunga);
    printf("Lama pinjaman: ");
    scanf(" %d", &waktu);
    if ((fptr = fopen(fileName, "r")) == NULL)
    {
        // Exit if NULL
        printf("Error! opening file");
    }
    else 
    {
        // reads text until newline is encountered
        fgets(str, 100, fptr);
        while (fgets(str, 100, fptr) != NULL)
        {
            char *token = strtok(str, ",");
            while (token != NULL)
            {
                if (count % 4 == 2)
                    price = atoi(token);
                if (count % 4 == 3)
                    qty = atoi(token);
                token = strtok(NULL, ",");
                count++;
            }
            totalPinjaman += price * qty;
        }
        if ((int)totalPinjaman == 0)
        {
            printf("Tidak ada yang perlu dibayar !\n");
        }
        else
        {
            angsuranPokok = totalPinjaman / waktu;
            sisaAngsuran = totalPinjaman;
            for (int i = 0; i < waktu; i++)
            {
                angsuranBulan = (sisaAngsuran * bunga) / 12;
                totalAngsuran = angsuranPokok + angsuranBulan;
                sisaAngsuran -= angsuranPokok;
                printf("Total angsuran bulan ke-%d: Rp%.2lf\n", i + 1, totalAngsuran);
            }
        }
    }
    return 0;
}
