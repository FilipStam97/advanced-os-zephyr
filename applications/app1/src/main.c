#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/gpio/gpio_emul.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <zephyr/sys/printk.h>

#define THRESHOLD_C 25.0
#define PERIOD_MS 1000



static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);
int get_led_output( const struct gpio_dt_spec *led );

/* Simulated sensor producing pseudo-random values */
static int simulated_temp_c(void)
{
    uint32_t t = k_uptime_get_32();
    return 18 + (t % 13);   // values from 18 to 30
}

int main(void)
{
    gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);

    bool actuator_on = false;

    printk("UART-simulated sensor demo (native_sim)\n");
    printk("Temperature threshold = %d C\n\n", THRESHOLD_C);

    if (!gpio_is_ready_dt(&led)) {
        printk("LED GPIO not ready\n");
        return 0;
    }


    while (1)
    {
  
        int temp = simulated_temp_c();
        printk("Sensor(temp) = %.2f C\n", temp);

        if (!actuator_on && temp >= THRESHOLD_C) {
            actuator_on = true;
            gpio_pin_set_dt(&led, 1);
            printk("---> ACTUATOR: LED ON\n");
        } else if (actuator_on && temp < THRESHOLD_C) {
            actuator_on = false;
            gpio_pin_set_dt(&led, 0);
            printk("---> ACTUATOR: LED OFF\n");
        }
        printk("Emulated LED pin value = %d\n\n", get_led_output(&led));
         k_msleep(PERIOD_MS);
    }

    return 0;
}

int get_led_output( const struct gpio_dt_spec *led )
{
    /*ge the emulated device from the led0 node, wich is basically gpio0*/
    const struct device *dev = device_get_binding(led->port->name);
    return gpio_emul_output_get(dev, 0);
}

