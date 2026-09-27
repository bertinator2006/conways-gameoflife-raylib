all: conway create

create:
	gcc create.c draw.c -o create -lraylib -fsanitize=address -g

conway:
	gcc main.c conway.c draw.c -o conway -lraylib -fsanitize=address -g

clean:
	rm conway create

