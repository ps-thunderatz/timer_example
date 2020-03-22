# Timer Example

Esse repositório contém um exemplo de como utilizar timers.

Nesse exemplo, o tempo de toggle de um LED (tempo que ele pisca) é controlado por um timer.
O tempo entre cada toggle segue uma PA de termo inicial `TOGGLE_TIME_START` e razão `TOGGLE_TIME_STEP`.
Além disso, `LED_ON_TIMES` representa o número de vezes que o LED irá acender.

## Descrição do cube e hardware

| Pino | Nucleo | Configuração   | Função |
|:---: |:---:   |:---            |:---    |
| -    | -      | TIM6           | Timer em ms |
| PA5  | D13    | GPIO Output    | Acender um LED |
