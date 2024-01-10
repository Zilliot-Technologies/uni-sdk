// Fade an LED between low and high brightness. An interrupt handler updates
// the PWM slice's output level each time the counter wraps.

#include "pico/stdlib.h"
#include <stdio.h>
#include "pico/time.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"

#define PWM_RED_LED_PIN 4
#define PWM_GREEN_LED_PIN 3
#define PWM_BLUE_LED_PIN 5

// #define RED_LED
#define GREEN_LED
// #define BLUE_LED

void on_pwm_wrap() {
    static int fade = 0;
    static bool going_up = true;

    #ifdef RED_LED
    // Clear the interrupt flag that brought us here
    pwm_clear_irq(pwm_gpio_to_slice_num(PWM_RED_LED_PIN));
    #endif 

    #ifdef GREEN_LED
    // Clear the interrupt flag that brought us here
    pwm_clear_irq(pwm_gpio_to_slice_num(PWM_GREEN_LED_PIN));
    #endif 

    #ifdef BLUE_LED
    // Clear the interrupt flag that brought us here
    pwm_clear_irq(pwm_gpio_to_slice_num(PWM_BLUE_LED_PIN));
    #endif 

    if (going_up) {
        ++fade;
        if (fade > 255) {
            fade = 255;
            going_up = false;
        }
    } else {
        --fade;
        if (fade < 0) {
            fade = 0;
            going_up = true;
        }
    }
    // Square the fade value to make the LED's brightness appear more linear
    // Note this range matches with the wrap value
    #ifdef RED_LED
    pwm_set_gpio_level(PWM_RED_LED_PIN, fade * fade);
    #endif

    #ifdef GREEN_LED
    pwm_set_gpio_level(PWM_GREEN_LED_PIN, fade * fade);
    #endif

    #ifdef BLUE_LED
    pwm_set_gpio_level(PWM_BLUE_LED_PIN, fade * fade);
    #endif
}

int main() {
    #ifdef RED_LED
    // Tell the LED pin that the PWM is in charge of its value.
    gpio_set_function(PWM_RED_LED_PIN, GPIO_FUNC_PWM);

    // Figure out which slice we just connected to the LED pin
    uint slice_num = pwm_gpio_to_slice_num(PWM_RED_LED_PIN);

    // Mask our slice's IRQ output into the PWM block's single interrupt line,
    // and register our interrupt handler
    pwm_clear_irq(slice_num);
    pwm_set_irq_enabled(slice_num, true);
    irq_set_exclusive_handler(PWM_IRQ_WRAP, on_pwm_wrap);
    irq_set_enabled(PWM_IRQ_WRAP, true);

    // Get some sensible defaults for the slice configuration. By default, the
    // counter is allowed to wrap over its maximum range (0 to 2**16-1)
    pwm_config config = pwm_get_default_config();
    // Set divider, reduces counter clock to sysclock/this value
    pwm_config_set_clkdiv(&config, 4.f);
    // Load the configuration into our PWM slice, and set it running.
    pwm_init(slice_num, &config, true);
    #endif

    #ifdef GREEN_LED
    gpio_set_function(PWM_GREEN_LED_PIN, GPIO_FUNC_PWM);

    uint slice_num = pwm_gpio_to_slice_num(PWM_GREEN_LED_PIN);

    pwm_clear_irq(slice_num);
    pwm_set_irq_enabled(slice_num, true);
    irq_set_exclusive_handler(PWM_IRQ_WRAP, on_pwm_wrap);
    irq_set_enabled(PWM_IRQ_WRAP, true);

    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 4.f);
    pwm_init(slice_num, &config, true);
    #endif

    #ifdef BLUE_LED
    gpio_set_function(PWM_BLUE_LED_PIN, GPIO_FUNC_PWM);

    uint slice_num = pwm_gpio_to_slice_num(PWM_BLUE_LED_PIN);

    pwm_clear_irq(slice_num);
    pwm_set_irq_enabled(slice_num, true);
    irq_set_exclusive_handler(PWM_IRQ_WRAP, on_pwm_wrap);
    irq_set_enabled(PWM_IRQ_WRAP, true);

    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 4.f);
    pwm_init(slice_num, &config, true);
    #endif

    // Everything after this point happens in the PWM interrupt handler, so we
    // can twiddle our thumbs
    while (1)
        tight_loop_contents();
}
