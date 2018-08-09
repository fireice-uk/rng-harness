#include <iostream>
#include "secure_prng.hpp"




int main(int argc, char **argv) {
    uint8_t sample[8];
    int n = 64;
    prng &obj = prng::inst();
    obj.generate_system_random_bytes(&sample[0], n);
    obj.generate_system_random_bytes(&sample[1], n);
    obj.generate_system_random_bytes(&sample[2], n);
    obj.generate_system_random_bytes(&sample[3], n);
    obj.generate_system_random_bytes(&sample[4], n);
    obj.generate_system_random_bytes(&sample[5], n);
    obj.generate_system_random_bytes(&sample[6], n);
    obj.generate_system_random_bytes(&sample[7], n);

    std::cout << std::hex << static_cast<int>(sample[0]) << static_cast<int>(sample[1]) << static_cast<int>(sample[2]) << static_cast<int>(sample[3]) << std::endl;
    std::cout << std::hex << static_cast<int>(sample[4]) << static_cast<int>(sample[5]) << static_cast<int>(sample[6]) << static_cast<int>(sample[7]) << std::endl;
    
    //std::cout << something << std::endl;

    std::cout << "Hello, world!" << std::endl;
    
    return 0;
}
