#include <iostream>
#include <vector>
#include <memory>

#include "wiringPiContext.hpp"
#include "units.hpp"
#include "stepper_coil.hpp"
#include "stepper.hpp"

template<class T>
std::initializer_list<T> make_init_list(std::initializer_list<T>&& l){
    return l;
}

int main(){
#ifdef HAS_WIRING_PI
    std::cout << "Wiring Pi found" << std::endl;
#else
    std::cout << "Wiring Pi not found" << std::endl;
#endif
    
    std::shared_ptr<plotter::context> context = std::make_shared<plotter::context>();

    context->write(4, true);
    context->write(2, false);
    context->write(30, true);


    using pin_list = std::initializer_list<plotter::pin>;
    using coil_state_list = std::initializer_list<plotter::stepper_coil::coil_state>;

    std::unique_ptr<plotter::stepper_coil> coil = 
        std::make_unique<plotter::stepper_coil>(context,
            pin_list({0,2,3,12}),
            coil_state_list({{0,0,0,0},{0,1,0,1},{1,0,1,0}})
        );

    plotter::stepper stepper(std::move(coil), 120.0);

    plotter::travel<std::milli> travel(2.0);
    //stepper.set_target(plotter::step(10));
    stepper.set_target(plotter::millimeters(2.0));

    for(int i = 0; i < 10; i++){
        stepper.tick();
    }
    std::cout << std::endl;
    stepper.set_target(plotter::millimeters(0.0));
    for(int i = 0; i < 5; i++){
        stepper.tick();
    }
}
