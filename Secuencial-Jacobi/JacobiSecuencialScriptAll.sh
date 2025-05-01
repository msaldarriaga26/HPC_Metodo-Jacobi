#!/bin/bash

executable="./jacobiSecuencialExe"

# ===== PRUEBA SIN -O3 =====
echo "Compilando SIN optimización..."
gcc JacobiSecuencial.c -o jacobiSecuencialExe

echo "Ejecutando pruebas SIN -O3..."
bash JacobiSecuencialScript.sh "JacobiSecuencialSinO3.csv"

# ===== PRUEBA CON -O3 =====
echo "Compilando CON -O3..."
gcc -O3 JacobiSecuencial.c -o jacobiSecuencialExe

echo "Ejecutando pruebas CON -O3..."
bash JacobiSecuencialScript.sh "JacobiSecuencialConO3.csv"

echo "✅ Pruebas finalizadas. Revisa JacobiSecuencialSinO3.csv y JacobiSecuencialConO3.csv"
