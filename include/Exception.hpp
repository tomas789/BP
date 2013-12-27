#ifndef _EXCEPTION_HPP
#define _EXCEPTION_HPP

#include <exception>

class NullPtrDereferenceException : public virtual std::exception {
public:
    const char * what() const noexcept;

    virtual ~NullPtrDereferenceException() = default;
};

#endif // _EXCEPTION_HPP
