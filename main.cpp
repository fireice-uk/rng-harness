#include <iostream>
#include "secure_prng.hpp"

int main(int argc, char **argv) {
    prng::inst();
    std::cout << "Hello, world!" << std::endl;
    
    return 0;
}
