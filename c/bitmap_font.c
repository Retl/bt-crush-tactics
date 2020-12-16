#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>

int charactersPerRow = 16;
int characterWidth = 8;
int characterHeight = 8;

char bitmapFontCharacterOrder[200] = " !\"#$\%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

SDL_Rect getBitmapFontRectFromCharacter(char targetCharacter) 
{
    SDL_Rect result = {0, 0, 8, 8};

    for (int i = 0; i < strlen(bitmapFontCharacterOrder); i++) 
    {
        if (bitmapFontCharacterOrder[i] == targetCharacter) 
        {
            int row = (i / charactersPerRow) * characterHeight;
            int col = (i % charactersPerRow) * characterWidth;

            result.x = col;
            result.y = row;
        } 
    }

    return result;

}