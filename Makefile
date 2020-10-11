all : scramble find_scramblers

find_scramblers : find_scramblers.c
	gcc -o find_scramblers find_scramblers.c -Wall -pedantic -O4

scramble : scramble.c
	gcc -o scramble scramble.c -Wall -pedantic -O4
