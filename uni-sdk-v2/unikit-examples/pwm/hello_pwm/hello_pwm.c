#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define PWM_GPIO_PIN1 3

int main() {

    // Tell GPIO 6 is allocated to the PWM
    gpio_set_function(PWM_GPIO_PIN1, GPIO_FUNC_PWM);

    // Find out which PWM slice is connected to GPIO
    uint slice_num = pwm_gpio_to_slice_num(PWM_GPIO_PIN1);

    // Set period of 4 cycles (0 to 3 inclusive)
    pwm_set_wrap(slice_num, 3);
    // Set channel A output high for one cycle before dropping
    pwm_set_chan_level(slice_num, PWM_CHAN_A, 1);
    
    // Set the PWM running
    pwm_set_enabled(slice_num, true);
    /// \end::setup_pwm[]

    // Note we could also use pwm_set_gpio_level(gpio, x) which looks up the
    // correct slice and channel for a given GPIO.
}
