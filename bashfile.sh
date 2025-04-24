#!/bin/bash
# Ejecutable de los tests
# Para que funcoine: chmod +x bashfile.sh (se ejecuta con: ./bashfile.sh)

# Realizar un script de bash que reciba como primer argumento un número con valor 0 o 1, y como segundo argumento el nombre del fichero de pruebas sin extensión 
# (por ejemplo, space_test) con el que se desea trabajar. Dicho script compilará el fichero indicado mediante llamadas a make y lo ejecutará si el primer argumento 
# vale 0 o lo ejecutará utilizando valgrind cuando el primer argumento valga 1. Cuando no se indique nada en el segundo argumento, compilará y ejecutará todas las 
# pruebas correspondientes a los programas terminados en _test.c. La entrega de dicho script se realizará durante la segunda semana de la iteración.

#!/bin/bash

if [[ "$1" -ne 0 && "$1" -ne 1 ]]; then #comprueba si son "not equal" a 0 o 1
    echo "El primer argumento debe ser 0 o 1."
    exit 1
fi

if [ -z "$2" ]; then #sin segundo argumento
    echo "Compilando y ejecutando todas las pruebas..."
    for test_file in ./src/*_test.c; do
        if [ -f "$test_file" ]; then #comprueba si existe el archivo
            ejecutable="${test_file%.c}" #quito .c
            ejecutable="./${ejecutable#./src/}" #quito src/
            make "$ejecutable"
            if [ "$1" -eq 0 ]; then #sin valgrind
                ./"$ejecutable"
            elif [ "$1" -eq 1 ]; then #con valgrind
                valgrind -s --show-leak-kinds=all --track-origins=yes --leak-check=full ./"$ejecutable"
            fi
            echo ""
        fi
    done
else #con segundo argumento
    test_file="./src/$2.c"
    if [ -f "$test_file" ]; then #comprueba si existe el archivo
        ejecutable="${test_file%.c}" #quito .c
        ejecutable="./${ejecutable#./src/}" #quito src/
        make "$ejecutable"
        if [ "$1" -eq 0 ]; then #sin valgrind
            ./"$ejecutable"
        elif [ "$1" -eq 1 ]; then #con valgrind
            valgrind -s --show-leak-kinds=all --track-origins=yes --leak-check=full ./"$ejecutable"
        fi
    else
        echo "El archivo $test_file no existe."
        exit 1
    fi
fi