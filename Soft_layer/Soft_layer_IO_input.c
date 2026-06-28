#include "Soft_layer_IO_input.h"

unsigned char IO_Input_L = 0;
unsigned char IO_Input_H = 0;

typedef struct
{
    GPIO_TypeDef *input_port;
    uint16_t input_pin;

    GPIO_TypeDef *led_port;
    uint16_t led_pin;

    unsigned char input_byte;
    unsigned char bit_mask;
} IO_ChannelConfig;

static const IO_ChannelConfig io_table[2] =
{
    {GPIOC, GPIO_Pin_6, GPIOC, GPIO_Pin_2, 0, 0x01},
    {GPIOD, GPIO_Pin_2, GPIOA, GPIO_Pin_0, 0, 0x02},
};

void digital_input_initialization(void)
{
    IO_Input_L = 0;
    IO_Input_H = 0;
}

static void IO_status_bit_set(const IO_ChannelConfig *channel, unsigned char high_level)
{
    if(channel->input_byte == 0)
    {
        if(high_level)
        {
            IO_Input_L |= channel->bit_mask;
        }
        else
        {
            IO_Input_L &= (unsigned char)(~channel->bit_mask);
        }
    }
    else
    {
        if(high_level)
        {
            IO_Input_H |= channel->bit_mask;
        }
        else
        {
            IO_Input_H &= (unsigned char)(~channel->bit_mask);
        }
    }
}

static void IO_led_set(const IO_ChannelConfig *channel, unsigned char on)
{
    if(on)
    {
        GPIO_ResetBits(channel->led_port, channel->led_pin);
    }
    else
    {
        GPIO_SetBits(channel->led_port, channel->led_pin);
    }
}

void IO_state_update(void)
{
    unsigned char i;
    unsigned char input_state;

    for(i = 0; i < 2; i++)
    {
        input_state = GPIO_ReadInputDataBit(io_table[i].input_port, io_table[i].input_pin);

        if(input_state == SET)
        {
            IO_led_set(&io_table[i], 1);
            IO_status_bit_set(&io_table[i], 1);
        }
        else
        {
            IO_led_set(&io_table[i], 0);
            IO_status_bit_set(&io_table[i], 0);
        }
    }
}
