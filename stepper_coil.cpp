#include <vector>
#include "stepper_coil.hpp"

namespace plotter{
/******************************************************************************/
/*                          Private Member Functions                          */
/******************************************************************************/
    const stepper_coil::coil_state& stepper_coil::get_current_state() const{
        return m_coil_states.at(m_state_index);
    }


    void stepper_coil::apply_state(const coil_state& state){
        for(unsigned long i = 0; i < state.size(); i++){
            m_wiring_pi_context->write(m_coil_pins.at(i), state.at(i));
        }
    }


    bool stepper_coil::is_state_index_valid(unsigned int index){
        return (index < m_coil_states.size());
    }


/******************************************************************************/
/*                               Public Interface                             */
/******************************************************************************/
    stepper_coil::stepper_coil(
            std::shared_ptr<plotter::context>& wiring_pi_context,
            std::vector<plotter::pin> pins,
            std::vector<coil_state> states,
            unsigned int starting_index) :m_wiring_pi_context(wiring_pi_context),
    m_coil_pins(pins),
    m_coil_states(states),
    m_state_index(starting_index){}


    void stepper_coil::enable(){
        apply_state(get_current_state());
    }


    void stepper_coil::disable(){
        const coil_state& current_state = get_current_state();
        coil_state zero_state{current_state.size(), false};
        apply_state(zero_state);
    }


    void stepper_coil::forward(){
        m_state_index++;
        if(!is_state_index_valid(m_state_index)){
            m_state_index = 0;
        }
        enable();
    }


    void stepper_coil::backward(){
        m_state_index--;
        if(!is_state_index_valid(m_state_index)){
            m_state_index = m_coil_states.size()-1;
        }
        enable();
    }


    void stepper_coil::set_state(unsigned int new_state_index){
        if(is_state_index_valid(new_state_index)){
                m_state_index = new_state_index;
                enable();
        }
    }

}
