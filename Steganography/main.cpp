#include <iostream>
#pragma warning(disable:4996)
#include "Image.h"

int main(int argc, char* argv[])
{
	uint8_t lsb = 2;				// count of least significant bits
	uint8_t cf = (1 << 8) >> lsb;	// compression factor (2bits -> 64)
	uint8_t mask = 0;				// bitmask (2bits -> 00000011)

	for (size_t i = 0; i < lsb; i++)
		mask = (mask << 1) | 1;

	if (argc != 3 && argc != 4)
	{
		std::cerr << "Encoding: " << argv[0] << " encode <original.png> <secret.png>" << std::endl;
		std::cerr << "Decoding: " << argv[0] << " decode <encoded.png>" << std::endl;
		return 1;
	}

	try
	{
		if (strcmp(argv[1], "encode") == 0)
		{
			Image original(argv[2]);
			Image secret(argv[3]);

			if (original.GetWidth() != secret.GetWidth() || original.GetHeight() != secret.GetHeight())
			{
				std::cerr << "Images must have the same dimensions." << std::endl;
				return 1;
			}

			for (size_t i = 0; i < secret.GetHeight(); i++)
			{
				for (size_t j = 0; j < secret.GetWidth(); j++)
				{
					Color compressed = secret.GetPixel(j, i);
					compressed.r /= cf;
					compressed.g /= cf;
					compressed.b /= cf;

					Color result = original.GetPixel(j, i);
					result.r = (result.r & ~mask) | (compressed.r & mask);
					result.g = (result.g & ~mask) | (compressed.g & mask);
					result.b = (result.b & ~mask) | (compressed.b & mask);
					original.SetPixel(j, i, result);
				}
			}

			original.SaveAs("result.png");
		}
		else if (strcmp(argv[1], "decode") == 0)
		{
			Image encoded(argv[2]);

			for (size_t i = 0; i < encoded.GetHeight(); i++)
			{
				for (size_t j = 0; j < encoded.GetWidth(); j++)
				{
					uint8_t mask = 0b11;

					Color uncompressed = encoded.GetPixel(j, i);
					uncompressed.r = (uncompressed.r & mask) * cf;
					uncompressed.g = (uncompressed.g & mask) * cf;
					uncompressed.b = (uncompressed.b & mask) * cf;

					encoded.SetPixel(j, i, uncompressed);
				}
			}

			encoded.SaveAs("decoded.png");
		}
		else
		{
			std::cerr << "Invalid command." << std::endl;
			return 1;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}