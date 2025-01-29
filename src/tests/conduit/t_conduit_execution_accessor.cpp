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

// TODO
// //-----------------------------------------------------------------------------
// TEST(conduit_exec_accessor, default_construct)
// {
//     index_t_accessor n_acc;
//     Node n;
//     n.set({-1,2,-3,4,-5});

//     n_acc = n.value();
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




