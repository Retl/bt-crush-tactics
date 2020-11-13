emcc -v
# emcc ./c/hello_world.c
# emcc ./c/btct.c -o ./dist/btct.html
emcc ./c/btct.c c/map.c -o ./dist/btct.html --use-preload-plugins --preload-file img/bg_splashes
node dist/a.out.js