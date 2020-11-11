#include "sponsor.h"
#include "map.h"

#include <stdio.h>

int main() {
  printf("hello, world!\n");
  Map testMap;
  mapInit(&testMap);
  mapDebugPrint(&testMap);
  printf("Filling the floor.\n");
  mapFillFloor(&testMap, 2);
  mapDebugPrint(&testMap);
  return 0;
}