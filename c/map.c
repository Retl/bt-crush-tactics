#include <stdio.h>
#include <string.h>
#include "map.h"

void mapInit(Map *map)
{
    // https://stackoverflow.com/questions/12179833/assign-string-to-element-in-structure-in-c
    strcpy(map->displayName, "Test Map");
    strcpy(map->textDesc, "A newly created room. Nothing too interesting here. Maybe add something?");
    strcpy(map->textExits, "No Escape!");
    strcpy(map->textContent, "One (1) Newly Created NULL.");
    map->width = 100;
    map->height = 100;
    int i, j;
    for (i = 0; i < map->height; i++)
    {
        for (j = 0; j < map->width; j++)
        {
            //printf("Enter value for disp[%d][%d]:", i, j);
            //scanf("%d", map->mapTiles[i][j]);
            map->mapTiles[i][j] = 0;
        }
    }
}

void mapFillFloor(Map *map, int floorLevel)
{
    int i, j;
    printf("Floor level: %i\n", floorLevel);
    for (i = 0; i < map->height; i++)
    {
        for (j = 0; j < map->width; j++)
        {
            //printf("Enter value for disp[%d][%d]:", i, j);
            //scanf("%d", map->mapTiles[i][j]);
            if (i >= (map->height - floorLevel)) {
                map->mapTiles[i][j] = 1;
            }
        }
    }
}

void mapDebugPrint(Map *map)
{
    int i, j;
    printf("%s%s\n", "Map Name: ", map->displayName);
    printf("%s%i\n", "Map Width: ", map->width);
    printf("%s%i\n", "Map Height: ", map->height);
    for (i = 0; i < map->height; i++)
    {
        for (j = 0; j < map->width; j++)
        {
            printf("%d ", map->mapTiles[i][j]);
            if (j == map->width)
            {
                printf("\n");
            }
        }
        printf("\n");
    }
    printf("\n");
}


void mapSetSGRumbleRamble(Map *map)
{
    // https://stackoverflow.com/questions/12179833/assign-string-to-element-in-structure-in-c
    strcpy(map->displayName, "Rumble Ramble-Station\n");
    strcpy(map->textDesc, "This seems to be the place people in this area go to discuss and practice their fighting techniques.\n"
    "A dimly lit room. The lights flicker as you look around. Posters of various muscled atheletes\n and fighters decorate all the walls.\n\n"
    "The sound of arcade machines and sparring matches makes the relatively cramped quarters a cacophony of action.\n"
    "There's a pool table and water cooler free for anyone to use when they're not being used as sparring or training equipment.\n"
    "If you're looking for a few new moves, this is probably the place to find a tutor.\n"
    );
    strcpy(map->textExits, "North: Gaming & Recreations - Hallway\n");
    strcpy(map->textContent, "A noisy water-cooler\nA slightly dented pool table.\nA Jam Blow Blast Arcade Machine.\n\n");
    
    map->width = 100;
    map->height = 100;
    int i, j;
    for (i = 0; i < map->height; i++)
    {
        for (j = 0; j < map->width; j++)
        {
            //printf("Enter value for disp[%d][%d]:", i, j);
            //scanf("%d", map->mapTiles[i][j]);
            map->mapTiles[i][j] = 0;
        }
    }
}