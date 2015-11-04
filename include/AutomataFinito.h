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
                bool _existeRelacion(string, char);
                string transicionDeterminista(char);
                bool verificarCaracter(char);
                list<string> relaciones(char);
                string nombre;
                bool aseptacion;
                map<string,list<char>> estadosDestino; ///APunto;
                map<string,list<char>> estadosOrigen; ///MeApuntan;
        };
        AutomataFinito();
        AutomataFinito(string);
        void crearEstado(string, bool);
        void crearEstado(string);
        void crearAlfabeto(list<char>);
        bool algunoEsAseptacion(list<string> &);
        bool esDeterminista();
        void addCaracter(const char);
        bool verificarCadena(string);
        AutomataFinito volverDeterminista();
        void print();
        bool crearRelacion(string, string, char);
        map<string,Estado *>& getEstados();
        virtual ~AutomataFinito();
    protected:
    private:
        bool _existeEstado(string, Estado *&);
        bool _existeCaracter(char);
        bool _verificarCadena(string, char, Estado *);
        list<string> _estadoConjunto(string);
        string _crearEstadoConjunto(list<string>&);
        Estado * estadoInicial;
        list<char> alfabeto;
        map<string,Estado *> estados;
        string name;
        bool determinista;
};

bool AutomataFinito::esDeterminista(){
    int siz = alfabeto.size();
    for(auto iter = estados.begin(); iter != estados.end(); ++iter){
        if(iter->second->estadosDestino.size() != siz) return false;
    }
    return true;
}

bool AutomataFinito::algunoEsAseptacion(list<string>& estados){
    for(string iter : estados){
        Estado * estado;
        _existeEstado(iter,estado);
        if(estado->aseptacion)return true;
    }
    return false;
}

string AutomataFinito::_crearEstadoConjunto(list<string> &lista){
    if(lista.empty())return "basura";
    if(lista.size() == 1) return lista.front();
    string resultado = "{";
    auto iter2 = lista.end();
    iter2--;
    for(auto iter = lista.begin(); iter != iter2; ++iter){
        for(char caracter : *iter){
            resultado.insert(resultado.end(),caracter);
        }
        resultado.insert(resultado.end(),',');
    }
    for(char caracter : *iter2){
        resultado.insert(resultado.end(),caracter);
    }
    resultado.insert(resultado.end(),'}');
    return resultado;
}

list<string> AutomataFinito::_estadoConjunto(string nombre){
    list<string> resultado;
    string sResultado;
    int estado = 0;
    for(auto iter = nombre.begin(); iter != nombre.end(); ++iter){
        switch(estado){
            case 0:
                if(*iter == '{') estado = 1;
                else return resultado;
            case 1:
                if(*iter == ',') estado = 2;
                else if(*iter == '}') estado = 3;
                else sResultado.insert(sResultado.end(),*iter);
            case 2:
                resultado.push_back(sResultado);
                sResultado.clear();
                estado = 1;
            case 3:
                resultado.push_back(sResultado);
                resultado.sort();
                return resultado;
        }
    }
}

list<string> AutomataFinito::Estado::relaciones(char caracter){
    list<string> resultado;
    for(auto iter = estadosDestino.begin(); iter != estadosDestino.end(); ++iter){
        if(_existeRelacion(iter->first,caracter)) resultado.push_back(iter->first);
    }
    resultado.sort();
    return resultado;
}

AutomataFinito AutomataFinito::volverDeterminista(){
    AutomataFinito nuevo;
    if(determinista)return nuevo;
    nuevo.crearEstado(estadoInicial->nombre,estadoInicial->aseptacion);
    nuevo.crearAlfabeto(alfabeto);
    for(auto iter = nuevo.getEstados().begin(); iter != nuevo.getEstados().end(); ++iter){
        list<string> estados = _estadoConjunto(iter->first);
        if(estados.empty()) estados.push_back(iter->first);
        for(auto iter2 = alfabeto.begin(); iter2 != alfabeto.end(); ++iter2){
            list<string> destinos;
            for(string s : estados){
                if(s == "basura"){
                    destinos.push_back("basura");
                    break;
                }
                Estado * temp;
                _existeEstado(s,temp);
                list<string> relaciones = temp->relaciones(*iter2);
                destinos.insert(destinos.end(),relaciones.begin(),relaciones.end());
            }
            string nDestino = _crearEstadoConjunto(destinos);
            nuevo.crearEstado(nDestino,algunoEsAseptacion(estados));
            nuevo.crearRelacion(iter->first,nDestino,*iter2);
        }
    }
    return nuevo;
}

