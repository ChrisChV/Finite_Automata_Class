# AutomatasFinitos
Producido y Financiado por Chris Chávez AK XNPIO

La funcion principal del programa es generar un autómata que reconozca una expresion regular dada.

CREACION MANUAL DE UNA AUTOMATA

    CONSTRUCTOR
    
        Se puede inicializar de dos formas:
        
          AutomataFinito autito //De esta forma se inicializa el automata con nombre "AutomataDefault";
          AutomataFinito autito("autito") //De esta forma se inicializa el automata con nombre "autito";
          
        IMPORTANTE: Poner siempre nombre a los automatas, y que al realizar las operaciones entre automatas es mejor
        que sus nombres sean diferentes.
        
    CREAR ESTADOS
        Se puede crear estados de dos formas:
        
          autito.crearEstado("1") //Se crea un estado de no aseptacion con nombre "1";
          autito.crearEstado("1",true) //Se crea un estado con nombre "1" que es de asptacion si el segundo parametro                                          es true.
          
        Si el nombre del estado se repite en el automata, el nuevo estado repetido no se crea.
    CREAR ALFABETO
    
        Se puede crear el alfabeto de dos formas:
        
          autito.crearAlfabeto(alfabeto) //Donde alfabeto es un list<char>
          autito.addCaracter('a') //Añade el caracter 'a' al alfabeto
          
        Si el caracter es repetido, este no se ingresa.
        
        IMPORTANTE: Es importante crear el alfabeto antes de crear las relaciones o hacer cualquier operacion.
    
    CREAR RELACIONES
        Las relaciones se crean de la siguiente forma:
        
          autito.crearRelacion("1","2",'a') //Se lee: Desde el estado "1", con 'a', voy al estado "2"
          
        Si cualquiera de los estados no existe o el caracter no esta en el alfabeto, la relacion no se crea.
    
    VERIFICAR CADENA
      Una vez creado nuestro automata, este puede verificar cadenas:
      
        bool flag = autito.verificarCadena("10001110"); //Devuelve true si el automata reconoce la cadena.
        
        Si cualquier caracter en la cadena no existe en el alfabeto, la funcion retorna false.
        
        NOTA: Para poder verificar la cadena, la funcion convierte al automata en un automata determinista si no lo es.
        
    
