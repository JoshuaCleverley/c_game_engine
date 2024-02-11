render="src/engine/render/render.c src/engine/render/render_init.c src/engine/render/render_util.c"
io="src/engine/io/io.c"
deps="deps/src/glad.c"
main="src/main.c src/engine/global.c"

libs="-lGL -lSDL2-2.0 -lSDL2_mixer -lfreetype -Ideps/include/linmath"

gcc -o game $main $deps $io $render -Ideps/include -Llib $libs
