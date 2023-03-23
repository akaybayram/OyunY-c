#if defined(_WIN32)
#include <plswindows.h>
#endif

#define ENET_IMPLEMENTATION
#include <enet/enet.h>
#include <raylib.h>
#include "ana.h"

#include <stdio.h>

int main()
{
	InitWindow(EKRAN_GENISLIGI, EKRAN_YUKSEKLIGI, PENCERE_BASLIK_ISMI);
	SetTargetFPS(FPS_SINIRI);
	SetExitKey(KEY_KP_SUBTRACT);
	oyun_yukle();
	while(!WindowShouldClose())
	{
		float dt = GetFrameTime();
		oyun_guncelle(dt);

		BeginDrawing();
		ClearBackground(FARUKGRISI);
    	oyun_ciz();
    	EndDrawing();
  	}
 	
	return 0;
}
