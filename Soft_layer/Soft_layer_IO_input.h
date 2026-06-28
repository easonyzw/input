#pragma once

#include "stm32f0xx.h"

void digital_input_initialization(void);
void IO_state_update(void);

extern unsigned char IO_Input_L;
extern unsigned char IO_Input_H;
