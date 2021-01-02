# emcc -v
# emcc ./c/hello_world.c
# emcc ./c/btct.c -o ./dist/btct.html
# emcc ./c/btct.c c/map.c -o ./dist/btct.html --use-preload-plugins --preload-file img/bg_splashes
# emcc ./c/btct.c c/map.c -O2 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --use-preload-plugins --preload-file img -o ./dist/btct.html
# node dist/a.out.js

# emcc c/btct.c c/map.c -g -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --use-preload-plugins --preload-file img -o ./dist/btct.html

# emcc c/btct.c c/map.c c/bitmap_font.c -g -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --use-preload-plugins --preload-file img -o ./dist/btct.html
# emcc c/btct.c c/map.c c/bitmap_font.c c/gamepad.c -g -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --use-preload-plugins --preload-file img -o ./dist/btct.html

# This version adds FORCE_FILESYSTEM and adds a pre-js script for the gamepads to be recognized before SDL starts checking for them.
# Thanks to https://github.com/emscripten-core/emscripten/issues/9318#issuecomment-525667486 for having this tip.
# https://github.com/emscripten-ports/SDL2/blob/master/test/emscripten/joystick-pre.js
# I couldn't get this snippet to work, even after changing the webkitGetGamepads to getGamepads...
# emcc c/btct.c c/map.c c/bitmap_font.c c/gamepad.c -g -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --use-preload-plugins --preload-file img -s FORCE_FILESYSTEM=1 --pre-js js/joystick-preconfig.js -o ./dist/btct.html 

emcc c/btct.c c/map.c c/bitmap_font.c c/gamepad.c -g -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --use-preload-plugins --preload-file img -o ./dist/btct.html