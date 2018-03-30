#include <iostream> 
#include "wiringPiContext.hpp"

#ifdef HAS_WIRING_PI
#include "i_wiringPi.h"
#endif

namespace plotter{
    context::context(){
#ifdef HAS_WIRING_PI
        wiringPiSetupGpio();
#else
        std::cout << "Initializing WiringPi Context..." << std::endl;
#endif
    }

    context::~context(){
#ifdef HAS_WIRING_PI
#else
        std::cout << "...Destroying WiringPi Context" << std::endl;
#endif
    }

    void context::write(pin pin_number, bool value){
#ifdef HAS_WIRING_PI
        digitalWrite(static_cast<int>(pin_number), static_cast<int>(value));
#else
        std::cout << "Writing " << value << " to pin #" << pin_number << std::endl;
#endif
    }
}
