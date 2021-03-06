#include "Rover.h"
#include "ubx_interpreter.h"
#include <AP_HAL/AP_HAL.h>

// const AP_HAL::HAL &hal = AP_HAL::get_HAL();
// void set_g(uint8_t buffer[], int start_value);

static void setup_uart(AP_HAL::UARTDriver *uart, const uint32_t baud)
{
    if (uart == nullptr)
    {
        // that UART doesn't exist on this platform
        hal.console->printf("Serial not available");

        return;
    }
    hal.console->printf("setup uart\n");
    uart->begin(baud);
    // uart->set_unbuffered_writes(true);
    // uart->set_flow_control(AP_HAL::UARTDriver::flow_control::FLOW_CONTROL_ENABLE);
}

void Rover::setup_telem()
{

    hal.scheduler->delay(1000);
    // hal.console->printf("Setup telem\n");

    setup_uart(hal.serial(2), 230400);
}

// void set_g(uint8_t buffer[], int start_value)
// {
//     for (int i = 0; i < 10; ++i)
//     {
//         buffer[i] = start_value;
//     }
// }

// uint8_t g_count[10];
// int g_i = 0;

void Rover::send_kart_message(void)
{
    // set_g(g_count, g_i);
    // ++g_i;
    // hal.serial(2)->write(&g_count[0], 10);

    _ubx.packPixhawkMessage();
    _ubx.writeMessage(hal.serial(2));
}