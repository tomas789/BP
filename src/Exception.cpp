#include "Exception.hpp"

const char * NullPtrDereferenceException::what() const noexcept {
    return "Dereferencing nullptr";
}

