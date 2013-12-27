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

