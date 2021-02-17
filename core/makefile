build:
		g++ -std=c++17 -Wfatal-errors \
		-g\
		./src/*.cpp \
		./src/components/*.cpp \
		-o game.exe \
		-I/usr/include/lib/lua \
		-L./lib/lua \
		-llua5.3 \
    	-lSDL2main \
        -lSDL2_image \
        -lSDL2_ttf \
        -lSDL2_mixer \
        -lSDL2
run:
		./game.exe