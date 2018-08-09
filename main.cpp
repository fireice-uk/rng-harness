#include <iostream>
#include "secure_prng.hpp"

int main(int argc, char **argv) {
    uint8_t something;
    int n = 32;
    prng &obj = prng::inst();
    obj.generate_system_random_bytes(&something, n);
    std::cout << "Hello, world!" << std::endl;
    
    return 0;
}
