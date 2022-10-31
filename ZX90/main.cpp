#include "ZX90.h"
#include "ZXCompiler.h"
#include <iostream>
#include <sstream>

int main()
{
	ZX90 zx90;
	ZXCompiler compiler;

	std::string inputBuffer;
	std::cin >> inputBuffer;

	std::vector<uint32_t> byteCode;

	if (inputBuffer == "file")
	{
		std::cout << "filename: " << std::endl;
		std::cin >> inputBuffer;
		compiler.ParseFile(inputBuffer, byteCode);
		zx90.Load(&byteCode[0], byteCode.size());

		while (true)
		{
			zx90.Tick();
		}
	}
	else if (inputBuffer == "live")
	{
		std::cout << "LIVE MODE: " << std::endl;
		while (true)
		{
			std::getline(std::cin >> std::ws, inputBuffer);
			compiler.Parse(inputBuffer, byteCode);
			zx90.Load(&byteCode[0], byteCode.size());
			zx90.Tick();
		}
	}

	std::cin >> inputBuffer;
	std::cout << "Goodbye" << std::endl;
}