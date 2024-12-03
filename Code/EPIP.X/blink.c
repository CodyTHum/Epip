/* 
 * File:   blink.c
 * Author: Private
 *
 * Created on October 23, 2024, 4:21 PM
 */

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL // 16 MHz clock speed

int main(void) {
    DDRB |= (1 << PB0); // Set PB0 as an output

    while (1) {
        PORTB ^= (1 << PB0); // Toggle PB0
        _delay_ms(500); // Delay 500ms
    }
}

