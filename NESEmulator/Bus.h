#pragma once

#include <cstdint>
#include "SixFiveOhTwo.h"

class Bus
{
public:
	Bus();
	~Bus();

public:
	SixFiveOhTwo cpu;


public:
	void write(uint16_t addr, uint8_t data);
	uint8_t read(uint16_t addr, bool readOnly = false);
};
