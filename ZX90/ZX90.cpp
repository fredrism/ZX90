#include "ZX90.h"
#include "ZXCompiler.h"
#include <iostream>

ZX90::ZX90()
{
	m_registers = { 0, 0, 0, 0, 0, 0 };

	std::vector<ZXInstruction> instructions;
	Generate_Instructions(instructions);

	for (auto& instr : instructions)
	{
		m_instructions[instr.code] = instr;
	}
}

ZX90::~ZX90()
{
}

void ZX90::Tick()
{
	uint32_t code = m_memory.Read(m_registers.PC++);

	ZXInstruction instruction;
	if (Decode(code, instruction))
	{
		instruction.func(m_memory.Ptr(m_registers.PC), &m_registers);
		m_registers.PC += instruction.argc;
	}
}

void ZX90::Load(uint32_t* program, uint32_t size)
{
	m_memory.Memset(0, 0, HEAP_START);
	m_memory.Copy(0, program, size);
}

bool ZX90::Decode(uint32_t instr, ZXInstruction& out)
{
	out = m_instructions[instr];
	return true;
}

void Generate_Instructions(std::vector<ZXInstruction>& result)
{
	uint32_t code = 0;
	result.push_back({
		code++,
		0,
		"NOP",
		[](uint32_t* args, ZXRegisters* registers) -> void {

		}
	});

	result.push_back({
		code++,
		0,
		"ADD",
		[](uint32_t* args, ZXRegisters* registers) -> void {
			registers->ACC = registers->X + registers->Y;
		}
	});

	result.push_back({
		code++,
		0,
		"SUB",
		[](uint32_t* args, ZXRegisters* registers) -> void {
			registers->ACC = registers->X - registers->Y;
		}
	});

	result.push_back({
		code++,
		0,
		"MUL",
		[](uint32_t* args, ZXRegisters* registers) -> void {
			registers->ACC = registers->X * registers->Y;
		}
	});

	result.push_back({
		code++,
		0,
		"DIV",
		[](uint32_t* args, ZXRegisters* registers) -> void {
			registers->ACC = registers->X / registers->Y;
		}
	});

	result.push_back({
		code++,
		2,
		"SET",
		[](uint32_t* args, ZXRegisters* registers) -> void {
			registers->Array[args[0]] = args[1];
		}
	});

	result.push_back({
		code++,
		2,
		"MOV",
		[](uint32_t* args, ZXRegisters* registers) -> void {
			registers->Array[args[0]] = registers->Array[args[1]];
		}
	});

	result.push_back({
		code++,
		0,
		"RET",
		[](uint32_t* args, ZXRegisters* registers) -> void {
			registers->PC = registers->RET;
			registers->RET = 0;
		}
	});

	result.push_back({
		code++,
		1,
		"JMP",
		[](uint32_t* args, ZXRegisters* registers) -> void {
			registers->PC = args[0];
		}
	});

	result.push_back({
		code++,
		1,
		"LOG",
		[](uint32_t* args, ZXRegisters* registers) -> void {
			std::cout << "[ZX90]: " << registers->Array[args[0]] << std::endl;
		}
	});
}