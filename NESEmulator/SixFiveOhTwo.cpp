#include "SixFiveOhTwo.h"

SixFiveOhTwo::SixFiveOhTwo(Bus* bus) {
	this->bus = bus;

	this->setFlag(FLAGS::Z, true);
	this->previousPins = this->pins = PINS::RW | PINS::SYNC | PINS::RES;
}

SixFiveOhTwo::~SixFiveOhTwo() {

}

void SixFiveOhTwo::setFlag(FLAGS flag, bool value) {
	if (value) {
		this->P |= flag;
	}
	else {
		this->P &= ~flag;
	}
}

bool SixFiveOhTwo::getFlag(FLAGS flag) {
	return (this->P & flag) > 0;
}

void SixFiveOhTwo::setAddress(uint16_t address) {
	this->pins &= ~(
		PINS::A0 | PINS::A1 | PINS::A2 | PINS::A3 |
		PINS::A4 | PINS::A5 | PINS::A6 | PINS::A7 |
		PINS::A8 | PINS::A9 | PINS::A10 | PINS::A11 |
		PINS::A12 | PINS::A13 | PINS::A14 | PINS::A15
		);

	if (address & 0b0000'0000'0000'0001) this->pins |= PINS::A0;
	if (address & 0b0000'0000'0000'0010) this->pins |= PINS::A1;
	if (address & 0b0000'0000'0000'0100) this->pins |= PINS::A2;
	if (address & 0b0000'0000'0000'1000) this->pins |= PINS::A3;
	if (address & 0b0000'0000'0001'0000) this->pins |= PINS::A4;
	if (address & 0b0000'0000'0010'0000) this->pins |= PINS::A5;
	if (address & 0b0000'0000'0100'0000) this->pins |= PINS::A6;
	if (address & 0b0000'0000'1000'0000) this->pins |= PINS::A7;
	if (address & 0b0000'0001'0000'0000) this->pins |= PINS::A8;
	if (address & 0b0000'0010'0000'0000) this->pins |= PINS::A9;
	if (address & 0b0000'0100'0000'0000) this->pins |= PINS::A10;
	if (address & 0b0000'1000'0000'0000) this->pins |= PINS::A11;
	if (address & 0b0001'0000'0000'0000) this->pins |= PINS::A12;
	if (address & 0b0010'0000'0000'0000) this->pins |= PINS::A13;
	if (address & 0b0100'0000'0000'0000) this->pins |= PINS::A14;
	if (address & 0b1000'0000'0000'0000) this->pins |= PINS::A15;
}

uint16_t SixFiveOhTwo::getAddress() {
	uint16_t address = 0x0000;

	address |= !!(this->pins & PINS::A0) << 0;
	address |= !!(this->pins & PINS::A1) << 1;
	address |= !!(this->pins & PINS::A2) << 2;
	address |= !!(this->pins & PINS::A3) << 3;
	address |= !!(this->pins & PINS::A4) << 4;
	address |= !!(this->pins & PINS::A5) << 5;
	address |= !!(this->pins & PINS::A6) << 6;
	address |= !!(this->pins & PINS::A7) << 7;
	address |= !!(this->pins & PINS::A8) << 8;
	address |= !!(this->pins & PINS::A9) << 9;
	address |= !!(this->pins & PINS::A10) << 10;
	address |= !!(this->pins & PINS::A11) << 11;
	address |= !!(this->pins & PINS::A12) << 12;
	address |= !!(this->pins & PINS::A13) << 13;
	address |= !!(this->pins & PINS::A14) << 14;
	address |= !!(this->pins & PINS::A15) << 15;

	return address;
}

void SixFiveOhTwo::setData(uint8_t data) {
	this->pins &= ~(
		PINS::D0 | PINS::D1 | PINS::D2 | PINS::D3 |
		PINS::D4 | PINS::D5 | PINS::D6 | PINS::D7
		);

	if (data & 0b0000'0001) this->pins |= PINS::D0;
	if (data & 0b0000'0010) this->pins |= PINS::D1;
	if (data & 0b0000'0100) this->pins |= PINS::D2;
	if (data & 0b0000'1000) this->pins |= PINS::D3;
	if (data & 0b0001'0000) this->pins |= PINS::D4;
	if (data & 0b0010'0000) this->pins |= PINS::D5;
	if (data & 0b0100'0000) this->pins |= PINS::D6;
	if (data & 0b1000'0000) this->pins |= PINS::D7;
}

uint8_t SixFiveOhTwo::getData() {
	uint8_t data = 0x00;

	data |= !!(this->pins & PINS::D0) << 0;
	data |= !!(this->pins & PINS::D1) << 1;
	data |= !!(this->pins & PINS::D2) << 2;
	data |= !!(this->pins & PINS::D3) << 3;
	data |= !!(this->pins & PINS::D4) << 4;
	data |= !!(this->pins & PINS::D5) << 5;
	data |= !!(this->pins & PINS::D6) << 6;
	data |= !!(this->pins & PINS::D7) << 7;

	return data;
}

void SixFiveOhTwo::enablePins(uint64_t pins) {
	this->pins |= pins;
}

void SixFiveOhTwo::disablePins(uint64_t pins) {
	this->pins &= ~pins;
}

void SixFiveOhTwo::accessMemory() {
	if (this->pins & PINS::RW) {
		// RW pin high = Read access
		uint16_t address = this->getAddress();
		uint8_t data = this->bus->read(address);
		this->setData(data);
	}
	else {
		// RW pin low = Write access
		uint16_t address = this->getAddress();
		uint8_t data = this->getData();
		this->bus->write(address, data);
	}
}

void SixFiveOhTwo::ADC(uint8_t value) {
	if (this->getFlag(FLAGS::D)) {
		// TODO: ADC in decimal mode.
	}
	else {
		uint16_t sum = this->A + value + (this->getFlag(FLAGS::C) ? 1 : 0);
		this->setFlag(FLAGS::C, sum & 0xFF00);
		this->setFlag(FLAGS::Z, (sum & 0x00FF) == 0);
		this->setFlag(FLAGS::V, ((uint16_t)value ^ sum) & ((uint16_t)this->A ^ sum) & 0x0080);
		this->setFlag(FLAGS::N, sum & 0x0080);
		this->A = sum & 0xFF;
	}
}

void SixFiveOhTwo::SBC(uint8_t value) {
	if (this->getFlag(FLAGS::D)) {
		// TODO: SBC in decimal mode.
	}
	else {
		uint16_t diff = this->A - value - (this->getFlag(FLAGS::C) ? 0 : 1);
		this->setFlag(FLAGS::C, !(diff & 0xFF00));
		this->setFlag(FLAGS::Z, diff & 0x00FF);
		this->setFlag(FLAGS::V, ((uint16_t)this->A ^ value) & ((uint16_t)this->A & diff) & 0x80);
		this->setFlag(FLAGS::N, diff & 0x0080);
		this->A = diff & 0xFF;
	}
}

void SixFiveOhTwo::tick() {
	if (this->pins & PINS::SYNC) {
		// Begin an instruction:
		this->enablePins(PINS::RW);
		this->setAddress(this->PC);
		this->accessMemory();
		this->IR = this->getData();		// Fetch instruction opcode.
		this->IC = 0;					// Reset instruction cycle counter.
		this->disablePins(PINS::SYNC);	// Current instruction must be complete executed, before an other one will be loaded.
	}

	switch (this->IR << 3 | this->IC) {
#pragma region 0x00 BRK
	case (0x00 << 3) | 0:
		this->PC++;
		break;
	case (0x00 << 3) | 1:
		this->enablePins(PINS::RW);
		this->setAddress(this->PC);
		this->accessMemory();
		this->getData(); // Do nothing with padding byte.
		this->PC++;
		break;
	case (0x00 << 3) | 2:
		this->setFlag(FLAGS::B, true);
		this->disablePins(PINS::RW);
		this->setAddress(this->S);
		this->setData(static_cast<uint8_t>(this->PC >> 8));
		this->accessMemory();
		this->S--;
		break;
	case (0x00 << 3) | 3:
		this->disablePins(PINS::RW);
		this->setAddress(this->S);
		this->setData(static_cast<uint8_t>(this->PC & 0xFF));
		this->accessMemory();
		this->S--;
		break;
	case (0x00 << 3) | 4:
		this->disablePins(PINS::RW);
		this->setAddress(this->S);
		this->setData(this->P);
		this->accessMemory();
		this->S--;
		break;
	case (0x00 << 3) | 5:
		this->enablePins(PINS::RW);
		this->setAddress(0xFFFE);
		this->accessMemory();
		this->PC = this->getData();
		break;
	case (0x00 << 3) | 6:
		this->enablePins(PINS::RW);
		this->setAddress(0xFFFF);
		this->accessMemory();
		this->PC |= (uint16_t)this->getData() << 8;

		this->enablePins(PINS::SYNC);
		break;
	case (0x00 << 3) | 7:
		break;
#pragma endregion
#pragma region 0x69 ADC
	case (0x69 << 3) | 0:
		this->PC++;
		break;
	case (0x69 << 3) | 1:
		this->enablePins(PINS::RW);
		this->setAddress(this->PC);
		this->accessMemory();
		this->ADC(this->getData());
		
		this->enablePins(PINS::SYNC);
		this->PC++;
		break;
	case (0x69 << 3) | 2: break;
	case (0x69 << 3) | 3: break;
	case (0x69 << 3) | 4: break;
	case (0x69 << 3) | 5: break;
	case (0x69 << 3) | 6: break;
	case (0x69 << 3) | 7: break;
#pragma endregion
	}
}
