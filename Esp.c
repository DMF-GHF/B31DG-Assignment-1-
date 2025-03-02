#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_system.h"
#include "rom/ets_sys.h"

#define DATA_PIN 15
#define SYNC_PIN 2
#define PB1_PIN 16
#define PB2_PIN 17

#ifdef DEBUG_MODE
static const unsigned long timeScale=1000;
#else
static const unsigned long timeScale=1;
#endif

static const unsigned long aTime=700;
static const unsigned long bTime=500;
static const int cPulses=9;
static const unsigned long dTime=2500;
static const unsigned long syncOnTime=50;

static bool outputEnable=false;
static bool outputSelect=false;

void generateNormalWaveform() {
    for(int i=1;i<=cPulses;i++){
        unsigned long on=aTime+(i-1)*50;
        gpio_set_level(DATA_PIN,1);
        ets_delay_us(on*timeScale);
        gpio_set_level(DATA_PIN,0);
        ets_delay_us(bTime*timeScale);
    }
    ets_delay_us(dTime*timeScale);
    gpio_set_level(SYNC_PIN,1);
    ets_delay_us(syncOnTime*timeScale);
    gpio_set_level(SYNC_PIN,0);
}

void generateAlternativeWaveform() {
    for(int i=cPulses;i>=1;i--){
        unsigned long on=aTime+(i-1)*50;
        gpio_set_level(DATA_PIN,1);
        ets_delay_us(on*timeScale);
        gpio_set_level(DATA_PIN,0);
        ets_delay_us(bTime*timeScale);
    }
    ets_delay_us(dTime*timeScale);
    gpio_set_level(SYNC_PIN,1);
    ets_delay_us(syncOnTime*timeScale);
    gpio_set_level(SYNC_PIN,0);
}

void app_main() {
    gpio_config_t io1={
        .pin_bit_mask=(1ULL<<DATA_PIN)|(1ULL<<SYNC_PIN),
        .mode=GPIO_MODE_OUTPUT
    };
    gpio_config(&io1);
    gpio_config_t io2={
        .pin_bit_mask=(1ULL<<PB1_PIN)|(1ULL<<PB2_PIN),
        .mode=GPIO_MODE_INPUT,
        .pull_up_en=1
    };
    gpio_config(&io2);
    while(1){
        if(!gpio_get_level(PB1_PIN)){
            outputEnable=!outputEnable;
            vTaskDelay(pdMS_TO_TICKS(300));
        }
        if(!gpio_get_level(PB2_PIN)){
            outputSelect=!outputSelect;
            vTaskDelay(pdMS_TO_TICKS(300));
        }
        if(outputEnable){
            if(!outputSelect) generateNormalWaveform();
            else generateAlternativeWaveform();
        } else {
            gpio_set_level(DATA_PIN,0);
            gpio_set_level(SYNC_PIN,0);
            vTaskDelay(pdMS_TO_TICKS(100));
        }
    }
}

