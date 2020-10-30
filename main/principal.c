#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "nvs_flash.h"
#include "freertos/queue.h"
//Archivos Propios
#include "webHTTP.h"
#include "WiFiconfig.h"
#include "UARTconfig.h"
#include "log_in.h"
//Macros y Definiciones
#define PILA 1024
#define tamCOLA 1
#define tamMSN 1
//Variables globales
xQueueHandle Cola_UART;

void app_main (void){
	nvs_flash_init();
	iniciarUART();
	configGPIO();
	Cola_UART = xQueueCreate(tamCOLA, tamMSN);
	xTaskCreatePinnedToCore(&log_in, "Log_in", PILA*2, NULL, 5, NULL, 0);
	xTaskCreatePinnedToCore(&servidorhttp, "tarea_serverHTTP", PILA*2, NULL, 5, NULL, 0);

}
