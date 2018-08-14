#include <iostream>
#include <iomanip>
#include "secure_prng.hpp"

int main(int argc, char **argv) 
{
	uint8_t sample[550];
    prng &obj = prng::inst();
	obj.generate_random(sample, 550);
        
    for(int i = 0; i < sizeof(sample); i++)
	{
		if(i % 32 == 0)
			std::cout << std::endl;
		
		std::cout << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(sample[i]);
	}
	std::cout << std::endl;
    return 0;
}
