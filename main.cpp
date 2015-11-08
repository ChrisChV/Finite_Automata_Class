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

    /*autito.crearEstado("S0");
    autito.crearEstado("S1");
    autito.crearEstado("S2",true);
    autito.addCaracter('x');
    autito.addCaracter('y');
    autito.crearRelacion("S0","S1",'y');
    autito.crearRelacion("S0","S2",'y');
    autito.crearRelacion("S1","S0",'x');
    */

    /*
    autito.crearEstado("1");
    autito.crearEstado("2");
    autito.crearEstado("3",true);
    autito.addCaracter('a');
    autito.addCaracter('b');
    autito.crearRelacion("1","2",'b');
    autito.crearRelacion("2","1",'a');
    autito.crearRelacion("1","3",'b');
    autito.crearRelacion("2","3",'a');
    */

    /*
    autito.crearEstado("1",true);
    autito.crearEstado("2",true);
    autito.crearEstado("3",true);
    autito.crearEstado("4");
    autito.crearEstado("5",true);
    autito.crearEstado("6");
    autito.addCaracter('a');
    autito.addCaracter('b');
    autito.crearRelacion("1","3",'a');
    autito.crearRelacion("1","6",'a');
    autito.crearRelacion("1","4",'b');
    autito.crearRelacion("1","5",'b');
    autito.crearRelacion("2","2",'a');
    autito.crearRelacion("2","2",'b');
    autito.crearRelacion("3","3",'a');
    autito.crearRelacion("3","4",'b');
    autito.crearRelacion("4","2",'a');
    autito.crearRelacion("4","2",'b');
    autito.crearRelacion("5","5",'a');
    autito.crearRelacion("5","5",'b');
    autito.crearRelacion("6","6",'b');
    autito.crearRelacion("6","5",'a');
    */

    autito.crearEstado("1");
    autito.crearEstado("2");
    autito.crearEstado("3");
    autito.crearEstado("4",true);
    autito.crearEstado("5");
    autito.crearEstado("6");
    autito.crearEstado("7");
    autito.crearEstado("8",true);
    autito.addCaracter('0');
    autito.addCaracter('1');
    autito.crearRelacion("1","2",'0');
    autito.crearRelacion("1","5",'1');
    autito.crearRelacion("2","2",'0');
    autito.crearRelacion("2","3",'1');
    autito.crearRelacion("3","4",'0');
    autito.crearRelacion("3","5",'1');
    autito.crearRelacion("4","2",'0');
    autito.crearRelacion("4","3",'1');
    autito.crearRelacion("5","6",'0');
    autito.crearRelacion("5","5",'1');
    autito.crearRelacion("6","6",'0');
    autito.crearRelacion("6","7",'1');
    autito.crearRelacion("7","8",'0');
    autito.crearRelacion("7","5",'1');
    autito.crearRelacion("8","6",'0');
    autito.crearRelacion("8","7",'1');


    autito.print();
    cout<<autito.esDeterminista()<<endl;
    AutomataFinito mini = autito.automataMinimo();
    mini.print();
    /*

    AutomataFinito att = autito.volverDeterminista();
    att.print();
    cout<<att.verificarCadena("abbbbbbbbbbbbbbbba")<<endl;;
    cout<<"HHHHHHHHHHolaaaaaaaaaaaaa"<<endl;
    cout<<att.esDeterminista()<<endl;
    */

}
