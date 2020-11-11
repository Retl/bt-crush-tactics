#include <stdio.h>
#include <string.h>
#include "map.h"

void mapInit(Map *map)
{
    // https://stackoverflow.com/questions/12179833/assign-string-to-element-in-structure-in-c
    strcpy(map->displayName, "Test Map");
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