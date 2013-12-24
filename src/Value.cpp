#include "Value.hpp"

FPValue::FPValue(double val)
    : val_(val) { }

FPValue::FPValue(const FPValue & v)
    : val_(v.val_) { }

Handle<Type> FPValue::GetType() const {
    return Handle<Type>(new FPType);
}

Handle<Value> FPValue::Clone() const {
    return Handle<Value>(new FPValue(*this));
}

BoolValue::BoolValue(bool val)
    : val_(val) { }

BoolValue::BoolValue(const BoolValue & v)
    : val_(v.val_) { }

Handle<Type> BoolValue::GetType() const {
    return Handle<Type>(new BoolType);
}

Handle<Value> BoolValue::Clone() const {
    return Handle<Value>(new BoolValue(*this));
}

VectorValue::VectorValue(Handle<Type> && t, std::vector<Handle<Value> > && vals)
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
    : t_(std::move(v.t_->Clone())) {
    for (auto & val : v.vals_)
        vals_.push_back(std::move(val->Clone()));
}

Handle<Type> VectorValue::GetType() const {
    return Handle<Type>(new VectorType(std::move(t_->Clone()), Size()));
}

Handle<Value> VectorValue::Clone() const {
    return Handle<Value>(new VectorValue(*this));
}

size_type VectorValue::Size() const {
    return vals_.size();
}
