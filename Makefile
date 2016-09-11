dames: dames.o  sdl_output.o damesio.o remplir_tab.o arbre.o rafle.o
	gcc dames.o damesio.o remplir_tab.o rafle.o arbre.o sdl_output.o -o dames -lSDLmain -lSDL

dames.o: dames.c rafle.h arbre.h remplir_tab.h damesio.h commun.h sdl_output.h
	gcc -c dames.c -lSDLmain -lSDL

sdl_output.o: sdl_output.c sdl_output.h damesio.h remplir_tab.h arbre.h rafle.h commun.h
	gcc -c sdl_output.c -lSDLmain -lSDL

damesio.o: damesio.c damesio.h commun.h
	gcc -c damesio.c -lSDLmain -lSDL

remplir_tab.o: remplir_tab.c remplir_tab.h commun.h
	gcc -c remplir_tab.c -lSDLmain -lSDL

arbre.o: arbre.c arbre.h commun.h
	gcc -c arbre.c -lSDLmain -lSDL

rafle.o: rafle.c rafle.h commun.h arbre.h remplir_tab.h
	gcc -c rafle.c -lSDLmain -lSDL


clean:
	rm -rf *.o dames 
