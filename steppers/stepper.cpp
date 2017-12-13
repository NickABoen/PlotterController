#include "stepper.hpp"
#include <iterator>

template <int StateCount, int PinCount>
int sequence_instance<StateCount, PinCount>::get_current_step() 
{
    return m_current_step;
}

template <int StateCount, int PinCount>
void sequence_instance<StateCount, PinCount>::set_current_step(int new_step)
{
    m_current_step = new_step;
}

template <int StateCount, int PinCount>
int sequence_instance<StateCount, PinCount>::get_target_step()
{
    return m_target_step;
}

template <int StateCount, int PinCount>
void sequence_instance<StateCount, PinCount>::set_target_step(int new_target_step)
{
    m_target_step = new_target_step;
}

template <int StateCount, int PinCount>
void sequence_instance<StateCount, PinCount>::step()
{
    if(m_current_step != m_target_step)
    {
        int direction = (m_current_step < m_target_step) ? 1 : -1;
        m_current_sequence += direction;
        m_current_step += direction;
    }
}
