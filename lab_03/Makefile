main: main.exe
	./main.exe

main.exe: main.c
	gcc -g -Wall -Werror -lm main.c -o main.exe
    
gener: gener.exe
	./gener.exe
    
gener.exe: gener.c
	gcc -Wall -Werror -lm  gener.c -o gener.exe

clean: 
	rm *.exe

