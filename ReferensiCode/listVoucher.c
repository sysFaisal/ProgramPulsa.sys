#include "globalheader.h"

voucherPulsa* alokasiList(char *provider, char *kode, int nominal, int harga, int stock) {
    voucherPulsa *New = (voucherPulsa *)malloc(sizeof(voucherPulsa));
    strcpy(New->provider, provider);
    strcpy(New->kodePulsa, kode);
    New->nominal = nominal;
    New->harga = harga;
    New->stock = stock;
    New->next = NULL;
    return New;
}

linkList createList(void) {
    linkList New;
    New.front = NULL;
    New.rear = NULL;
    New.counter = 0;
    return New;
}

int isEmptyList(linkList L) {
    return (L.front == NULL);
}

int cariKodePulsa(linkList L, char *kodePulsa) {
    if (isEmptyList(L)) {
        return 0;
    }
    
    voucherPulsa *Temp = L.front;
    while (Temp != NULL) {
        if (strcmp(Temp->kodePulsa, kodePulsa) == 0) {
            return 1;
        }
        Temp = Temp->next;
    }
    
    return 0;
}

int getJumlahList(linkList L) {
    return (L.counter);
}

void addFirstList(linkList *L, char *provider, char *kode, int nominal, int harga, int stock) {
    voucherPulsa *New = alokasiList(provider, kode, nominal, harga, stock);
    if (isEmptyList(*L)) {
        L->front = New;
        L->rear = New;
        L->counter = 1;
        return;
    }
    
    New->next = L->front;
    L->front = New;
    L->counter = L->counter + 1;
}

void addLastList(linkList *L, char *provider, char *kode, int nominal, int harga, int stock) {
    voucherPulsa *New = alokasiList(provider, kode, nominal, harga, stock);
    if (isEmptyList(*L)) {
        addFirstList(L, provider, kode, nominal, harga, stock);
        return;
    }
    
    L->rear->next = New;
    L->rear = New;
    L->counter = L->counter + 1;
}

voucherPulsa* cariVoucher(linkList *L, char *kode) {
    if (isEmptyList(*L)) {
        return NULL;
    }
    
    voucherPulsa *Temp = L->front;
    while (Temp != NULL) {
        if (strcmp(Temp->kodePulsa, kode) == 0) {
            return Temp;
        }
        Temp = Temp->next;
    }
    return NULL;
}

int kurangiStock(linkList *L, char *kode, int minstock, int *actualSell, int *harga) {
    if (isEmptyList(*L)) {
        return 0;
    }
    
    voucherPulsa *Temp = cariVoucher(L, kode);
    if (Temp != NULL) {
        if (Temp->stock < minstock) {
            *actualSell = Temp->stock;
            *harga = Temp->harga;
            Temp->stock = 0;
            return 1;
        }
        
        Temp->stock = Temp->stock - minstock;
        *harga = Temp->harga;
        *actualSell = minstock;
        return 1;
    }
    
    return 0;
}

void cetaklinkList(linkList L) {
    if (isEmptyList(L)) {
        return;
    }
    
    printf("=== Daftar Voucher Pulsa ===\n");
    printColumn("No", 5);
    printColumn("Kode", 15);
    printColumn("Provider", 15);
    printColumn("Nominal", 12);
    printColumn("Harga", 12);
    printColumn("Stock", 10);
    printf("\n");
    
    int counter = 0;
    voucherPulsa *Temp = L.front;
    while (Temp != NULL) {
        counter = counter + 1;
        
        char no[10];
        sprintf(no, "%d.", counter);
        printColumn(no, 5);
        printColumn(Temp->kodePulsa, 15);
        printColumn(Temp->provider, 15);
        sprintf(no, "%d", Temp->nominal);
        printColumn(no, 12);
        sprintf(no, "%d", Temp->harga);
        printColumn(no, 12);
        sprintf(no, "%d", Temp->stock);
        printColumn(no, 10);
        printf("\n");
        
        Temp = Temp->next;
    }
    printf("\n");
}
