# Controle de Servomotor por PWM no RP2040

Este projeto implementa o controle de um **servomotor micro servo padrão** utilizando o **Raspberry Pi Pico W** através da modulação por largura de pulso (**PWM**). A simulação é feita no ambiente **Wokwi**.

## 🎯 Objetivos
- Configurar a GPIO 22 para gerar um **PWM de 50 Hz (período de 20 ms)**.
- Ajustar o ciclo ativo (duty cycle) para posicionar o servomotor em **0°, 90° e 180°**.
- Implementar uma varredura **suave e periódica** entre 0° e 180°.
- Integrar o **LED RGB (GPIO 12)** para análise do comportamento da iluminação.

## 🛠 Requisitos
- **Microcontrolador**: Raspberry Pi Pico W (ou simulação no Wokwi)
- **Linguagem**: C (usando o Pico SDK)
- **Simulador**: [Wokwi](https://wokwi.com/)
- **Ferramenta Educacional**: BitDogLab (para experimento com LED RGB)

## 🔧 Configuração do PWM
| Posição do Servo | Largura de Pulso | Duty Cycle |
|-----------------|-----------------|------------|
| 180°           | 2400 µs          | 12.0%      |
| 90°            | 1470 µs          | 7.35%      |
| 0°             | 500 µs           | 2.5%       |

A movimentação entre 0° e 180° ocorre de forma **suave**, com incrementos de **5 µs a cada 10 ms**.

## 📜 Código
O código configura o PWM para o **servomotor (GPIO 22)** e o **LED RGB (GPIO 12)**. O LED RGB tem seu brilho ajustado de acordo com o ângulo do servo.

### Comportamento Esperado no LED RGB
- Quando o servo está em **0°**, o LED fica com **mínima intensidade**.
- Quando o servo está em **180°**, o LED fica com **máxima intensidade**.
- Durante a varredura suave, o brilho do LED **aumenta e diminui gradualmente**.

## 🚀 Execução
1. **Compilar o código** usando o **Pico SDK**.
2. **Subir para o Raspberry Pi Pico** ou **executar no Wokwi**.
3. **Observar a movimentação do servomotor e a variação da iluminação do LED RGB**.

## 📌 Observações
- No Wokwi, os valores podem ser ajustados conforme necessário para melhor visualização.
- A ferramenta **BitDogLab** permite observar o comportamento do LED RGB conforme o controle PWM do servo.

## 📷 Demonstração
Confira o vídeo da simulação: [Clique aqui](https://www.dropbox.com/scl/fi/i32f4t9dqggn4c1durb4o/2025-02-04-08-52-05.mkv?rlkey=s6ofq9yumuts3h8chte052cuj&dl=0)

## 📚 Referências
- [Pico SDK Documentation](https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-c-sdk.pdf)
- [Wokwi Simulator](https://wokwi.com/)

