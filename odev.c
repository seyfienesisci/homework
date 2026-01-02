#include <stdio.h>
#include <stdlib.h>

#define N 8

typedef struct Dugum {
    int veri;
    struct Dugum* sonraki;
} Dugum;

char* bina[N] = {"MDBF", "Kutuphane", "Yemekhane", "Yurt", "Kapali Spor Salonu", "Yetenek Vadisi", "BHGIDF", "Iskenderun Cafe"};
int matris[N][N], kuyruk[100], on, arka;
Dugum* liste[N];

void kenarEkle(int r, int c) {
    matris[r][c] = 1;
    matris[c][r] = 1;

    Dugum* yeni = malloc(sizeof(Dugum));
    yeni->veri = c;
    yeni->sonraki = liste[r];
    liste[r] = yeni;

    yeni = malloc(sizeof(Dugum));
    yeni->veri = r;
    yeni->sonraki = liste[c];
    liste[c] = yeni;
}

void bfs(int baslangic, int hedef) {
    int visit[N] = {0}, gelinenBina[N], i;
    for (i = 0; i < N; i++) {
        gelinenBina[i] = -1;
    }

    on = arka = 0;
    kuyruk[arka++] = baslangic;
    visit[baslangic] = 1;

    while (on < arka) {
        int simdiki = kuyruk[on++];
        if (simdiki == hedef) {
            break;
        }

        for (Dugum* temp = liste[simdiki]; temp != NULL; temp = temp->sonraki) {
            if (!visit[temp->veri]) {
                visit[temp->veri] = 1;
                gelinenBina[temp->veri] = simdiki;
                kuyruk[arka++] = temp->veri;
            }
        }
    }

    printf("\n=== BFS ===\n%s -> %s\nYol: ", bina[baslangic], bina[hedef]);
    int yol[N], uzunluk = 0, gecici = hedef;
    
    while (gecici != -1) {
        yol[uzunluk++] = gecici;
        gecici = gelinenBina[gecici];
    }

    for (i = uzunluk - 1; i >= 0; i--) {
        printf("%s", bina[yol[i]]);
        if (i > 0) {
            printf(" -> ");
        } else {
            printf("\n");
        }
    }
}

void dfsKopukluk(int dugum, int visit[], int bilesen[]) {
    visit[dugum] = 1;
    for (Dugum* temp = liste[dugum]; temp != NULL; temp = temp->sonraki) {
        if (!visit[temp->veri]) {
            bilesen[temp->veri] = bilesen[dugum];
            dfsKopukluk(temp->veri, visit, bilesen);
        }
    }
}

void dfs() {
    int visit[N] = {0}, bilesen[N], sayac = 0, i, j;
    for (i = 0; i < N; i++) {
        bilesen[i] = -1;
    }

    for (i = 0; i < N; i++) {
        if (!visit[i]) {
            bilesen[i] = sayac;
            dfsKopukluk(i, visit, bilesen);
            sayac++;
        }
    }

    printf("\n=== DFS ===\nBilesen Sayisi: %d\n", sayac);
    for (i = 0; i < sayac; i++) {
        printf("Bilesen %d: ", i + 1);
        for (j = 0; j < N; j++) {
            if (bilesen[j] == i) {
                printf("%s ", bina[j]);
            }
        }
        printf("\n");
    }
    printf("%s\n", sayac > 1 ? "Kopuk alan var" : "Tum binalar bagli");
}

