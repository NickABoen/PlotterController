#ifndef STEPPER_HPP
#define STEPPER_HPP
#pragma once

#include <ratio>
#include <vector>
#include <memory>

#include "wiringPiContext.hpp"
#include "units.hpp"
#include "stepper_coil.hpp"

namespace plotter{

    /**
     * Represents a single stepper motor and the necessary interface for
     * controlling it.
     *
     * @author Nick Boen
     * @version 0.1
     * @since 03-10-2018
     */
    class stepper{
        //Members
        public:
        private:

            /**
             * The coil configuration and state for this stepper motor
             */
            std::unique_ptr<stepper_coil> m_coil;

            /**
             * Reconfigurable step resolution
             */
            const double m_steps_per_millimeter;

            /**
             * Current step this stepper motor is at
             */
            int m_current_step;

            /**
             * Current target step this stepper motor is trying to get to
             */
            int m_target_step;

            /**
             * Marks homing as a special state of the stepper to continue
             * in a single direction until a limit switch is hit
             */
            bool m_is_homing;

        //Interface
        public:
            
            /**
             * Basic initialization of a stepper motor
             *
             * @param coil: coil configuration that this stepper owns
             * @param steps_per_mm: movement resolution of this stepper
             */
            stepper(std::unique_ptr<stepper_coil> coil, double steps_per_mm)
                :   m_coil(std::move(coil)),
                    m_steps_per_millimeter(steps_per_mm),
                    m_is_homing(false){}

            /**
             * Initialization of stepper motor
             *
             * @param R: static Ratio representing the step resolution
             * @param coil: coil configuration that this stepper owns
             */
            template<class R=std::ratio<1>>
            stepper(std::unique_ptr<stepper_coil> coil)
                :stepper(coil, R::num/R::den){}

            /**
             * Set the target this stepper should move towards
             *
             * @param target_step: absolute position to move to in steps
             */
            void set_target(step target_step);

            /**
             * Teleport the stepper position to the given step without 
             * actuating the stepper motor
             *
             * @param target_step: step value to teleport to
             */
            void teleport(step target_step);

            /**
             * Stop actuating the stepper motor on the next tick
             */
            void stop();

            /**
             * Set the stepper in homing mode where it'll move toward the home
             * positions until stepper::stop() is called
             */
            void home();

            /**
             * Tick function for the stepper motor. The stepper will move
             * towards its target position each time this is called. Intended
             * for use in a process loop to syncronize multiple steppers.
             */
            void tick();

        //Templates
        public:

            /**
             * Set the target this stepper should move towards. Converts
             * the travel resolution to steps
             *
             * @param R: Ratio of travel unit relative to meters
             * @param target_position: travel position and unit to move to
             */
            template<class R>
            void set_target(travel<R> target_position){
                double target_mm = convert<R,std::milli>(target_position.value);
                set_target(target_mm * m_steps_per_millimeter);
            }

            /**
             * Teleport the stepper position to the given travel value without
             * actuating the stepper motor. Automatically converts travel unit
             * into steps
             *
             * @param R: Ratio of travel unit relative to meters
             * @param target_position: travel position and unit to teleport to
             */
            template<class R>
            void teleport(travel<R> target_position){
                double new_position = convert<R, std::milli>(target_position.value);
                teleport(new_position * m_steps_per_millimeter);
            }

        private:

            /**
             * Directly sets the member target value. Base function call for
             * the other set_target functions
             *
             * @param step: step to target
             */
            void set_target(int step);

            /**
             * Directly sets the member stepper position. Base function call
             * for the other teleport functions
             *
             * @param step: step to set position to 
             */
            void teleport(int step);
    };
}

#endif
