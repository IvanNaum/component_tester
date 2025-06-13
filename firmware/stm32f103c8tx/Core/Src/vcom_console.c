#include "vcom_console.h"

#include "commands.h"
#include "leds.h"
#include "usbd_cdc_if.h"
extern leds_t leds_status;

volatile bool run_console_flag = 0;  // flag for calling console from main

volatile uint8_t vcom_console_ring_buffer[CONSOLE_MAX_COMMAND_SIZE * 2];
volatile uint16_t vcom_console_ring_head = 0;
volatile uint16_t vcom_console_ring_tail = 0;

extern command_t commands_list[NUM_COMMANDS];

static uint16_t _read_func(char* buffer);
static void _write_func(const char* buffer);

bool vcom_console_init(console_t* state) {
    console_init(state, commands_list, NUM_COMMANDS, _read_func, _write_func);
    return true;
}
void vcom_console_process(console_t* console_status) {
    console_process(console_status);
    return;
}

static uint16_t _read_func(char* buffer) {
    uint16_t bytes_read = 0;

    // Копируем данные, пока есть что читать и есть место в буфере
    while (vcom_console_ring_tail != vcom_console_ring_head) {
        buffer[bytes_read] = (char)vcom_console_ring_buffer[vcom_console_ring_tail];
        vcom_console_ring_tail = (vcom_console_ring_tail + 1) % (CONSOLE_MAX_COMMAND_SIZE * 2);
        bytes_read++;
    }

    return bytes_read;
}
static void _write_func(const char* buffer) {
    CDC_Transmit_FS(buffer, strlen(buffer));
    return;
}