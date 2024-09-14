#include <stdio.h>
#include <stdlib.h>
#include <gccore.h>
#include <asndlib.h>
#include <mp3player.h>
#include <grrlib.h>
#include <time.h>

// Include generated headers
#include "Jazz_mp3.h"
#include "title_png.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

// Function to generate a random noise texture for film grain
GRRLIB_texImg* GenerateGrainTexture(int width, int height) {
    // Allocate memory for the grain texture
    GRRLIB_texImg* grainTex = GRRLIB_CreateEmptyTexture(width, height);

    // Seed the random number generator
    srand(time(NULL));

    // Fill the texture with random noise
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Generate random noise (grayscale, same value for R, G, B)
            u8 noise = rand() % 256;

            // Set the pixel in the texture (RGBA format)
            ((u32*)grainTex->data)[y * width + x] = (noise << 24) | (noise << 16) | (noise << 8) | 0x80;  // Alpha set to 50% (0x80)
        }
    }

    return grainTex;
}


void SetupTEVForFilmGrain() {
    // Set up the first TEV stage for the scene texture (base texture)
    GX_SetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);

    // Set up the second TEV stage for the grain texture
    GX_SetTevOp(GX_TEVSTAGE1, GX_TEV_ADD);  // Add the grain texture to the base texture
    GX_SetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);

    // Blend control for the grain texture (subtle blending)
    GX_SetTevKColor(GX_KCOLOR0, (GXColor){128, 128, 128, 255});  // Blending constant
    GX_SetTevKColorSel(GX_TEVSTAGE1, GX_TEV_KCSEL_K0_R);  // Select the red channel for blending
    GX_SetTevKAlphaSel(GX_TEVSTAGE1, GX_TEV_KASEL_K0_A);  // Select the alpha channel for blending control
}

//---------------------------------------------------------------------------------
int main(int argc, char **argv) {
//---------------------------------------------------------------------------------

    // Initialise GRRLib
    GRRLIB_Init();

    // Load the title screen texture
    GRRLIB_texImg *title = GRRLIB_LoadTexture(title_png);

    // Generate the grain texture procedurally
    GRRLIB_texImg* grainTex = GenerateGrainTexture(SCREEN_WIDTH, SCREEN_HEIGHT);

    // Initialise the attached controllers
    PAD_Init();

    // Initialise the audio subsystem
    ASND_Init();

    MP3Player_Init();
    MP3Player_PlayBuffer(Jazz_mp3, Jazz_mp3_size, NULL);

    // To have a cool effect anti-aliasing is turned on
    GRRLIB_Settings.antialias = true;

    // Black background
    GRRLIB_SetBackgroundColour(0x00, 0x00, 0x00, 0xFF);

    // Set up TEV for film grain blending
    SetupTEVForFilmGrain();

    while (1) {
        PAD_ScanPads();

        int buttonsDown = PAD_ButtonsDown(0);

        if (buttonsDown & PAD_BUTTON_START) {
            break; // Exit the loop and clean up
        }

        // Draw the title screen
        GRRLIB_DrawImg(0, 0, title, 0, 1, 1, 0xFFFFFFFF);

        // Draw the grain texture with subtle blending
        GRRLIB_DrawImg(0, 0, grainTex, 0, 1, 1, 0x80FFFFFF);  // Render with 50% opacity for subtle grain

        // Render the final scene
        GRRLIB_Render();
    }

    // Clean up
    GRRLIB_FreeTexture(title);
    GRRLIB_FreeTexture(grainTex);
    GRRLIB_Exit();
    exit(0);
}
