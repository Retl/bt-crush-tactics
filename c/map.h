#ifndef MAP_H
#define MAP_H

typedef struct {
	char displayName[200];
    char textDesc[3000];

    // Placeholdery. START FIXME
    char textExits[3000];
    char textContent[3000];
    // Placeholdery. END FIXME

    int width;
    int height;
    int mapTiles[100][100];
    int entities[200];
    //Canons
    // Notoriety
	// TemporaryStatus tempStatuses[MAX_TEMP_STATUSES];
	//TemporaryStatus tempStatuses[10];
} Map;

void mapInit(Map *map, int width, int height);
void mapFillFloor(Map *map, int floorLevel);
void mapDebugPrint(Map *map);

void mapSetSGRumbleRamble(Map *map);

#endif