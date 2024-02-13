render="src/engine/render/render.c src/engine/render/render_init.c src/engine/render/render_util.c"
io="src/engine/io/io.c"
config="src/engine/config/config.c"
time="src/engine/time/time.c"
input="src/engine/input/input.c"
arraylist="src/engine/arraylist/arraylist.c"
physics="src/engine/physics/physics.c"
deps="deps/src/glad.c"
main="src/main.c src/engine/global.c"
files="$main $deps $io $render $config $input $time $arraylist $physics"

libs="-lGL -lSDL2-2.0 -lSDL2_mixer -Ideps/include/linmath"

gcc -o game $files -Ideps/include -lm -Llib $libs -g
