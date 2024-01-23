#include <Arduino.h>
#include <HardwareSerial.h>
#include <STM32LowPower.h>
#include <STM32RTC.h>
#include "stm32f4xx.h"
#include "stm32f4xx_hal_exti.h"
#include "stm32f4xx_hal_usart.h"
#include "stm32f4xx_hal_uart.h"

HardwareSerial Serial2(PA3,PA2);

void repetitionsIncrease(void);

bool sleep = true;
volatile int repetitions = 0;

void setup() {

  pinMode(PC13, OUTPUT);
  
  LowPower.begin();
  LowPower.attachInterruptWakeup(PA3, repetitionsIncrease, RISING, SLEEP_MODE);
   
}

void loop() {
  for (int i = 0; i < repetitions; i++) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
  }
  LowPower.sleep();

}

void repetitionsIncrease() {
  repetitions ++;
}