int main() {
    int kenarlar[][2] = {{0,1},{0,2},{0,6},{0,7},{1,4},{1,7},{2,5},{2,6},{2,7},{3,5}};
    int r, c, baslangic, hedef, secim;

    for (r = 0; r < N; r++) {
        for (c = 0; c < N; c++) {
            matris[r][c] = 0;
        }
        liste[r] = NULL;
    }

    for (int i = 0; i < 10; i++) {
        kenarEkle(kenarlar[i][0], kenarlar[i][1]);
    }

    while (1) {
        printf("\nBinalar:\n");
        for (int i = 0; i < N; i++) {
            printf("%d. %s\n", i + 1, bina[i]);
        }
        printf("\n1.Matris 2.Liste 3.BFS 4.DFS 5.Cikis\nSecim: ");
        scanf("%d", &secim);

        if (secim == 1) {
            printf("\n");
            for (r = 0; r < N; r++) {
                for (c = 0; c < N; c++) {
                    printf("%d ", matris[r][c]);
                }
                printf("\n");
            }
        } else if (secim == 2) {
            printf("\n");
            for (r = 0; r < N; r++) {
                printf("%d: ", r + 1);
                for (Dugum* temp = liste[r]; temp != NULL; temp = temp->sonraki) {
                    printf("%d ", temp->veri + 1);
                }
                printf("\n");
            }
        } else if (secim == 3) {
            printf("Baslangic: "); scanf("%d", &baslangic);
            printf("Hedef: "); scanf("%d", &hedef);
            bfs(baslangic - 1, hedef - 1);
        } else if (secim == 4) {
            dfs();
        } else if (secim == 5) {
            break;
        }
    }

    for (r = 0; r < N; r++) {
        Dugum* temp = liste[r];
        while (temp != NULL) {
            Dugum* sonraki = temp->sonraki;
            free(temp);
            temp = sonraki;
        }
    }
    return 0;
}

/*

#include <stdio.h>
#include <string.h>

#define MAX 50

// Global değişkenler
char aktifSayfa[100] = \"Ana Sayfa\";
char geriYigini[MAX][100];
char ileriYigini[MAX][100];
int geriTop = -1;
int ileriTop = -1;

// Yığına ekleme
void ekle(char yigin[][100], int *top, char *sayfa) {
    (*top)++;
    strcpy(yigin[*top], sayfa);
}

// Yığından çıkarma
int cikar(char yigin[][100], int *top, char *sonuc) {
    if (*top >= 0) {
        strcpy(sonuc, yigin[*top]);
        (*top)--;
        return 1;
    }
    return 0;
}

// Yığını temizle
void temizle(int *top) {
    *top = -1;
}

// Yığını yazdır
void yazdir(char yigin[][100], int top, char *isim) {
    printf(\"%s: [\", isim);
    for (int i = 0; i <= top; i++) {
        printf(\"%s\", yigin[i]);
        if (i < top) printf(\", \");
    }
    printf(\"]\n\");
}

// visit(url) - Yeni sayfa ziyaret et
void visit(char *url) {
    ekle(geriYigini, &geriTop, aktifSayfa);
    strcpy(aktifSayfa, url);
    temizle(&ileriTop);
}

// back() - Geri git
void back() {
    char onceki[100];
    if (cikar(geriYigini, &geriTop, onceki)) {
        ekle(ileriYigini, &ileriTop, aktifSayfa);
        strcpy(aktifSayfa, onceki);
    }
}

// forward() - İleri git
void forward() {
    char sonraki[100];
    if (cikar(ileriYigini, &ileriTop, sonraki)) {
        ekle(geriYigini, &geriTop, aktifSayfa);
        strcpy(aktifSayfa, sonraki);
    }
}

int main() {
    int secim;
    char url[100];

    while (1) {
        printf(\"\nAktif Sayfa: %s\n\", aktifSayfa);
        yazdir(geriYigini, geriTop, \"Back\");
        yazdir(ileriYigini, ileriTop, \"Forward\");
        
        printf(\"\n1. Yeni URL Ziyaret Et\n\");
        printf(\"2. Back\n\");
        printf(\"3. Forward\n\");
        printf(\"4. Cikis\n\");
        printf(\"Seciminiz: \");
        scanf(\"%d\", &secim);

        if (secim == 1) {
            printf(\"URL: \");
            scanf(\"%s\", url);
            visit(url);
        } else if (secim == 2) {
            back();
        } else if (secim == 3) {
            forward();
        } else if (secim == 4) {
            break;
        }
    }

    return 0;
}

*/