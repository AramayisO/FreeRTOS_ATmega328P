#include <avr/io.h>

/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"
#include "croutine.h"

/* Priority definitions for tasks. */
#define mainBLINK_LED_TASK_PRIORITY ( tskIDLE_PRIORITY + 1 )

/* The period between LED state changes. */
#define mainLED_BLINK_PERIOD ( ( TickType_t ) 500 / portTICK_PERIOD_MS )

/*
 * The task function to blink the LED.
 */
static void vBlinkLED( void *pvParameters );

/*
 * The idle hook is used to scheduler co-routines.
 */
void vApplicationIdleHook( void );

/*---------------------------------------------------------------------------*/

int main(void)
{
	/* Define task handles. */
	TaskHandle_t xBlinkTask;
	
    /* Create tasks. */
	xTaskCreate( vBlinkLED, "Blink", configMINIMAL_STACK_SIZE, NULL, mainBLINK_LED_TASK_PRIORITY, &xBlinkTask);
	
	/* Start task scheduler. */
	vTaskStartScheduler();
	
    return 0;
}
/*---------------------------------------------------------------------------*/

static void vBlinkLED( void *pvParameters )
{
	/* The parameters are not used. */
	( void ) pvParameters;
	
	DDRB |= ( 1 << PORTB5 );
	
	/* Cycle forever, turning the LED on then off. */
	for ( ;; )
	{
		PORTB ^= ( 1 << PORTB5 );
		vTaskDelay( mainLED_BLINK_PERIOD );
	}
}
/*---------------------------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	vCoRoutineSchedule();
}
/*---------------------------------------------------------------------------*/
