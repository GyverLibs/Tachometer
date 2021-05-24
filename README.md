![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)
![author](https://img.shields.io/badge/author-AlexGyver-informational.svg)
# Tachometer
Библиотека тахометра для Arduino без привязки к железу
- Вызывай tick() в прерывании по фронту
- Забирай getRPM() частоту в оборотах в минуту
- Забирай getHz() частоту в Герцах
- Забирай getPeriod() период в мкс
- Встроенный медианный фильтр
    
### Совместимость
Совместима со всеми Arduino платформами (используются Arduino-функции)

## Содержание
- [Установка](#install)
- [Инициализация](#init)
- [Использование](#usage)
- [Пример](#example)
- [Версии](#versions)
- [Баги и обратная связь](#feedback)

<a id="install"></a>
## Установка
- Библиотеку можно найти по названию **Tachometer** и установить через менеджер библиотек в:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Скачать библиотеку](https://github.com/GyverLibs/Tachometer/archive/refs/heads/main.zip) .zip архивом для ручной установки:
    - Распаковать и положить в *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Распаковать и положить в *C:\Program Files\Arduino\libraries* (Windows x32)
    - Распаковать и положить в *Документы/Arduino/libraries/*
    - (Arduino IDE) автоматическая установка из .zip: *Скетч/Подключить библиотеку/Добавить .ZIP библиотеку…* и указать скачанный архив
- Читай более подробную инструкцию по установке библиотек [здесь](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)

<a id="init"></a>
## Инициализация
```cpp
Tachometer tacho;
```

<a id="usage"></a>
## Использование
```cpp
void tick();                    // тикер - вызывать в прерывании по фронту
void setWindow(int window);     // установка количества тиков для счёта времени (по умолч 10)
void setTimeout(uint32_t tout); // таймаут прерываний (мс), после которого считается что вращение прекратилось (по умолч 1000)
uint16_t getRPM();              // получить обороты в минуту
float getHz();                  // получить герцы
uint32_t getPeriod();           // получить период в мкс
```

<a id="example"></a>
## Пример
Остальные примеры смотри в **examples**!
```cpp
// управляем 4 пин вентилятором и измеряем обороты
#define PWM_PIN 10    // ШИМ пин (подключать через резик 100-1000 Ом)
#define TACH_PIN 2    // пин тахометра (желательна внешняя подтяжка 10к к VCC)

#include <Tachometer.h>
Tachometer tacho;

void setup() {
  Serial.begin(9600);
  pinMode(PWM_PIN, OUTPUT);

  // пин тахометра вентилятора подтягиваем к VCC
  pinMode(TACH_PIN, INPUT_PULLUP);

  // настраиваем прерывание
  attachInterrupt(0, isr, FALLING);

  // включаем вентиль на скорость 150 (из 255)
  analogWrite(PWM_PIN, 190);
  
  //tacho.setWindow(20);		// установка количества тиков для счёта времени (по умолч 10)
  //tacho.setTimeout(2000);	// таймаут прерываний (мс), после которого считается что вращение прекратилось
}

// обработчик прерывания
void isr() {
  tacho.tick();   // сообщаем библиотеке об этом
}

void loop() {
  // выводим два раза в секунду
  static uint32_t tmr;
  if (millis() - tmr > 100) {
    tmr = millis();
    Serial.println(tacho.getRPM());			// RPM
	//Serial.println(tacho.getHz());		// Hz
	//Serial.println(tacho.getPeriod());	// us
  }
}
```

<a id="versions"></a>
## Версии
- v1.1

<a id="feedback"></a>
## Баги и обратная связь
При нахождении багов создавайте **Issue**, а лучше сразу пишите на почту [alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
Библиотека открыта для доработки и ваших **Pull Request**'ов!