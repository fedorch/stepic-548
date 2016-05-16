#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
 
int main(int argc, char **argv) {
    if(argc == 1) { // если запускаем без аргументов, выводим справку
        printf("getopt test\n");
        printf("usage:\n");
        printf(" opts -a n -b m -o s\n");
        printf("example:\n");
        printf(" $ opts -a 323 -b 23 -o '-'\n");
        printf(" 323 — 23 = 300\n");
        return 0;
    }
    char *opts = "a:b:o:"; // доступные опции, каждая принимает аргумент
    int a, b;  // тут храним числа
    char op;   // а тут оператор
    int opt;   // каждая следующая опция попадает сюда
    while((opt = getopt(argc, argv, opts)) != -1) { // вызываем getopt пока она не вернет -1
        switch(opt) {
            case 'a': // если опция -a, преобразуем строку с аргументом в число
                a = atoi(optarg);
                break;
             case 'b': // тоже для -b
                 b = atoi(optarg);
                 break;
             case 'o': // в op сохраняем оператор
                 op = optarg[0];
                 break;
        }
    }
    switch(op) {
        case '+': // если опаратор + складываем, и т.д.
            printf("%d + %d = %d\n", a, b, a + b);
            break;
        case '-':
            printf("%d - %d = %d\n", a, b, a - b);
            break;
        case '*':
            printf("%d * %d = %d\n", a, b, a * b);
            break;
        case '/':
            printf("%d / %d = %d\n", a, b, a / b);
            break;
    }
    return 0;
}