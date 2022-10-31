#pragma once
#include "ZXMemory.h"
#include <unordered_map>
#include <vector>
#include <stdint.h>
#include <string>
#include <functional>

struct ZXRegisters
{
	union
	{
		struct
		{
			uint32_t X;			// General Purpose
			uint32_t Y;			// General Purpose
			uint32_t ACC;		// Accumulator
			uint32_t PC;		// Program Counter
			uint32_t RET;		// Return Address
			uint32_t INC;		// Incrementor
		};
		uint32_t Array[6];
	};
};

struct ZXInstruction
{
	uint32_t code;
	uint32_t argc;
	std::string name;
	std::function<void(uint32_t* args, ZXRegisters* registers)> func;
};

void Generate_Instructions(std::vector<ZXInstruction>& result);

class ZX90
{
public:
	ZX90();
	~ZX90();

	void Tick();
	void Load(uint32_t* program, uint32_t size);

private:
	bool Decode(uint32_t instr, ZXInstruction& out);
	
	std::unordered_map<uint32_t, ZXInstruction> m_instructions;

	ZXRegisters m_registers;
	ZXMemory m_memory;
};