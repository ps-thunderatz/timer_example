# Timer Example

Esse repositório contém um exemplo de como utilizar timers.

Nesse exemplo, o tempo de toggle de um LED (tempo que ele pisca) é controlado por um timer.
O tempo entre cada toggle é uma PA de termo inicial `FIRST_TOGGLE_TIME` e razão `TOGGLE_TIME_STEP`.
Além disso, `NUMBER_OF_TOGGLES` representa o índice do maior termo que a PA pode ter.

## Descrição do cube e hardware

| Pino | Nucleo | Configuração   | Função |
|:---: |:---:   |:---            |:---    |
| -    | -      | TIM1           | Timer em ms |
| PA5  | D13    | GPIO Output    | Acender um LED |
