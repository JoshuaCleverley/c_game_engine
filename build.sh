files="src/main.c src/engine/global.c src/engine/render/render.c src/engine/render/render_init.c src/engine/io/io.c deps/src/glad.c"
libs="-lGL -lSDL2-2.0 -lSDL2_mixer -lfreetype -Ideps/include/linmath"

gcc -o game $files -Ideps/include -Llib $libs
