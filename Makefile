all: Asteroids Asteroids.exe

Asteroids:
	gcc \
-Wpedantic \
-Wall \
-O3 \
-std=c99 \
-oAsteroids \
*.c \
-lglut \
-lGL \
-lm

freeglut-MinGW.zip:
	wget "http://files.transmissionzero.co.uk/software/development/GLUT/freeglut-MinGW.zip"

freeglut: freeglut-MinGW.zip
	unzip freeglut-MinGW

Asteroids.exe: freeglut
	i686-w64-mingw32-gcc-win32 \
-static-libgcc \
-mwindows \
-Wpedantic \
-Wall \
-O3 \
-std=c99 \
-oAsteroids.exe \
-DFREEGLUT_STATIC \
-Ifreeglut/include \
-Lfreeglut/lib \
*.c \
-lfreeglut_static \
-lwinmm \
-lopengl32 \
-lm

clean:
	rm -R -f Asteroids Asteroids.exe freeglut-MinGW.zip freeglut
