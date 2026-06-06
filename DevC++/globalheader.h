#ifndef _GLOBAL_HEADER_H
#define _GLOBAL_HEADER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/* ============ External Utils ============ */
#define MAX_STRING 100
#define MAX_COLUMN 100

char* saferString(char *text, int maxlength);
void printColumn(char *text, int maxlength);
int isDigit(char *text, int cekPanjang);
char* generateID();
char* getHours();
char* getTanggal();
void pauseProgram();

/* ============ Tabel Laporan ============ */
#define nmax 100

typedef struct {
    char tanggal[100];
    char kodePulsa[50];
    int jumlah;
    long long int total;
} laporan;

typedef struct {
    laporan Tabel[nmax + 1];
    int counter;
} tabelLaporan;

tabelLaporan createTabel(void);
int isEmptyTabel(tabelLaporan T);
int isFullTabel(tabelLaporan T);
int searchKodeVoucher(tabelLaporan T, char *kodePulsa);
void pushTabel(tabelLaporan *T, char *tanggal, char *kodePulsa, int jumlah, long long int total);
void cetakTabel(tabelLaporan T);




/* ============ List Voucher ============ */
typedef struct VoucherNode {
    char kodePulsa[50];
    char provider[100];
    int nominal;
    int harga;
    int stock;
    struct VoucherNode *next;
} voucherPulsa;


typedef struct {
    voucherPulsa *front;
    voucherPulsa *rear;
    int counter;
} linkList;


linkList createList(void);
int isEmptyList(linkList L);
int cariKodePulsa(linkList L, char *kodePulsa);
int getJumlahList(linkList L);
void addFirstList(linkList *L, char *provider, char *kode, int nominal, int harga, int stock);
void addLastList(linkList *L, char *provider, char *kode, int nominal, int harga, int stock);
voucherPulsa* cariVoucher(linkList *L, char *kode);
int kurangiStock(linkList *L, char *kode, int minstock, int *actualSell, int *harga);
void cetaklinkList(linkList L);



/* ============ Queue Customer ============ */
typedef struct QueueNode {
    char nama[100];
    char noHP[20];
    char kodePulsa[50];
    char tanggal[100];
    int jumlah;
    struct QueueNode *next;
} QueueCos;

typedef struct {
    QueueCos *front;
    QueueCos *rear;
    int counter;
} Costumer;

Costumer createQueue(void);
int isEmptyQueue(Costumer L);
int isFullQueue(Costumer L);
void enqueue(Costumer *L, char *nama, char *noHp, char *kodePulsa, char *Tanggal, int jumlah);
int dequeue(Costumer *L, char *nama, char *noHp, char *kodePulsa, int *jumlah);
int batalAntrian(Costumer *L, char *nama, char *noHp);
void cetakCostumer(Costumer L);


/* ============ Stack History ============ */
typedef struct StackNode {
    char idTransaksi[20];
    char namaPembeli[100];
    char noHP[20];
    char kodePulsa[50];
    char tanggal[100];
    int jumlah;
    long long int totalHarga;
    char status[20];
    struct StackNode *next;
} stackHistory;


typedef struct {
    stackHistory *first;
    int counter;
} History;

History createHistory(void);
int isEmptyHistory(History L);
int pushHistory(History *L, char *idTransaksi, char *namaPembeli, char *noHp, char *kodePulsa,
               char *tanggal, int jumlah, long long int totalHarga, char *status);
void pop(History *L);
void cetakHistory(History L);


#endif
