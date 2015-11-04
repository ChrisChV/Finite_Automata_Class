#include <iostream>
#include "AutomataFinito.h"
using namespace std;

int main()
{
    AutomataFinito autito;
    /*
    autito.crearEstado("1");
    autito.crearEstado("2");
    autito.crearEstado("3",true);
    autito.crearEstado("basura");
    autito.addCaracter('a');
    autito.addCaracter('b');
    autito.crearRelacion("1","2",'a');
    autito.crearRelacion("1","basura",'b');
    autito.crearRelacion("2","2",'a');
    autito.crearRelacion("2","3",'b');
    autito.crearRelacion("3","3",'b');
    autito.crearRelacion("3","basura",'a');
    autito.crearRelacion("basura","basura",'a');
    autito.crearRelacion("basura","basura",'b');
    */
    autito.crearEstado("S0");
    autito.crearEstado("S1");
    autito.crearEstado("S2",true);
    autito.addCaracter('x');
    autito.addCaracter('y');
    autito.crearRelacion("S0","S1",'y');
    autito.crearRelacion("S0","S2",'y');
    autito.crearRelacion("S1","S0",'x');
    autito.print();
    AutomataFinito att = autito.volverDeterminista();
    att.print();

}
