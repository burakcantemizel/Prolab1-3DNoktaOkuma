//! Programlama Laboratuvarı 1 - 3D Nokta Okuma
//!       Özge Poyraz - Burak Can Temizel
//!        180202025  -     180202024

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <math.h>

struct Dosya_bilgisi { //Dosya bilgilerini tutan struct yapisi
    int hata_durumu, alan_tipi, nokta_adeti, data_tipi;
};
struct Hatalar { //Hata bilgilerini tutan struct yapisi
    int baslik, surum, alan,nokta_baslik, nokta_sayisi, data_bilgisi, parametre, satir_no;
};
struct Nokta { //Nokta bilgilerini tutan struct yapisi
    double x, y, z;
    int r, g, b;
};
struct Parametre_hatasi{ //Parametre hatalarini tutan struct yapisi
    int *hata_kodu;
    int *satir_no;
}*ph;

int maks_param_hata = 0; //param hatalari dinamik dizi maks boyutu tutan değişken

//Varsayilan dosya baslik bilgileri(Dosya yapisi kontrolunde kullanilacak)
const char varsayilan_baslik[] = "# Noktalar dosya format\n";
const char varsayilan_surum[] = "VERSION 1\n";
const char varsayilan_alan_nokta_rgb[] = "ALANLAR x y z r g b\n";
const char varsayilan_alan_nokta[] = "ALANLAR x y z\n";
const char varsayilan_noktalar_kelimesi[] = "NOKTALAR";
const char varsayilan_data_ascii[] = "DATA ascii\n";
const char varsayilan_data_binary[] = "DATA binary\n";

struct Nokta * noktalar; //Dinamik olarak islemlerde kullanacagimiz noktalar dizisiş
struct Dosya_bilgisi dosya_bilgileri[0]; //Okunan nkt sayisina gore boyutlanacak dosya bilgisi dizisi

DIR * klasor; //Klasor degiskeni
struct dirent * klasor_girdisi; //Dosya girdileri icin kullanilacak struct yapisi

int nkt_adet; //nkt adeti
int nkt_uzunluk; //okunan nktlerden en uzununun boyutu

int dosya_kontrolu_yapildi_mi = 0; //İslemlerden once dosya kontrolu yapildi mi diye bakilacak.

