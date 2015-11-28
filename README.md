# AutomatasFinitos

###Producido y Financiado por Chris Chávez AK XNPIO

La funcion principal del programa es generar un autómata que reconozca una expresion regular dada.

1. CREACION MANUAL DE UNA AUTOMATA

    1. CONSTRUCTOR
    
        Se puede inicializar de dos formas:
        
          ```AutomataFinito autito //De esta forma se inicializa el automata con nombre "AutomataDefault";
          AutomataFinito autito("autito") //De esta forma se inicializa el automata con nombre "autito";```
          
        IMPORTANTE: Poner siempre nombre a los automatas, y que al realizar las operaciones entre automatas es mejor
        que sus nombres sean diferentes.
        
    2. CREAR ESTADOS
    
        Se puede crear estados de dos formas:
        
          ```autito.crearEstado("1") //Se crea un estado de no aseptacion con nombre "1";
          autito.crearEstado("1",true) //Se crea un estado con nombre "1" que es de asptacion si el segundo parametro                                          es true.```
          
        Si el nombre del estado se repite en el automata, el nuevo estado repetido no se crea.
        
    3. CREAR ALFABETO
    
        Se puede crear el alfabeto de dos formas:
        
          ```autito.crearAlfabeto(alfabeto) //Donde alfabeto es un list<char>
          autito.addCaracter('a') //Añade el caracter 'a' al alfabeto```
          
        Si el caracter es repetido, este no se ingresa.
        
        IMPORTANTE: Es importante crear el alfabeto antes de crear las relaciones o hacer cualquier operacion.
    
    4. CREAR RELACIONES
    
        Las relaciones se crean de la siguiente forma
        
          ```autito.crearRelacion("1","2",'a') //Se lee: Desde el estado "1", con 'a', voy al estado "2"```
          
        Si cualquiera de los estados no existe o el caracter no esta en el alfabeto, la relacion no se crea.
    
    5. VERIFICAR CADENA
    
        Una vez creado nuestro automata, este puede verificar cadenas:
      
        ```bool flag = autito.verificarCadena("10001110"); //Devuelve true si el automata reconoce la cadena```
        
        Si cualquier caracter en la cadena no existe en el alfabeto, la funcion retorna false.
        
        NOTA: Para poder verificar la cadena, la funcion convierte al automata en un automata determinista si no lo es.
        
2. VISUALIZACIÓN DE UN AUTOMATA

    ![Imagen](/home/Documentos/AutomatasFInitos/autito.jpg)
    
    1. COLORES
    
        * Cuando un Estado esta pintado de Negro, éste es un estado normal.
        * Cuando un Estado esta pintado de Rojo, éste es un estado de aseptación.
        * Cuando un Estado esta pintado de Verde, éste es el estado inicial.
        * Cuando un Estado esta pintado de Azul, éste es el estado inicial y es de aseptación.
    
    2. FUNCION
    
        Para poder imprimir el automata, se tiene que ejecutar la siguiente función:
        
            autito.print();
        
        La funcion genera un pdf con el nombre del automata y lo guarda en la carpeta donde se encuentra el proyecto.

3. OPERACIONES

    1. VOLVER DETERMINISTA
    
        ```autito2 = autito.volverDeterminista();```

    2. AUTOMATA MÍNIMO
    
        ```autito2 = autito.volverDeterminista().automataMinimo();```
        
        IMPORTANTE: El autómata tiene que ser determinista para poder encontrar su mínimo.
    
    3. UNION
    
        ```autito3 = autito.uni(autito2, "union");```
        
        El segundo parametro es el nombre del automata resultante.
        
    4. CONCADENACION
    
        ```autito3 = autito.concat(autito2, "concat");```
        
        El segundo parametro es el nombre del automata resultante.
        
    5. ESTRELLA DE KLEENE
    
        ```autito2 = autito.estrellitaDeKleene();```
        
    6. SUMA DE KLEENE
    
        ```autito2 = autito.sumitaDeKleene();```
        
    7. INVERSO
    
        ```autito2 = autito.reverso();```
        
    8. COMPLEMENTO
    
            autito.complemento();
    
4. GENERAR UN AUTOMATA A PARTIR DE UNA EXPRESIÓN REGULAR

    1. PASO 1
        
        Crear un Automata con el alfabeto de la expresión regular.
        
            AutomataFinito autito("autito");
            autito.addCaracter('a');
            autito.addCaracter('b');
    
    2. PASO 2
    
        Llamar a la funcion
        
            AutomataFinito resultado = autito2.generarDeExpresionRegular("(a*abab(aba)*)V(b*Va)","resultado");
        
        El primer parámetro es la expresión regular y el segundo el nombre del automata.
        El automata resultante es el autómata mínimo.

