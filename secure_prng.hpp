class prng{
public:
  prng(){
  }
  
  ~prng(){
  }
  
  inline static prng& inst(){
    static prng inst;
    return inst;
  }
    
  inline static const prng& cinst(){
    static const prng& inst = prng::inst();
    return inst;
  }
  
};
