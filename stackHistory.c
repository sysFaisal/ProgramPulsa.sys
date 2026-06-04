#include "globalheader.h"
#include <string.h>
#include <stdlib.h>

/* Fungsi bantu untuk membuat node baru */
stackHistory* alokasiHistory(char *idTransaksi, char *namaPembeli,
                             char *noHp, char *kodePulsa,
                             char *tanggal, int jumlah,
                             long long int totalHarga,
                             char *status) {

    stackHistory *New = (stackHistory *)malloc(sizeof(stackHistory));

    strcpy(New->idTransaksi, idTransaksi);
    strcpy(New->namaPembeli, namaPembeli);
    strcpy(New->noHP, noHp);
    strcpy(New->kodePulsa, kodePulsa);
    strcpy(New->tanggal, tanggal);

    New->jumlah = jumlah;
    New->totalHarga = totalHarga;

    strcpy(New->status, status);

    New->next = NULL;

    return New;
}

History createHistory(void) {
    History New;

    New.first = NULL;
    New.counter = 0;

    return New;
}

int isEmptyHistory(History L) {
    return (L.first == NULL);
}

int pushHistory(History *L, char *idTransaksi, char *namaPembeli,
                char *noHp, char *kodePulsa,
                char *tanggal, int jumlah,
                long long int totalHarga,
                char *status) {

    stackHistory *New;

    New = alokasiHistory(
        idTransaksi,
        namaPembeli,
        noHp,
        kodePulsa,
        tanggal,
        jumlah,
        totalHarga,
        status
    );

    if (New == NULL) {
        return 0;
    }

    if (isEmptyHistory(*L)) {
        L->first = New;
        L->counter = 1;
        return 1;
    }

    New->next = L->first;
    L->first = New;
    L->counter = L->counter + 1;

    return 1;
}

void pop(History *L) {
    if (isEmptyHistory(*L)) {
        return;
    }

    stackHistory *Temp = L->first;

    if (L->first->next == NULL) {
        L->first = NULL;
        L->counter = 0;
        free(Temp);
        return;
    }

    L->first = L->first->next;
    L->counter = L->counter - 1;

    free(Temp);
}

void cetakHistory(History L) {
    if (isEmptyHistory(L)) {
        printf("Belum ada history pembelian.\n\n");
        return;
    }

    printf("=== History Pembelian ===\n");

    printColumn("No", 5);
    printColumn("ID", 15);
    printColumn("Nama", 15);
    printColumn("No HP", 15);
    printColumn("Kode", 12);
    printColumn("Qty", 8);
    printColumn("Total", 15);
    printColumn("Status", 12);
    printf("\n");

    int counter = 0;
    char text[100];

    stackHistory *Temp = L.first;

    while (Temp != NULL) {

        counter = counter + 1;

        sprintf(text, "%d.", counter);
        printColumn(text, 5);

        printColumn(Temp->idTransaksi, 15);
        printColumn(Temp->namaPembeli, 15);
        printColumn(Temp->noHP, 15);
        printColumn(Temp->kodePulsa, 12);

        sprintf(text, "%d", Temp->jumlah);
        printColumn(text, 8);

        sprintf(text, "%lld", Temp->totalHarga);
        printColumn(text, 15);

        printColumn(Temp->status, 12);

        printf("\n");

        Temp = Temp->next;
    }

    printf("\n");
}