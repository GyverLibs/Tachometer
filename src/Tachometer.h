/*
    Библиотека тахометра для Arduino без привязки к железу
    Документация:
    GitHub: https://github.com/GyverLibs/Tachometer
    Возможности:	
    - Вызывай tick() в прерывании по фронту
    - Забирай getRPM() частоту в оборотах в минуту
    - Забирай getHz() частоту в Герцах
    - Забирай getPeriod() период в мкс
    - Встроенный таймаут отсутствия сигнала
    
    AlexGyver, alex@alexgyver.ru
    https://alexgyver.ru/
    MIT License

    Версии:
    v1.1
    v1.2 - оптимизация
    v1.3 - улучшена стабильность, уменьшен вес кода
*/

#ifndef _Tachometer_h
#define _Tachometer_h
#include <Arduino.h>

class Tachometer {
public:
    // тикер - вызывать в прерывании по фронту
    void tick() {
        if (ticks <= window) {
            if (!ticks) tmr = micros();
            if (ticks == window) tmr = micros() - tmr;
            ticks++;
        }
    }
    
    // установка количества тиков для счёта времени (по умолч 10)
    void setWindow(uint8_t nwindow) {
        window = nwindow;
        ticks = 0;
    }
    
    // таймаут прерываний (мс), после которого считается что вращение прекратилось (по умолч 1000)
    void setTimeout(uint16_t ntout) {
        tout = ntout;
    }
    
    // получить обороты в минуту
    uint32_t getRPM() {
        return getTime() ? (60000000ul / prd) : 0;
    }

    // получить частоту в герцах
    float getHz() {
        return getTime() ? (1000000.0 / prd) : 0;
    }
    
    // получить период в мкс
    uint32_t getUs() {
        return getTime() ? prd : 0;
    }
    // Return Total Tick Count 
    uint32_t getTicks() {
        return ticks;
    }

private:
    bool getTime() {
        if (ticks > window) {
            tmrMs = millis();
            prd = (uint32_t)tmr / window;
            ticks = 0;
        }
        return (millis() - tmrMs < tout && prd);
    }
    
    volatile uint32_t tmr;
    volatile uint8_t ticks = 0;
    
    uint8_t window = 10;
    uint32_t tmrMs = millis();
    uint32_t prd = 0;
    uint16_t tout = 1000;
};
#endif
