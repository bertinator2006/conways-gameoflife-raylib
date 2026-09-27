debug_create:
	gcc create.c draw.c -o create -lraylib -fsanitize=address -g

debug_conway:
	gcc main.c conway.c draw.c -o conway -lraylib -fsanitize=address -g

create:
	gcc create.c draw.c -o create -lraylib

conway:
	gcc main.c conway.c draw.c -o conway -lraylib

all: conway create

