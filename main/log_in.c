#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "freertos/queue.h"
#include <string.h>
#include "WiFiconfig.h"
extern xQueueHandle Cola_UART;

void entrada (char *user[8], char *pass[8]){
	char Rx[1];
	uint8_t ic = 0, pureba = 0;
	char usuario[8], clave[8];
	uart_write_bytes(UART_NUM_0, (const char*) "usuario: ", 9);
	if(xQueueReceive(Cola_UART,&Rx,1000/portTICK_RATE_MS)==pdTRUE){
		usuario[ic]=Rx[0];
		ic++;
		if(usuario[ic] == 0x0D){
			uart_write_bytes(UART_NUM_0, (const char*) usuario, strlen(usuario));
			uart_write_bytes(UART_NUM_0, (const char*) "\n\rclave: ", 11);
			ic = 0;
			if(xQueueReceive(Cola_UART,&Rx,1000/portTICK_RATE_MS)==pdTRUE){
				clave[ic]=Rx[0];
				ic++;
				if (clave[ic] == 0x0D){
					uart_write_bytes(UART_NUM_0, (const char*) clave, strlen(clave));
				*user = usuario;
				*pass = clave;
				}
			}
		}
	}
	for (int i=0;i < strlen(usuario);i++)clave[i]=0;
	for (int i=0;i < strlen(clave);i++)clave[i]=0;

}

void log_in (void *P){
	char userok[8], passok[8];
	const char usercheck[8]={"jhonsepv"}, passcheck[8]={"password"};
	uint8_t ok = 0;
	entrada(&userok, &passok);
	while (!ok){
		if ((usercheck == userok) && (passcheck == passok)){
			uart_write_bytes(UART_NUM_0, (const char*) "\n\r--- Acceso concedido ---", 28);
			iniciar_wifi();
			ok = 1;
		}else{
			uart_write_bytes(UART_NUM_0, (const char*) "\n\r--- Usuario o calve invalida ---", 36);
			for (int i=0;i < strlen(userok);i++)userok[i]=0;
			for (int i=0;i < strlen(passok);i++)passok[i]=0;
		}
	}
}

