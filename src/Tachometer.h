/*
    Библиотека тахометра для Arduino без привязки к железу
    Документация:
    GitHub: https://github.com/GyverLibs/Tachometer
    Возможности:	
    - Вызывай tick() в прерывании по фронту
    - Забирай getRPM() частоту в оборотах в минуту
    - Забирай getHz() частоту в Герцах
    - Забирай getPeriod() период в мкс
    - Встроенный медианный фильтр
    
    AlexGyver, alex@alexgyver.ru
    https://alexgyver.ru/
    MIT License

    Версии:
    v1.1
*/

#ifndef Tachometer_h
#define Tachometer_h
#include <Arduino.h>

class Tachometer {
public:
    // тикер - вызывать в прерывании по фронту
    void tick() {   // tachoTime - время в мкс каждых _window тиков
        if (!ticks--) {
            ticks = _window - 1;
            tachoTime = micros() - tachoTimer;
            tachoTimer += tachoTime;  //== tachoTimer = micros();
            ready = true;
        }
    }
    
    // установка количества тиков для счёта времени (по умолч 10)
    void setWindow(int window) {
        _window = window;
    }
    
    // таймаут прерываний (мс), после которого считается что вращение прекратилось (по умолч 1000)
    void setTimeout(uint32_t tout) {
        _tout = tout * 1000ul;
    }
    
    // получить обороты в минуту
    uint16_t getRPM() {
        if (ready) {	// если готовы новые данные
            ready = false;
            if (tachoTime != 0) rpm = (uint32_t)_window * 60000000 / median3(tachoTime);
        }
        if (micros() - tachoTimer > _tout) rpm = 0;
        return rpm;
    }

    // получить герцы
    float getHz() {
        if (ready) {  // если готовы новые данные
            ready = false;
            if (tachoTime != 0) hz = (float)_window * 1000000 / median3(tachoTime);
        }
        if (micros() - tachoTimer > _tout) hz = 0;
        return hz;
    }

    // получить период в мкс
    uint32_t getPeriod() {
        return median3(tachoTime);
    }

private:
    // быстрая медиана
    long median3(long value) {
        buf[counter] = value;
        if (++counter > 2) counter = 0;
        if ((buf[0] <= buf[1]) && (buf[0] <= buf[2])) return (buf[1] <= buf[2]) ? buf[1] : buf[2];
        else {
            if ((buf[1] <= buf[0]) && (buf[1] <= buf[2])) return (buf[0] <= buf[2]) ? buf[0] : buf[2];
            else return (buf[0] <= buf[1]) ? buf[0] : buf[1];
        }
    }

    volatile uint32_t tachoTime = 100000;   // для плавного старта значений
    volatile uint32_t tachoTimer = micros();
    volatile int ticks = 0;
    volatile bool ready = false;
    uint32_t buf[3] = {100000, 100000, 100000}; // для плавного старта значений
    uint8_t counter = 0;
    int rpm = 0;
    float hz = 0.0;
    int _window = 10;
    uint32_t _tout = 1000000;
};
#endif