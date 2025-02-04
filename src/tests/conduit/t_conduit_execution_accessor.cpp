// Copyright (c) Lawrence Livermore National Security, LLC and other Conduit
// Project developers. See top-level LICENSE AND COPYRIGHT files for dates and
// other details. No copyright assignment is required to contribute to Conduit.

//-----------------------------------------------------------------------------
///
/// file: conduit_array.cpp
///
//-----------------------------------------------------------------------------

#include "conduit.hpp"

#include <iostream>
#include "gtest/gtest.h"

using namespace conduit;

// TODO we should have tests for data array, exec acc/arr, and setters that go between all four

//-----------------------------------------------------------------------------
TEST(conduit_exec_accessor, value)
{

    Node n;
    n.set((int8)10);

    int8_exec_accessor  i8_acc(n);
    int16_exec_accessor i16_acc(n);
    int32_exec_accessor i32_acc(n);
    int64_exec_accessor i64_acc(n);

    uint8_exec_accessor  ui8_acc(n);
    uint16_exec_accessor ui16_acc(n);
    uint32_exec_accessor ui32_acc(n);
    uint64_exec_accessor ui64_acc(n);
    
    
    float32_exec_accessor f32_acc(n);
    float64_exec_accessor f64_acc(n);
    
    EXPECT_EQ(i8_acc[0],(int8)(10));
    EXPECT_EQ(i16_acc[0],(int16)(10));
    EXPECT_EQ(i32_acc[0],(int32)(10));
    EXPECT_EQ(i64_acc[0],(int64)(10));
    
    
    EXPECT_EQ(ui8_acc[0],(uint8)(10));
    EXPECT_EQ(ui16_acc[0],(uint16)(10));
    EXPECT_EQ(ui32_acc[0],(uint32)(10));
    EXPECT_EQ(ui64_acc[0],(uint64)(10));

    EXPECT_EQ(f32_acc[0],(float32)(10));
    EXPECT_EQ(f64_acc[0],(float64)(10));

}


//-----------------------------------------------------------------------------
TEST(conduit_exec_accessor, summary_stats)
{
    std::vector<int64>   v_int64 ={-1,0,1};
    std::vector<uint64>  v_uint64 = {1,2,3};
    std::vector<float64> v_float64= {-1.0,0.0,1.0};

    Node v_int64_node;
    v_int64_node.set(v_int64);
    Node v_uint64_node;
    v_uint64_node.set(v_uint64);
    Node v_float64_node;
    v_float64_node.set(v_float64);

    int64_exec_accessor   va_int64(v_int64_node);
    uint64_exec_accessor  va_uint64(v_uint64_node);
    float64_exec_accessor va_float64(v_float64_node);


    EXPECT_EQ(va_int64.min(),-1);
    EXPECT_EQ(va_int64.max(),1);
    EXPECT_EQ(va_int64.mean(),0);
    EXPECT_EQ(va_int64.sum(),0);
    EXPECT_EQ(va_int64.count(-1),1);

    EXPECT_EQ(va_uint64.min(),1);
    EXPECT_EQ(va_uint64.max(),3);
    EXPECT_EQ(va_uint64.mean(),2);
    EXPECT_EQ(va_uint64.sum(),6);
    EXPECT_EQ(va_uint64.count(2),1);

    EXPECT_EQ(va_float64.min(),-1.0);
    EXPECT_EQ(va_float64.max(),1.0);
    EXPECT_EQ(va_float64.mean(),0.0);
    EXPECT_EQ(va_float64.sum(),0.0);
    EXPECT_EQ(va_float64.count(0.0),1);

}



