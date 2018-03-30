#include "stepper.hpp"

#include <ratio>
#include <memory>
#include <vector>
#include <iostream>

namespace plotter{

    /**
     * Set the target this stepper should move towards
     *
     * @param target_step: absolute position to move to in steps
     */
    void stepper::set_target(step target_step){
        set_target(target_step.value);
    }

    /**
     * Directly sets the member target value. Base function call for
     * the other set_target functions
     *
     * @param step: step to target
     */
    void stepper::set_target(int step){
        m_target_step = step;
    }

    /**
     * Teleport the stepper position to the given step without 
     * actuating the stepper motor
     *
     * @param target_step: step value to teleport to
     */
    void stepper::teleport(step target_step){
        teleport(target_step.value);
    }

    /**
     * Directly sets the member stepper position. Base function call
     * for the other teleport functions
     *
     * @param step: step to set position to 
     */
    void stepper::teleport(int step){
        m_current_step = step;
    }

    /**
     * Stop actuating the stepper motor on the next tick
     */
    void stepper::stop(){
        m_is_homing = false;
        m_target_step = m_current_step;
    }

    /**
     * Set the stepper in homing mode where it'll move toward the home
     * positions until stepper::stop() is called
     */
    void stepper::home(){
        m_is_homing = true;
    }

    /**
     * Tick function for the stepper motor. The stepper will move
     * towards its target position each time this is called. Intended
     * for use in a process loop to syncronize multiple steppers.
     */
    void stepper::tick(){
        if(m_is_homing || m_target_step < m_current_step){
            m_coil->backward();
            m_current_step--;
        }
        else if(m_target_step > m_current_step){
            m_coil->forward();
            m_current_step++;
        }
    }

};