void klasor_kontrol() { //Klasor kontrolu yapiliyor
    klasor = opendir("."); //Programin bulunduguzu dizini aciyoruz.
    if(klasor == NULL) { //Klasor okumada hata olusursa
        printf("Klasor okunurken bir hata olustu!n");
        exit(1);
    }
}
void nkt_dosyalari_kontrol() { //nkt isim dizisine ait bilgiler hesaplaniyor
    int nkt_sayac = 0;
    int mevcut_girdi_uzunlugu = 0;
    int maks_girdi_uzunlugu = 0;
    while( (klasor_girdisi = readdir(klasor) ) != NULL) { //Klasor icerisindeki tum girdileri okuyoruz.
        if(strstr(klasor_girdisi->d_name, ".nkt") != NULL && strstr(klasor_girdisi->d_name, "output") == NULL) { //nkt ise ve output degilse
            nkt_sayac += 1; //nkt dosyalarini sayiyoruz
            mevcut_girdi_uzunlugu = strlen(klasor_girdisi->d_name); //En uzun dosya adini tespit ediyoruz
            if(maks_girdi_uzunlugu < mevcut_girdi_uzunlugu) {
                maks_girdi_uzunlugu = mevcut_girdi_uzunlugu;
            }
        }
    }
    nkt_adet = nkt_sayac; //nkt adetini hesapliyoruz
    nkt_uzunluk = maks_girdi_uzunlugu + 1;//Sonlandirma karakteri de dahil.
}
void nkt_dosyalari_yukle(char nkt_dosyalari[][nkt_uzunluk], char nkt_output_dosyalari[][nkt_uzunluk]) { //nkt isim dizisine dosya isimleri atiliyor.
    int nkt_sayac = 0;
    rewinddir(klasor); //Klasorde tekrar islem yapacagimiz icin basa sariyoruz.
    while( (klasor_girdisi = readdir(klasor) ) != NULL ) { //Klasordeki dosyalari tekrar okuyoruz
        if(strstr(klasor_girdisi->d_name, ".nkt") != NULL && strstr(klasor_girdisi->d_name, "output") == NULL) { //nkt ise ve output degilse
            strcpy(nkt_dosyalari[nkt_sayac], klasor_girdisi->d_name); //nkt isim dizisine atiyoruz.
            nkt_sayac += 1;
        }
    }
}
void nkt_dosyalari_ac(FILE * dosyalar[nkt_adet],char nkt_dosyalari[nkt_adet][nkt_uzunluk]) { //nktler dosyalar olarak aciliyor
    int dosya_sayac;
    for(dosya_sayac = 0; dosya_sayac < nkt_adet; dosya_sayac++) { //Tum dosyalar isimlerine gore aciliyor
        dosyalar[dosya_sayac] = fopen(nkt_dosyalari[dosya_sayac], "r");
        if(dosyalar[dosya_sayac] == NULL) { //Eger bir hata olusursa hata veriliyor.
            printf("%s dosyasi acilirken bir hata olustu.", nkt_dosyalari[dosya_sayac]);
            exit(1);
        }
    }
}
void nkt_dosyalari_hata_kontrol(FILE * dosyalar[nkt_adet],char nkt_dosyalari[nkt_adet][nkt_uzunluk], char nkt_output_dosyalari[nkt_adet][nkt_uzunluk], struct Hatalar * dosya_hatalari) { //hata kontrol fonksiyonu
    int dosya_sayac;
    char satir_boyutu = 100;
    char satir[satir_boyutu];
    int parametre_hatasi_satir = 0;
    struct Hatalar hatalar; //Hata bilgilerini tutmak icin hatalar structini olusturduk.

    for(dosya_sayac = 0; dosya_sayac < nkt_adet; dosya_sayac++) { //Tum nktler icin yapiyoruz islemi.
        hatalar.parametre = 0; //Baslangicta her dosya icin parametre hatasini sifirliyoruz ilerde tespit edecegiz.
        printf("~~%s dosyasi icin hata kontrolu:\n", nkt_dosyalari[dosya_sayac]);

        fgets(satir, satir_boyutu, dosyalar[dosya_sayac]); //Baslik hatasi kontrolu
        if(strcmp(satir, varsayilan_baslik) != 0) {
            hatalar.baslik = 1;
            printf("-->Baslik bilgisi hatali bir sekilde verilmis!\n");
        } else {
            hatalar.baslik = 0;
        }

        fgets(satir, satir_boyutu, dosyalar[dosya_sayac]); //Surum hatasi kontrolu
        if(strcmp(satir, varsayilan_surum) != 0) {
            hatalar.surum = 1;
            printf("-->Surum bilgisi hatali bir sekilde verilmis!\n");
        } else {
            hatalar.surum = 0;
        }

        fgets(satir, satir_boyutu, dosyalar[dosya_sayac]); //Alan tipi kontrolu
        if(strcmp(satir, varsayilan_alan_nokta) == 0) { //xyz
            dosya_bilgileri[dosya_sayac].alan_tipi = 0;
            hatalar.alan = 0;
        } else if(strcmp(satir, varsayilan_alan_nokta_rgb) == 0) { //xyzrgb
            dosya_bilgileri[dosya_sayac].alan_tipi = 1;
            hatalar.alan = 0;
        } else {
            dosya_bilgileri[dosya_sayac].alan_tipi = -1;
            hatalar.alan = 1;
            printf("-->Alan tipi hatali bir sekilde verilmis. Dosya uygun bir nokta yapisi belirtmiyor!Parametre hatalarina bakilamaz.\n");
        }

        char noktalar_kelimesi[9]; //Nokta sayisi ve nokta basligi kontrolu
        float verilen_nokta_adeti;
        fscanf(dosyalar[dosya_sayac], "%s", noktalar_kelimesi);
        fscanf(dosyalar[dosya_sayac], "%f", &verilen_nokta_adeti);
        if(strcmp(noktalar_kelimesi, varsayilan_noktalar_kelimesi) == 0) {
            hatalar.nokta_baslik = 0;
        } else {
            hatalar.nokta_baslik = 1;
            printf("-->Nokta baslik bilgisi hatali bir sekilde verilmis!\n");
        }

        fgets(satir, satir_boyutu, dosyalar[dosya_sayac]); //fscanfden sonra bir satir atlatiyoruz.

        fgets(satir, satir_boyutu, dosyalar[dosya_sayac]); //Data tipi kontrolu
        if(strcmp(satir, varsayilan_data_ascii) == 0) {
            dosya_bilgileri[dosya_sayac].data_tipi = 0; //ascii
            hatalar.data_bilgisi = 0;
        } else if(strcmp(satir, varsayilan_data_binary) == 0) {
            dosya_bilgileri[dosya_sayac].data_tipi = 1; //binary
            hatalar.data_bilgisi = 0;
        } else {
            dosya_bilgileri[dosya_sayac].data_tipi = -1;
            hatalar.data_bilgisi = 1;
            printf("-->Data bilgisi hatali bir sekilde verilmis!\n");
        }


        int gercek_nokta_adeti = 0; //Binary ve ascii için ortak ->Buradan sonrasi ascii ve binary icin farkli sekilde olacak
        int hata_no = 0; //maks hata noyu sayip maks hata adetini dondurcek
        ph[dosya_sayac].hata_kodu = malloc(sizeof(int));
        ph[dosya_sayac].satir_no = malloc(sizeof(int));
        if(dosya_bilgileri[dosya_sayac].data_tipi == 0) { //Ascii ise
            while(fgets(satir, satir_boyutu, dosyalar[dosya_sayac]) != NULL ) {
                const char ayrac[2] = " ";
                char * kelime_girdisi;
                int parametre_sayisi = 0;

                kelime_girdisi = strtok(satir, ayrac); //ilk kelimeyi aldik
                parametre_sayisi += 1; //1. parametre

                while(kelime_girdisi != NULL) {
                    kelime_girdisi = strtok(NULL, ayrac);
                    parametre_sayisi += 1; //2. parametre ve diğer parametreler
                }
                //Parametre hatalari belli kodlara sahip ve 2 rakamdan olusuyor ilki beklenen parametre sayisi ikincisi gercekte olan
                parametre_sayisi -= 1; //Parametre sayisi 1 fazla donuyor ,satir sonlarinda bakacagiz parametre hatalarina
                if(dosya_bilgileri[dosya_sayac].alan_tipi == 0) { //alan xyz ise
                    if(parametre_sayisi > 3) { // ilk hata verildi mi kontrolü eklenirse sadece ilk satirdaki hatayi dondurecek
                        parametre_hatasi_satir = gercek_nokta_adeti;
                        hatalar.parametre = 34;
                        ph[dosya_sayac].hata_kodu[hata_no] = 34;
                        ph[dosya_sayac].satir_no[hata_no] = parametre_hatasi_satir+1;
                        hata_no += 1;
                        printf("-->%d. noktada xyz alan tipi icin fazladan parametre verilmis!\n", parametre_hatasi_satir+1);
                    } else if(parametre_sayisi < 3) {
                        parametre_hatasi_satir = gercek_nokta_adeti;
                        hatalar.parametre = 30;
                        ph[dosya_sayac].hata_kodu[hata_no] = 30;
                        ph[dosya_sayac].satir_no[hata_no] = parametre_hatasi_satir+1;
                        hata_no += 1;
                        printf("-->%d. noktada xyz bilgisi eksik verilmis!\n", parametre_hatasi_satir+1);
                    }
                } else if(dosya_bilgileri[dosya_sayac].alan_tipi == 1) { //xyzrgb
                    if(parametre_sayisi > 6) {
                        parametre_hatasi_satir = gercek_nokta_adeti;
                        hatalar.parametre = 67;
                        ph[dosya_sayac].hata_kodu[hata_no] = 67;
                        ph[dosya_sayac].satir_no[hata_no] = parametre_hatasi_satir+1;
                        hata_no += 1;
                        printf("-->%d. noktada xyzrgb alan tipi icin fazladan parametre verilmis!\n", parametre_hatasi_satir+1);
                    } else if(parametre_sayisi >= 3 && parametre_sayisi < 6) {
                        parametre_hatasi_satir = gercek_nokta_adeti;
                        hatalar.parametre = 63;
                        ph[dosya_sayac].hata_kodu[hata_no] = 63;
                        ph[dosya_sayac].satir_no[hata_no] = parametre_hatasi_satir+1;
                        hata_no += 1;
                        printf("-->%d. noktada rgb bilgisi eksik verilmis!\n", parametre_hatasi_satir+1);
                    } else if(parametre_sayisi < 3) {
                        parametre_hatasi_satir = gercek_nokta_adeti;
                        hatalar.parametre = 60;
                        ph[dosya_sayac].hata_kodu[hata_no] = 60;
                        ph[dosya_sayac].satir_no[hata_no] = parametre_hatasi_satir+1;
                        hata_no += 1;
                        printf("-->%d. noktada xyz ve rgb bilgisi eksik verilmis!\n", parametre_hatasi_satir+1);
                    }
                }//Yukarida parametre hatalarimi hata kodu gibi dondurduk.
                gercek_nokta_adeti += 1; //Her satir bir nokta
                ph[dosya_sayac].hata_kodu = realloc(ph[dosya_sayac].hata_kodu, (hata_no+1) * sizeof(int)); //Dinamik dizileri boyutlandırdık.
                ph[dosya_sayac].satir_no = realloc(ph[dosya_sayac].satir_no, (hata_no+1) * sizeof(int));
                if(hata_no > maks_param_hata){
                    maks_param_hata = hata_no;
                }
                //Nokta adeti her arttiginda parametre dizilerinide reallocluyoruz.
            }
        } else if(dosya_bilgileri[dosya_sayac].data_tipi == 1) { //Binary ise
            fclose(dosyalar[dosya_sayac]); //Dosyayi kapatip binary okuma modunda aciyoruz.
            dosyalar[dosya_sayac] = fopen(nkt_dosyalari[dosya_sayac],"rb");
            char satir[100];
            int baslik_satiri = 5;
            int k;
            for(k = 0; k < baslik_satiri; k++) { //İmleci dataya götürdük.
                fgets(satir,100,dosyalar[dosya_sayac]);
            }
            if(dosya_bilgileri[dosya_sayac].alan_tipi == 0) { // x y z
                float parametre;
                int binary_parametre_sayaci = 0;
                size_t sayac;
                while(1) {
                    sayac = fread(&parametre, sizeof(parametre),1,dosyalar[dosya_sayac]);
                    if(sayac < 1) {
                        break;
                    }
                    binary_parametre_sayaci += 1;
                    if(binary_parametre_sayaci % 3 == 0) {
                        gercek_nokta_adeti += 1;
                    }
                }
            } else if(dosya_bilgileri[dosya_sayac].alan_tipi == 1) { // x y z r g b
                float parametre;
                int parametre2;
                size_t sayac;
                while(1) {
                    sayac = fread(&parametre,sizeof(float),1,dosyalar[dosya_sayac]);
                    sayac = fread(&parametre,sizeof(float),1,dosyalar[dosya_sayac]);
                    sayac = fread(&parametre,sizeof(float),1,dosyalar[dosya_sayac]);
                    sayac = fread(&parametre2,sizeof(int),1,dosyalar[dosya_sayac]);
                    sayac = fread(&parametre2,sizeof(int),1,dosyalar[dosya_sayac]);
                    sayac = fread(&parametre2,sizeof(int),1,dosyalar[dosya_sayac]);
                    if(sayac < 1) {
                        break;
                    }
                    gercek_nokta_adeti += 1;
                }
            }
        }

        dosya_bilgileri[dosya_sayac].nokta_adeti = gercek_nokta_adeti; //Gercek nokta adetini dosya bilgilerine gonderiyoruz.

        if((float)gercek_nokta_adeti == verilen_nokta_adeti) { //Nokta sayisi tutmuyorsa hata
            hatalar.nokta_sayisi = 0;
        } else {
            hatalar.nokta_sayisi = 1;
            printf("-->Nokta sayisi dosyada belirtilen ile ayni degil!\n");
        }

        //En son hatalari yazdirmak icin struct yapimizla donduruyoruz.
        if(hatalar.alan == 1 || hatalar.baslik == 1 || hatalar.data_bilgisi == 1 ||
                hatalar.nokta_baslik == 1 || hatalar.nokta_sayisi == 1 || hatalar.parametre != 0 || hatalar.surum == 1) {

            dosya_bilgileri[dosya_sayac].hata_durumu = 1;
            if(hatalar.baslik == 1) {
                dosya_hatalari[dosya_sayac].baslik = 1;
            }
            if(hatalar.surum == 1) {
                dosya_hatalari[dosya_sayac].surum = 1;
            }
            if(hatalar.alan == 1) {
                dosya_hatalari[dosya_sayac].alan = 1;
            }
            if(hatalar.data_bilgisi == 1) {
                dosya_hatalari[dosya_sayac].data_bilgisi = 1;
            }
            if(hatalar.nokta_sayisi == 1) {
                dosya_hatalari[dosya_sayac].nokta_sayisi = 1;
            }
            if(hatalar.nokta_baslik == 1) {
                dosya_hatalari[dosya_sayac].nokta_baslik = 1;
            }
            dosya_hatalari[dosya_sayac].satir_no = parametre_hatasi_satir+1;
        } else {
            dosya_bilgileri[dosya_sayac].hata_durumu = 0;
            printf("-->Bu dosyada herhangi bir hata bulunmamaktadir.\n");
        }
        printf("\n");
    }
}
void ascii_nokta_oku_diziye_at(FILE * dosya,struct Nokta * noktalar,int alan_tipi) { //ascii noktalari okuma fonksiyonu
    int satir_boyutu = 100;
    char satir[satir_boyutu];
    fseek(dosya,0, SEEK_SET); //dosyanin basina gidelim once
    int k;
    int baslik_satirlari = 5;
    for(k = 0; k < baslik_satirlari; k++) {
        fgets(satir, satir_boyutu, dosya);
    } // 5 satir bos okuyoruz.

    //Burdan sonra nokta okuyoruz. alan tipi 0 icin ilk 3 parametre alcaz alan tipi 1 icin 6 parametre
    if(alan_tipi == 0) {
        int nokta_indeks = 0;
        int parametre_sayaci;

        while(fgets(satir, satir_boyutu, dosya) != NULL) {
            parametre_sayaci = 1;
            const char ayrac[2] = " ";
            char * kelime_girdisi;

            kelime_girdisi = strtok(satir,ayrac);//Burada ilk parametre donuyor.
            noktalar[nokta_indeks].x = atof(kelime_girdisi);

            while(kelime_girdisi != NULL) {
                parametre_sayaci += 1;
                kelime_girdisi = strtok(NULL, ayrac);
                if(parametre_sayaci == 2) {
                    noktalar[nokta_indeks].y = atof(kelime_girdisi);
                }
                if(parametre_sayaci == 3) {
                    noktalar[nokta_indeks].z = atof(kelime_girdisi);
                }
            }
            nokta_indeks++;
        }
    } else if(alan_tipi == 1) {
        int nokta_indeks = 0;
        int parametre_sayaci;

        while(fgets(satir, satir_boyutu, dosya) != NULL) {
            parametre_sayaci = 1;
            const char ayrac[2] = " ";
            char * kelime_girdisi;

            kelime_girdisi = strtok(satir,ayrac);//Burada ilk parametre donuyor.
            noktalar[nokta_indeks].x = atof(kelime_girdisi);

            while(kelime_girdisi != NULL) {
                parametre_sayaci += 1;
                kelime_girdisi = strtok(NULL, ayrac);
                if(parametre_sayaci == 2) {
                    noktalar[nokta_indeks].y = atof(kelime_girdisi);
                }
                if(parametre_sayaci == 3) {
                    noktalar[nokta_indeks].z = atof(kelime_girdisi);
                }
                if(parametre_sayaci == 4) {
                    noktalar[nokta_indeks].r = atoi(kelime_girdisi);
                }
                if(parametre_sayaci == 5) {
                    noktalar[nokta_indeks].g = atoi(kelime_girdisi);
                }
                if(parametre_sayaci == 6) {
                    noktalar[nokta_indeks].b = atoi(kelime_girdisi);
                }
            }
            nokta_indeks++;
        }
    }
}
void binary_nokta_oku_diziye_at(FILE * dosya, struct Nokta * noktalar,int alan_tipi) { //binary noktalari okuma fonksiyonu
    char satir[100];
    int baslik_sayisi = 5;
    int k;
    for(k = 0; k < baslik_sayisi; k++) {
        fgets(satir,100,dosya); //Baslik satirlarini atliyoruz
    }
    size_t fread_sayac;
    int nokta_indeks = 0;
    if(alan_tipi == 0) { //xyz ise
        while(1) {
            float param1,param2,param3;
            fread_sayac = fread(&param1,sizeof(float),1,dosya);
            fread_sayac = fread(&param2,sizeof(float),1,dosya);
            fread_sayac = fread(&param3,sizeof(float),1,dosya);

            if(fread_sayac < 1) {
                break;
            }
            noktalar[nokta_indeks].x = param1;
            noktalar[nokta_indeks].y = param2;
            noktalar[nokta_indeks].z = param3;
            nokta_indeks++;
        }
    } else if(alan_tipi == 1) { //xyzrgb ise
        while( 1 ) {
            float param1,param2,param3;
            int param4,param5,param6;
            fread_sayac = fread(&param1,sizeof(float),1,dosya);
            fread_sayac = fread(&param2,sizeof(float),1,dosya);
            fread_sayac = fread(&param3,sizeof(float),1,dosya);
            fread_sayac = fread(&param4,sizeof(int),1,dosya);
            fread_sayac = fread(&param5,sizeof(int),1,dosya);
            fread_sayac = fread(&param6,sizeof(int),1,dosya);
            if(fread_sayac < 1) {
                break;
            }
            noktalar[nokta_indeks].x = param1;
            noktalar[nokta_indeks].y = param2;
            noktalar[nokta_indeks].z = param3;
            noktalar[nokta_indeks].r = param4;
            noktalar[nokta_indeks].g = param5;
            noktalar[nokta_indeks].b = param6;
            nokta_indeks++;
        }
    }
}
double uzaklik_hesapla(double x1, double y1, double z1, double x2, double y2, double z2) { //uzaklik hesabi
    return sqrt( pow(x2-x1,2) + pow(y2-y1,2) + pow(z2-z1,2) );
}
int kurenin_icinde_mi(double kure_x, double kure_y, double kure_z, double kure_r, double nokta_x, double nokta_y, double nokta_z) { //kure hesabi
    if(uzaklik_hesapla(kure_x,kure_y,kure_z,nokta_x,nokta_y,nokta_z) <= kure_r) {
        return 1;
    }
    return 0;
}

