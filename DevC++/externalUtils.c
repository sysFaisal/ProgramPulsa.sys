#include "globalheader.h"

void pauseProgram(){
    char temp[10];

    printf("Tekan Enter untuk lanjut...");
    fgets(temp, sizeof(temp), stdin);
};

char* saferString(char *text, int maxlength) {
    static char result[MAX_STRING];
    strcpy(result, text);
    
    if ((int)strlen(text) > maxlength) {
        result[maxlength - 2] = '.';
        result[maxlength - 1] = '.';
        result[maxlength] = '\0';
    }
    return result;
}

void printColumn(char *text, int maxlength) {
    char format[20];
    sprintf(format, "%%-%ds", maxlength);
    printf(format, saferString(text, maxlength - 1));
}

int isDigit(char *text, int cekPanjang) {
    if (strlen(text) == 0) {
        return 0;
    }
    
    if (cekPanjang && (int)strlen(text) > 9) {
        return 0;
    }
    
    for (int i = 0; i < (int)strlen(text); i++) {
        if (!(text[i] >= '0' && text[i] <= '9')) {
            return 0;
        }
    }
    return 1;
}

char* generateID() {
    static char id[20];
    srand(time(0));
    int number = rand() % 900000 + 100000;
    sprintf(id, "TRX%d", number);
    return id;
}

char* getHours() {
    static char jam[20];
    time_t now = time(0);
    struct tm *ltm = localtime(&now);
    
    sprintf(jam, "%02d:%02d", ltm->tm_hour, ltm->tm_min);
    return jam;
}

char* getTanggal() {
    static char tanggal[50];
    time_t now = time(0);
    struct tm *ltm = localtime(&now);
    
    sprintf(tanggal, "%d/%d/%d,%02d:%02d",
            ltm->tm_mday,
            1 + ltm->tm_mon,
            1900 + ltm->tm_year,
            ltm->tm_hour,
            ltm->tm_min);
    
    return tanggal;
}
