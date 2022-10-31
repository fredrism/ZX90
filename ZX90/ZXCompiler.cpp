#include "ZXCompiler.h"
#include <iostream>

ZXCompiler::ZXCompiler()
{
	std::vector<ZXInstruction> instructions;
	Generate_Instructions(instructions);

	for (auto& instr : instructions)
	{
		m_instructions[instr.name] = instr;
	}

	m_registers["X"] = 0;
	m_registers["Y"] = 1;
	m_registers["ACC"] = 2;
	m_registers["PC"] = 3;
	m_registers["RET"] = 4;
	m_registers["INC"] = 5;
}

ZXCompiler::~ZXCompiler()
{
}

bool ZXCompiler::Parse(std::string src, std::vector<uint32_t>& dst)
{
	std::vector<char> buffer;
	std::vector<std::string> words;
	
	for(char c : src)
	{ 
		if (c == ' ')
		{
			buffer.push_back('\0');
			words.push_back(&buffer[0]);
			buffer.clear();
		}
		else
		{
			buffer.push_back(c);
		}
	}

	buffer.push_back('\0');
	words.push_back(&buffer[0]);
	buffer.clear();

	if (words[0][0] == '#') return true;	//Comment detection

	if (words[0] == "LABEL")
	{
		m_labels[words[1]] = dst.size() - 1;
		return true;
	}
	else if (m_instructions.find(words[0]) == m_instructions.end())
	{
		std::cout << "Error: " << src << std::endl;
		std::cout << "	Cause: " << "Failed to read instruction: " << words[0] << std::endl;
		return false;
	}

	ZXInstruction instr = m_instructions[words[0]];

	if (instr.argc + 1 != words.size())
	{
		std::cout << "Error: " << src << std::endl;
		std::cout << "	Cause: " << "Incorrect instruction count, should be " << instr.argc << std::endl;
		return false;
	}

	dst.push_back(instr.code);

	for (int i = 1; i < words.size(); i++)
	{
		if (m_registers.find(words[i]) != m_registers.end())
		{
			dst.push_back(m_registers[words[i]]);
		}
		else if (m_labels.find(words[i]) != m_labels.end())
		{
			dst.push_back(m_labels[words[i]]);
		}
		else
		{
			uint32_t arg = 0;
			try
			{
				arg = std::stoi(words[i]);
			}
			catch (const std::invalid_argument& ia)
			{
				std::cout << ia.what() << std::endl;
				std::cout << "Error: " << src << std::endl;
				return false;
			}

			dst.push_back(arg);
		}
	}

	return true;
}

bool ZXCompiler::ParseFile(std::string file, std::vector<uint32_t>& dst)
{
	std::ifstream fstream(file);

	if (fstream.is_open())
	{
		std::string line;
		int i = 0;
		while(std::getline(fstream, line))
		{
			if (!Parse(line, dst))
			{
				std::cout << "	line: " << i << ", " << file << std::endl;
				return false;
			}

			i++;
		}
	}

	return true;
}
