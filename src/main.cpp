#include <Arduino.h>
#include <HardwareSerial.h>
#include <STM32LowPower.h>
#include <STM32RTC.h>
#include "stm32f4xx.h"
#include "stm32f4xx_hal_exti.h"
#include "stm32f4xx_hal_usart.h"
#include "stm32f4xx_hal_uart.h"

//HardwareSerial Serial2(PA3,PA2);

void repetitionsIncrease(void);

bool sleep = true;
volatile int repetitions = 0;
String inputString = "";

void setup() {
  
  SerialUSB.begin(115200);
  Serial2.begin(115200);
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  
  LowPower.begin();
  LowPower.attachInterruptWakeup(PA3, repetitionsIncrease, RISING, DEEP_SLEEP_MODE);
   
}

void loop() {

  if(sleep){
    sleep = false;
    SerialUSB.println("Falling sleep");
    digitalWrite(LED_BUILTIN, HIGH);
    
    attachInterrupt(PA3, repetitionsIncrease, RISING);
    
    LowPower.deepSleep();

    SerialUSB.println("Waking up"); 
    digitalWrite(LED_BUILTIN, LOW); 
  }

  if(Serial2.available()){
    inputString = Serial2.readString();
    int lengthString = inputString.length();
    char arrChar[lengthString];
    inputString.toCharArray(arrChar,lengthString);
    
    Serial2.print(inputString);
    Serial2.println(repetitions);
    
    if(strstr(arrChar,"OK") != 0){
      sleep = true;
    }
  }
}

void repetitionsIncrease() {
  
  repetitions ++;
  detachInterrupt(PA3);
  Serial2.begin(115200);
}
