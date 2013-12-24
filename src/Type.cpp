#include "Type.hpp"

bool Type::operator== (const Type & other) const {
    if (typeid(*this) != typeid(other))
        return false;

    return Equal(other);
}

SimpleType::~SimpleType() { }

CompositeType::~CompositeType() { }

bool FPType::Equal(const Type & other) const {
    return true;
}

Handle<Type> FPType::Clone() const {
    return Handle<Type>(new FPType);
}

std::string FPType::ToString() const {
    return "FloatingPoint";
}

FPType::~FPType() { }

bool BoolType::Equal(const Type & other) const {
    return true;
}

Handle<Type> BoolType::Clone() const {
    return Handle<Type>(new BoolType);
}

std::string BoolType::ToString() const {
    return "Bool";
}

BoolType::~BoolType() { }

bool VectorType::Equal(const Type & other) const {
    return *t_ == static_cast<const VectorType &>(other);
}

VectorType::VectorType(Handle<Type> && t, size_type n)
    : t_(std::move(t)), n_(n) { }

Handle<Type> VectorType::Clone() const {
    return Handle<Type>(new VectorType(std::move(t_->Clone()), n_));
}

std::string VectorType::ToString() const {
    return "[" + t_->ToString() + "]";
}

VectorType::~VectorType() { }

IncompatibileTypesException::IncompatibileTypesException(
        Handle<Type> && expected,
        Handle<Type> && actual) {
    msg_ = "Incompatibile types: " + expected->ToString() + ", " + actual->ToString();
}

IncompatibileTypesException::IncompatibileTypesException(
        IncompatibileTypesException && e) noexcept
    : msg_(std::move(e.msg_)) { }

IncompatibileTypesException::IncompatibileTypesException(
        const IncompatibileTypesException & e)
    : msg_(e.msg_) { }

const char * IncompatibileTypesException::what() const noexcept {
    return msg_.c_str();
}

IncompatibileTypesException::~IncompatibileTypesException() { }
    
