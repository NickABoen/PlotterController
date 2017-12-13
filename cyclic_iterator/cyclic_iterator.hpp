#ifndef CYCLIC_ITERATOR_HPP
#define CYCLIC_ITERATOR_HPP

#include <iterator>

/** cyclic_iterator
 * Template for any valid bidirectional iterator that manages functionality for
 * connecting the beginning and end of the iterator as if the end was an
 * adjacent element to the beginning when stepping forward and vice-versa when
 * stepping backward. 
 */
template <class Iterator>
struct cyclic_iterator
{
    private:
        /**
         * The reference iterator that is currently being pointed to
         */
        Iterator m_current;

        /**
         * The reference iterator that marks the beginning of the sequence
         */
        Iterator m_begin;

        /**
         * The reference iterator that marks the end of the sequence
         */
        Iterator m_end;

    public:
        /** General Constructor
         * Constructs a cyclic_iterator when given a full definition of it
         *
         * @param it    Iterator reference to where the cyclic_iterator should 
         *              start
         * @param begin Iterator reference to the beginning of the cycle
         * @param end   Iterator reference to the end of the cycle
         */
        cyclic_iterator(Iterator it, Iterator begin, Iterator end):
            m_current(it),
            m_begin(begin),
            m_end(end)
        {}

        /** Default Value Constructor
         * Constructs a cyclic_iterator with its current iterator reference
         * pointed to the beginning of the sequence defined by begin and end
         *
         * @param begin Iterator reference to the beginning of the cycle
         * @param end   Iterator reference to the end of the cycle
         */
        cyclic_iterator(Iterator begin, Iterator end):
            cyclic_iterator(begin, begin, end)
        {}

        /** Copy Constructor
         * Copies the Iterator references from the existing cyclic_iterator
         *
         * @param other cyclic_iterator whose values should be copied
         */
        cyclic_iterator(const cyclic_iterator<Iterator>& other):
            cyclic_iterator(other.m_current, other.m_begin, other.m_end)
        {}

        /** Move Constructor
         * Moves the Iterator references from the existing r-value
         * cyclic_iterator
         *
         * @param other cyclic_iterator r-value reference to move values from
         */
        cyclic_iterator(cyclic_iterator<Iterator>&& other):
            cyclic_iterator(other.m_current, other.m_begin, other.m_end)
        {}

        /** next
         * Steps the current iterator reference to the next iterator reference.
         * If at the end of the sequence, the current iterator will reference
         * the beginning of the sequence
         */
        void next();

        /** previous
         * Steps the current iterator reference to the previous iterator 
         * referenc. If at the beginning of the sequence, the current iterator
         * will reference the last element before the end of the sequence
         */
        void previous();

        /** get_current 
         * Retrieves the current iterator reference for external use
         * 
         * @return  iterator reference this cyclic_iterator is currently
         *          pointing to
         */
        Iterator get_current();

        /*--------------------------------------------------------------------*/
        /*-------------------------Operator Overloads-------------------------*/
        /*--------------------------------------------------------------------*/
        
        /** Operator += 
         * Steps forward through the given number of elements in the sequence
         *
         * @param amount    Number of steps to make
         * @return          reference to this cyclic_iterator
         */
        cyclic_iterator<Iterator>& operator+=(unsigned int amount);

        /** Operator -=
         * Steps backward through the given number of elements in the sequence
         *
         * @param amount    Number of steps to make
         * @return          reference to this cyclic_iterator
         */
        cyclic_iterator<Iterator>& operator-=(unsigned int amount);

        /** Prefix Operator ++
         * Steps forward by a single step in the sequence, wrapping as
         * necessary. Same as cyclic_iterator::next()
         *
         * @return  reference to this cyclic_iterator
         */
        cyclic_iterator<Iterator>& operator++();

        /** Prefix Operator --
         * Steps backward by a single step in the sequence, wrapping as
         * necessary. Same as cyclic_iterator::previous()
         *
         * @return  reference to this cyclic_iterator
         */
        cyclic_iterator<Iterator>& operator--();

        /** Postfix Operator ++
         * Steps forward by a single step in the sequence, wrapping as 
         * necessary. Similar to cyclic_iterator::next()
         *
         * @return Copy of this cyclic_iterator before the step is made
         */
        cyclic_iterator<Iterator> operator++(int);

        /** Postfix Operator --
         * Steps backward by a single step in the sequence, wrapping as 
         * necessary. Similar to cyclic_iterator::previous()
         *
         * @return Copy of this cyclic_iterator before the step is made
         */
        cyclic_iterator<Iterator> operator--(int);
};

/** make_cyclic_iterator
 * Template inference method that allows for the construction of a
 * cyclic_iterator without the need to explicitly list it's template
 * type arguments
 *
 * @param begin Iterator reference to the beginning of the sequence
 * @param end   Iterator reference to the end of the sequence
 * @return      Newly constructed cyclic_iterator based on inferred Iterator
 *              type
 */
template <class Iterator>
cyclic_iterator<Iterator> make_cyclic_iterator(Iterator begin, Iterator end)
{
    return cyclic_iterator<Iterator>(begin, end);
}

/*****************************************************************************/
/*                      Member Function Implementation                       */
/*****************************************************************************/
template <class Iterator>
void cyclic_iterator<Iterator>::next()
{
    std::advance(m_current, 1);
    if(m_current == m_end)
    {
        std::advance(m_current, std::distance(m_end, m_begin));
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

template <class Iterator>
cyclic_iterator<Iterator>& cyclic_iterator<Iterator>::operator+=(unsigned int amount)
{
    for(unsigned int i = 0; i < amount; i++)
    {
        next();
    }
    return *this;
}

template <class Iterator>
cyclic_iterator<Iterator>& cyclic_iterator<Iterator>::operator-=(unsigned int amount)
{
    for(unsigned int i = 0; i < amount; i++)
    {
        previous();
    }
    return *this;
}

template <class Iterator>
cyclic_iterator<Iterator>& cyclic_iterator<Iterator>::operator++()
{
    return (*this) += 1;
}

template <class Iterator>
cyclic_iterator<Iterator>& cyclic_iterator<Iterator>::operator--()
{
    return (*this) -= 1;
}

template <class Iterator>
cyclic_iterator<Iterator> cyclic_iterator<Iterator>::operator++(int)
{
    cyclic_iterator<Iterator> new_cycle(*this);
    next();
    return new_cycle;
}

template <class Iterator>
cyclic_iterator<Iterator> cyclic_iterator<Iterator>::operator--(int)
{
    cyclic_iterator<Iterator> new_cycle(*this);
    previous();
    return new_cycle;
}
#endif
