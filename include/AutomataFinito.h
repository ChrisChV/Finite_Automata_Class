#ifndef AUTOMATAFINITO_H
#define AUTOMATAFINITO_H

#include "list"
#include "map"
#include "algorithm"
#include "fstream"
#include "cstring"
#include "iostream"

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
                int numero;
                map<string,list<char>> estadosDestino; ///APunto;
                map<string,list<char>> estadosOrigen; ///MeApuntan;
        };
        AutomataFinito();
        AutomataFinito(string);
        void crearEstado(string, bool);
        void crearEstado(string);
        void crearAlfabeto(list<char>);
        void cambiarEstadoInicial(string);
        bool algunoEsAseptacion(list<string> &);
        bool esDeterminista();
        void addCaracter(const char);
        void _addDestinos(string, map<string,list<char>>&,map<string,string>&);
        AutomataFinito uni(AutomataFinito &second,string);
        AutomataFinito concat(AutomataFinito &second, string);
        bool verificarCadena(string);
        AutomataFinito volverDeterminista();
        AutomataFinito automataMinimo();
        AutomataFinito generarAutomataElemental(char);
        int size();
        bool empty();
        void print();
        bool crearRelacion(string, string, char);
        map<string,Estado *>& getEstados();
        virtual ~AutomataFinito();
    protected:
    private:
        AutomataFinito(Estado * estadoInicial,list<char> alfabeto,map<string,Estado *> estados,string name,bool determinista);
        bool _existeEstado(string, Estado *&);
        bool _existeCaracter(char);
        bool _verificarCadena(string, char, Estado *);
        void _crearEstado(string, bool);
        void _addCaracter(const char);
        void _recuperarTipoEstado(list<string> &, list<string> &);
        int _AM_buscarResultados(string, char,list<tuple<int,string>> &);
        list<string> _AM_generarParticiones(map<int,list<string>>);
        AutomataFinito _AM_generarAutomata(list<tuple<int,string>>&,string,string);
        AutomataFinito _VD_generarAutomata();
        list<string> _estadoConjunto(string);
        string _crearEstadoConjunto(list<string>&);
        Estado * estadoInicial;
        list<char> alfabeto;
        map<string,string> _copiarEstados(map<string,Estado*> second);
        map<string,string> __copiarEstados(map<string,Estado*> second);
        map<string,Estado *> estados;
        map<char, AutomataFinito> automatasElementales;
        string name;
        bool minimo;
        bool determinista;
};

AutomataFinito AutomataFinito::concat(AutomataFinito &second,  string n){
    AutomataFinito res(n);
    ///CREARALFABETO PENDEJO



    return res;
}


map<string,string> AutomataFinito::__copiarEstados(map<string,Estado*> second){
    map<string,string> nombres;
    map<string,Estado *> es;
    string tt = name + to_string(this->estados.size());
    _crearEstado(tt,estadoInicial->aseptacion);
    nombres[estadoInicial->nombre] = tt;
    es[estadoInicial->nombre] = estadoInicial;
    for(auto iter = estados.begin(); iter != estados.end(); ++iter){
        if(iter->second != estadoInicial){
            string temp = name + to_string(this->estados.size());
            _crearEstado(temp,iter->second->aseptacion);
            nombres[iter->second->nombre] = temp;
            es[iter->second->nombre] = iter->second;
        }
    }
    for(auto iter2 = nombres.begin(); iter2 != nombres.end(); ++iter2){
        _addDestinos(iter2->second,es[iter2->first]->estadosDestino,nombres);
    }
    return nombres;
}

AutomataFinito AutomataFinito::generarAutomataElemental(char caracter){
    AutomataFinito res;
    string temp = caracter + to_string(res.size());
    res.crearEstado(temp,false);
    string temp2 = caracter + to_string(res.size());
    res.crearEstado(temp2,true);
    Estado * tt;
    _existeEstado(temp,tt);
    res._addCaracter(caracter);
    res.crearRelacion(temp,temp2,caracter);
    return res;
}

void AutomataFinito::_addDestinos(string es, map<string,list<char>>& desti,map<string,string>&nombres){
    for(auto iter = desti.begin(); iter != desti.end(); ++iter){
        for(char c : iter->second){
            crearRelacion(es,nombres[iter->first],c);
        }
    }
}


