emcc -v
# emcc ./c/hello_world.c
# emcc ./c/btct.c -o ./dist/btct.html
# emcc ./c/btct.c c/map.c -o ./dist/btct.html --use-preload-plugins --preload-file img/bg_splashes
# emcc ./c/btct.c c/map.c -O2 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --use-preload-plugins --preload-file img -o ./dist/btct.html
# node dist/a.out.js

emcc c/btct.c c/map.c -g -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --use-preload-plugins --preload-file img -o ./dist/btct.html
