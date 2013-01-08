all: main.c
	gcc -Wall -o sim main.c /usr/lib/libnetlink.a 
