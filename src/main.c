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
 * @brief Variavel que guarda o tempo em ms até o proximo toggle do LED
 */
uint16_t toggle_time = FIRST_TOGGLE_TIME;

/**
 * @brief Variavel que guarda o valor a ser comparado com o counter do timer
 */
uint16_t tim_compare = FIRST_TOGGLE_TIME;

/*****************************************
 * Main Function
 *****************************************/

int main(void) {
    mcu_init();

    MX_TIM1_Init();
    HAL_TIM_Base_Start_IT(&htim1);

    __HAL_TIM_SET_AUTORELOAD(&htim1, TIM_PERIOD);

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

    for (;;) {
        uint16_t tim_counter = __HAL_TIM_GET_COUNTER(&htim1);

        if (tim_counter > tim_compare) {
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
            toggle_time += TOGGLE_TIME_STEP;
            tim_compare += toggle_time;
        }

        /* Aqui o resto do código pode ser executado */
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
    if (htim == &htim1) {
        toggle_time = FIRST_TOGGLE_TIME;
        tim_compare = FIRST_TOGGLE_TIME;
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
    }
}
