#include <stdio.h>
#include <stdlib.h>

typedef struct Dugum {
    int veri;
    struct Dugum *sonraki;
} Dugum;

Dugum *bas = NULL;

void listeYazdir();

void basaDugumEkle(int veri);

void sonaDugumEkle(int veri);

void arayaDugumEkle(int veri, int konum);

void dugumSil(int konum);

void listeyiSerbestBirak();

int main() {
    int secim, veri, konum;

    while (1) {
        printf("\n--- Menu ---\n");
        printf("1- Liste Yazdir\n");
        printf("2- Basa Dugum Ekle\n");
        printf("3- Sona Dugum Ekle\n");
        printf("4- Araya Dugum Ekle\n");
        printf("5- Dugum Sil\n");
        printf("6- Programdan Cik\n");

        printf("Secim yapin: ");
        scanf("%d", &secim);

        switch (secim) {
            case 1:
                listeYazdir();
                break;
            case 2:
                printf("Bir tamsayi girin: ");
                scanf("%d", &veri);
                basaDugumEkle(veri);
                break;
            case 3:
                printf("Bir tamsayi girin: ");
                scanf("%d", &veri);
                sonaDugumEkle(veri);
                break;
            case 4:
                printf("Bir tamsayi girin: ");
                scanf("%d", &veri);
                printf("Bir konum girin (0'dan baslayarak): ");
                scanf("%d", &konum);
                arayaDugumEkle(veri, konum);
                break;
            case 5:
                printf("Silinecek konumu girin (0'dan baslayarak): ");
                scanf("%d", &konum);
                dugumSil(konum);
                break;
            case 6:
                printf("Programdan cikiliyor...\n");
                listeyiSerbestBirak();
                exit(0);
            default:
                printf("Yanlis secim, tekrar deneyin!\n");
        }
    }
}

void listeYazdir() {
    Dugum *geciciDugum = bas;

    printf("Liste: ");
    while (geciciDugum != NULL) {
        printf("%d --> ", geciciDugum->veri);
        geciciDugum = geciciDugum->sonraki;
    }
    printf("NULL\n");
}

void basaDugumEkle(int veri) {
    Dugum *yeniDugum = malloc(sizeof(Dugum));

    if (!yeniDugum) {
        printf("Bellek ayirma hatasi olustu\n");
        return;
    }

    yeniDugum->veri = veri;
    yeniDugum->sonraki = bas;
    bas = yeniDugum;
}

void sonaDugumEkle(int veri) {
    Dugum *yeniDugum = malloc(sizeof(Dugum));

    if (!yeniDugum) {
        printf("Bellek ayirma hatasi olustu\n");
        return;
    }

    yeniDugum->veri = veri;
    yeniDugum->sonraki = NULL;

    if (bas == NULL) {
        bas = yeniDugum;
        return;
    }

    Dugum *gecici = bas;
    while (gecici->sonraki != NULL) {
        gecici = gecici->sonraki;
    }

    gecici->sonraki = yeniDugum;
}

void arayaDugumEkle(int veri, int konum) {
    if (konum < 0) {
        printf("Siralama indeksi 0'dan kucuk olamaz.\n");
        return;
    }

    Dugum *yeniDugum = malloc(sizeof(Dugum));
    
    if (!yeniDugum) {
        printf("Bellek ayirma hatasi olustu\n");
        return;
    }

    yeniDugum->veri = veri;

    if (konum == 0) {
        yeniDugum->sonraki = bas;
        bas = yeniDugum;
        return;
    }

    Dugum *gecici = bas;
    for (int i = 0; gecici != NULL && i < konum - 1; i++) {
        gecici = gecici->sonraki;
    }

    if (gecici == NULL) {
        printf("Konum liste uzunlugundan buyuk!\n");
        free(yeniDugum);
        return;
    }

    yeniDugum->sonraki = gecici->sonraki;
    gecici->sonraki = yeniDugum;
}

void dugumSil(int konum) {
    if (bas == NULL || konum < 0) {
        printf("Liste bos veya konum gecersiz!\n");
        return;
    }

    Dugum *gecici = bas;

    if (konum == 0) {
        bas = gecici->sonraki;
        free(gecici);
        printf("0. konum silindi!\n");
        return;
    }

    for (int i = 0; gecici != NULL && i < konum - 1; i++) {
        gecici = gecici->sonraki;
    }

    if (gecici == NULL || gecici->sonraki == NULL) {
        printf("Konum liste uzunlugundan buyuk! Silme basarisiz.\n");
        return;
    }

    Dugum *silinecekDugum = gecici->sonraki;
    gecici->sonraki = silinecekDugum->sonraki;
    free(silinecekDugum);
    printf("%d konumundaki dugum silindi.\n", konum);
}

void listeyiSerbestBirak() {
    Dugum *mevcut = bas;
    Dugum *sonraki;

    while (mevcut != NULL) {
        sonraki = mevcut->sonraki;
        free(mevcut);
        mevcut = sonraki;
    }

    bas = NULL;
}
