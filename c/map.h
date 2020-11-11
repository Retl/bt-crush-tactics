#ifndef MAP_H
#define MAP_H

typedef struct {
	char displayName[200];
    int width;
    int height;
    int mapTiles[100][100];
    int entities[200];
    //Canons
    // Notoriety
	// TemporaryStatus tempStatuses[MAX_TEMP_STATUSES];
	//TemporaryStatus tempStatuses[10];
} Map;

void mapInit(Map *map);
void mapFillFloor(Map *map, int floorLevel);
void mapDebugPrint(Map *map);

#endif