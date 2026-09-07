//Gerardo Adrián Jiménez García


El programa simula, muchas veces, a un "caminante" que empieza en la posición
0 y en cada paso se mueve una unidad a la izquierda o a la derecha, según una
probabilidad p. Repite esto muchas veces y al final calcula, para cada número 
de pasos, el promedio de las posiciones y la varianza de esas posiciones. 
Los resultados se guardan en archivos .dat.

VARIABLES
- S: número de pasos que da el caminante en una sola caminata.
- N: número de caminatas independientes que se simulan. Entre más grande sea N, 
     los promedios y varianzas se acercan más a lo esperado.
- p: probabilidad de que en cada paso, el caminante se mueva a la derecha. La 
     probabilidad de ir a la izquierda es q = 1 - p.

ARCHIVOS QUE GENERA:
- random_walks.dat: todas las posiciones, paso por paso, de cada una de las
                    N caminatas.
- average_positions.dat: el desplazamiento promedio ⟨R⟩ en cada paso.
- variance_positions.dat: la varianza σ²_R en cada paso.

ARCHIVO graficar.py
graficar.py lee average_positions.dat y variance_positions.dat y con esos datos
genera dos imágenes (.png): desplazamiento_promedio.png y varianza.png. 

COMPILAR
Es probable que tenga un directorio distinto, por lo que hago énfasis en que
abras la terminal y te encuentres justamente en donde esta el archivo main.cpp
junto al código graficar.py, e.g.

    cd Documentos/FisicaEstadistica/randomwalker1D

Una vez estes en esta carpeta dentro de la terminal, copia los siguiente tal cual 
uno por uno en la terminal:

    g++ main.cpp -o main
    -o main

te pedirá los valores de S, N y p, una vez dados, el codigo finalizará. Ahora ejecuta lo
siguiente dentro de la terminal

    python3 graficar.py

se generarán las imagenes correspondientes dentro de la carpeta.
