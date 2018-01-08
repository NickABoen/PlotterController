#include <iostream>
#include <vector>

#include "i_wiringPi.hpp"
#include "steppers/stepper.hpp"
#include "cyclic_iterator/cyclic_iterator.hpp"

template <int PinCount>
void print_motor_state(const motor_state<PinCount>& state)
{
    for(auto x : state)
    {
        std::cout << x << ',';
    }
    std::cout << std::endl;
}

int main(){
    std::cout << "Hello World - Motor States" << std::endl;

#ifdef HAS_WIRING_PI
    std::cout << "Wiring Pi found" << std::endl;
#else
    std::cout << "Wiring Pi not found" << std::endl;
#endif

    //sequence_instance<3,3> stepper(bipolar_average_motor);
    motor_sequence<3,3> test
    {{
         motor_state<3>{{1,0,0}},
         motor_state<3>{{0,1,0}},
         motor_state<3>{{0,0,1}},
     }};

    auto cycler = make_cyclic_iterator(std::begin(test), std::end(test));
    motor_state<3>& current = *cycler.get_current();
    std::cout << "set = " << std::endl;
    for(auto x : test)
    {
        print_motor_state<3>(x);
    }
    std::cout << std::endl;

    std::cout << "current = ";
    print_motor_state<3>(current);

    std::cout << "Forward:" << std::endl;
    for(int i = 0; i < 20; ++i)
    {
        auto current_state = *cycler.get_current();
        print_motor_state<3>(current_state);
        cycler++;
    }

    std::cout << std::endl << "Backward:" << std::endl;
    for(int i = 0; i < 20; ++i)
    {
        auto current_state = *cycler.get_current();
        print_motor_state<3>(current_state);
        //cycler.previous();
        //cycler -= 2;
        cycler--;
    }

    std::cout << "set = " << std::endl;
    for(auto x : test)
    {
        print_motor_state<3>(x);
    }
    std::cout << std::endl;

    return 0;
}
