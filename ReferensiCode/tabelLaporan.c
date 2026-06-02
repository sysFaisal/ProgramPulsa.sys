#include "globalheader.h"

laporan alokasiTabel(char *tanggal, char *kodePulsa, int jumlah, long long int total) {
    laporan New;
    strcpy(New.tanggal, tanggal);
    strcpy(New.kodePulsa, kodePulsa);
    New.jumlah = jumlah;
    New.total = total;
    return New;
}

tabelLaporan createTabel(void) {
    tabelLaporan New;
    New.counter = 0;
    for (int i = 0; i <= nmax; i++) {
        New.Tabel[i].jumlah = 0;
        New.Tabel[i].total = 0;
        strcpy(New.Tabel[i].kodePulsa, " ");
        strcpy(New.Tabel[i].tanggal, " ");
    }
    return New;
}

int isEmptyTabel(tabelLaporan T) {
    return (T.counter <= 0);
}

int isFullTabel(tabelLaporan T) {
    return (T.counter == nmax);
}

int searchKodeVoucher(tabelLaporan T, char *kodePulsa) {
    if (isEmptyTabel(T)) {
        return 0;
    }
    
    for (int i = 1; i <= T.counter; i++) {
        if (strcmp(T.Tabel[i].kodePulsa, kodePulsa) == 0) {
            return 1;
        }
    }
    return 0;
}

void pushTabel(tabelLaporan *T, char *tanggal, char *kodePulsa, int jumlah, long long int total) {
    if (isEmptyTabel(*T)) {
        T->counter = 1;
        T->Tabel[T->counter] = alokasiTabel(tanggal, kodePulsa, jumlah, total);
        return;
    }
    
    if (!isFullTabel(*T)) {
        T->counter = T->counter + 1;
        T->Tabel[T->counter] = alokasiTabel(tanggal, kodePulsa, jumlah, total);
        return;
    }
}

void cetakTabel(tabelLaporan T) {
    if (isEmptyTabel(T)) {
        return;
    }
    
    printf("=== Laporan ========================================\n");
    printColumn("No", 5);
    printColumn("Tanggal", 20);
    printColumn("Kode", 10);
    printColumn("Qty", 8);
    printColumn("Total", 12);
    printf("\n");
    
    for (int i = 1; i <= T.counter; i++) {
        char no[10];
        sprintf(no, "%d", i);
        printColumn(no, 5);
        printColumn(T.Tabel[i].tanggal, 20);
        printColumn(T.Tabel[i].kodePulsa, 10);
        sprintf(no, "%d", T.Tabel[i].jumlah);
        printColumn(no, 8);
        sprintf(no, "%lld", T.Tabel[i].total);
        printColumn(no, 12);
        printf("\n");
    }
    printf("\n");
}
