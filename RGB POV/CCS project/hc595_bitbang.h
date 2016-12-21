/**
 * Shift register 74HC595 bitbang library header.
 *
 * TODO: Add documentation.
 */
#ifndef _HC595_BITBANG_H_
#define _HC595_BITBANG_H_
#include <stdint.h>

void InitSPI(void);
void PushLine(uint8_t Line);

#endif // _HC595_BITBANG_H_
