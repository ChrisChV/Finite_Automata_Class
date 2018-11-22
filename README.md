# Finite Automata Class

### Created by Christofer Chávez (XnpioChV)

The principal function of this class is create a finite automata from a regular expresion. With this class you can create automatas manualy, vizualizate it and verify strings. Also you can apply operators like union, reverse, concatenate, etc, and you can convert any automata in its deterministic form and find its minimal form.

1. MANUAL CREATION OF AN AUTOMATA

    1. CONSTRUCTOR
    
        You can initialize an automata in two ways:
        
          ```AutomataFinito automata // In this way, the automaton with the name "AutomataByDefault" is initialized;
          AutomataFinito automata("automata") //In this way the automata with name "automata" is initialized;```
          
        IMPORTANT: Always name automatas, since when performing operations between automata it is better that their names are different.
        
    2. CREATING STATES
    
        You can create states in two ways:
        
          ```automata.crearEstado("1") //A non-acceptance state with name "1" is created;
          automata.crearEstado("1",true) //A state with name "1" is created, which is an accepted state if the second parameter is true.```
          
        If the name of the state is repeated in the automata, the new repeated state is not created.
        
    3. CERATING ALPHABET
    
        You can create the alphabet in two ways:
        
          ```automata.crearAlfabeto(alfabeto) //Where alphabet is a list <char>
          automata.addCaracter('a') //Add the character 'a' to the alphabet```
          
        If the character is repeated, it is not entered.
        
        IMPORTANT: It is important to create the alphabet before creating relationships or doing any operation.
    
    4. CREATING RELATIONSHIPS
    
        Relationships are created in the following way
        
          ```automata.crearRelacion("1","2",'a') //It reads: From the "1" state, with 'a', I go to the "2" state```
          
        If any of the states does not exist or the character is not in the alphabet, the relationship is not created.
    
    5. VERIFY STRING
    
        Once created our automata, this can verify strings:
      
        ```bool flag = automata.verificarCadena("10001110"); //Returns true if the automata recognizes the string```
        
        If any character in the string does not exist in the alphabet, the function returns false.
        
        NOTE: In order to verify the string, the function converts the automata into a deterministic automata if it is not.
        
2. VISUALIZATION OF AN AUTOMATA

    ![Automata Generado a partir de la expresion regular: (a*abab(aba)*)V(b*Va)](autito.jpg "Automaton Generated from the regular expression: (a*abab(aba)*)V(b*Va)")
    
    1. COLORS
    
        * When a State is painted in Black, this is a normal state.
        * When a state is painted red, this is a state of aseptation.
        * When a State is painted Green, this is the initial state.
        * When a State is painted Blue, this is the initial state and it is aseptation.
    
    2. FUNCTION
    
        To be able to print the automata, you have to execute the following function:
        
            automata.print();
        
        The function generates a PDF with the name of the automaton and saves it in the folder where the project is located.

3. OPERATIONS

    1. CONVERT TO ITS DETERMINISTIC FORM
    
        ```automata2 = automata.volverDeterminista();```

    2. MINIMUM AUTOMATA
    
        ```automata2 = automata.volverDeterminista().automataMinimo();```
        
        IMPORTANT: The automaton has to be deterministic in order to find its minimum.
    
    3. UNION
    
        ```automata3 = automata.uni(automata2, "union");```
        
        The second parameter is the name of the resulting automaton.
        
    4. CONCATENATION
    
        ```automata3 = automata.concat(automata2, "concat");```
        
        The second parameter is the name of the resulting automaton.
        
    5. KLEENE'S STAR
    
        ```automata2 = automata.estrellitaDeKleene();```
        
    6. KLEENE'S SUM
    
        ```automata2 = automata.sumitaDeKleene();```
        
    7. INVERSE
    
        ```automata2 = automata.reverso();```
        
    8. COMPLEMENT
    
            automata.complemento();
    
4. GENERATING AN AUTOMATA FROM A REGULAR EXPRETION

    1. STEP 1
        
        Create an Automata with the alphabet of the regular expression.
        
            AutomataFinito automata("automata");
            automata.addCaracter('a');
            automata.addCaracter('b');
    
    2. STEP 2
    
        Call te function:
        
            AutomataFinito result = automata.generarDeExpresionRegular("(a*abab(aba)*)V(b*Va)","result");
        
        The first parameter is the regular expression and the second the name of the automata.
        The resulting automata is the minimum automaton.

