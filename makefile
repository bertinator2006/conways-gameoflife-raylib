all: conway create

create:
	gcc create.c draw.c -o create -lraylib

conway:
	gcc main.c conway.c draw.c -o conway -lraylib

clean:
	rm conway create

# -fsanitize=address -g
