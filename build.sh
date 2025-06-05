CC="clang"
# $CC -c -o miniaudio.o ./external/miniaudio.c -I ./external/

time $CC -Wall -Wextra -Werror -std=c99 -o main miniaudio.o ./src/*.c -I ./src/ -I ./external/ -lole32 -lshell32 -luuid