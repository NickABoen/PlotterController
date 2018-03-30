#pragma once
#ifndef STEPPER_COIL_HPP
#define STEPPER_COIL_HPP

#include <vector>
#include <memory>

#include "wiringPiContext.hpp"
#include "units.hpp"

namespace plotter{

    /**
     * Represents the configuration and state of a set of stepper coils.
     * This allows the separation of the soft concept of a stepper and the
     * hardware itself.
     */
    struct stepper_coil{
        //Types
        public:

            /**
             * Coils can either be on or off, and most steppers have multiple
             * coils. These coils can be enabled in various combinations to
             * achieve different configurations of torque and angular velocity
             */
            using coil_state = std::vector<plotter::bool_t>;

        //Member Variables
        private:
            /**
             * Valid context to the wiring pi library. This also allows for
             * a default library interface for simulation or adapting to an
             * alternative library
             */
            std::shared_ptr<plotter::context> m_wiring_pi_context;

            /**
             * A vector with the same size as the number of coils this 
             * configuration represents that maps the coil to a specific GPIO
             * pin.
             */
            std::vector<plotter::pin> m_coil_pins;

            /**
             * The sequential states that the coils, as a set, can have. 
             * This will be stepped through as the stepper_coil is instructed
             * to step forward and backward.
             */
            std::vector<coil_state> m_coil_states;

            /**
             * The index of the current state that this stepper_coil is at
             * that reflects the state of the coils it governs as defined
             * by m_coil_pins
             */
            unsigned int m_state_index;

        //Private Member Functions
        private:

            /**
             * Retrieve the current coil state of this stepper_coil 
             *
             * @return: current coil state of these stepper coils
             */
            const coil_state& get_current_state() const;

            /**
             * Apply the given state to the hardware that this stepper_coil 
             * is connected to via the wiring_pi context
             *
             * @param state: coil state to apply to the hardware coils
             */
            void apply_state(const coil_state& state);

            /**
             * Checks if the current index is a valid index into the set of 
             * coil states
             *
             * @param index: index to check
             * @return: true if the index is valid, false otherwise.
             */
            bool is_state_index_valid(unsigned int index);

        //Public Interface
        public:

            /**
             * Initialize stepper_coil with the hardware context, pins that
             * it connects to, and the states that it governs
             *
             * @param wiring_pi_context: hardware interface
             * @param pins: Set of GPIO pins that each coil connects to
             * @param states: Ordered set of states that this stepper_coil 
             *                iterates through
             * @param starting_index: Optional index to initialize the stepper
             *                        to
             */
            stepper_coil(
                    std::shared_ptr<plotter::context>& wiring_pi_context,
                    std::vector<plotter::pin> pins,
                    std::vector<coil_state> states,
                    unsigned int starting_index=0);

            /**
             * Applies the current state of the stepper, enables the stepper
             * if previously disabled
             */
            void enable();

            /**
             * Clears the coils and disengages the stepper. This will prevent
             * the stepper from growing hot while maintaining a constant state,
             * but will also allow the motor to slip
             */
            void disable();

            /**
             * Step the coils forward in the set of coil states
             */
            void forward();

            /**
             * Step the coils backward in the set of coil states
             */
            void backward();

            /**
             * Explicitly change the coil state to the given index
             *
             * @param new_state_index: state to set the coils to
             */
            void set_state(unsigned int new_state_index);
    };
}

#endif