//-----------------------------------------------------------------------------
TEST(conduit_exec_accessor, as_cstyle)
{

    Node n;
    n.set((int8)10);

    char_exec_accessor         c_acc(n);
    signed_char_exec_accessor  sc_acc(n);
    signed_short_exec_accessor ss_acc(n);
    signed_int_exec_accessor   si_acc(n);
    signed_long_exec_accessor  sl_acc(n);

#ifdef CONDUIT_HAS_LONG_LONG
    signed_long_long_exec_accessor  sll_acc(n);
#endif

    unsigned_char_exec_accessor  usc_acc(n);
    unsigned_short_exec_accessor uss_acc(n);
    unsigned_int_exec_accessor   usi_acc(n);
    unsigned_long_exec_accessor  usl_acc(n);

#ifdef CONDUIT_HAS_LONG_LONG
    unsigned_long_long_exec_accessor  usll_acc(n);
#endif

    float_exec_accessor  f_acc(n);
    double_exec_accessor d_acc(n);

#ifdef CONDUIT_USE_LONG_DOUBLE
    long_double_exec_accessor  ld_acc(n);
#endif

    EXPECT_EQ(c_acc[0],(char)(10));
    EXPECT_EQ(sc_acc[0],(signed char)(10));
    EXPECT_EQ(ss_acc[0],(signed short)(10));
    EXPECT_EQ(si_acc[0],(signed int)(10));
    EXPECT_EQ(sl_acc[0],(signed long)(10));

#ifdef CONDUIT_HAS_LONG_LONG
    EXPECT_EQ(sll_acc[0],(signed long long)(10));
#endif

    EXPECT_EQ(usc_acc[0],(unsigned char)(10));
    EXPECT_EQ(uss_acc[0],(unsigned short)(10));
    EXPECT_EQ(usi_acc[0],(unsigned int)(10));
    EXPECT_EQ(usl_acc[0],(unsigned long)(10));

#ifdef CONDUIT_HAS_LONG_LONG
    EXPECT_EQ(usll_acc[0],(unsigned long long)(10));
#endif

    EXPECT_EQ(f_acc[0],(float)(10));
    EXPECT_EQ(d_acc[0],(double)(10));

#ifdef CONDUIT_USE_LONG_DOUBLE
    EXPECT_EQ(ld_acc[0],(long double)(10));
#endif 

}

// // TODO
// //-----------------------------------------------------------------------------
// TEST(conduit_exec_accessor, default_construct)
// {
//     index_t_accessor n_acc;
//     Node n;
//     n.set({-1,2,-3,4,-5});

//     n_acc = n.value(); // .value() should give us an exec accessor
//     EXPECT_EQ(n_acc[0],(index_t)(-1));
//     EXPECT_EQ(n_acc[1],(index_t)( 2));
//     EXPECT_EQ(n_acc[2],(index_t)(-3));
//     EXPECT_EQ(n_acc[3],(index_t)( 4));
//     EXPECT_EQ(n_acc[4],(index_t)(-5));


// ///////////////////

//     index_t_exec_accessor n_acc;
//     Node n;
//     n.set({-1,2,-3,4,-5});
//     index_t_exec_accessor n_acc2(n);

//     n_acc = n_acc2;
//     EXPECT_EQ(n_acc[0],(index_t)(-1));
//     EXPECT_EQ(n_acc[1],(index_t)( 2));
//     EXPECT_EQ(n_acc[2],(index_t)(-3));
//     EXPECT_EQ(n_acc[3],(index_t)( 4));
//     EXPECT_EQ(n_acc[4],(index_t)(-5));
// }


//-----------------------------------------------------------------------------
TEST(conduit_exec_accessor, set)
{

    Node n;
    n.set(DataType::int8(10));

    int8_exec_accessor  i8_acc(n);
    int16_exec_accessor i16_acc(n);
    int32_exec_accessor i32_acc(n);
    int64_exec_accessor i64_acc(n);

    uint8_exec_accessor  ui8_acc(n);
    uint16_exec_accessor ui16_acc(n);
    uint32_exec_accessor ui32_acc(n);
    uint64_exec_accessor ui64_acc(n);

    float32_exec_accessor f32_acc(n);
    float64_exec_accessor f64_acc(n);

    i8_acc.set(0,-4);
    i16_acc.set(1,-8);
    i32_acc.set(2,-16);
    i64_acc.set(3,-32);

    ui8_acc.set(4, 4);
    ui16_acc.set(5,8);
    ui32_acc.set(6,16);
    ui64_acc.set(7,32);

    f32_acc.set(8,16);
    f64_acc.set(9,32);

    EXPECT_EQ(i32_acc[0],-4);
    EXPECT_EQ(i32_acc[1],-8);
    EXPECT_EQ(i32_acc[2],-16);
    EXPECT_EQ(i32_acc[3],-32);

    EXPECT_EQ(i32_acc[4],4);
    EXPECT_EQ(i32_acc[5],8);
    EXPECT_EQ(i32_acc[6],16);
    EXPECT_EQ(i32_acc[7],32);

    EXPECT_EQ(i32_acc[8],16);
    EXPECT_EQ(i32_acc[9],32);

}


