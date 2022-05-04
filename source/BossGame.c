#include <stdio.h>
#include <stdlib.h>
#include <gccore.h>
#include <aesndlib.h>
#include <gcmodplay.h>
#include <grrlib.h>
#include <ogc/lwp_watchdog.h>

// include generated headers
#include "technique_mod.h"
#include "FreeMonoBold_ttf.h"

static MODPlay play;
static u8 CalculateFrameRate();


//---------------------------------------------------------------------------------
int main(int argc, char **argv) {
//---------------------------------------------------------------------------------

	char FPS[255] = "";
	// Initialise GRRLib
	GRRLIB_Init();

	// Load the font from memory
    GRRLIB_ttfFont *myFont = GRRLIB_LoadTTF(FreeMonoBold_ttf, FreeMonoBold_ttf_size);

	 // Create an empty texture to store a copy of the screen
    GRRLIB_texImg *CopiedImg = GRRLIB_CreateEmptyTexture(rmode->fbWidth, rmode->efbHeight);

	

	// Initialise the attached controllers
	PAD_Init();

	// Initialise the audio subsystem
	AESND_Init();

	

	MODPlay_Init(&play);
	MODPlay_SetMOD(&play,technique_mod);
	MODPlay_Start(&play);

	// To have a cool effect anti-aliasing is turned on
    GRRLIB_Settings.antialias = true;

    // Black background
    GRRLIB_SetBackgroundColour(0x00, 0x00, 0x00, 0xFF);

	int tick=0;

	while(1) {
	
		GRRLIB_DrawImg(0, 0, CopiedImg, 0, 1, 1, 0xFFFFFFFF);
		sprintf(FPS, "Current tick: %d", tick);
            GRRLIB_PrintfTTF(500+1, 25+1, myFont, FPS, 12, 0x000000FF);
            GRRLIB_PrintfTTF(500, 25, myFont, FPS, 12, 0xFFFFFFFF);
		
		

		PAD_ScanPads();

		int buttonsDown = PAD_ButtonsDown(0);

		if( buttonsDown & PAD_BUTTON_A ) {
			printf("Button A pressed.\n");
		}

		if (buttonsDown & PAD_BUTTON_START) {
			exit(0);
		}
		tick++;
		GRRLIB_Render();
	}

	GRRLIB_FreeTTF(myFont);
	GRRLIB_Exit();
	exit(0);
}

/**
 * This function calculates the number of frames we render each second.
 * @return The number of frames per second.
 */
static u8 CalculateFrameRate()
{
    static u8 frameCount = 0;
    static u32 lastTime;
    static u8 FPS = 0;
    u32 currentTime = ticks_to_millisecs(gettime());

    frameCount++;
    if(currentTime - lastTime > 1000) {
        lastTime = currentTime;
        FPS = frameCount;
        frameCount = 0;
    }
    return FPS;
}
