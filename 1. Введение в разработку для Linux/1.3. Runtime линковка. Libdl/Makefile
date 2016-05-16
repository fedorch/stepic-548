all: exe lib

exe: main.c
	gcc main.c -fPIC -ldl -o hello

lib: hello.c hello.h
	gcc -shared hello.c -fPIC -o libHello.so

clean:
	-rm hello libHello.so 2>/dev/null