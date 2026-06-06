#include "globalheader.h"

#define MAX_ANTRIAN 150  

QueueCos* alokasiQueue(char *nama, char *noHp, char *kodePulsa, char *Tanggal, int jumlah) {
    QueueCos *New = (QueueCos *)malloc(sizeof(QueueCos));
    strcpy(New->nama, nama);
    strcpy(New->noHP, noHp);
    strcpy(New->kodePulsa, kodePulsa);
    strcpy(New->tanggal, Tanggal);
    New->jumlah = jumlah;
    New->next = NULL;
    return New;
}

Costumer createQueue(void) {
    Costumer New;
    New.front = NULL;
    New.rear = NULL;
    New.counter = 0;
    return New;
}

int isEmptyQueue(Costumer L) {
    return (L.front == NULL);
}

/* ini buat cek apakah antrian sudah penuh */
int isFullQueue(Costumer L) {
    return (L.counter >= MAX_ANTRIAN);
}

void enqueue(Costumer *L, char *nama, char *noHp, char *kodePulsa, char *Tanggal, int jumlah) {
    /* lalu tolak kalo antrian sudah penuh */
    if (isFullQueue(*L)) {
        printf("Antrian penuh! Maksimal %d orang.\n", MAX_ANTRIAN);
        return;
    }

    QueueCos *New = alokasiQueue(nama, noHp, kodePulsa, Tanggal, jumlah);
    if (isEmptyQueue(*L)) {
        L->front = New;
        L->rear = New;
        L->counter = 1;
        return;
    }
    
    L->rear->next = New;
    L->rear = New;
    L->counter = L->counter + 1;
}

int dequeue(Costumer *L, char *nama, char *noHp, char *kodePulsa, int *jumlah) {
    if (isEmptyQueue(*L)) {
        return 0;
    }
    
    QueueCos *Temp = L->front;
    strcpy(nama, Temp->nama);
    strcpy(noHp, Temp->noHP);
    strcpy(kodePulsa, Temp->kodePulsa);
    *jumlah = Temp->jumlah;
    
    if (L->front->next == NULL) {
        L->front = NULL;
        L->rear = NULL;
        L->counter = 0;
        free(Temp);
        return 1;
    }
    
    L->front = L->front->next;
    L->counter = L->counter - 1;
    free(Temp);
    return 1;
}

/* ini buat batalin antrian berdasarkan nama & noHP
 * Bisa hapus di posisi (depan, tengah, belakang)
 * Return: 1 jika berhasil, 0 jika tidak ditemukan */
int batalAntrian(Costumer *L, char *nama, char *noHp) {
    if (isEmptyQueue(*L)) {
        printf("Antrian kosong, tidak ada yang dibatalkan.\n");
        return 0;
    }

    QueueCos *cari = L->front;
    QueueCos *prev = NULL;

    while (cari != NULL) {
        if (strcmp(cari->nama, nama) == 0 && strcmp(cari->noHP, noHp) == 0) {

            if (prev == NULL) {
                /* Node di depan (front) */
                L->front = cari->next;
                if (L->front == NULL) L->rear = NULL;
            } else if (cari->next == NULL) {
                /* Node di belakang (rear) */
                prev->next = NULL;
                L->rear = prev;
            } else {
                /* Node di tengah */
                prev->next = cari->next;
            }

            L->counter = L->counter - 1;
            free(cari);
            printf("Antrian atas nama %s berhasil dibatalkan.\n", nama);
            return 1;
        }

        prev = cari;
        cari = cari->next;
    }

    printf("Customer '%s' dengan No HP '%s' tidak ditemukan.\n", nama, noHp);
    return 0;
}

void cetakCostumer(Costumer L) {
    if (isEmptyQueue(L)) {
        return;
    }

    /* Tampilkan info sisa slot */
    printf("Antrian: %d/%d orang\n", L.counter, MAX_ANTRIAN);
    printf("=== Daftar Antrian ========================================\n");
    printColumn("No", 5);
    printColumn("Nama", 14);
    printColumn("No HP", 16);
    printColumn("Kode", 11);
    printColumn("Qty", 7);
    printColumn("Tanggal", 20);
    printf("\n");
    
    int counter = 0;
    QueueCos *Temp = L.front;
    
    while (Temp != NULL) {
        counter = counter + 1;
        
        char no[10];
        sprintf(no, "%d.", counter);
        printColumn(no, 5);
        printColumn(Temp->nama, 14);
        printColumn(Temp->noHP, 16);
        printColumn(Temp->kodePulsa, 11);
        sprintf(no, "%d", Temp->jumlah);
        printColumn(no, 7);
        printColumn(Temp->tanggal, 20);
        printf("\n");
        
        Temp = Temp->next;
    }
    printf("\n");
}
