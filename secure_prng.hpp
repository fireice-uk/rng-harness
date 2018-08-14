#include <string.h>
#include "keccak.h"

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
	prng()
	{
		#if defined(_WIN32)
			if(!CryptAcquireContext(&prov, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT | CRYPT_SILENT))
			{
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

	~prng()
	{
		#if defined(_WIN32)
			if(!CryptReleaseContext(prov, 0))
			{
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

	void generate_random(uint8_t* output, size_t size_bytes)
	{
		if(size_bytes <= 32)
		{
			generate_system_random_bytes(output, size_bytes);
			return;
		}
		else
		{
			uint64_t buffer[5];
			buffer[0] = 0;
			generate_system_random_bytes(reinterpret_cast<uint8_t*>(buffer+1), sizeof(buffer) - sizeof(uint64_t));
			
			while(size_bytes > 200)
			{
				buffer[0]++;
				keccak(reinterpret_cast<uint8_t*>(buffer), sizeof(buffer), output, 200);
				output += 200;
				size_bytes -= 200;
			}
			
			if(size_bytes > 0)
			{
				uint8_t last[200];
				buffer[0]++;
				keccak(reinterpret_cast<uint8_t*>(buffer), sizeof(buffer), last, 200);
				memcpy(output, last, size_bytes);
			}
		}
	}

	inline void generate_system_random_bytes(uint8_t* result, size_t n)
	{
		#if defined(_WIN32)  
			if(CryptGenRandom(prov, (DWORD)n, result))
			{
				std::cerr << "CryptGenRandom Failed " << std::endl;
			}
		#else
			while(true)
			{
				ssize_t res = read(fd, result, n);
				if((size_t)res == n)
				{
					break;
				}
				if(res < 0)
				{
					if(errno != EINTR)
					{
						std::cerr << "EXIT_FAILURE :: read /dev/urandom" << std::endl;
						std::abort();
					}
				}
				else if(res == 0)
				{
					std::cerr << "EXIT_FAILURE :: read /dev/urandom: end of file " << std::endl;
					std::abort();
				}
				else
				{
					result += res;
					n -= (size_t)res;
				}
			}    
		#endif
	}

	inline static prng& inst()
	{
		static thread_local prng inst;
		return inst;
	}

	inline static const prng& cinst()
	{
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
