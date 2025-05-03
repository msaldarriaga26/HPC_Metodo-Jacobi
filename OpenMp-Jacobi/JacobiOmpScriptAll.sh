#!/bin/bash

executable="./JacobiExecutableOmp"

# ===== PRUEBA SIN O3 =====
echo "Compilando SIN optimización..."
gcc -fopenmp JacobiOmp.c -o JacobiExecutableOmp

echo "Ejecutando pruebas SIN O3..."
bash JacobiOmpScript.sh "JacobiOmpTimesSinO3.csv"

# ===== PRUEBA CON O3 =====
echo "Compilando CON -O3..."
gcc -fopenmp -O3 JacobiOmp.c -o JacobiExecutableOmp

echo "Ejecutando pruebas CON O3..."
bash JacobiOmpScript.sh "JacobiOmpTimesconO3.csv"

echo "✅ Ambas pruebas finalizadas. Revisa los archivos CSV."
