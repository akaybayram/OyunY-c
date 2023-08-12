#ifndef OYUNCU_H_
#define OYUNCU_H_

#include <raylib.h>

typedef enum
{
    OYUNCU_DURUM_DURMA,
    OYUNCU_DURUM_KOSMA,
    OYUNCU_DURUM_SAYISI,
} OyuncuDurum;

typedef enum
{
    GOVDE_TIPI_KATI,
} GovdeTipi;

#include <stdint.h>
typedef uint32_t Id;
typedef struct
{
    Id id;
    GovdeTipi tip;
    Rectangle kare;
    Vector2 hareket_yonu;
    float hiz;
} Govde;

Govde govde_uret(float const x, float const y, float const en, float const boy, GovdeTipi const tip, float const hiz);
void govde_guncelle(Govde* govde, float const dt);
void govde_ciz(Govde const* const govde);
Vector2* govde_konumu_getir(Govde const* const govde);
Vector2* govde_boyutu_getir(Govde const* const govde);
Vector2* govde_hareket_yonu_getir(Govde const* const govde);

typedef struct
{
    OyuncuDurum durum;
    Govde govde;
    float olcek;
} OyuncuTip;

void oyuncu_ayarla(OyuncuTip* oyuncu);
void oyuncu_ciz(OyuncuTip* o);
void oyuncu_guncelle(OyuncuTip* o, float const dt);

#endif // OYUNCU_H_