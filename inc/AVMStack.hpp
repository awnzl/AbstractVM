#ifndef __AVMSTACK_HPP
# define __AVMSTACK_HPP

# include <iostream>
# include <stack>

template<typename T> class AVMStack : public std::stack<T> {
public:
    typedef typename std::stack<T>::container_type::reverse_iterator iterator;
    AVMStack<T>() : std::stack<T>() {
    }
    
    ~AVMStack<T>() {
    }
    
    AVMStack<T>(AVMStack<T> const & src) : std::stack<T>(src) {
    }
    
    iterator begin() {
        return std::stack<T>::c.rbegin();
    }
    
    iterator end() {
        return std::stack<T>::c.rend();
    }
};

#endif