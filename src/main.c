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

#define TOGGLE_TIME_START_MS 150
#define TOGGLE_TIME_STEP_MS 75

/*****************************************
 * Private Variables
 *****************************************/

/**
 * @brief Arithmetic progression actual term index.
 */
uint8_t ap_index = 1;

/**
 * @brief Value to compare with timer counter.
 */
uint16_t tim_compare_ms = TOGGLE_TIME_START_MS;

/*****************************************
 * Main Function
 *****************************************/

int main(void) {
    mcu_init();

    MX_TIM6_Init();
    HAL_TIM_Base_Start(&htim6);

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

    for (;;) {
        if (__HAL_TIM_GET_COUNTER(&htim6) > tim_compare_ms) {
            __HAL_TIM_SET_COUNTER(&htim6, 0); /**< Reset timer to start counting new toggle delay */

            if (ap_index > (LED_ON_TIMES * 2)) {
                ap_index = 0;
            } else {
                HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
            }

            tim_compare_ms = TOGGLE_TIME_START_MS + TOGGLE_TIME_STEP_MS * ap_index;
            ap_index++;
        }

        /* Here, the rest of the code can be executed */
    }
}
