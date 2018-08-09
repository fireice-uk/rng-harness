class prng
{
public:
  prng(){
  }
  
  ~prng(){
  }
  
  inline static thread_local prng& inst(){
    static thread_local prng inst;
    return inst;
  }
    
  inline static thread_local const prng& cinst(){
    static thread_local const prng& inst = prng::inst();
    return inst;
  }
  
};
