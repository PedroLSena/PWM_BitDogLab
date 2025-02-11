#include "pico/stdlib.h"
#include "hardware/pwm.h"

// Função auxiliar para mapear um valor de um intervalo para outro
static inline uint map_value(uint value, uint in_min, uint in_max, uint out_min, uint out_max) {
    return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int main() {
    // Inicializa stdio (opcional, apenas para debug)
    stdio_init_all();

    // ========= Configuração do PWM para o servomotor ========= //
    // Utilizaremos a GPIO 22 para o sinal do servo.
    const uint SERVO_PIN = 22;
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    uint servo_slice = pwm_gpio_to_slice_num(SERVO_PIN);

    // Para obter um clock de PWM de 1 MHz (1 tick = 1 µs),
    // usamos o clock do sistema (125 MHz) com um divisor de 125.
    // Como queremos um período de 20 ms, o wrap deve ser 20000 - 1 = 19999.
    pwm_config servo_config = pwm_get_default_config();
    pwm_config_set_clkdiv(&servo_config, 125.0f);
    pwm_config_set_wrap(&servo_config, 19999);
    pwm_init(servo_slice, &servo_config, true);

    // ========= Configuração do PWM para o LED RGB ========= //
    // Utilizaremos a GPIO 12 para controlar (por exemplo) o brilho de um dos
    // canais do LED RGB. Aqui, usamos um wrap de 255 para obter resolução de 8 bits.
    const uint LED_PIN = 12;
    gpio_set_function(LED_PIN, GPIO_FUNC_PWM);
    uint led_slice = pwm_gpio_to_slice_num(LED_PIN);
    pwm_config led_config = pwm_get_default_config();
    pwm_config_set_wrap(&led_config, 255);
    pwm_init(led_slice, &led_config, true);

    // ========= Posicionamento inicial do servo ========= //
    // (2.400 µs -> 180°)
    pwm_set_gpio_level(SERVO_PIN, 2400);
    // Mapeia o valor do pulso para brilho (0 a 255) para efeito visual:
    uint led_level = map_value(2400, 500, 2400, 0, 255);
    printf("180");
    pwm_set_gpio_level(LED_PIN, led_level);
    sleep_ms(5000);  // Aguarda 5 segundos

    // Posição 90° (1.470 µs)
    pwm_set_gpio_level(SERVO_PIN, 1470);
    led_level = map_value(1470, 500, 2400, 0, 255);
    printf("90");
    pwm_set_gpio_level(LED_PIN, led_level);
    sleep_ms(5000);  // Aguarda 5 segundos

    // Posição 0° (500 µs)
    pwm_set_gpio_level(SERVO_PIN, 500);
    led_level = map_value(500, 500, 2400, 0, 255);  // Resultado = 0
    printf(")");
    pwm_set_gpio_level(LED_PIN, led_level);
    sleep_ms(5000);  // Aguarda 5 segundos

    // ========= Movimento suave periódico entre 0° e 180° ========= //
    // A cada 10 ms, incrementa (ou decrementa) a largura de pulso em 5 µs.
    int pulse = 500;      // Inicia em 0° (500 µs)
    int incremento = 5;   // Variação de 5 µs
    
    while (true) {
        pwm_set_gpio_level(SERVO_PIN, pulse);

        // Atualiza o LED para refletir (por exemplo) o ângulo do servo
        led_level = map_value(pulse, 500, 2400, 0, 255);
        pwm_set_gpio_level(LED_PIN, led_level);

        sleep_ms(10);
        pulse += incremento;
        if (pulse >= 2400) {
            pulse = 2400;
            incremento = -5;
        } else if (pulse <= 500) {
            pulse = 500;
            incremento = 5;
        }
        printf("0-180");
    }

    return 0;
}
