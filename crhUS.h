#ifndef crhUS_h
#define crhUS_h

# include "Arduino.h"

class crhUS
{
  public:
      crhUS(int trigPin, int echoPin);
      int ping();
      int duration;
      int tP, eP;
      
  private:
  
};
#endif