map<string,string> AutomataFinito::_copiarEstados(map<string,Estado*> estados){
    map<string,string> nombres;
    map<string,Estado *> es;
    for(auto iter = estados.begin(); iter != estados.end(); ++iter){
        string temp = name + to_string(this->estados.size());
        _crearEstado(temp,iter->second->aseptacion);
        nombres[iter->second->nombre] = temp;
        es[iter->second->nombre] = iter->second;
    }
    cout<<"W"<<nombres.size()<<endl;
    cout<<"W"<<es.size()<<endl;
    for(auto iter2 = nombres.begin(); iter2 != nombres.end(); ++iter2){
        cout<<"ITERFIRST->"<<iter2->first<<endl;
        cout<<"ITERSECOND->"<<iter2->second<<endl;
        _addDestinos(iter2->second, es[iter2->first]->estadosDestino,nombres);
    }
    return nombres;
}

AutomataFinito AutomataFinito::uni(AutomataFinito &second,string n){
    AutomataFinito res(n);
    res.crearAlfabeto(alfabeto);
    for(char c : second.alfabeto){
        res._addCaracter(c);
    }
    string temp = n + to_string(res.estados.size());
    res._crearEstado(temp,estadoInicial->aseptacion or second.estadoInicial->aseptacion);
    auto nombres1 = res._copiarEstados(this->estados);
    auto nombres2 = res._copiarEstados(second.estados);
    res._addDestinos(res.estadoInicial->nombre,estadoInicial->estadosDestino,nombres1);
    res._addDestinos(res.estadoInicial->nombre,second.estadoInicial->estadosDestino,nombres2);
    return res;
}

void AutomataFinito::cambiarEstadoInicial(string estado){
    Estado * temp;
    if(!_existeEstado(estado,temp))return;
    estadoInicial = temp;
}

void AutomataFinito::_recuperarTipoEstado(list<string> &finales, list<string> &noFinales){
    for(auto iter = estados.begin(); iter != estados.end(); ++iter){
        if(iter->second->aseptacion){
            Estado * temp;
            _existeEstado(iter->first,temp);
            if(!iter->second->estadosOrigen.empty() or temp == estadoInicial) finales.push_back(iter->first);
        }
        else
        {
            Estado * temp;
            _existeEstado(iter->first,temp);
            if(!iter->second->estadosOrigen.empty() or temp == estadoInicial) noFinales.push_back(iter->first);
        }
    }
}

list<string> AutomataFinito::_AM_generarParticiones(map<int,list<string>> resultados){
    list<string> resultado;
    for(auto iter = resultados.begin(); iter != resultados.end(); ++iter){
        resultado.push_back(_crearEstadoConjunto(iter->second));
    }
    return resultado;
}

int AutomataFinito::_AM_buscarResultados(string estado, char caracter,list<tuple<int,string>> &candidatos){
    Estado * temp;
    if(!_existeEstado(estado,temp))cout<<"NOEXISTO"<<endl;
    string resultado = temp->relaciones(caracter).front();
    const char * c_resultado = resultado.c_str();
    list<tuple<int,string>> estados;
    for(auto iter : candidatos){
        list<string> resEstadoCon = _estadoConjunto(get<1>(iter));
        for(string siter: resEstadoCon){
            estados.push_back(make_tuple(get<0>(iter),siter));
        }
    }
    for(auto iter : estados){
        const char * c_iter = get<1>(iter).c_str();
        if(strcmp(c_resultado,c_iter) == 0)return get<0>(iter);
    }
    return -1;
}


