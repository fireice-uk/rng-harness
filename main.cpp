#include <iostream>
#include "secure_prng.hpp"





int main(int argc, char **argv) 
{
	uint8_t sample[32];
    prng &obj = prng::inst();
	obj.generate_random(sample, 32);
	
    /*uint8_t sample[64];
    prng &obj = prng::inst();
    for(int i = 0; i < 32; i++)
    {
      obj.generate_system_random_bytes(&sample, 1);
    }
        
    for(int i = 0; i < 32; i++)
      std::cout << std::hex << static_cast<int>(sample[i]);
    std::cout << std::endl;

    for(int i = 32; i < 64; i++)
      std::cout << std::hex << static_cast<int>(sample[i]);
    std::cout << std::endl;*/
    
    /*
    for(int i = 0; i < 32; i++)
      std::cout << std::hex << sample[i];
    std::cout << std::endl;

    for(int i = 32; i < 64; i++)
      std::cout << std::hex << sample[i];
    std::cout << std::endl;     
    */

    
    return 0;
}
