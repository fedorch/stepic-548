all: exe lib

exe: main.c hello.h libHello.so
    gcc main.c -fPIC -L. -lHello -o Hello

lib: hello.c hello.h
    gcc -shared hello.c -fPIC -o libHello.so

clean:
    -rm hello libHello.so 2>/dev/null