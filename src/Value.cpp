#include <utility>
#include <string>

#include "Exception.hpp"
#include "Value.hpp"

ValueHandle::ValueHandle(Value * v) {
    if (!v) 
        throw NullPtrDereferenceException();
    v_ = v;
}

ValueHandle::ValueHandle(const ValueHandle & v) {
    *this = v;
}

ValueHandle::ValueHandle(ValueHandle && v) {
    *this = std::move(v);
}

Value & ValueHandle::operator* () {
    return *v_;
}

const Value & ValueHandle::operator* () const {
    return *v_;
}

Value * ValueHandle::operator-> () {
    return v_;
}

const Value * ValueHandle::operator-> () const {
    return v_;
}

ValueHandle & ValueHandle::operator= (const ValueHandle & v) {
    *this = std::move(v->Clone());
    return *this;
}

ValueHandle & ValueHandle::operator= (ValueHandle && v) {
    swap(v);
    return *this;
}

void ValueHandle::swap(ValueHandle & v) {
    std::swap(v_, v.v_);
}

ValueHandle::~ValueHandle() {
    delete v_;
}

FPValue::FPValue(double val)
    : val_(val) { }

FPValue::FPValue(const FPValue & v)
    : val_(v.val_) { }

TypeHandle FPValue::GetType() const {
    return TypeHandle(new FPType);
}

ValueHandle FPValue::Clone() const {
    return ValueHandle(new FPValue(*this));
}

BoolValue::BoolValue(bool val)
    : val_(val) { }

BoolValue::BoolValue(const BoolValue & v)
    : val_(v.val_) { }

TypeHandle BoolValue::GetType() const {
    return TypeHandle(new BoolType);
}

ValueHandle BoolValue::Clone() const {
    return ValueHandle(new BoolValue(*this));
}

VectorValue::VectorValue(TypeHandle && t, std::vector<ValueHandle > && vals)
    : t_(std::move(t)) {

    for (size_type i = 0; i < vals.size(); ++i) {
        if (*t_ == *vals[i]->GetType())
            vals_.push_back(std::move(vals[i]));
        else 
            throw IncompatibileTypesException(
                    std::move(t_->Clone()), 
                    std::move(vals[i]->GetType()));
    }
}

VectorValue::VectorValue(const VectorValue & v)
    : t_(v.t_) {
    for (auto & val : v.vals_)
        vals_.push_back(std::move(val->Clone()));
}

TypeHandle VectorValue::GetType() const {
    return TypeHandle(new VectorType(std::move(t_->Clone()), Size()));
}

ValueHandle VectorValue::Clone() const {
    return ValueHandle(new VectorValue(*this));
}

size_type VectorValue::Size() const {
    return vals_.size();
}
