#include "globalheader.h"
#include <string.h>
#include <stdlib.h>

tabelLaporan createTabel(void) {
    tabelLaporan New;
    New.counter = 0;
    return New;
}

int isEmptyTabel(tabelLaporan T) {
    return (T.counter == 0);
}

int isFullTabel(tabelLaporan T) {
    return (T.counter >= nmax);
}

int searchKodeVoucher(tabelLaporan T, char *kodePulsa) {
    if (isEmptyTabel(T)) {
        return 0;
    }

    int i;
    for (i = 0; i < T.counter; i++) {
        if (strcmp(T.Tabel[i].kodePulsa, kodePulsa) == 0) {
            return 1;
        }
    }

    return 0;
}

void pushTabel(tabelLaporan *T, char *tanggal, char *kodePulsa, int jumlah, long long int total) {
    if (isFullTabel(*T)) {
        printf("Tabel laporan penuh!\n");
        return;
    }

    strcpy(T->Tabel[T->counter].tanggal, tanggal);
    strcpy(T->Tabel[T->counter].kodePulsa, kodePulsa);
    T->Tabel[T->counter].jumlah = jumlah;
    T->Tabel[T->counter].total = total;

    T->counter = T->counter + 1;
}

void cetakTabel(tabelLaporan T) {
    if (isEmptyTabel(T)) {
        printf("Belum ada laporan pembelian.\n\n");
        return;
    }

    printf("=== Laporan Pembelian Pulsa ===\n");

    printColumn("No", 5);
    printColumn("Tanggal", 20);
    printColumn("Kode Pulsa", 15);
    printColumn("Jumlah", 10);
    printColumn("Total", 15);
    printf("\n");

    int i;
    int counter = 0;
    char text[100];

    for (i = 0; i < T.counter; i++) {
        counter++;

        sprintf(text, "%d.", counter);
        printColumn(text, 5);

        printColumn(T.Tabel[i].tanggal, 20);
        printColumn(T.Tabel[i].kodePulsa, 15);

        sprintf(text, "%d", T.Tabel[i].jumlah);
        printColumn(text, 10);

        sprintf(text, "%lld", T.Tabel[i].total);
        printColumn(text, 15);

        printf("\n");
    }

    printf("\n");
}