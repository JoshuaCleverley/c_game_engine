files="src/*.c"
libs="-lGL -lSDL2-2.0 -lSDL2_mixer -lfreetype"

gcc -o game $files -Iinclude -Llib $libs