//-----------------------------------------------------------------------------
TEST(conduit_exec_accessor, fill)
{
    Node n;
    n.set(DataType::int32(10));

    int32_array    arr = n.value();
    int64_exec_accessor acc(n);

    acc.fill(-1);

    for(int i=0;i<10;i++)
    {
        EXPECT_EQ(arr[0],-1);
    }
}




//-----------------------------------------------------------------------------
TEST(conduit_exec_accessor, to_string)
{
    Node n;
    n.set(DataType::int32(6));

    int32_exec_accessor acc(n);

    std::string res = acc.to_string();
    std::cout << res << std::endl;
    EXPECT_EQ(res,"[0, 0, 0, 0, 0, 0]");

    res = acc.to_summary_string();
    std::cout << res << std::endl;
    EXPECT_EQ(res,"[0, 0, 0, ..., 0, 0]");
}


//-----------------------------------------------------------------------------
TEST(conduit_exec_accessor, set_using_data_array)
{
    std::vector<int8>  v_int8(10,-8);
    std::vector<int16> v_int16(10,-16);
    std::vector<int32> v_int32(10,-32);
    std::vector<int64> v_int64(10,-64);

    std::vector<uint8>  v_uint8(10,8);
    std::vector<uint16> v_uint16(10,16);
    std::vector<uint32> v_uint32(10,32);
    std::vector<uint64> v_uint64(10,64);

    std::vector<float32>  v_float32(10,32.0);
    std::vector<float64>  v_float64(10,64.0);

    int8_array    va_int8(&v_int8[0],DataType::int8(10));
    int16_array   va_int16(&v_int16[0],DataType::int16(10));
    int32_array   va_int32(&v_int32[0],DataType::int32(10));
    int64_array   va_int64(&v_int64[0],DataType::int64(10));

    uint8_array   va_uint8(&v_uint8[0],DataType::uint8(10));
    uint16_array  va_uint16(&v_uint16[0],DataType::uint16(10));
    uint32_array  va_uint32(&v_uint32[0],DataType::uint32(10));
    uint64_array  va_uint64(&v_uint64[0],DataType::uint64(10));

    float32_array  va_float32(&v_float32[0],DataType::float32(10));
    float64_array  va_float64(&v_float64[0],DataType::float64(10));


    Node n;

    // int8_array
    n["vint8"].set(DataType::int8(10));
    int8_exec_accessor vint8_acc(n["vint8"]);
    vint8_acc.set(va_int8);
    int8 *n_int8_ptr = n["vint8"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_int8_ptr[i],va_int8[i]);
    }

    // int16_array
    n["vint16"].set(DataType::int16(10));
    int16_exec_accessor vint16_acc(n["vint16"]);
    vint16_acc.set(va_int16);
    int16 *n_int16_ptr = n["vint16"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_int16_ptr[i],va_int16[i]);
    }

    // int32_array
    n["vint32"].set(DataType::int32(10));
    int32_exec_accessor vint32_acc(n["vint32"]);
    vint32_acc.set(va_int32);
    int32 *n_int32_ptr = n["vint32"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_int32_ptr[i],va_int32[i]);
    }

    // int64_array
    n["vint64"].set(DataType::int64(10));
    int64_exec_accessor vint64_acc(n["vint64"]);
    vint64_acc.set(va_int64);
    int64 *n_int64_ptr = n["vint64"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_int64_ptr[i],va_int64[i]);
    }

    // uint8_array
    n["vuint8"].set(DataType::uint8(10));
    uint8_exec_accessor vuint8_acc(n["vuint8"]);
    vuint8_acc.set(va_uint8);
    uint8 *n_uint8_ptr = n["vuint8"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_uint8_ptr[i],va_uint8[i]);
    }

    // uint16_array
    n["vuint16"].set(DataType::uint16(10));
    uint16_exec_accessor vuint16_acc(n["vuint16"]);
    vuint16_acc.set(va_uint16);
    uint16 *n_uint16_ptr = n["vuint16"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_uint16_ptr[i],va_uint16[i]);
    }

    // uint32_array
    n["vuint32"].set(DataType::uint32(10));
    uint32_exec_accessor vuint32_acc(n["vuint32"]);
    vuint32_acc.set(va_uint32);
    uint32 *n_uint32_ptr = n["vuint32"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_uint32_ptr[i],va_uint32[i]);
    }

    // uint64_array
    n["vuint64"].set(DataType::uint64(10));
    uint64_exec_accessor vuint64_acc(n["vuint64"]);
    vuint64_acc.set(va_uint64);
    uint64 *n_uint64_ptr = n["vuint64"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_uint64_ptr[i],va_uint64[i]);
    }


    // float32_array
    n["vfloat32"].set(DataType::float32(10));
    float32_exec_accessor vfloat32_acc(n["vfloat32"]);
    vfloat32_acc.set(va_float32);
    float32 *n_float32_ptr = n["vfloat32"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_float32_ptr[i],va_float32[i]);
    }

    // float64_array
    n["vfloat64"].set(DataType::float64(10));
    float64_exec_accessor vfloat64_acc(n["vfloat64"]);
    vfloat64_acc.set(va_float64);
    float64 *n_float64_ptr = n["vfloat64"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_float64_ptr[i],va_float64[i]);
    }

}



