#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globalheader.h"

void tambahVoucher(linkList *D) {
    char kode[50], provider[100], nominal[20], harga[20], stock[20];
    char fix;
    
    printf("\n== tambahVoucher ==\n");
    while (1) {
        printf("Provider : ");
        fgets(provider, sizeof(provider), stdin);
        provider[strcspn(provider, "\n")] = '\0';
        
        printf("Nominal : ");
        fgets(nominal, sizeof(nominal), stdin);
        nominal[strcspn(nominal, "\n")] = '\0';
        
        printf("Harga : ");
        fgets(harga, sizeof(harga), stdin);
        harga[strcspn(harga, "\n")] = '\0';
        
        printf("Stock : ");
        fgets(stock, sizeof(stock), stdin);
        stock[strcspn(stock, "\n")] = '\0';
        
        printf("Kode Pulsa : ");
        fgets(kode, sizeof(kode), stdin);
        kode[strcspn(kode, "\n")] = '\0';
        
        if (!(isDigit(nominal, 1) && isDigit(harga, 1) && isDigit(stock, 1))) {
            printf("Gagal Memasukkan!\n");
            printf("Tekan Apa saja untuk Keluar...");
            fgets(kode, sizeof(kode), stdin);
            return;
        }
        
        addFirstList(D, provider, kode, atoi(nominal), atoi(harga), atoi(stock));
        
        printf("Lagi? (y/n) : ");
        scanf("%c", &fix);
        getchar();
        
        if (!(fix == 'y' || fix == 'Y')) {
            return;
        }
    }
}

void enqueueCos(Costumer *C, linkList *D) {
    char nama[100], noHP[20], kodePulsa[50], jumlah[20];
    char fix;
    
    if (isEmptyList(*D)) {
        printf("\nVoucher Pulsa Kosong...\n");
        pauseProgram();
        return;
    }
    
    while (1) {
        if (isFullQueue(*C)) {
            printf("\nAntrian Penuh! Tidak dapat menambahkan customer baru.\n");
            pauseProgram();
            return;
        }

        printf("\n");
        cetaklinkList(*D);
        printf("== antrianCostumer ==\n");
        
        printf("Nama : ");
        fgets(nama, sizeof(nama), stdin);
        nama[strcspn(nama, "\n")] = '\0';
        
        printf("No Hp : ");
        fgets(noHP, sizeof(noHP), stdin);
        noHP[strcspn(noHP, "\n")] = '\0';
        
        printf("Kode Pulsa : ");
        fgets(kodePulsa, sizeof(kodePulsa), stdin);
        kodePulsa[strcspn(kodePulsa, "\n")] = '\0';
        
        printf("Jumlah : ");
        fgets(jumlah, sizeof(jumlah), stdin);
        jumlah[strcspn(jumlah, "\n")] = '\0';
        
        if (!cariKodePulsa(*D, kodePulsa)) {
            printf("Kode Pulsa Tidak dapat ditemukan!\n");
            printf("Tekan Apa saja untuk Keluar...");
            fgets(kodePulsa, sizeof(kodePulsa), stdin);
            return;
        }
        
        if (!(isDigit(noHP, 0) && isDigit(jumlah, 1))) {
            printf("Gagal Memasukkan!\n");
            printf("Tekan Apa saja untuk Keluar...");
            fgets(kodePulsa, sizeof(kodePulsa), stdin);
            return;
        }
        
        enqueue(C, nama, noHP, kodePulsa, getTanggal(), atoi(jumlah));
        
        printf("Lagi? (y/n) : ");
        scanf("%c", &fix);
        getchar();
        
        if (!(fix == 'y' || fix == 'Y')) {
            return;
        }
    }
}