AutomataFinito AutomataFinito::_AM_generarAutomata(list<tuple<int,string>>& candidatos,string estadoInicial,string name){
    AutomataFinito nuevo(name);
    nuevo.crearAlfabeto(alfabeto);
    map<string,list<string>> estadosConjunto;
    for(auto tuple_iter : candidatos){
        list<string> temp = _estadoConjunto(get<1>(tuple_iter));
        estadosConjunto[get<1>(tuple_iter)] = temp;
        string name = "[" + temp.front() + "]";
        nuevo._crearEstado(name,algunoEsAseptacion(temp));
    }
    for(auto iter = estadosConjunto.begin(); iter != estadosConjunto.end(); ++iter){
        Estado * temp;
        string name = "[" + iter->second.front() + "]";

        _existeEstado(iter->second.front(),temp);
        for(char alfa_iter : alfabeto){
            string relacion = temp->relaciones(alfa_iter).front();
            for(auto iter2 = estadosConjunto.begin(); iter2 != estadosConjunto.end(); ++iter2){
                if(find(iter2->second.begin(),iter2->second.end(),relacion) != iter2->second.end()){
                    cout<<"dsadsadasdasda"<<endl;
                    string name2 = "[" + iter2->second.front() +  "]";
                    cout<<"namw2->"<<name2<<endl;
                    nuevo.crearRelacion(name,name2,alfa_iter);
                    nuevo.print();
                }
            }
        }
    }
    string estadoI = "[" + estadoInicial + "]";
    nuevo.cambiarEstadoInicial(estadoI);
    nuevo.minimo = true;
    return nuevo;
}

AutomataFinito AutomataFinito::automataMinimo(){
    if(!esDeterminista())return AutomataFinito(name);
    list<tuple<int,string>> candidatos;
    list<tuple<int,string>> candidatosSiguientes;
    list<string> estadosFinales;
    list<string> estadosNoFinales;
    _recuperarTipoEstado(estadosFinales, estadosNoFinales);
    candidatos.push_back(make_tuple(1,_crearEstadoConjunto(estadosFinales)));
    candidatos.push_back(make_tuple(2,_crearEstadoConjunto(estadosNoFinales)));
    int cont = 3;
    bool huboParticion = true;
    while(huboParticion){
        candidatosSiguientes.clear();
        huboParticion = false;
        for(auto iter : candidatos){
            list<string> sEstados = _estadoConjunto(get<1>(iter));
            map<int,list<string>>  resultados;
            for(char c_iter : alfabeto){
                resultados.clear();
                for(string s_iter : sEstados){
                    cout<<"SITER->"<<s_iter<<endl;
                    resultados[_AM_buscarResultados(s_iter,c_iter,candidatos)].push_back(s_iter);
                }
                if(resultados.size() > 1)break;
            }
            if(resultados.size() == 1){
                candidatosSiguientes.push_back(make_tuple(candidatosSiguientes.size() + 1 , get<1>(iter)));
            }
            else{
                huboParticion = true;
                list<string> particiones = _AM_generarParticiones(resultados);
                for(string part_iter : particiones){
                    candidatosSiguientes.push_back(make_tuple(candidatosSiguientes.size() + 1,part_iter));
                }
            }
        }
        candidatos = candidatosSiguientes;
    }
    return  _AM_generarAutomata(candidatosSiguientes,estadoInicial->nombre,name);


}

bool AutomataFinito::esDeterminista(){
    int siz = alfabeto.size();
    for(auto iter = estados.begin(); iter != estados.end(); ++iter){
        int temp = 0;
        for(auto iter2 = iter->second->estadosDestino.begin(); iter2 != iter->second->estadosDestino.end(); ++iter2){
            temp += iter2->second.size();
        }
        if(siz != temp)return false;
    }
    return true;
}

