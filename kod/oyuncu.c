#include "oyuncu.h"
#include "animasyon.h"

#include <raylib.h>
#include <raymath.h>
#include <stdio.h>

AnimasyonVeri v = {0};
Animasyon a[OYUNCU_DURUM_SAYISI] = {0};

static Id hazir_id = 0;
Govde govde_uret(float const x, float const y, float const en, float const boy, GovdeTipi const tip, float const hiz)
{
    return (Govde) {
        .id = hazir_id++,
        .kare = {
            .x = x,
            .y = y,
            .width = en,
            .height = boy
        },
        .tip = tip,
        .hiz = hiz
    };
}

void govde_guncelle(Govde* govde, float const dt)
{
    govde->hareket_yonu.y = IsKeyDown(KEY_S) - IsKeyDown(KEY_W);    
    govde->hareket_yonu.x = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);    

    govde->hareket_yonu = Vector2Normalize(govde->hareket_yonu);

    Vector2* govde_konum = govde_konumu_getir(govde);
    *govde_konum = Vector2Add(*govde_konum, Vector2Scale(govde->hareket_yonu, govde->hiz * dt));
}

void govde_ciz(Govde const* const govde)
{
    const Color govde_renk = {25, 25, 180, 70};
    Vector2 const* const boyut = govde_boyutu_getir(govde);
    Vector2 const* const konum = govde_konumu_getir(govde);
    DrawRectangleV(*konum, *boyut, govde_renk);
}

Vector2* govde_konumu_getir(Govde const* const govde)
{
    return (Vector2*)&govde->kare;
}

Vector2* govde_boyutu_getir(Govde const* const govde)
{
    return (Vector2*)&govde->kare.width;
}

Vector2* govde_hareket_yonu_getir(Govde const* const govde)
{
    return (Vector2*)&govde->hareket_yonu;
}

void oyuncu_ayarla(OyuncuTip* oyuncu)
{
    oyuncu->olcek = 2.0f;
    v = animasyon_veri_uret("cizimler/ast.png", oyuncu->olcek, (Vector2){8, 2});
    a[OYUNCU_DURUM_DURMA] = animasyon_uret(&v, (Vector2){0, 7}, 0.8);
    a[OYUNCU_DURUM_KOSMA] = animasyon_uret(&v, (Vector2){8, 15}, 0.8);

    oyuncu->govde = govde_uret(
        500, 500,                       // x, y 
        v.kare_boyut.x * oyuncu->olcek, // en
        v.kare_boyut.y * oyuncu->olcek, // boy
        GOVDE_TIPI_KATI,                // tip
        100                             // hiz
    );

    oyuncu->durum = OYUNCU_DURUM_DURMA;
}

void oyuncu_ciz(OyuncuTip* o)
{
    Vector2 const* const konum = govde_konumu_getir(&o->govde);
    animasyon_ciz(&a[o->durum], *konum);
    govde_ciz(&o->govde);
}

void oyuncu_guncelle(OyuncuTip* o, float const dt)
{
    govde_guncelle(&o->govde, dt);

    Vector2* hareket_yonu = govde_hareket_yonu_getir(&o->govde);
    if(hareket_yonu->x == 0 && hareket_yonu->y == 0)
    {
        o->durum = OYUNCU_DURUM_DURMA;
    }
    else
    {
        o->durum = OYUNCU_DURUM_KOSMA;
    }
    
    if(hareket_yonu->x < 0)
    {
        a[o->durum].veri->dondur = true;
    }
    else if (hareket_yonu->x > 0)
    {
        a[o->durum].veri->dondur = false;
    }

    animasyon_guncelle(&a[o->durum], dt);
}