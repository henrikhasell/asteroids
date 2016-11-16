all:
	gcc -oAsteroids -std=c99 *.c -lglut -lGL -lm
freeglut-MinGW.zip:
	wget "http://files.transmissionzero.co.uk/software/development/GLUT/freeglut-MinGW.zip"
freeglut: freeglut-MinGW.zip
	unzip freeglut-MinGW
windows: freeglut
	i686-w64-mingw32-gcc-win32 \
-mwindows \
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
