#include <string.h>

#if defined(_WIN32)

#include <stdio.h>
#include <windows.h>
#include <wincrypt.h>

#else

#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#endif

class prng
{
public:
  prng(){
    #if defined(_WIN32)
      if(!CryptAcquireContext(&prov, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT | CRYPT_SILENT)){
        std::cerr << "CryptAcquireContext Failed " << std::endl;
        std::abort();
      }

    #else
      if((fd = open("/dev/urandom", O_RDONLY | O_NOCTTY | O_CLOEXEC)) < 0)
      {
        std::cerr << "Exit Failure :: open /dev/urandom" << std::endl;
        std::abort();
      }
    #endif    
  }
  
  ~prng(){
    #if defined(_WIN32)
      if(!CryptReleaseContext(prov, 0)){
        std::cerr << "CryptReleaseContext" << std::endl;
        std::abort();
      }
    #else
      if(close(fd) < 0)
      {
        std::cerr << "Exit Failure :: close /dev/urandom " << std::endl; 
        std::abort();
      }
    #endif    
  }
    
  inline static thread_local prng& inst(){
    static thread_local prng inst;
    return inst;
  }
    
  inline static thread_local const prng& cinst(){
    static thread_local const prng& inst = prng::inst();
    return inst;
  }
  
  
private:
  #if defined(_WIN32)
    HCRYPTPROV prov;
  #else
    int fd;
  #endif
  
};