void dequeueCos(Costumer *C, linkList *D, History *H, tabelLaporan *T) {
    char nama[100], noHp[20], kodePulsa[50];
    int minStock = 0;
    char fix;
    int actualSell = 0, actualHarga = 0;
    char *idTransaksi;
    char *tanggal;
    
    printf("\n");
    cetakCostumer(*C);
    
    while (1) {
        if (isEmptyList(*D)) {
            printf("Voucher Pulsa Kosong...\n");
            pauseProgram();
            return;
        }
        
        if (isEmptyQueue(*C)) {
            printf("Queue Kosong...\n");
            pauseProgram();
            return;
        }
        
        printf("Proses Antrian? (y/n) : ");
        scanf("%c", &fix);
        getchar();
        
        if (!(fix == 'y' || fix == 'Y')) {
            return;
        }
        
        dequeue(C, nama, noHp, kodePulsa, &minStock);
        kurangiStock(D, kodePulsa, minStock, &actualSell, &actualHarga);
        
        idTransaksi = generateID();
        tanggal = getTanggal();
        
        printf("\n");
        if (actualSell == 0) {
            printf("== Struk Belanja ==\n");
            printf("Status Pembayaran : Gagal\n");
            printf("id Transaksi : %s\n", idTransaksi);
            printf("nama Pembeli : %s\n", nama);
            printf("kode Pulsa : %s\n", kodePulsa);
            printf("Tanggal : %s\n", tanggal);
            printf("Jumlah : %d\n", minStock);
            printf("total Harga : %lld\n\n", (long long)minStock * actualHarga);
            
            pushHistory(H, idTransaksi, nama, noHp, kodePulsa, tanggal, minStock, (long long)minStock * actualHarga, "Gagal");
        } else {
            printf("== Struk Belanja ==\n");
            printf("Status Pembayaran : Berhasil\n");
            printf("id Transaksi : %s\n", idTransaksi);
            printf("nama Pembeli : %s\n", nama);
            printf("kode Pulsa : %s\n", kodePulsa);
            printf("Tanggal : %s\n", tanggal);
            printf("Jumlah : %d\n", actualSell);
            printf("total Harga : %lld\n\n", (long long)actualSell * actualHarga);
            
            pushHistory(H, idTransaksi, nama, noHp, kodePulsa, tanggal, actualSell, (long long)actualSell * actualHarga, "Berhasil");
            pushTabel(T, tanggal, kodePulsa, actualSell, (long long)actualSell * actualHarga);
        }
        
        cetakCostumer(*C);
    }
}

void editStock(linkList *D) {
    if (isEmptyList(*D)) {
        return;
    }
    
    printf("\n");
    cetaklinkList(*D);
    
    char kodePulsa[50], stock[20];
    printf("== editStock Voucher ==\n");
    printf("Kode Pulsa : ");
    fgets(kodePulsa, sizeof(kodePulsa), stdin);
    kodePulsa[strcspn(kodePulsa, "\n")] = '\0';
    
    voucherPulsa *Temp = cariVoucher(D, kodePulsa);
    
    if (Temp == NULL) {
        printf("\nKode Pulsa Tidak ditemukan!\n");
        pauseProgram();
        return;
    }
    
    printf("Stock Baru : ");
    fgets(stock, sizeof(stock), stdin);
    stock[strcspn(stock, "\n")] = '\0';
    
    if (!isDigit(stock, 1)) {
        printf("\nGagal Menambahkan!\n");
        pauseProgram();
        return;
    }
    
    Temp->stock = atoi(stock);
    printf("\nBerhasil Mengedit Stock!..\n");
    
    pauseProgram();
}

int main() {
    History H = createHistory();
    linkList D = createList();
    Costumer C = createQueue();
    tabelLaporan T = createTabel();
    
    int caseMain = 0;
    char input[20];
    input[0] = '\0';
     
    do {
        system("clear");
        printf("=== Program Konter ===\n");
        printf("1. Tambah Voucher\n");
        printf("2. Lihat Voucher\n");
        printf("3. Edit Voucher\n");
        printf("4. Tambah Antrian\n");
        printf("5. Proses Antrian\n");
        printf("6. Lihat Antrian\n");
        printf("7. Lihat History\n");
        printf("8. Lihat Laporan\n");
        printf("0. Keluar\n");
        printf("Pilihan : ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        
        if (!isDigit(input, 0)) {
            caseMain = 999;
        } else {
            caseMain = atoi(input);
        }
        
        switch (caseMain) {
            case 1:
                tambahVoucher(&D);
                break;
            
            case 2:
                printf("\n");
                if (isEmptyList(D)) {
                    printf("Voucher Kosong!.\n");
                    pauseProgram();
                    break;
                }
                
                cetaklinkList(D);
                pauseProgram();
                break;
            
            case 3:
                editStock(&D);
                break;
            
            case 4:
                enqueueCos(&C, &D);
                break;
            
            case 5:
                dequeueCos(&C, &D, &H, &T);
                break;
            
            case 6:
                printf("\n");
                if (isEmptyQueue(C)) {
                    printf("Tidak Ada Antrian!.\n");
                    pauseProgram();
                    break;
                }
                
                cetakCostumer(C);
                pauseProgram();
                break;
            
            case 7:
                printf("\n");
                if (isEmptyHistory(H)) {
                    printf("Tidak Ada History!.\n");
                    pauseProgram();
                    break;
                }
                
                cetakHistory(H);
                pauseProgram();
                break;
            
            case 8:
                printf("\n");
                if (isEmptyTabel(T)) {
                    printf("Tidak Ada Laporan!.\n");
                    pauseProgram();
                    break;
                }
                
                cetakTabel(T);
                pauseProgram();
                break;
            
            case 0:
                printf("Keluar program...\n");
                break;
            
            default:
                printf("Pilihan tidak valid!\n");
                pauseProgram();
        }
    } while (caseMain != 0);
    
    return 0;
}