//-----------------------------------------------------------------------------
TEST(conduit_exec_accessor, set_using_data_accessor)
{
    std::vector<int8>  v_int8(10,-8);
    std::vector<int16> v_int16(10,-16);
    std::vector<int32> v_int32(10,-32);
    std::vector<int64> v_int64(10,-64);

    std::vector<uint8>  v_uint8(10,8);
    std::vector<uint16> v_uint16(10,16);
    std::vector<uint32> v_uint32(10,32);
    std::vector<uint64> v_uint64(10,64);

    std::vector<float32>  v_float32(10,32.0);
    std::vector<float64>  v_float64(10,64.0);

    int8_accessor  vacc_int8(&v_int8[0],DataType::int8(10));
    int16_accessor vacc_int16(&v_int16[0],DataType::int16(10));
    int32_accessor vacc_int32(&v_int32[0],DataType::int32(10));
    int64_accessor vacc_int64(&v_int64[0],DataType::int64(10));
    
    uint8_accessor  vacc_uint8(&v_uint8[0],DataType::uint8(10));
    uint16_accessor vacc_uint16(&v_uint16[0],DataType::uint16(10));
    uint32_accessor vacc_uint32(&v_uint32[0],DataType::uint32(10));
    uint64_accessor vacc_uint64(&v_uint64[0],DataType::uint64(10));

    float32_accessor vacc_float32(&v_float32[0],DataType::float32(10));
    float64_accessor vacc_float64(&v_float64[0],DataType::float64(10));


    Node n;

    // int8_array
    n["vint8"].set(DataType::int8(10));
    int8_exec_accessor vint8_acc(n["vint8"]);
    vint8_acc.set(vacc_int8);
    int8 *n_int8_ptr = n["vint8"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_int8_ptr[i],v_int8[i]);
    }

    // int16_array
    n["vint16"].set(DataType::int16(10));
    int16_exec_accessor vint16_acc(n["vint16"]);
    vint16_acc.set(vacc_int16);
    int16 *n_int16_ptr = n["vint16"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_int16_ptr[i],v_int16[i]);
    }

    // int32_array
    n["vint32"].set(DataType::int32(10));
    int32_exec_accessor vint32_acc(n["vint32"]);
    vint32_acc.set(vacc_int32);
    int32 *n_int32_ptr = n["vint32"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_int32_ptr[i],v_int32[i]);
    }

    // int64_array
    n["vint64"].set(DataType::int64(10));
    int64_exec_accessor vint64_acc(n["vint64"]);
    vint64_acc.set(vacc_int64);
    int64 *n_int64_ptr = n["vint64"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_int64_ptr[i],v_int64[i]);
    }

    // uint8_array
    n["vuint8"].set(DataType::uint8(10));
    uint8_exec_accessor vuint8_acc(n["vuint8"]);
    vuint8_acc.set(vacc_uint8);
    uint8 *n_uint8_ptr = n["vuint8"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_uint8_ptr[i],v_uint8[i]);
    }

    // uint16_array
    n["vuint16"].set(DataType::uint16(10));
    uint16_exec_accessor vuint16_acc(n["vuint16"]);
    vuint16_acc.set(vacc_uint16);
    uint16 *n_uint16_ptr = n["vuint16"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_uint16_ptr[i],v_uint16[i]);
    }

    // uint32_array
    n["vuint32"].set(DataType::uint32(10));
    uint32_exec_accessor vuint32_acc(n["vuint32"]);
    vuint32_acc.set(vacc_uint32);
    uint32 *n_uint32_ptr = n["vuint32"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_uint32_ptr[i],v_uint32[i]);
    }

    // uint64_array
    n["vuint64"].set(DataType::uint64(10));
    uint64_exec_accessor vuint64_acc(n["vuint64"]);
    vuint64_acc.set(vacc_uint64);
    uint64 *n_uint64_ptr = n["vuint64"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_uint64_ptr[i],v_uint64[i]);
    }


    // float32_array
    n["vfloat32"].set(DataType::float32(10));
    float32_exec_accessor vfloat32_acc(n["vfloat32"]);
    vfloat32_acc.set(vacc_float32);
    float32 *n_float32_ptr = n["vfloat32"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_float32_ptr[i],v_float32[i]);
    }

    // float64_array
    n["vfloat64"].set(DataType::float64(10));
    float64_exec_accessor vfloat64_acc(n["vfloat64"]);
    vfloat64_acc.set(vacc_float64);
    float64 *n_float64_ptr = n["vfloat64"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_float64_ptr[i],v_float64[i]);
    }

}


