#pragma once
#include "ZX90.h"
#include <fstream>

class ZXCompiler
{
public:
	ZXCompiler();
	~ZXCompiler();

	bool Parse(std::string src, std::vector<uint32_t>& dst);
	bool ParseFile(std::string file, std::vector<uint32_t>& dst);

private:
	std::unordered_map<std::string, ZXInstruction> m_instructions;
	std::unordered_map<std::string, uint32_t> m_registers;
	std::unordered_map<std::string, uint32_t> m_labels;
};

