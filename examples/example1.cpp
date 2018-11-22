/***
 * example1.cpp
 * 
 * Created by Christofer Chávez (XnpioChV)
 * 
 * In this example I show how you can create an automata manualy.
 * 
 ***/

#include <iostream>
#include "../include/AutomataFinito.h"

using namespace std;

int main(){

    AutomataFinito automata;
    automata.crearEstado("1");
    automata.crearEstado("2");
    automata.crearEstado("3");
    automata.crearEstado("4",true);
    automata.crearEstado("5");
    automata.crearEstado("6");
    automata.crearEstado("7");
    automata.crearEstado("8",true);
    automata.addCaracter('0');
    automata.addCaracter('1');
    automata.crearRelacion("1","2",'0');
    automata.crearRelacion("1","5",'1');
    automata.crearRelacion("2","2",'0');
    automata.crearRelacion("2","3",'1');
    automata.crearRelacion("3","4",'0');
    automata.crearRelacion("3","5",'1');
    automata.crearRelacion("4","2",'0');
    automata.crearRelacion("4","3",'1');
    automata.crearRelacion("5","6",'0');
    automata.crearRelacion("5","5",'1');
    automata.crearRelacion("6","6",'0');
    automata.crearRelacion("6","7",'1');
    automata.crearRelacion("7","8",'0');
    automata.crearRelacion("7","5",'1');
    automata.crearRelacion("8","6",'0');
    automata.crearRelacion("8","7",'1');
    automata.print();

}