//-----------------------------------------------------------------------------
TEST(conduit_exec_accessor, set_using_exec_array)
{
    std::vector<int8>  v_int8(10,-8);
    std::vector<int16> v_int16(10,-16);
    std::vector<int32> v_int32(10,-32);
    std::vector<int64> v_int64(10,-64);

    std::vector<uint8>  v_uint8(10,8);
    std::vector<uint16> v_uint16(10,16);
    std::vector<uint32> v_uint32(10,32);
    std::vector<uint64> v_uint64(10,64);

    std::vector<float32>  v_float32(10,32.0);
    std::vector<float64>  v_float64(10,64.0);

    Node v_int8_node;
    v_int8_node.set(v_int8);
    Node v_int16_node;
    v_int16_node.set(v_int16);
    Node v_int32_node;
    v_int32_node.set(v_int32);
    Node v_int64_node;
    v_int64_node.set(v_int64);

    Node v_uint8_node;
    v_uint8_node.set(v_uint8);
    Node v_uint16_node;
    v_uint16_node.set(v_uint16);
    Node v_uint32_node;
    v_uint32_node.set(v_uint32);
    Node v_uint64_node;
    v_uint64_node.set(v_uint64);

    Node v_float32_node;
    v_float32_node.set(v_float32);
    Node v_float64_node;
    v_float64_node.set(v_float64);

    int8_exec_array    va_int8(v_int8_node);
    int16_exec_array   va_int16(v_int16_node);
    int32_exec_array   va_int32(v_int32_node);
    int64_exec_array   va_int64(v_int64_node);

    uint8_exec_array   va_uint8(v_uint8_node);
    uint16_exec_array  va_uint16(v_uint16_node);
    uint32_exec_array  va_uint32(v_uint32_node);
    uint64_exec_array  va_uint64(v_uint64_node);

    float32_exec_array  va_float32(v_float32_node);
    float64_exec_array  va_float64(v_float64_node);


    Node n;

    // int8_array
    n["vint8"].set(DataType::int8(10));
    int8_exec_accessor vint8_acc(n["vint8"]);
    vint8_acc.set(va_int8);
    int8 *n_int8_ptr = n["vint8"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_int8_ptr[i],va_int8[i]);
    }

    // int16_array
    n["vint16"].set(DataType::int16(10));
    int16_exec_accessor vint16_acc(n["vint16"]);
    vint16_acc.set(va_int16);
    int16 *n_int16_ptr = n["vint16"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_int16_ptr[i],va_int16[i]);
    }

    // int32_array
    n["vint32"].set(DataType::int32(10));
    int32_exec_accessor vint32_acc(n["vint32"]);
    vint32_acc.set(va_int32);
    int32 *n_int32_ptr = n["vint32"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_int32_ptr[i],va_int32[i]);
    }

    // int64_array
    n["vint64"].set(DataType::int64(10));
    int64_exec_accessor vint64_acc(n["vint64"]);
    vint64_acc.set(va_int64);
    int64 *n_int64_ptr = n["vint64"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_int64_ptr[i],va_int64[i]);
    }

    // uint8_array
    n["vuint8"].set(DataType::uint8(10));
    uint8_exec_accessor vuint8_acc(n["vuint8"]);
    vuint8_acc.set(va_uint8);
    uint8 *n_uint8_ptr = n["vuint8"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_uint8_ptr[i],va_uint8[i]);
    }

    // uint16_array
    n["vuint16"].set(DataType::uint16(10));
    uint16_exec_accessor vuint16_acc(n["vuint16"]);
    vuint16_acc.set(va_uint16);
    uint16 *n_uint16_ptr = n["vuint16"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_uint16_ptr[i],va_uint16[i]);
    }

    // uint32_array
    n["vuint32"].set(DataType::uint32(10));
    uint32_exec_accessor vuint32_acc(n["vuint32"]);
    vuint32_acc.set(va_uint32);
    uint32 *n_uint32_ptr = n["vuint32"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_uint32_ptr[i],va_uint32[i]);
    }

    // uint64_array
    n["vuint64"].set(DataType::uint64(10));
    uint64_exec_accessor vuint64_acc(n["vuint64"]);
    vuint64_acc.set(va_uint64);
    uint64 *n_uint64_ptr = n["vuint64"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_uint64_ptr[i],va_uint64[i]);
    }


    // float32_array
    n["vfloat32"].set(DataType::float32(10));
    float32_exec_accessor vfloat32_acc(n["vfloat32"]);
    vfloat32_acc.set(va_float32);
    float32 *n_float32_ptr = n["vfloat32"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_float32_ptr[i],va_float32[i]);
    }

    // float64_array
    n["vfloat64"].set(DataType::float64(10));
    float64_exec_accessor vfloat64_acc(n["vfloat64"]);
    vfloat64_acc.set(va_float64);
    float64 *n_float64_ptr = n["vfloat64"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_float64_ptr[i],va_float64[i]);
    }

}



