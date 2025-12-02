#ifndef __DigiKeyboardEs_H__
#define __DigiKeyboardEs_H__

#include <Arduino.h>
#include "DigiKeyboard.h"

class DigiKeyboardEsDevice : public Print {
private:
  bool _capsLockFlag = false;
  
  void sendKeyPress(uint8_t key, uint8_t mod = 0) {
    DigiKeyboard.sendKeyPress(key, mod);
    DigiKeyboard.delay(5); // Pequeño delay para asegurar envío
  }
  
  void sendKeyRelease() {
    DigiKeyboard.sendKeyPress(0, 0);
    DigiKeyboard.delay(5);
  }

public:
  size_t write(uint8_t chr) {
    uint8_t key = 0;
    uint8_t mod = 0;
    
    // Letras minúsculas (a-z)
    if (chr >= 'a' && chr <= 'z') {
      key = 0x04 + (chr - 'a');
    }
    // Letras MAYÚSCULAS (A-Z)
    else if (chr >= 'A' && chr <= 'Z') {
      key = 0x04 + (chr - 'A');
      mod = MOD_SHIFT_LEFT;
    }
    // Números (1-9)
    else if (chr >= '1' && chr <= '9') {
      key = 0x1E + (chr - '1');
    }
    // Número 0
    else if (chr == '0') {
      key = 0x27;
    }
    // Caracteres especiales
    else {
      switch(chr) {
        case ' ': key = 0x2C; break;
        case '.': key = 0x37; break;
        case '-': key = 0x38; break;
        case ',': key = 0x36; break;
        case '+': key = 0x30; break;
        case '<': key = 0x64; break;
        case '\'': key = 0x2D; break;
        case ':': key = 0x37; mod = MOD_SHIFT_LEFT; break;
        case '_': key = 0x38; mod = MOD_SHIFT_LEFT; break;
        case ';': key = 0x36; mod = MOD_SHIFT_LEFT; break;
        case '*': key = 0x30; mod = MOD_SHIFT_LEFT; break;
        case '>': key = 0x64; mod = MOD_SHIFT_LEFT; break;
        case '=': key = 0x27; mod = MOD_SHIFT_LEFT; break;
        case '?': key = 0x2D; mod = MOD_SHIFT_LEFT; break;
        case '!': key = 0x1E; mod = MOD_SHIFT_LEFT; break;
        case '"': key = 0x1F; mod = MOD_SHIFT_LEFT; break;
        case '(': key = 0x25; mod = MOD_SHIFT_LEFT; break;
        case ')': key = 0x26; mod = MOD_SHIFT_LEFT; break;
        case '/': key = 0x24; mod = MOD_SHIFT_LEFT; break;
        case '&': key = 0x23; mod = MOD_SHIFT_LEFT; break;
        case '%': key = 0x22; mod = MOD_SHIFT_LEFT; break;
        case '$': key = 0x21; mod = MOD_SHIFT_LEFT; break;
        case '\\': key = 0x35; mod = MOD_ALT_RIGHT; break;
        case '|': key = 0x31; mod = MOD_ALT_RIGHT; break;
        case '@': key = 0x1F; mod = MOD_ALT_RIGHT; break;
        case '#': key = 0x20; mod = MOD_ALT_RIGHT; break;
        case '~': key = 0x21; mod = MOD_ALT_RIGHT; break;
        case '[': key = 0x2F; mod = MOD_ALT_RIGHT; break;
        case ']': key = 0x30; mod = MOD_ALT_RIGHT; break;
        case '{': key = 0x34; mod = MOD_ALT_RIGHT; break;
        case '}': key = 0x33; mod = MOD_ALT_RIGHT; break;
        default: return 0;
      }
    }
    
    if (key) {
      // SOLUCIÓN MEJORADA: Secuencia más robusta
      
      // 1. Liberar cualquier tecla previa (solo para seguridad)
      sendKeyRelease();
      DigiKeyboard.delay(1);
      
      // 2. Presionar tecla con modificador si existe
      sendKeyPress(key, mod);
      DigiKeyboard.delay(10); // Delay suficiente para que se registre
      
      // 3. Liberar tecla
      sendKeyRelease();
      
      // 4. Delay entre teclas (reducido pero suficiente)
      DigiKeyboard.delay(15);
      
      return 1;
    }
    return 0;
  }
  
  void sendKeyStroke(uint8_t keyStroke, uint8_t modifiers = 0) {
    // Versión mejorada de sendKeyStroke
    sendKeyPress(keyStroke, modifiers);
    DigiKeyboard.delay(15);
    sendKeyRelease();
    DigiKeyboard.delay(20); // Delay extra después de ENTER
  }
  
  void print(const char* str) {
    while (*str) {
      write(*str++);
    }
  }
  
  void delay(long milli) {
    DigiKeyboard.delay(milli);
  }
  
  using Print::write;
};

DigiKeyboardEsDevice DigiKeyboardEs = DigiKeyboardEsDevice();

#endif
