#ifndef CYCLIC_ITERATOR_TPP
#define CYCLIC_ITERATOR_TPP

template <class Iterator>
void cyclic_iterator<Iterator>::next()
{
    std::advance(m_current, 1);
    if(m_current == m_end)
    {
        m_current = m_begin;
    }
}

template <class Iterator>
void cyclic_iterator<Iterator>::previous()
{
    if(m_current == m_begin)
    {
        m_current = std::prev(m_end);
    }
    else
    {
        std::advance(m_current, -1);
    }
}

template <class Iterator>
Iterator cyclic_iterator<Iterator>::get_current()
{ 
    return m_current;
}

cyclic_iterator<Iterator>& operator

#endif
