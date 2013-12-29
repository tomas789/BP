#include <gtest/gtest.h>

#include "Type.hpp"

TEST(Type, TypeAndItsDerivates) {
    Type * fp = new FPType;
    Type * fp_2 = new FPType;

    // Test bool Type::operator== (const Type &) const;
    ASSERT_EQ(*fp, *fp_2);

    // Test virtual TypeHandle TypeHandle::Clone() const
    TypeHandle fp_clone = fp->Clone();
    ASSERT_EQ(*fp_clone, *fp);
    ASSERT_NE(fp_clone.operator-> (), fp);

    // Test virtual std::string TypeHandle::ToString() const
    ASSERT_STREQ("FloatingPoint", fp_clone->ToString().c_str());
}

TEST(TypeHandle, Equal) {
    TypeHandle fp = FPType::get();
    TypeHandle bo = BoolType::get();
    TypeHandle vfp3 = VectorType::get(FPType::get(), 3);
    TypeHandle vfp3_2 = VectorType::get(FPType::get(), 3);
    TypeHandle vfp4 = VectorType::get(FPType::get(), 4);
    TypeHandle vbo4 = VectorType::get(BoolType::get(), 4);

    ASSERT_EQ(fp, fp);
    ASSERT_NE(fp, bo);
    ASSERT_NE(vfp3, vfp4);
    ASSERT_NE(vbo4, vfp4);
    ASSERT_EQ(vfp3, vfp3_2);
}

TEST(Type, TypeHandle) {
    Type * fp_ptr = new FPType;

    // Testing TypeHandle::TypeHandle(Type * t)
    TypeHandle fp(fp_ptr);
    ASSERT_EQ(fp_ptr, fp.operator->());

    // Testing TypeHandle::TypeHandle(const TypeHandle & t)
    TypeHandle fp2(fp);
    ASSERT_EQ(fp, fp2);

    // Testing TypeHandle::TypeHandle(TypeHandle && t)
    TypeHandle fp3(std::move(fp2));
    ASSERT_EQ(fp, fp3);
}

TEST(Type, FunctionType) {
    TypeHandle fp = FPType::get();
    TypeHandle bo = BoolType::get();

    std::vector<TypeHandle> args;
    args.push_back(FPType::get());

    std::vector<TypeHandle> args2;
    args2.push_back(BoolType::get());

    TypeHandle f1 = FunctionType::get(fp, args);
    TypeHandle f2 = FunctionType::get(fp, args);

    ASSERT_EQ(f1, f2);
    ASSERT_EQ(f1, FunctionType::get(FPType::get(), args));
}

TEST(Type, FunctionType_ToString) {
    std::vector<TypeHandle> args;
    args.push_back(std::move(BoolType::get()));
    TypeHandle f1 = FunctionType::get(FPType::get(), args);
    ASSERT_STREQ("FloatingPoint(Bool)", f1->ToString().c_str());

    TypeHandle f2 = FunctionType::get(BoolType::get(), args);
    ASSERT_STREQ("Bool(Bool)", f2->ToString().c_str());

    std::vector<TypeHandle> args2;
    args2.push_back(FPType::get());
    args2.push_back(BoolType::get());
    TypeHandle f3 = FunctionType::get(FPType::get(), args2);
    ASSERT_STREQ("FloatingPoint(FloatingPoint,Bool)", f3->ToString().c_str());
}

TEST(Type, ConvertingTypeToString) {
    TypeHandle fp = FPType::get();
    ASSERT_STREQ("FloatingPoint", fp->ToString().c_str());

    TypeHandle bo = BoolType::get();
    ASSERT_STREQ("Bool", bo->ToString().c_str());

    TypeHandle vfp = VectorType::get(FPType::get(), 3);
    ASSERT_STREQ("[FloatingPoint;3]", vfp->ToString().c_str());

    TypeHandle vbo = VectorType::get(BoolType::get(), 4);
    ASSERT_STREQ("[Bool;4]", vbo->ToString().c_str());
}

