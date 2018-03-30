#ifndef STEPPER_HPP
#define STEPPER_HPP

/**
 *  Stepper motor library for interfacing between software and a physical motor
 */

#include "../wiringPiContext.hpp"

#include "../i_wiringPi.hpp"
#include "../cyclic_iterator/cyclic_iterator.hpp"
#include <array>

template <int PinCount>
using motor_state = std::array<int, PinCount>;

template <int StateCount, int PinCount>
using motor_sequence = std::array<motor_state<PinCount>, StateCount>;

const motor_sequence<4,4> bipolar_average_motor
{{
    motor_state<4>{{1,0,0,0}},
    motor_state<4>{{0,1,0,0}},
    motor_state<4>{{0,0,1,0}},
    motor_state<4>{{0,0,0,1}}
 }};

const motor_sequence<4,4> bipolar_high_torgue_motor
{{
    motor_state<4>{{1,1,0,0}},
    motor_state<4>{{0,1,1,0}},
    motor_state<4>{{0,0,1,1}},
    motor_state<4>{{1,0,0,1}}
 }};

const motor_sequence<8,4> bipolar_high_res_motor
{{
    motor_state<4>{{1,0,0,0}},
    motor_state<4>{{1,1,0,0}},
    motor_state<4>{{0,1,0,0}},
    motor_state<4>{{0,1,1,0}},
    motor_state<4>{{0,0,1,0}},
    motor_state<4>{{0,0,1,1}},
    motor_state<4>{{0,0,0,1}},
    motor_state<4>{{1,0,0,1}}
 }};

class sequence_interface
{
    public:
        /** Default virtual destructor for proper memory management */
        virtual ~sequence_interface()=default;

        /**
         * Get the value of the current step this stepper is on
         *
         * @return value of the current step
         */
        virtual int get_current_step() = 0;
        /**
         * Override the current step value, this effectively "relocates" the
         * stepper motor without actually moving it.
         *
         * @param new_value new position of the stepper motor
         */
        virtual void set_current_step(int new_value) = 0;

        /**
         * Get the target step that this stepper is trying to get to.
         * Can be positive or negative
         *
         * @return value of the current target step
         */
        virtual int get_target_step() = 0;
        /**
         * Set the current target of this stepper motor. Every time it is
         * stepped it will move the current_step toward this value;
         */
        virtual void set_target_step(int new_value) = 0;

        virtual int get_target_step_difference(){
            return get_target_step() - get_current_step();
        }

        virtual void step() = 0;
};

template <int StateCount, int PinCount>
class sequence_instance : public sequence_interface
{
    using motor_iterator = cyclic_iterator<motor_sequence<StateCount,PinCount>>;
    private:
        int m_current_step;
        int m_target_step;
        const motor_sequence<StateCount, PinCount> m_sequence;
        motor_iterator m_current_sequence;

    public:
        sequence_instance() = delete;
        sequence_instance(const motor_sequence<StateCount,PinCount> sequence)
            : m_current_step(0), m_sequence(sequence), 
            m_current_sequence(make_cyclic_iterator(std::begin(m_sequence), std::end(m_sequence))){}

        sequence_instance(motor_sequence<StateCount,PinCount>&& sequence)
            : m_current_step(0), m_sequence(sequence),m_current_sequence(
                    make_cyclic_iterator(std::begin(m_sequence), std::end(m_sequence)))
        {}

        //sequence_interface implementation
        virtual int get_current_step() override;
        virtual void set_current_step(int new_step) override;
        virtual int get_target_step() override;
        virtual void set_target_step(int new_target_step) override;
        virtual void step() override;
};
#endif
