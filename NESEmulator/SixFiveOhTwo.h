#pragma once
#include "Bus.h";

class SixFiveOhTwo
{
public:
	SixFiveOhTwo(Bus *bus);
	~SixFiveOhTwo();

public:
	// Registers:
	uint8_t A = 0x00;	// 8-bit accumulator register (A)
	uint8_t X = 0x00;	// 8-bit index register (X)
	uint8_t Y = 0x00;	// 8-bit index register (Y)
	uint8_t P = 0x00;	// 7 processor status flag bits (P)
	uint8_t S = 0x00;	// 8-bit stack pointer (S)
	uint16_t PC = 0x00;	// 16-bit program counter (PC)

private:
	uint8_t IR = 0x00;	// Instruction register
	uint8_t IC = 0x00; // Instruction cycle: Current cycle of the instruction.

private:
	enum FLAGS : uint8_t {
		C = 0b1 << 0,	// Carry
		Z = 0b1 << 1,	// Zero
		I = 0b1 << 2,	// Interrupt Disable
		D = 0b1 << 3,	// Decimal
		B = 0b1 << 4,	// Break
		_U = 0b1 << 5,	// Unused
		V = 0b1 << 6,	// Overflow
		N = 0b1 << 7	// Negative
	};

	void setFlag(FLAGS flag, bool value);
	bool getFlag(FLAGS flag);

public:
	enum PINS : uint64_t {
		A0 = 0b1ULL << 0,	// Address bus pin #0
		A1 = 0b1ULL << 1,	// Address bus pin #1
		A2 = 0b1ULL << 2,	// Address bus pin #2
		A3 = 0b1ULL << 3,	// Address bus pin #3
		A4 = 0b1ULL << 4,	// Address bus pin #4
		A5 = 0b1ULL << 5,	// Address bus pin #5
		A6 = 0b1ULL << 6,	// Address bus pin #6
		A7 = 0b1ULL << 7,	// Address bus pin #7
		A8 = 0b1ULL << 8,	// Address bus pin #8
		A9 = 0b1ULL << 9,	// Address bus pin #9
		A10 = 0b1ULL << 10,	// Address bus pin #10
		A11 = 0b1ULL << 11,	// Address bus pin #11
		A12 = 0b1ULL << 12,	// Address bus pin #12
		A13 = 0b1ULL << 13,	// Address bus pin #13
		A14 = 0b1ULL << 14,	// Address bus pin #14
		A15 = 0b1ULL << 15,	// Address bus pin #15

		D0 = 0b1ULL << 16,	// Data bus pin #0
		D1 = 0b1ULL << 17,	// Data bus pin #1
		D2 = 0b1ULL << 18,	// Data bus pin #2
		D3 = 0b1ULL << 19,	// Data bus pin #3
		D4 = 0b1ULL << 20,	// Data bus pin #4
		D5 = 0b1ULL << 21,	// Data bus pin #5
		D6 = 0b1ULL << 22,	// Data bus pin #6
		D7 = 0b1ULL << 23,	// Data bus pin #7

		RW = 0b1ULL << 24,	// Control pin: Memory read or write access
		SYNC = 0b1ULL << 25,// Control pin: 
		IRQ = 0b1ULL << 26,	// Control pin: (Input) Interrupt Request
		NMI = 0b1ULL << 27,	// Control pin: (Input) Non-Maskable Interrupt
		RDY = 0b1ULL << 28,	// Control pin:
		RES = 0b1ULL << 29	// Control pin: Request RESET
	};

	// The state of 40 pins.
	uint64_t pins = (0b1ULL << 40) - 1;

	/// <summary>
	/// Set the address bus pins with a 16-bit address.
	/// </summary>
	/// <param name="address">A 16-bit address will be set.</param>
	void setAddress(uint16_t address);

	/// <summary>
	/// Get a 16-bit address which is currently set on the address bus pins.
	/// </summary>
	/// <returns>A 16-bit address on the address bus pins.</returns>
	uint16_t getAddress();

	/// <summary>
	/// Set the data bus pins with an 8-bit data value.
	/// </summary>
	/// <param name="data">An 8-bit data value will be set.</param>
	void setData(uint8_t data);

	/// <summary>
	/// Get an 8-bit data value which is currently set on the data bus pins.
	/// </summary>
	/// <returns>An 8-bit data value on the data bus pins.</returns>
	uint8_t getData();

	/// <summary>
	/// Enable pins.
	/// </summary>
	/// <param name="pins">A mask of pins.</param>
	void enablePins(uint64_t pins);

	/// <summary>
	/// Disable pins.
	/// </summary>
	/// <param name="pins">A mask of pins.</param>
	void disablePins(uint64_t pins);

private:
	// The last state of pins, using for compare with the current state of pins.
	uint64_t previousPins = (0b1ULL << 40) - 1;

private:
	void ADC(uint8_t value);
	void SBC(uint8_t value);

public:
	void tick();

private:
	Bus* bus = nullptr;
	// uint8_t read(uint16_t address);
	// void write(uint16_t address, uint8_t data);

	void accessMemory();

private:
	

};
