#include <string>
#include <utility>
#include <vector>

#include "Exception.hpp"
#include "Type.hpp"

TypeHandle::TypeHandle(Type * t) { 
    if (!t)
        throw NullPtrDereferenceException();

    t_ = t;
}

TypeHandle::TypeHandle(const TypeHandle & t) {
    *this = t;
}

TypeHandle::TypeHandle(TypeHandle && t) {
    *this = std::move(t);
}

TypeHandle::TypeHandle(std::unique_ptr<Type> && t)
    : t_(t.release()) { }

TypeHandle & TypeHandle::operator= (const TypeHandle & other) {
    *this = std::move(other->Clone());
    return *this;
}

TypeHandle & TypeHandle::operator= (TypeHandle && other) {
    t_ = nullptr;
    std::swap(t_, other.t_);
    return *this;
}

bool TypeHandle::operator== (const TypeHandle & other) const {
    if (!t_)
        throw NullPtrDereferenceException();

    return *t_ == *other.t_;
}

bool TypeHandle::operator!= (const TypeHandle & other) const {
    return !(*this == other);
}

TypeHandle::operator std::string() const {
    return t_->ToString();
}

Type * TypeHandle::operator-> () {
    return t_;
}

const Type * TypeHandle::operator-> () const {
    return t_;
}

Type & TypeHandle::operator* () {
    return *t_;
}

const Type & TypeHandle::operator* () const {
    return *t_;
}

TypeHandle::~TypeHandle() {
    delete t_;
}

bool Type::operator== (const Type & other) const {
    if (typeid(*this) != typeid(other))
        return false;

    return Equal(other);
}

bool FunctionType::Equal(const Type & other) const {
    const FunctionType & f = static_cast<const FunctionType &>(other);
    return RetVal_ == f.RetVal_ && Args_ == f.Args_;
}

FunctionType::FunctionType(TypeHandle && RetVal, std::vector<TypeHandle> && Args)
    : RetVal_(std::move(RetVal)), Args_(std::move(Args)) { }

TypeHandle FunctionType::Clone() const {
    TypeHandle NewRetVal = RetVal_->Clone();
    std::vector<TypeHandle> NewArgs;
    for (auto & a : Args_)
        NewArgs.push_back(std::move(a->Clone()));

    return TypeHandle(new FunctionType(std::move(NewRetVal), std::move(NewArgs)));
}

std::string FunctionType::ToString() const {
    std::string str;

    str = RetVal_->ToString();
    
    str += "(";
    for (auto it = Args_.begin();; ++it) {
        str += (*it)->ToString();
        if (it + 1 != Args_.end())
            str += ",";
        else
            break;
    }

    return str += ")";
}

TypeHandle FunctionType::get(TypeHandle && RetVal, std::vector<TypeHandle> && Args) {
    return TypeHandle(new FunctionType(std::move(RetVal), std::move(Args)));
}

TypeHandle FunctionType::get(const TypeHandle & RetVal, const std::vector<TypeHandle> & Args) {
    std::vector<TypeHandle> NewArgs;

    for (auto & a : Args)
        NewArgs.push_back(std::move(a->Clone()));

    return std::move(FunctionType::get(std::move(RetVal->Clone()), std::move(NewArgs)));
}

bool FPType::Equal(const Type & other) const {
    return true;
}

TypeHandle FPType::Clone() const {
    return TypeHandle(new FPType);
}

std::string FPType::ToString() const {
    return "FloatingPoint";
}

TypeHandle FPType::get() {
    return TypeHandle(new FPType);
}

bool BoolType::Equal(const Type & other) const {
    return true;
}

TypeHandle BoolType::Clone() const {
    return TypeHandle(new BoolType);
}

std::string BoolType::ToString() const {
    return "Bool";
}

TypeHandle BoolType::get() {
    return TypeHandle(new BoolType);
}

bool VectorType::Equal(const Type & other) const {
    const VectorType & v = static_cast<const VectorType &>(other);
    return *t_ == *v.t_ && n_ == v.n_;
}

VectorType::VectorType(TypeHandle && t, size_type n)
    : t_(std::move(t)), n_(n) { }

TypeHandle VectorType::Clone() const {
    return TypeHandle(new VectorType(std::move(t_->Clone()), n_));
}

std::string VectorType::ToString() const {
    return "[" + t_->ToString() + ";" + std::to_string(n_) + "]";
}

TypeHandle VectorType::get(TypeHandle && t, size_type n) {
    return TypeHandle(new VectorType(std::move(t), n));
}

IncompatibileTypesException::IncompatibileTypesException(
        TypeHandle && expected,
        TypeHandle && actual) {
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

