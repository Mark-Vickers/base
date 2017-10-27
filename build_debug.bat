@call mingw_path.bat

gcc -g -Wall -c src/main.c
windres -o resfile.o src/resfile.rc

gcc -o bin/main.exe resfile.o main.o -lgdi32

call tidy.bat

pause