bool AutomataFinito::algunoEsAseptacion(list<string>& estados){
    for(string iter : estados){
        Estado * estado;
        //cout<<"ITER->"<<iter<<endl;
        if(_existeEstado(iter,estado)){
            //cout<<estado->nombre<<"->"<<estado->aseptacion<<endl;
            if(estado->aseptacion)return true;
        }
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
    auto it = nombre.begin();
    for(auto iter = nombre.begin(); iter != nombre.end(); ++iter){
        switch(estado){
            case 0:
                if(*iter == '{') estado = 1;
                else{
                    resultado.push_back(nombre);
                    return resultado;
                }
                break;
            case 1:
                if(*iter == ',') estado = 2;
                else if(*iter == '}'){
                    resultado.push_back(sResultado);
                    ///cout<<"CON->"<<sResultado<<endl;
                    resultado.sort();
                    return resultado;
                }
                else sResultado.insert(sResultado.end(),*iter);
                break;
            case 2:
                resultado.push_back(sResultado);
                ///cout<<"CON->"<<sResultado<<endl;
                sResultado.clear();
                estado = 1;
                sResultado.insert(sResultado.end(),*iter);
                break;
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

AutomataFinito AutomataFinito::_VD_generarAutomata(){
    AutomataFinito res(name);
    res.crearAlfabeto(alfabeto);
    map<string,string> nombres;
    map<string,Estado *> es;
    string tt = estadoInicial->nombre;
    if(tt[0] == '{'){
        tt[0] = '[';
        tt[tt.size() - 1] = ']';
        for(int i = 0; i < tt.size(); i++){
            if(tt[i] == ','){
                tt[i] = ';';
            }
        }
    }
    res._crearEstado(tt,estadoInicial->aseptacion);
    nombres[estadoInicial->nombre] = tt;
    es[estadoInicial->nombre] = estadoInicial;
    for(auto iter = estados.begin(); iter != estados.end(); ++iter){
        if(iter->second != estadoInicial){
            string temp = iter->second->nombre;
            if(temp[0] == '{'){
                temp[0] = '[';
                temp[temp.size() - 1] = ']';
                for(int i = 0; i < temp.size(); i++){
                    if(temp[i] == ','){
                        temp[i] = ';';
                    }
                }
            }
            res._crearEstado(temp,iter->second->aseptacion);
            nombres[iter->second->nombre] = temp;
            es[iter->second->nombre] = iter->second;
        }
    }
    cout<<nombres.size()<<endl;
    cout<<"FFFFFFFFFFFFFFFFFFFFF"<<endl;
    for(auto iter2 = nombres.begin(); iter2 != nombres.end(); ++iter2){
        cout<<"FFFF1->"<<iter2->first<<endl;
        cout<<"FFFF2->"<<iter2->second<<endl;
        cout<<"FFFF3->"<<es[iter2->first]->nombre<<endl;
        res._addDestinos(iter2->second,es[iter2->first]->estadosDestino,nombres);
    }
    return res;
}

AutomataFinito AutomataFinito::volverDeterminista(){
    AutomataFinito nuevo(name);
    if(determinista or !estadoInicial){
        AutomataFinito det(estadoInicial,alfabeto,estados,name,determinista);
        return det;
    }
    nuevo._crearEstado(estadoInicial->nombre,estadoInicial->aseptacion);
    nuevo.crearAlfabeto(alfabeto);
    ///nuevo.print();
    ///char t;
    ///cin>>t;
    list<string> candidatos;
    candidatos.push_back(estadoInicial->nombre);
    auto nuevoEstados = nuevo.getEstados();
    for(auto iter = candidatos.begin(); iter != candidatos.end(); ++iter){
        cout<<"HHHHH->"<<*iter<<endl;
        list<string> estados = _estadoConjunto(*iter);
        ///cout<<"holaaa->"<<estados.front()<<endl;
        for(auto iter2 = alfabeto.begin(); iter2 != alfabeto.end(); ++iter2){
            list<string> destinos;
            for(string s : estados){
                const char *stemp = s.c_str();
                if(strcmp(stemp,"basura") == 0){
                    destinos.push_back("basura");
                    break;
                }
                Estado * temp;
                _existeEstado(s,temp);
                list<string> relaciones = temp->relaciones(*iter2);
                destinos.insert(destinos.end(),relaciones.begin(),relaciones.end());
            }
            string nDestino = _crearEstadoConjunto(destinos);
            //cout<<"DESTINO->"<<nDestino<<endl;
            ///cout<<nDestino<<"->"<<endl;
            list<string> temp = _estadoConjunto(nDestino);
            bool asep = algunoEsAseptacion(temp);
            if(estados.front() == "basura") asep = false;
            //cout<<asep<<endl;

            nuevo._crearEstado(nDestino,asep);
            ///nuevo.print();
            ///char t;
            ///cin>>t;
            nuevo.crearRelacion(*iter,nDestino,*iter2);
            if(find(candidatos.begin(),candidatos.end(),nDestino) == candidatos.end()) candidatos.push_back(nDestino);
            ///nuevo.print();
            ///char t;
            ///cin>>t;
        }
    }
    return nuevo._VD_generarAutomata();
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
    if(!estadoInicial){
        archivo<<"digraph{"<<endl<<"}";
        archivo.close();
        string comando = "dot -Tpdf " + name + ".dot -o " + name + ".pdf";
        const char *c = comando.c_str();
        system(c);
        return;
    }
    archivo<<"digraph{"<<endl;
    for(auto iter = estados.begin(); iter != estados.end(); ++iter){
        string color = "black";
        if(iter->second->aseptacion) color = "red";
        ///cout<<iter->second->numero<<"->"<<iter->first<<endl;
        archivo<<iter->second->numero<<" [label=\""<<iter->first<<"\"color = \""<<color<<"\"];"<<endl;
        for(auto iter2 = iter->second->estadosDestino.begin(); iter2 != iter->second->estadosDestino.end(); ++iter2){
            for(auto iter3 = iter2->second.begin(); iter3 != iter2->second.end(); ++iter3){
                Estado * temp;
                _existeEstado(iter2->first,temp);
                ///cout<<temp->numero<<"->"<<temp->nombre<<endl;
                archivo<<iter->second->numero<<"->"<<temp->numero<<" [label=\""<<*iter3<<"\"];"<<endl;
            }
        }
    }
    string color = "green";
    if(estadoInicial->aseptacion) color = "blue";
    archivo<<estadoInicial->numero<<" [label = \""<<estadoInicial->nombre<< "\"color = \""<<color<<"\"];"<<endl;
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

void AutomataFinito::_addCaracter(const char caracter){
    if(find(alfabeto.begin(),alfabeto.end(),caracter) != alfabeto.end())return;
    alfabeto.push_back(caracter);
    determinista = esDeterminista();
}

void AutomataFinito::addCaracter(const char caracter){
    if(find(alfabeto.begin(),alfabeto.end(),caracter) != alfabeto.end())return;
    automatasElementales[caracter] = generarAutomataElemental(caracter);
    alfabeto.push_back(caracter);
    determinista = esDeterminista();
}

void AutomataFinito::_crearEstado(string name, bool aseptacion){
    Estado * nuevo;
    if(_existeEstado(name,nuevo))return;
    nuevo = new Estado(name,aseptacion);
    if(!estadoInicial) estadoInicial = nuevo;
    estados[name] = nuevo;
    nuevo->numero = estados.size() - 1;
    determinista = esDeterminista();
}

void AutomataFinito::crearEstado(string name, bool aseptacion){
    if(name == "basura")return;
    Estado * nuevo;
    if(_existeEstado(name,nuevo))return;
    nuevo = new Estado(name,aseptacion);
    if(!estadoInicial) estadoInicial = nuevo;
    estados[name] = nuevo;
    nuevo->numero = estados.size() - 1;
    determinista = esDeterminista();
}

void AutomataFinito::crearEstado(string name){
    if(name == "basura")return;
    Estado * nuevo;
    if(_existeEstado(name,nuevo))return;
    nuevo = new Estado(name);
    if(!estadoInicial) estadoInicial = nuevo;
    estados[name] = nuevo;
    nuevo->numero = estados.size() - 1;
    determinista = esDeterminista();
}

bool AutomataFinito::_existeEstado(string name, Estado *&estado){
    auto iter =  estados.find(name);
    estado = iter->second;
    if(iter != estados.end())return true;
    return false;
}

bool AutomataFinito::empty(){
    return estados.empty();
}

int AutomataFinito::size(){
    return estados.size();
}

AutomataFinito::Estado::Estado(string name){
    nombre = name;
}

AutomataFinito::Estado::Estado(){
    nombre = nullptr;
    aseptacion = false;
    numero = -1;
}

AutomataFinito::Estado::Estado(string name, bool aseptacion){
    nombre = name;
    this->aseptacion = aseptacion;
    numero = -1;
}

AutomataFinito::AutomataFinito(){
    estadoInicial = nullptr;
    determinista = false;
    name = "AutomataDefault";
    minimo = false;
}

AutomataFinito::AutomataFinito(Estado * estadoInicial,list<char> alfabeto,map<string,Estado *> estados,string name,bool determinista){
    this->estadoInicial = estadoInicial;
    this->alfabeto = alfabeto;
    this->estados = estados;
    this->name = name;
    this->determinista = determinista;
    minimo = false;
}

AutomataFinito::AutomataFinito(string name){
    estadoInicial = nullptr;
    determinista = false;
    this->name = name;
    minimo = false;
}

AutomataFinito::~AutomataFinito(){

}

#endif // AUTOMATAFINITO_H
