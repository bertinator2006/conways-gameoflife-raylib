all: conway create

create: create.o draw.o
	gcc create.o draw.o -o create -lraylib

conway: main.o conway.o draw.o
	gcc main.o conway.o draw.o -o conway -lraylib

clean:
	rm conway create

# -fsanitize=address -g
