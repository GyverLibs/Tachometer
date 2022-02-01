// измеряем обороты вентилятора от пк
#define TACH_PIN 2    // пин тахометра (желательна внешняя подтяжка 4.7к к VCC)

#include <Tachometer.h>
Tachometer tacho;

void setup() {
  Serial.begin(9600);

  // пин тахометра вентилятора подтягиваем к VCC
  pinMode(TACH_PIN, INPUT_PULLUP);

  // настраиваем прерывание
  attachInterrupt(0, isr, FALLING);

  //tacho.setWindow(20);    // установка количества тиков для счёта времени (по умолч 10)
  //tacho.setTimeout(2000); // таймаут прерываний (мс), после которого считается что вращение прекратилось
}

// обработчик прерывания
void isr() {
  tacho.tick();   // сообщаем библиотеке об этом
}

void loop() {
  // выводим 10 раз в секунду
  static uint32_t tmr;
  if (millis() - tmr > 100) {
    tmr = millis();
    Serial.println(tacho.getRPM());     // RPM
    //Serial.println(tacho.getHz());    // Hz
    //Serial.println(tacho.Us());       // us
  }
}