#include "functions.h"




// gcc -o test src/TestFinal.c resources.c -I include `pkg-config --cflags --libs gtk+-3.0 webkit2gtk-4.0`


int main(int argc, char** argv) {
    gtk_init(&argc, &argv);





    return 0;
}