all:
	gcc main.c conway.c -o conway -lraylib

debug:
	gcc main.c conway.c -o conway -lraylib -fsanitize=address -g
