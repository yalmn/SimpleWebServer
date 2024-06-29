all:
	gcc -o webserver webserver.c
	./webserver
	rm -r webserver