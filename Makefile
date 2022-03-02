build:
	gcc -g -o tema2 mainBody.c lists-functions.c Queue.c utils.c Stack.c -Wall

clean:
	rm -rf tema2