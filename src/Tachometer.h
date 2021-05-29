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
    v1.2 - оптимизация
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
            tachoTime = median3(tachoTime);
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
        if (micros() - tachoTimer > _tout || tachoTime == 0) return 0;
        else return _window * 60000000ul / tachoTime;
    }

    // получить герцы
    float getHz() {
        if (micros() - tachoTimer > _tout || tachoTime == 0) return 0;
        else return _window * 1000000.0 / tachoTime;
    }
    
    // получить период в мкс
    uint32_t getUs() {
        if (micros() - tachoTimer > _tout || tachoTime == 0) return 0;
        else return tachoTime / _window;
    }

    // получить период в мкс (legacy)
    uint32_t getPeriod() {
        return getUs();
    }

private:
    // быстрая медиана
    uint32_t median3(uint32_t value) {
        buf[counter] = value;
        if (++counter > 2) counter = 0;
        if ((buf[0] <= buf[1]) && (buf[0] <= buf[2])) return (buf[1] <= buf[2]) ? buf[1] : buf[2];
        else {
            if ((buf[1] <= buf[0]) && (buf[1] <= buf[2])) return (buf[0] <= buf[2]) ? buf[0] : buf[2];
            else return (buf[0] <= buf[1]) ? buf[0] : buf[1];
        }
    }

    volatile uint32_t tachoTime = 100000;       // для плавного старта значений
    volatile uint32_t tachoTimer = micros();
    volatile int ticks = 0;
    volatile int _window = 10;
    
    uint32_t _tout = 1000000;
    uint32_t buf[3] = {100000, 100000, 100000}; // для плавного старта значений
    uint8_t counter = 0;
};
#endif