string AutomataFinito::Estado::transicionDeterminista(char caracter){
    for(auto iter = estadosDestino.begin(); iter != estadosDestino.end(); ++iter){
        if(find(iter->second.begin(),iter->second.end(),caracter) != iter->second.end()) return iter->first;
    }
}

bool AutomataFinito::verificarCadena(string cadena){
    Estado * estadoActual = estadoInicial;
    if(!estadoActual) return false;
    if(!determinista){
        determinista = esDeterminista();
        if(!determinista) return volverDeterminista().verificarCadena(cadena);
    }
    for(auto iter = cadena.begin(); iter != cadena.end(); ++iter){
        if(!_existeCaracter(*iter))return false;
        estadoActual = estados.find(estadoActual->transicionDeterminista(*iter))->second;
    }
    if(estadoActual->aseptacion) return true;
    return false;
}

void AutomataFinito::print(){
    string file = name + ".dot";
    ofstream archivo(file);
    archivo<<"digraph{"<<endl;
    for(auto iter = estados.begin(); iter != estados.end(); ++iter){
        string color = "black";
        if(iter->second->aseptacion) color = "red";
        archivo<<iter->first<<" [color = \""<<color<<"\"];"<<endl;
        for(auto iter2 = iter->second->estadosDestino.begin(); iter2 != iter->second->estadosDestino.end(); ++iter2){
            for(auto iter3 = iter2->second.begin(); iter3 != iter2->second.end(); ++iter3){
                archivo<<iter->first<<"->"<<iter2->first<<" [label=\""<<*iter3<<"\"];"<<endl;
            }
        }
    }
    string color = "green";
    if(estadoInicial->aseptacion) color = "blue";
    archivo<<estadoInicial->nombre<<" [color = \""<<color<<"\"];"<<endl;
    archivo<<"}";
    archivo.close();
    string comando = "dot -Tpdf " + name + ".dot -o " + name + ".pdf";
    const char *c = comando.c_str();
    system(c);
}

bool AutomataFinito::crearRelacion(string AF1, string AF2, char caracter){
    Estado * estado1;
    Estado * estado2;
    if(!_existeEstado(AF1,estado1) or !_existeEstado(AF2,estado2) or !_existeCaracter(caracter))return false;
    if(estado1->_existeRelacion(AF2,caracter))return false;
    estado1->estadosDestino[AF2].push_back(caracter);
    estado2->estadosOrigen[AF1].push_back(caracter);
    determinista = esDeterminista();
    return true;
}

map<string,AutomataFinito::Estado *>& AutomataFinito::getEstados(){
    return estados;
}

bool AutomataFinito::_existeCaracter(char caracter){
    if(find(alfabeto.begin(), alfabeto.end(), caracter) != alfabeto.end())return true;
    return false;
}

void AutomataFinito::crearAlfabeto(list<char> alfabeto){
    this->alfabeto = alfabeto;
    determinista = false;
}

bool AutomataFinito::Estado::_existeRelacion(string name, char caracter){
    if(estadosDestino.find(name) != estadosDestino.end()){
        if(find(estadosDestino[name].begin(), estadosDestino[name].end(),caracter) != estadosDestino[name].end())return true;
    }
    return false;
}

void AutomataFinito::addCaracter(const char caracter){
    if(find(alfabeto.begin(),alfabeto.end(),caracter) != alfabeto.end())return;
    alfabeto.push_back(caracter);
    determinista = esDeterminista();
}

void AutomataFinito::crearEstado(string name, bool aseptacion){
    Estado * nuevo;
    if(_existeEstado(name,nuevo))return;
    nuevo = new Estado(name,aseptacion);
    if(!estadoInicial) estadoInicial = nuevo;
    estados[name] = nuevo;
    determinista = esDeterminista();
}

void AutomataFinito::crearEstado(string name){
    Estado * nuevo;
    if(_existeEstado(name,nuevo))return;
    nuevo = new Estado(name);
    if(!estadoInicial) estadoInicial = nuevo;
    estados[name] = nuevo;
    determinista = esDeterminista();
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
    determinista = false;
    name = "AutomataDefault";
}

AutomataFinito::AutomataFinito(string name){
    estadoInicial = nullptr;
    determinista = false;
    this->name = name;
}

AutomataFinito::~AutomataFinito(){

}

#endif // AUTOMATAFINITO_H