int main() {
    klasor_kontrol();
    nkt_dosyalari_kontrol();

    char nkt_dosyalari[nkt_adet][nkt_uzunluk]; //nktlerin isim bilgilerini tutan dizi
    char nkt_output_dosyalari[nkt_adet][nkt_uzunluk+8];//outputlarin isim bilgilerini tutan dizi "output_" eklenerek olusturulcak.

    realloc(dosya_bilgileri, nkt_adet * sizeof(struct Dosya_bilgisi)); //nkt adeti kadar dosya_bilgileri dizisi olusturuyorum.
    nkt_dosyalari_yukle(nkt_dosyalari, nkt_output_dosyalari); //nkt dosyalarinin isim bilgilerini diziye attik

    /*
    struct Parametre_hatasi parametre_hatalari[nkt_adet];
    memset(parametre_hatalari,0,nkt_adet * sizeof(struct Parametre_hatasi));
    */
    ph = malloc(nkt_adet * sizeof(struct Parametre_hatasi));

    printf("###### 3D Nokta Bilgisi Okuyucu ######\n\n"); //Program arayuzu
    printf("~~Bu program klasordeki nkt dosyalarindan nokta bilgilerini okur ve bazi hesaplamalar gerceklestirir.\n");
    printf("~~!!Herhangi bir islem gerceklestirilmeden once hata kontrolu yapilmasi gerekmektedir.\n");
    printf("~~!!Output dosyalari islem sirasina gore bicimlenmektedir.Varsayilan tip icin islemleri sirasiyla yapiniz.\n");
    printf("\nKlasorden okunan nkt dosyalari: \n"); //Klasorden okunan nkt dosyalarini yazdiriyoruz.
    int i;
    for(i = 0; i < nkt_adet; i++) {
        printf("->%s\n", nkt_dosyalari[i]);
    }

    FILE * dosyalar[nkt_adet]; //nkt adeti kadar dosya olusturuyoruz.
    FILE * output_dosyalari[nkt_adet]; //nkt adeti kadar da output olusturuyoruz.
    nkt_dosyalari_ac(dosyalar,nkt_dosyalari); //Olusturdugumuz dosyalari aciyoruz

    struct Hatalar dosya_hatalari[nkt_adet];
    memset(dosya_hatalari,0,nkt_adet * sizeof(struct Hatalar)); //Tüm elemanlarini sıfırladık.

    int islem_numarasi;
    while(1) {
        printf("\n"); //Menu arayuzu
        printf("###### Uygulama Menusu ######\n\n");
        printf("1) Dosya hata kontrolu\n");
        printf("2) En yakin ve en uzak noktalar\n");
        printf("3) Tum noktalari icine alan en kucuk kup\n");
        printf("4) Kurenin icindeki noktalar\n");
        printf("5) Noktalarin ortalama uzakligi\n");
        printf("6) Cikis\n");
        printf("\nGerceklestirmek istediginiz islemi giriniz >> ");
        scanf("%d",&islem_numarasi);

        switch(islem_numarasi-1) {
        case 0:
            if(dosya_kontrolu_yapildi_mi == 0) {
                printf("\n###### Dosya Kontrolu ######\n\n");
                nkt_dosyalari_hata_kontrol(dosyalar,nkt_dosyalari,nkt_output_dosyalari,dosya_hatalari);
                dosya_kontrolu_yapildi_mi = 1;

                int i;
                for(i = 0; i < nkt_adet; i++) { //Outputlari olusturup secim1'i basiyoruz.
                    strcpy(nkt_output_dosyalari[i], "output_");
                    strcat(nkt_output_dosyalari[i], nkt_dosyalari[i]);
                    output_dosyalari[i] = fopen(nkt_output_dosyalari[i], "w");
                    if(dosya_bilgileri[i].hata_durumu == 0) {
                        fputs("SECIM 1\nBu dosyada herhangi bir hata bulunmamaktadir.\n",output_dosyalari[i]);
                    } else {
                        fputs("SECIM 1\nBu dosyada hatalar mevcuttur.\n",output_dosyalari[i]);
                        if(dosya_hatalari[i].baslik == 1) {
                            fputs("-->Baslik bilgisi hatali verilmis!\n",output_dosyalari[i]);
                        }
                        if(dosya_hatalari[i].surum == 1) {
                            fputs("-->Surum bilgisi hatali verilmis!\n",output_dosyalari[i]);
                        }
                        if(dosya_hatalari[i].alan == 1) {
                            fputs("-->Alan tipi hatali bir sekilde verilmis.Dosya uygun bir nokta yapisi belirtmiyor!Parametre hatalarina bakilamaz.Lutfen nokta yapisini duzeltin.\n",output_dosyalari[i]);
                        }
                        if(dosya_hatalari[i].data_bilgisi == 1) {
                            fputs("-->Data bilgisi hatali verilmis!\n",output_dosyalari[i]);
                        }
                        if(dosya_hatalari[i].nokta_sayisi == 1) {
                            fputs("-->Nokta sayisi dosyada belirtilen ile ayni degil!\n",output_dosyalari[i]);
                        }
                        if(dosya_hatalari[i].nokta_baslik == 1) {
                            fputs("-->Nokta baslik bilgisi hatali verilmis!\n",output_dosyalari[i]);
                        }

                        int param_sayac; //Parametre hatalarini basiyoruz.
                        for(param_sayac = 0; param_sayac < maks_param_hata; param_sayac++){
                        switch(ph[i].hata_kodu[param_sayac]){
                            case 34:
                                fprintf(output_dosyalari[i],"-->%d. noktada xyz icin fazladan parametre verilmis!\n",ph[i].satir_no[param_sayac]);
                                break;
                            case 30:
                                fprintf(output_dosyalari[i],"-->%d. noktada xyz bilgisi eksik verilmis!\n",ph[i].satir_no[param_sayac]);
                                break;
                            case 67:
                                fprintf(output_dosyalari[i],"-->%d. noktada xyzrgb icin fazladan parametre verilmis!\n",ph[i].satir_no[param_sayac]);
                                break;
                            case 63:
                                fprintf(output_dosyalari[i],"-->%d. noktada rgb bilgisi eksik verilmis!\n",ph[i].satir_no[param_sayac]);
                                break;
                            case 60:
                                fprintf(output_dosyalari[i],"-->%d. noktada xyz ve rgb eksik verilmis!\n",ph[i].satir_no[param_sayac]);
                                break;
                            default:
                                break;
                            }
                        }
                    }
                    fclose(output_dosyalari[i]);
                }
            } else {
                printf("\n~~!!!Dosya kontrolu zaten yapilmis!!!~~\n");
            }
            break;
        case 1:
            if(dosya_kontrolu_yapildi_mi == 0) {
                printf("\n~~Lutfen once dosya kontrolunu gerceklestiriniz.!~~\n");
                continue;
            }
            printf("\n###### En Yakin ve En Uzak Noktalar ######\n\n");
            int i;
            for(i = 0; i < nkt_adet; i++) {
                if(dosya_bilgileri[i].hata_durumu == 0) {
                    noktalar = realloc(noktalar,dosya_bilgileri[i].nokta_adeti * sizeof(struct Nokta));
                    printf("~~%s dosyasi icin islem yapiliyor >>\n", nkt_dosyalari[i]);
                    if(dosya_bilgileri[i].data_tipi == 0) { //ascii
                        ascii_nokta_oku_diziye_at(dosyalar[i], noktalar, dosya_bilgileri[i].alan_tipi);
                    } else if(dosya_bilgileri[i].data_tipi == 1) { //binary
                        fclose(dosyalar[i]);
                        dosyalar[i] = fopen(nkt_dosyalari[i],"rb");
                        binary_nokta_oku_diziye_at(dosyalar[i],noktalar,dosya_bilgileri[i].alan_tipi);
                    }
                    double min_uzaklik = uzaklik_hesapla(noktalar[0].x, noktalar[0].y, noktalar[0].z, noktalar[1].x, noktalar[1].y, noktalar[1].z);
                    double max_uzaklik = uzaklik_hesapla(noktalar[0].x, noktalar[0].y, noktalar[0].z, noktalar[1].x, noktalar[1].y, noktalar[1].z);
                    int min_nokta1_indeks = 0;
                    int min_nokta2_indeks = 1;
                    int max_nokta1_indeks = 0;
                    int max_nokta2_indeks = 1;
                    int sayac1,sayac2;
                    printf("~~%d nokta icin ",dosya_bilgileri[i].nokta_adeti);
                    printf("uzakliklar hesaplaniyor bu islem biraz zaman alabilir... >>\n");
                    double mevcut_uzaklik = 0;
                    for(sayac1 = 0; sayac1 < dosya_bilgileri[i].nokta_adeti; sayac1++) {
                        for(sayac2 = sayac1+1; sayac2 < dosya_bilgileri[i].nokta_adeti; sayac2++) {
                            mevcut_uzaklik = uzaklik_hesapla(noktalar[sayac1].x, noktalar[sayac1].y, noktalar[sayac1].z, noktalar[sayac2].x, noktalar[sayac2].y, noktalar[sayac2].z);
                            if(min_uzaklik > mevcut_uzaklik) {
                                min_uzaklik = mevcut_uzaklik;
                                min_nokta1_indeks = sayac1;
                                min_nokta2_indeks = sayac2;
                            }
                            if(max_uzaklik < mevcut_uzaklik) {
                                max_uzaklik = mevcut_uzaklik;
                                max_nokta1_indeks = sayac1;
                                max_nokta2_indeks = sayac2;
                            }
                        }
                    }
                    printf("En kisa uzaklik : %f\n", min_uzaklik);
                    printf("En uzun uzaklik : %f\n", max_uzaklik);
                    if(dosya_bilgileri[i].alan_tipi == 0) { // konsol ekranı çıktıları xyz ise
                        printf("En yakin 1. noktanin bilgileri: %lf %lf %lf Nokta numarasi: %d\n", noktalar[min_nokta1_indeks].x,noktalar[min_nokta1_indeks].y,noktalar[min_nokta1_indeks].z,min_nokta1_indeks+1);
                        printf("En yakin 2. noktanin bilgileri: %lf %lf %lf Nokta numarasi: %d\n", noktalar[min_nokta2_indeks].x,noktalar[min_nokta2_indeks].y,noktalar[min_nokta2_indeks].z,min_nokta2_indeks+1);
                        printf("En uzak 1. noktanin bilgileri: %lf %lf %lf Nokta numarasi: %d\n", noktalar[max_nokta1_indeks].x,noktalar[max_nokta1_indeks].y,noktalar[max_nokta1_indeks].z,max_nokta1_indeks+1);
                        printf("En uzak 2. noktanin bilgileri: %lf %lf %lf Nokta numarasi: %d\n\n", noktalar[max_nokta2_indeks].x,noktalar[max_nokta2_indeks].y,noktalar[max_nokta2_indeks].z,max_nokta2_indeks+1);
                    } else if(dosya_bilgileri[i].alan_tipi == 1) { //xyzrgb ise
                        printf("En yakin 1. noktanin bilgileri: %lf %lf %lf %d %d %d Nokta numarasi: %d\n", noktalar[min_nokta1_indeks].x,noktalar[min_nokta1_indeks].y,noktalar[min_nokta1_indeks].z,
                               noktalar[min_nokta1_indeks].r,noktalar[min_nokta1_indeks].g,noktalar[min_nokta1_indeks].b,min_nokta1_indeks+1);
                        printf("En yakin 2. noktanin bilgileri: %lf %lf %lf %d %d %d Nokta numarasi: %d\n", noktalar[min_nokta2_indeks].x,noktalar[min_nokta2_indeks].y,noktalar[min_nokta2_indeks].z,
                               noktalar[min_nokta2_indeks].r,noktalar[min_nokta2_indeks].g,noktalar[min_nokta2_indeks].b,min_nokta2_indeks+1);
                        printf("En uzak 1. noktanin bilgileri: %lf %lf %lf %d %d %d Nokta numarasi: %d\n", noktalar[max_nokta1_indeks].x,noktalar[max_nokta1_indeks].y,noktalar[max_nokta1_indeks].z,
                               noktalar[max_nokta1_indeks].r,noktalar[max_nokta1_indeks].g,noktalar[max_nokta1_indeks].b,max_nokta1_indeks+1);
                        printf("En uzak 2. noktanin bilgileri: %lf %lf %lf %d %d %d Nokta numarasi: %d\n\n", noktalar[max_nokta2_indeks].x,noktalar[max_nokta2_indeks].y,noktalar[max_nokta2_indeks].z,
                               noktalar[max_nokta2_indeks].r,noktalar[max_nokta2_indeks].g,noktalar[max_nokta2_indeks].b,max_nokta2_indeks+1);
                    }
                    if(dosya_bilgileri[i].data_tipi == 0) { //ascii için output çıktıları
                        output_dosyalari[i] = fopen(nkt_output_dosyalari[i], "a");
                        if(dosya_bilgileri[i].alan_tipi == 0) { //xyz
                            fprintf(output_dosyalari[i],"SECIM 2\n");
                            fprintf(output_dosyalari[i],"%f %f %f\n", noktalar[min_nokta1_indeks].x,noktalar[min_nokta1_indeks].y,noktalar[min_nokta1_indeks].z);
                            fprintf(output_dosyalari[i],"%f %f %f\n", noktalar[min_nokta2_indeks].x,noktalar[min_nokta2_indeks].y,noktalar[min_nokta2_indeks].z);
                            fprintf(output_dosyalari[i],"%f %f %f\n", noktalar[max_nokta1_indeks].x,noktalar[max_nokta1_indeks].y,noktalar[max_nokta1_indeks].z);
                            fprintf(output_dosyalari[i],"%f %f %f\n", noktalar[max_nokta2_indeks].x,noktalar[max_nokta2_indeks].y,noktalar[max_nokta2_indeks].z);
                        } else if(dosya_bilgileri[i].alan_tipi == 1) { //xyzrgb
                            fprintf(output_dosyalari[i],"SECIM 2\n");
                            fprintf(output_dosyalari[i],"%f %f %f %d %d %d\n", noktalar[min_nokta1_indeks].x,noktalar[min_nokta1_indeks].y,noktalar[min_nokta1_indeks].z,
                                    noktalar[min_nokta1_indeks].r,noktalar[min_nokta1_indeks].g,noktalar[min_nokta1_indeks].b);
                            fprintf(output_dosyalari[i],"%f %f %f %d %d %d\n", noktalar[min_nokta2_indeks].x,noktalar[min_nokta2_indeks].y,noktalar[min_nokta2_indeks].z,
                                    noktalar[min_nokta2_indeks].r,noktalar[min_nokta2_indeks].g,noktalar[min_nokta2_indeks].b);
                            fprintf(output_dosyalari[i],"%f %f %f %d %d %d\n", noktalar[max_nokta1_indeks].x,noktalar[max_nokta1_indeks].y,noktalar[max_nokta1_indeks].z,
                                    noktalar[max_nokta1_indeks].r,noktalar[max_nokta1_indeks].g,noktalar[max_nokta1_indeks].b);
                            fprintf(output_dosyalari[i],"%f %f %f %d %d %d\n", noktalar[max_nokta2_indeks].x,noktalar[max_nokta2_indeks].y,noktalar[max_nokta2_indeks].z,
                                    noktalar[max_nokta2_indeks].r,noktalar[max_nokta2_indeks].g,noktalar[max_nokta2_indeks].b);
                        }
                    } else if(dosya_bilgileri[i].data_tipi == 1) { //Binary için output çıktıları
                        output_dosyalari[i] = fopen(nkt_output_dosyalari[i], "a+b");
                        fprintf(output_dosyalari[i],"SECIM 2\n");
                        if(dosya_bilgileri[i].alan_tipi == 0) { //xyz
                            fwrite(&(noktalar[min_nokta1_indeks].x),sizeof(double),1,output_dosyalari[i]);  fwrite(&(noktalar[min_nokta1_indeks].y),sizeof(double),1,output_dosyalari[i]);
                            fwrite(&(noktalar[min_nokta1_indeks].z),sizeof(double),1,output_dosyalari[i]);  fwrite(&(noktalar[min_nokta2_indeks].x),sizeof(double),1,output_dosyalari[i]);
                            fwrite(&(noktalar[min_nokta2_indeks].y),sizeof(double),1,output_dosyalari[i]);  fwrite(&(noktalar[min_nokta2_indeks].z),sizeof(double),1,output_dosyalari[i]);
                            fwrite(&(noktalar[max_nokta1_indeks].x),sizeof(double),1,output_dosyalari[i]);  fwrite(&(noktalar[max_nokta1_indeks].y),sizeof(double),1,output_dosyalari[i]);
                            fwrite(&(noktalar[max_nokta1_indeks].z),sizeof(double),1,output_dosyalari[i]);  fwrite(&(noktalar[max_nokta2_indeks].x),sizeof(double),1,output_dosyalari[i]);
                            fwrite(&(noktalar[max_nokta2_indeks].y),sizeof(double),1,output_dosyalari[i]);  fwrite(&(noktalar[max_nokta2_indeks].z),sizeof(double),1,output_dosyalari[i]);
                        } else if(dosya_bilgileri[i].alan_tipi == 1) { //xyzrgb
                            fwrite(&(noktalar[min_nokta1_indeks].x),sizeof(double),1,output_dosyalari[i]);  fwrite(&(noktalar[min_nokta1_indeks].y),sizeof(double),1,output_dosyalari[i]);
                            fwrite(&(noktalar[min_nokta1_indeks].z),sizeof(double),1,output_dosyalari[i]);  fwrite(&(noktalar[min_nokta1_indeks].r),sizeof(int),1,output_dosyalari[i]);
                            fwrite(&(noktalar[min_nokta1_indeks].g),sizeof(int),1,output_dosyalari[i]);     fwrite(&(noktalar[min_nokta1_indeks].b),sizeof(int),1,output_dosyalari[i]);
                            fwrite(&(noktalar[min_nokta2_indeks].x),sizeof(double),1,output_dosyalari[i]);  fwrite(&(noktalar[min_nokta2_indeks].y),sizeof(double),1,output_dosyalari[i]);
                            fwrite(&(noktalar[min_nokta2_indeks].z),sizeof(double),1,output_dosyalari[i]);  fwrite(&(noktalar[min_nokta2_indeks].r),sizeof(int),1,output_dosyalari[i]);
                            fwrite(&(noktalar[min_nokta2_indeks].g),sizeof(int),1,output_dosyalari[i]);     fwrite(&(noktalar[min_nokta2_indeks].b),sizeof(int),1,output_dosyalari[i]);
                            fwrite(&(noktalar[max_nokta1_indeks].x),sizeof(double),1,output_dosyalari[i]);  fwrite(&(noktalar[max_nokta1_indeks].y),sizeof(double),1,output_dosyalari[i]);
                            fwrite(&(noktalar[max_nokta1_indeks].z),sizeof(double),1,output_dosyalari[i]);  fwrite(&(noktalar[max_nokta1_indeks].r),sizeof(int),1,output_dosyalari[i]);
                            fwrite(&(noktalar[max_nokta1_indeks].g),sizeof(int),1,output_dosyalari[i]);     fwrite(&(noktalar[max_nokta1_indeks].b),sizeof(int),1,output_dosyalari[i]);
                            fwrite(&(noktalar[max_nokta2_indeks].x),sizeof(double),1,output_dosyalari[i]);  fwrite(&(noktalar[max_nokta2_indeks].y),sizeof(double),1,output_dosyalari[i]);
                            fwrite(&(noktalar[max_nokta2_indeks].z),sizeof(double),1,output_dosyalari[i]);  fwrite(&(noktalar[max_nokta2_indeks].r),sizeof(int),1,output_dosyalari[i]);
                            fwrite(&(noktalar[max_nokta2_indeks].g),sizeof(int),1,output_dosyalari[i]);     fwrite(&(noktalar[max_nokta2_indeks].b),sizeof(int),1,output_dosyalari[i]);
                        }
                    }
                    fclose(output_dosyalari[i]);
                }
            }
            break;

        case 2:
            if(dosya_kontrolu_yapildi_mi == 0) {
                printf("\n~~Lutfen once dosya kontrolunu gerceklestiriniz.!~~\n");
                continue;
            }
            printf("\n###### Tum Noktalari Icine Alan En Kucuk Kup ######\n\n");
            printf("~~Her nokta kumesi icin en kucuk kupun ayrit uzunlugu bellidir.\n~~Fakat herhangi bir eksendeki noktalar arasi uzaklik bu degerden\n~~kucuk ise ");
            printf("sonsuz sayida en kucuk kup cizilebilmektedir.\n~~Bu program kupu merkeze oteleyerek kose degerlerini size verir.\n\n");
            for(i = 0; i < nkt_adet; i++) {
                if(dosya_bilgileri[i].hata_durumu == 0) {
                    noktalar = realloc(noktalar,dosya_bilgileri[i].nokta_adeti * sizeof(struct Nokta));
                    //struct Nokta noktalar[dosya_bilgileri[i].nokta_adeti];
                    printf("~~%s dosyasi icin en kucuk kup islemi yapiliyor >>\n", nkt_dosyalari[i]);
                    if(dosya_bilgileri[i].data_tipi == 0) { //ascii
                        ascii_nokta_oku_diziye_at(dosyalar[i], noktalar, dosya_bilgileri[i].alan_tipi);
                    } else if(dosya_bilgileri[i].data_tipi == 1) { //binary
                        fclose(dosyalar[i]);
                        dosyalar[i] = fopen(nkt_dosyalari[i],"rb");
                        binary_nokta_oku_diziye_at(dosyalar[i],noktalar,dosya_bilgileri[i].alan_tipi);
                    }
                    double xMin = noktalar[0].x;    double xMax = noktalar[0].x;    double yMin = noktalar[0].y;
                    double yMax = noktalar[0].y;    double zMin = noktalar[0].z;    double zMax = noktalar[0].z;
                    int sayac;
                    for(sayac = 0; sayac < dosya_bilgileri[i].nokta_adeti; sayac++) { //eksenlerdeki min maks noktaların tespiti
                        if(yMin > noktalar[sayac].y) {
                            yMin = noktalar[sayac].y;
                        }
                        if(yMax < noktalar[sayac].y) {
                            yMax = noktalar[sayac].y;
                        }
                        if(xMin > noktalar[sayac].x) {
                            xMin = noktalar[sayac].x;
                        }
                        if(xMax < noktalar[sayac].x) {
                            xMax = noktalar[sayac].x;
                        }
                        if(zMin > noktalar[sayac].z) {
                            zMin = noktalar[sayac].z;
                        }
                        if(zMax < noktalar[sayac].z) {
                            zMax = noktalar[sayac].z;
                        }
                    }
                    double kup_x = (xMax+xMin) / 2.0;   double kup_y = (yMax+yMin) / 2.0;   double kup_z = (zMax+zMin) / 2.0; //kupun merkez noktasi
                    double kup_yari_kenar;
                    double uzunluklar[6];

                    uzunluklar[0] = uzaklik_hesapla(kup_x,0,0,xMin,0,0);    uzunluklar[1] = uzaklik_hesapla(kup_x,0,0,xMax,0,0);
                    uzunluklar[2] = uzaklik_hesapla(0, kup_y,0, 0, yMin,0); uzunluklar[3] = uzaklik_hesapla(0, kup_y,0,0,yMax,0);
                    uzunluklar[4] = uzaklik_hesapla(0,0,kup_z,0,0,zMin);    uzunluklar[5] = uzaklik_hesapla(0,0,kup_z,0,0,zMax);

                    kup_yari_kenar = uzunluklar[0]; //Her eksendeki maks uzunlugunda en cok olanini buluyoruz bu kenari verecek
                    for(sayac = 0; sayac < 6; sayac++) {
                        if(kup_yari_kenar < uzunluklar[sayac]) {
                            kup_yari_kenar = uzunluklar[sayac];
                        }
                    }
                    //Küp merkez noktasi ve yarikenar uzunlugunu biliyoruz buradan köşe noktalarini hesaplicaz.
                    struct Nokta kup_noktalar[8];
                    kup_noktalar[0].x = kup_x + kup_yari_kenar; kup_noktalar[0].y = kup_y - kup_yari_kenar; kup_noktalar[0].z = kup_z - kup_yari_kenar;
                    kup_noktalar[1].x = kup_x + kup_yari_kenar; kup_noktalar[1].y = kup_y - kup_yari_kenar; kup_noktalar[1].z = kup_z + kup_yari_kenar;
                    kup_noktalar[2].x = kup_x - kup_yari_kenar; kup_noktalar[2].y = kup_y - kup_yari_kenar; kup_noktalar[2].z = kup_z + kup_yari_kenar;
                    kup_noktalar[3].x = kup_x - kup_yari_kenar; kup_noktalar[3].y = kup_y - kup_yari_kenar; kup_noktalar[3].z = kup_z - kup_yari_kenar;
                    kup_noktalar[4].x = kup_x + kup_yari_kenar; kup_noktalar[4].y = kup_y + kup_yari_kenar; kup_noktalar[4].z = kup_z - kup_yari_kenar;
                    kup_noktalar[5].x = kup_x + kup_yari_kenar; kup_noktalar[5].y = kup_y + kup_yari_kenar; kup_noktalar[5].z = kup_z + kup_yari_kenar;
                    kup_noktalar[6].x = kup_x - kup_yari_kenar; kup_noktalar[6].y = kup_y + kup_yari_kenar; kup_noktalar[6].z = kup_z + kup_yari_kenar;
                    kup_noktalar[7].x = kup_x - kup_yari_kenar; kup_noktalar[7].y = kup_y + kup_yari_kenar; kup_noktalar[7].z = kup_z - kup_yari_kenar;

                    for(sayac = 0; sayac < 8; sayac++) {
                        if(dosya_bilgileri[i].alan_tipi == 0) {
                            printf("%f %f %f\n",kup_noktalar[sayac].x,kup_noktalar[sayac].y,kup_noktalar[sayac].z);
                        } else {
                            printf("%f %f %f %d %d %d\n",kup_noktalar[sayac].x,kup_noktalar[sayac].y,kup_noktalar[sayac].z,255, 255, 255);
                        }
                    }
                    printf("\n");

                    //Output kısmi
                    if(dosya_bilgileri[i].data_tipi == 0) { //ascii
                        output_dosyalari[i] = fopen(nkt_output_dosyalari[i], "a");
                        if(dosya_bilgileri[i].alan_tipi == 0) { //xyz
                            fprintf(output_dosyalari[i],"SECIM 3\n");
                            int kup_sayac;
                            for(kup_sayac = 0; kup_sayac < 8; kup_sayac++) {
                                fprintf(output_dosyalari[i],"%f %f %f\n",kup_noktalar[kup_sayac].x,kup_noktalar[kup_sayac].y,kup_noktalar[kup_sayac].z);
                            }
                        } else if(dosya_bilgileri[i].alan_tipi == 1) { //xyzrgb
                            fprintf(output_dosyalari[i],"SECIM 3\n");
                            int kup_sayac;
                            for(kup_sayac = 0; kup_sayac < 8; kup_sayac++) {
                                fprintf(output_dosyalari[i],"%f %f %f %d %d %d\n",kup_noktalar[kup_sayac].x,kup_noktalar[kup_sayac].y,kup_noktalar[kup_sayac].z, 255, 255, 255);
                            }
                        }
                    } else if(dosya_bilgileri[i].data_tipi == 1) { //Binary için
                        output_dosyalari[i] = fopen(nkt_output_dosyalari[i], "a+b");
                        fprintf(output_dosyalari[i],"\nSECIM 3\n");
                        if(dosya_bilgileri[i].alan_tipi == 0) {
                            int kup_sayac;
                            for(kup_sayac = 0; kup_sayac < 8; kup_sayac++) {
                                fwrite(&(kup_noktalar[kup_sayac].x),sizeof(double),1,output_dosyalari[i]);
                                fwrite(&(kup_noktalar[kup_sayac].y),sizeof(double),1,output_dosyalari[i]);
                                fwrite(&(kup_noktalar[kup_sayac].z),sizeof(double),1,output_dosyalari[i]);
                            }
                        } else if(dosya_bilgileri[i].alan_tipi == 1) {
                            int kup_sayac;
                            for(kup_sayac = 0; kup_sayac < 8; kup_sayac++) {
                                fwrite(&(kup_noktalar[kup_sayac].x),sizeof(double),1,output_dosyalari[i]);
                                fwrite(&(kup_noktalar[kup_sayac].y),sizeof(double),1,output_dosyalari[i]);
                                fwrite(&(kup_noktalar[kup_sayac].z),sizeof(double),1,output_dosyalari[i]);
                                fwrite(&(kup_noktalar[kup_sayac].r),sizeof(int),1,output_dosyalari[i]);
                                fwrite(&(kup_noktalar[kup_sayac].g),sizeof(int),1,output_dosyalari[i]);
                                fwrite(&(kup_noktalar[kup_sayac].b),sizeof(int),1,output_dosyalari[i]);
                            }
                        }
                    }
                    fclose(output_dosyalari[i]);
                }
            }
            break;

        case 3:
            if(dosya_kontrolu_yapildi_mi == 0) {
                printf("\n~~Lutfen once dosya kontrolunu gerceklestiriniz.!~~\n");
                continue;
            }
            printf("\n###### Kurenin Icerisindeki Noktalar ######\n\n");
            float kure_x, kure_y, kure_z, kure_r;
            printf("~~Kurenin x degerini giriniz >> ");
            scanf("%f",&kure_x);
            printf("~~Kurenin y degerini giriniz >> ");
            scanf("%f",&kure_y);
            printf("~~Kurenin z degerini giriniz >> ");
            scanf("%f",&kure_z);
            printf("~~Kurenin yaricap degerini giriniz >> ");
            scanf("%f",&kure_r);

            for(i = 0; i < nkt_adet; i++) {
                if(dosya_bilgileri[i].hata_durumu == 0) {
                    noktalar = realloc(noktalar,dosya_bilgileri[i].nokta_adeti * sizeof(struct Nokta));
                    //struct Nokta noktalar[dosya_bilgileri[i].nokta_adeti];
                    printf("\n~~%s dosyasi icin kurenin icindeki noktalar bulunuyor... >>\n", nkt_dosyalari[i]);

                    if(dosya_bilgileri[i].data_tipi == 0) { //ascii
                        ascii_nokta_oku_diziye_at(dosyalar[i],noktalar, dosya_bilgileri[i].alan_tipi);
                    } else if(dosya_bilgileri[i].data_tipi == 1) { //Binary
                        fclose(dosyalar[i]);
                        dosyalar[i] = fopen(nkt_dosyalari[i],"rb");
                        binary_nokta_oku_diziye_at(dosyalar[i],noktalar,dosya_bilgileri[i].alan_tipi);
                    }
                    int sayac;
                    int nokta_indis = 0;
                    int yazilan_nokta_adeti = 0;
                    for(sayac = 0; sayac < dosya_bilgileri[i].nokta_adeti; sayac++) {
                        if(kurenin_icinde_mi(kure_x, kure_y, kure_z, kure_r,noktalar[sayac].x, noktalar[sayac].y, noktalar[sayac].z) == 1) {
                            //Eğer çemberin içindeyse ekrana yazdircam.
                            if(dosya_bilgileri[i].alan_tipi == 0) { //xyz
                                printf("%f %f %f Nokta numarasi: %d\n",noktalar[sayac].x, noktalar[sayac].y, noktalar[sayac].z,sayac+1);
                                yazilan_nokta_adeti += 1;
                            } else if(dosya_bilgileri[i].alan_tipi == 1) { //xyzrgb
                                printf("%f %f %f %d %d %d Nokta numarasi: %d\n", noktalar[sayac].x, noktalar[sayac].y, noktalar[sayac].z, noktalar[sayac].r, noktalar[sayac].g, noktalar[sayac].b,sayac+1);
                                yazilan_nokta_adeti += 1;
                            }
                        }
                        nokta_indis += 1;
                    }
                    printf("\n~~%d adet nokta kurenin icerisindedir.\n",yazilan_nokta_adeti);
                    //Output kısmi
                    if(dosya_bilgileri[i].data_tipi == 0) { //ascii
                        output_dosyalari[i] = fopen(nkt_output_dosyalari[i], "a");
                        fprintf(output_dosyalari[i],"SECIM 4\n");
                        fprintf(output_dosyalari[i],"cx = %f\n",kure_x);
                        fprintf(output_dosyalari[i],"cy = %f\n",kure_y);
                        fprintf(output_dosyalari[i],"cz = %f\n",kure_z);
                        fprintf(output_dosyalari[i],"cr = %f\n",kure_r);
                        if(dosya_bilgileri[i].alan_tipi == 0) {
                            fprintf(output_dosyalari[i],"%s",varsayilan_alan_nokta);
                        } else {
                            fprintf(output_dosyalari[i],"%s",varsayilan_alan_nokta_rgb);
                        }
                        fprintf(output_dosyalari[i],"Noktalar %d\n",dosya_bilgileri[i].nokta_adeti);
                        if(dosya_bilgileri[i].data_tipi == 0) {
                            fprintf(output_dosyalari[i],"%s",varsayilan_data_ascii);
                        } else {
                            fprintf(output_dosyalari[i],"%s",varsayilan_data_binary);
                        }
                        if(dosya_bilgileri[i].alan_tipi == 0) { //xyz
                            for(sayac = 0; sayac < dosya_bilgileri[i].nokta_adeti; sayac++) {
                                if(kurenin_icinde_mi(kure_x, kure_y, kure_z, kure_r,noktalar[sayac].x, noktalar[sayac].y, noktalar[sayac].z) == 1) {
                                    fprintf(output_dosyalari[i],"%f %f %f\n",noktalar[sayac].x, noktalar[sayac].y, noktalar[sayac].z);
                                }
                            }
                        } else if(dosya_bilgileri[i].alan_tipi == 1) { //xyzrgb
                            for(sayac = 0; sayac < dosya_bilgileri[i].nokta_adeti; sayac++) {
                                if(kurenin_icinde_mi(kure_x, kure_y, kure_z, kure_r,noktalar[sayac].x, noktalar[sayac].y, noktalar[sayac].z) == 1) {
                                    fprintf(output_dosyalari[i],"%f %f %f %d %d %d\n",noktalar[sayac].x, noktalar[sayac].y, noktalar[sayac].z,noktalar[sayac].r,noktalar[sayac].g,noktalar[sayac].b);
                                }
                            }
                        }
                    } else if(dosya_bilgileri[i].data_tipi == 1) { //Binary için
                        output_dosyalari[i] = fopen(nkt_output_dosyalari[i], "a+b");
                        fprintf(output_dosyalari[i],"\nSECIM 4\n");
                        fprintf(output_dosyalari[i],"cx = %f\n",kure_x);
                        fprintf(output_dosyalari[i],"cy = %f\n",kure_y);
                        fprintf(output_dosyalari[i],"cz = %f\n",kure_z);
                        fprintf(output_dosyalari[i],"cr = %f\n",kure_r);
                        if(dosya_bilgileri[i].alan_tipi == 0) {
                            fprintf(output_dosyalari[i],"%s",varsayilan_alan_nokta);
                        } else {
                            fprintf(output_dosyalari[i],"%s",varsayilan_alan_nokta_rgb);
                        }
                        fprintf(output_dosyalari[i],"Noktalar %d\n",dosya_bilgileri[i].nokta_adeti);
                        if(dosya_bilgileri[i].data_tipi == 0) {
                            fprintf(output_dosyalari[i],"%s",varsayilan_data_ascii);
                        } else {
                            fprintf(output_dosyalari[i],"%s",varsayilan_data_binary);
                        }

                        if(dosya_bilgileri[i].alan_tipi == 0) {
                            for(sayac = 0; sayac < dosya_bilgileri[i].nokta_adeti; sayac++) {
                                if(kurenin_icinde_mi(kure_x, kure_y, kure_z, kure_r,noktalar[sayac].x, noktalar[sayac].y, noktalar[sayac].z) == 1) {
                                    fwrite(&(noktalar[sayac].x),sizeof(double),1,output_dosyalari[i]);
                                    fwrite(&(noktalar[sayac].y),sizeof(double),1,output_dosyalari[i]);
                                    fwrite(&(noktalar[sayac].z),sizeof(double),1,output_dosyalari[i]);
                                }
                            }
                        } else if(dosya_bilgileri[i].alan_tipi == 1) {
                            for(sayac = 0; sayac < dosya_bilgileri[i].nokta_adeti; sayac++) {
                                if(kurenin_icinde_mi(kure_x, kure_y, kure_z, kure_r,noktalar[sayac].x, noktalar[sayac].y, noktalar[sayac].z) == 1) {
                                    fwrite(&(noktalar[sayac].x),sizeof(double),1,output_dosyalari[i]);
                                    fwrite(&(noktalar[sayac].y),sizeof(double),1,output_dosyalari[i]);
                                    fwrite(&(noktalar[sayac].z),sizeof(double),1,output_dosyalari[i]);
                                    fwrite(&(noktalar[sayac].r),sizeof(int),1,output_dosyalari[i]);
                                    fwrite(&(noktalar[sayac].g),sizeof(int),1,output_dosyalari[i]);
                                    fwrite(&(noktalar[sayac].b),sizeof(int),1,output_dosyalari[i]);
                                }
                            }
                        }
                    }
                    fclose(output_dosyalari[i]);
                }
            }
            break;
        case 4:
            if(dosya_kontrolu_yapildi_mi == 0) {
                printf("\n~~Lutfen once dosya kontrolunu gerceklestiriniz.!~~\n");
                continue;
            }
            printf("\n###### Noktalarin Ortalama Uzakligi ######\n");
            for(i = 0; i < nkt_adet; i++) {
                if(dosya_bilgileri[i].hata_durumu == 0) {
                    noktalar = realloc(noktalar,dosya_bilgileri[i].nokta_adeti * sizeof(struct Nokta));
                    //struct Nokta noktalar[dosya_bilgileri[i].nokta_adeti];
                    printf("\n%s dosyasi icin tum noktalarin ortalama uzakliklari islemi yapiliyor... >>\n", nkt_dosyalari[i]);
                    if(dosya_bilgileri[i].data_tipi == 0) { //Ascii
                        ascii_nokta_oku_diziye_at(dosyalar[i],noktalar,dosya_bilgileri[i].alan_tipi);
                    } else if(dosya_bilgileri[i].data_tipi == 1) { //Binary
                        fclose(dosyalar[i]);
                        dosyalar[i] = fopen(nkt_dosyalari[i],"rb");
                        binary_nokta_oku_diziye_at(dosyalar[i],noktalar,dosya_bilgileri[i].alan_tipi);
                    }

                    double toplam_uzaklik = 0; //Data tipi kayması float mu yoksa double mi incele.
                    double uzaklik_adeti = 0;
                    double mevcut_uzaklik = 0;
                    double ortalama_uzaklik;

                    int sayac1,sayac2;

                    for(sayac1 = 0; sayac1 < dosya_bilgileri[i].nokta_adeti-1; sayac1++) {
                        for(sayac2 = sayac1+1; sayac2 < dosya_bilgileri[i].nokta_adeti; sayac2++) {
                            mevcut_uzaklik = uzaklik_hesapla(noktalar[sayac1].x,noktalar[sayac1].y,noktalar[sayac1].z,noktalar[sayac2].x, noktalar[sayac2].y, noktalar[sayac2].z);
                            uzaklik_adeti += 1.0;
                            toplam_uzaklik += mevcut_uzaklik;
                        }
                    }
                    ortalama_uzaklik = toplam_uzaklik / uzaklik_adeti;
                    printf("Ortalama uzaklik: %lf\n", ortalama_uzaklik);
                    //Noktalar dizisi var.
                    //Output kısmi
                    if(dosya_bilgileri[i].data_tipi == 0) { //ascii
                        output_dosyalari[i] = fopen(nkt_output_dosyalari[i], "a");
                        fprintf(output_dosyalari[i],"SECIM 5\n");
                        fprintf(output_dosyalari[i],"%f",ortalama_uzaklik);
                    } else if(dosya_bilgileri[i].data_tipi == 1) { //Binary için
                        output_dosyalari[i] = fopen(nkt_output_dosyalari[i], "a+b");
                        fprintf(output_dosyalari[i],"\nSECIM 5\n");
                        fwrite(&(ortalama_uzaklik),sizeof(double),1,output_dosyalari[i]);
                    }
                    fclose(output_dosyalari[i]);
                }
            }
            break;
        case 5:
            exit(0);
            break;
        default:
            printf("\n~~Gecersiz islem lutfen tekrar deneyiniz.\n");
            break;
        }
    }
    return 0;
}
