/***
 * example2.cpp
 * 
 * Created by Christofer Chávez (XnpioChV)
 * 
 * In this example I show how you can create an automata from a regular expresion.
 * 
 ***/

#include <iostream>
#include "../include/AutomataFinito.h"

using namespace std;

int main(){

    AutomataFinito automata("automata");
    automata.addCaracter('a');
    automata.addCaracter('b');
    AutomataFinito resultado = automata.generarDeExpresionRegular("(a*abab(aba)*)V(b*Va)","automata");
    resultado.print();

}