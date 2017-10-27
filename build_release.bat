@call mingw_path.bat

gcc -Wall -c src/main.c
windres -o resfile.o src/resfile.rc

gcc -o bin/main.exe resfile.o main.o -mwindows

strip bin/main.exe

call tidy.bat

pause