//-----------------------------------------------------------------------------
TEST(conduit_exec_accessor, set_using_exec_accessor)
{
    std::vector<int8>  v_int8(10,-8);
    std::vector<int16> v_int16(10,-16);
    std::vector<int32> v_int32(10,-32);
    std::vector<int64> v_int64(10,-64);

    std::vector<uint8>  v_uint8(10,8);
    std::vector<uint16> v_uint16(10,16);
    std::vector<uint32> v_uint32(10,32);
    std::vector<uint64> v_uint64(10,64);

    std::vector<float32>  v_float32(10,32.0);
    std::vector<float64>  v_float64(10,64.0);

    Node v_int8_node;
    v_int8_node.set(v_int8);
    Node v_int16_node;
    v_int16_node.set(v_int16);
    Node v_int32_node;
    v_int32_node.set(v_int32);
    Node v_int64_node;
    v_int64_node.set(v_int64);

    Node v_uint8_node;
    v_uint8_node.set(v_uint8);
    Node v_uint16_node;
    v_uint16_node.set(v_uint16);
    Node v_uint32_node;
    v_uint32_node.set(v_uint32);
    Node v_uint64_node;
    v_uint64_node.set(v_uint64);

    Node v_float32_node;
    v_float32_node.set(v_float32);
    Node v_float64_node;
    v_float64_node.set(v_float64);

    int8_exec_accessor    vacc_int8(v_int8_node);
    int16_exec_accessor   vacc_int16(v_int16_node);
    int32_exec_accessor   vacc_int32(v_int32_node);
    int64_exec_accessor   vacc_int64(v_int64_node);

    uint8_exec_accessor   vacc_uint8(v_uint8_node);
    uint16_exec_accessor  vacc_uint16(v_uint16_node);
    uint32_exec_accessor  vacc_uint32(v_uint32_node);
    uint64_exec_accessor  vacc_uint64(v_uint64_node);

    float32_exec_accessor  vacc_float32(v_float32_node);
    float64_exec_accessor  vacc_float64(v_float64_node);


    Node n;

    // int8_array
    n["vint8"].set(DataType::int8(10));
    int8_exec_accessor vint8_acc(n["vint8"]);
    vint8_acc.set(vacc_int8);
    int8 *n_int8_ptr = n["vint8"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_int8_ptr[i],v_int8[i]);
    }

    // int16_array
    n["vint16"].set(DataType::int16(10));
    int16_exec_accessor vint16_acc(n["vint16"]);
    vint16_acc.set(vacc_int16);
    int16 *n_int16_ptr = n["vint16"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_int16_ptr[i],v_int16[i]);
    }

    // int32_array
    n["vint32"].set(DataType::int32(10));
    int32_exec_accessor vint32_acc(n["vint32"]);
    vint32_acc.set(vacc_int32);
    int32 *n_int32_ptr = n["vint32"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_int32_ptr[i],v_int32[i]);
    }

    // int64_array
    n["vint64"].set(DataType::int64(10));
    int64_exec_accessor vint64_acc(n["vint64"]);
    vint64_acc.set(vacc_int64);
    int64 *n_int64_ptr = n["vint64"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_int64_ptr[i],v_int64[i]);
    }

    // uint8_array
    n["vuint8"].set(DataType::uint8(10));
    uint8_exec_accessor vuint8_acc(n["vuint8"]);
    vuint8_acc.set(vacc_uint8);
    uint8 *n_uint8_ptr = n["vuint8"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_uint8_ptr[i],v_uint8[i]);
    }

    // uint16_array
    n["vuint16"].set(DataType::uint16(10));
    uint16_exec_accessor vuint16_acc(n["vuint16"]);
    vuint16_acc.set(vacc_uint16);
    uint16 *n_uint16_ptr = n["vuint16"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_uint16_ptr[i],v_uint16[i]);
    }

    // uint32_array
    n["vuint32"].set(DataType::uint32(10));
    uint32_exec_accessor vuint32_acc(n["vuint32"]);
    vuint32_acc.set(vacc_uint32);
    uint32 *n_uint32_ptr = n["vuint32"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_uint32_ptr[i],v_uint32[i]);
    }

    // uint64_array
    n["vuint64"].set(DataType::uint64(10));
    uint64_exec_accessor vuint64_acc(n["vuint64"]);
    vuint64_acc.set(vacc_uint64);
    uint64 *n_uint64_ptr = n["vuint64"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_uint64_ptr[i],v_uint64[i]);
    }


    // float32_array
    n["vfloat32"].set(DataType::float32(10));
    float32_exec_accessor vfloat32_acc(n["vfloat32"]);
    vfloat32_acc.set(vacc_float32);
    float32 *n_float32_ptr = n["vfloat32"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_float32_ptr[i],v_float32[i]);
    }

    // float64_array
    n["vfloat64"].set(DataType::float64(10));
    float64_exec_accessor vfloat64_acc(n["vfloat64"]);
    vfloat64_acc.set(vacc_float64);
    float64 *n_float64_ptr = n["vfloat64"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_float64_ptr[i],v_float64[i]);
    }

}

