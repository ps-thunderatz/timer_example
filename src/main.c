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

#define NUMBER_OF_TOGGLES 6

#define FIRST_TOGGLE_TIME 100
#define TOGGLE_TIME_STEP 200

/** @brief Calculates the timer period using the sum of the terms from an arithmetic progression */
#define TIM_PERIOD (2 * FIRST_TOGGLE_TIME + TOGGLE_TIME_STEP * NUMBER_OF_TOGGLES) * (NUMBER_OF_TOGGLES + 1) / 2

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
uint16_t tim_compare = FIRST_TOGGLE_TIME;

/*****************************************
 * Main Function
 *****************************************/

int main(void) {
    mcu_init();

    MX_TIM6_Init();
    HAL_TIM_Base_Start_IT(&htim6);

    __HAL_TIM_SET_AUTORELOAD(&htim6, TIM_PERIOD);

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

    for (;;) {
        uint16_t tim_counter = __HAL_TIM_GET_COUNTER(&htim6);

        if (tim_counter > tim_compare) {
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
            tim_compare += (FIRST_TOGGLE_TIME + TOGGLE_TIME_STEP * ap_index); /**< Sums the next term of the AP */
            ap_index++;
        }

        /* Aqui o resto do código pode ser executado */
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
    if (htim == &htim6) {
        ap_index = 1;
        tim_compare = FIRST_TOGGLE_TIME;
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
    }
}
