/**
 * @file main.c
 *
 * @brief Main function
 */

#include "mcu.h"
#include "tim.h"

/*****************************************
 * Private Constants
 *****************************************/

#define LED_ON_TIMES 5

#define TOGGLE_TIME_START 150
#define TOGGLE_TIME_STEP 75

/*****************************************
 * Private Variables
 *****************************************/

/**
 * @brief Arithmetic progression actual term.
 */
uint8_t ap_index = 1;

/**
 * @brief Value to compare with timer counter.
 */
uint16_t tim_compare = TOGGLE_TIME_START;

/*****************************************
 * Main Function
 *****************************************/

int main(void) {
    mcu_init();

    MX_TIM6_Init();
    HAL_TIM_Base_Start_IT(&htim6);

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

    for (;;) {
        if (__HAL_TIM_GET_COUNTER(&htim6) > tim_compare) {
            __HAL_TIM_SET_COUNTER(&htim6, 0);

            if (ap_index > (LED_ON_TIMES * 2)) {
                ap_index = 0;
            } else {
                HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
            }

            tim_compare = TOGGLE_TIME_START + TOGGLE_TIME_STEP * ap_index;
            ap_index++;
        }

        /* Aqui o resto do código pode ser executado */
    }
}
