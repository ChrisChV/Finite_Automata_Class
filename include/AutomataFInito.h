#ifndef AUTOMATAFINITO_H
#define AUTOMATAFINITO_H

#include "list"
#include "map"
#include "algorithm"
#include "fstream"

using namespace std;

class AutomataFinito
{
    public:
        class Estado{
            public:
                Estado();
                Estado(string);
                Estado(string, bool);
                string nombre;
                bool aseptacion;
                map<string,char> estadosDestino; ///APunto;
                map<string,char> estadosOrigen; ///MeApuntan;
        };
        AutomataFinito();
        AutomataFinito(string);
        void crearEstado(string, bool);
        void crearAlfabeto(list<char> alfabeto);
        void print();
        bool crearRelacion(string, string, char);
        virtual ~AutomataFinito();
    protected:
    private:
        bool _existeEstado(string, Estado *&);
        bool _existeCaracter(char);
        Estado * estadoInicial;
        list<char> alfabeto;
        map<string,Estado *> estados;
        string name;


};


void AutomataFinito::print(){
    string file = name + ".dot";
    ofstream archivo(file);
    archivo<<"digraph{"<<endl;
    for(auto iter = estados.begin(); iter != estados.end(); ++iter){
        archivo<<iter->first<<endl;
        for(auto iter2 = iter->second->estadosDestino.begin(); iter2 != iter->second->estadosDestino.end(); ++iter2){
            archivo<<iter->first<<"->"<<iter2->first<<" [label =\""<<iter2->second<<"\"];"<<endl;
        }
    }
    archivo<<"}";
    archivo.close();
    string comando = "dot -Tpdf " + name + ".dot -o " + name + ".pdf";
    const char *c = comando.c_str();
    system(c);
}

bool AutomataFinito::crearRelacion(string AF1, string AF2, char caracter){
    Estado * estado1;
    Estado * estado2;
    if(!_existeEstado(AF1,estado1) or !_existeEstado(AF2,estado2) or _existeCaracter(caracter))return false;


}

bool AutomataFinito::_existeCaracter(char caracter){
    if(find(alfabeto.begin(), alfabeto.end(), caracter) != alfabeto.end())return true;
    return false;
}

void AutomataFinito::crearAlfabeto(list<char> alfabeto){
    this->alfabeto = alfabeto;
}

void AutomataFinito::crearEstado(string name, bool aseptacion){
    Estado * nuevo;
    if(_existeEstado(name,nuevo))return;
    nuevo = new Estado(name,aseptacion);
    if(!estadoInicial) estadoInicial = nuevo;
    estados[name] = nuevo;
}

bool AutomataFinito::_existeEstado(string name, Estado *&estado){
    auto iter =  estados.find(name);
    estado = iter->second;
    if(iter != estados.end())return true;
    return false;
}

AutomataFinito::Estado::Estado(string name){
    nombre = name;
}

AutomataFinito::Estado::Estado(){
    nombre = nullptr;
    aseptacion = false;
}

AutomataFinito::Estado::Estado(string name, bool aseptacion){
    nombre = name;
    this->aseptacion = aseptacion;
}

AutomataFinito::AutomataFinito(){
    estadoInicial = nullptr;
    name = "AutomataDefault";
}

AutomataFinito::AutomataFinito(string name){
    estadoInicial = nullptr;
    this->name = name;
}

AutomataFinito::~AutomataFinito(){

}

#endif // AUTOMATAFINITO_H
