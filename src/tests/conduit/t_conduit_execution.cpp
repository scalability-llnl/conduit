// Copyright (c) Lawrence Livermore National Security, LLC and other Conduit
// Project developers. See top-level LICENSE AND COPYRIGHT files for dates and
// other details. No copyright assignment is required to contribute to Conduit.

//-----------------------------------------------------------------------------
///
/// file: t_conduit_execution.cpp
///
//-----------------------------------------------------------------------------

#include "conduit.hpp"
#include "conduit_execution.hpp"
#include "conduit_memory_manager.hpp"

#include <iostream>
#include "gtest/gtest.h"

using namespace conduit;

void *device_alloc(index_t bytes)
{
#if defined(CONDUIT_USE_RAJA)
    return execution::DeviceMemory::allocate(bytes);
#else
    return execution::HostMemory::allocate(bytes);
#endif
}

void device_free(void *ptr)
{
#if defined(CONDUIT_USE_RAJA)
    return execution::DeviceMemory::deallocate(ptr);
#else
    return execution::HostMemory::deallocate(ptr);
#endif
}

void conduit_device_prepare()
{
    execution::init_device_memory_handlers();
}

// TODO someday we want allocator to make sense for nodes when we are done with them

//---------------------------------------------------------------------------//
// example functor 
//---------------------------------------------------------------------------//
struct MyFunctor
{
    int res;
    int size;
    template<typename ComboPolicyTag>
    void operator()(ComboPolicyTag &exec)
    {
        std::cout << typeid(ComboPolicyTag).name() << std::endl;
        using thetag = typename ComboPolicyTag::for_policy;
        std::cout << typeid(thetag).name() << std::endl;
        res = 0;
        conduit::execution::forall<thetag>(0, size, [=] (int i)
        {
            std::cout << i << std::endl;
            res ++;
        });
    }
};

//---------------------------------------------------------------------------//
// Mock of a class templated on a concrete tag
// (like a RAJA Reduction Object)
//---------------------------------------------------------------------------//
template <typename ExecPolicy>
class MySpecialClass
{
public:
    using policy = ExecPolicy;
    int val;

    MySpecialClass(int _val)
    :val(_val)
    {}
    
    void exec(int i) const
    {
        std::cout << typeid(policy).name() << " exec " <<  val << " " <<  i << std::endl;
    }
};

//---------------------------------------------------------------------------//
// example functor using MySpecialClass
//---------------------------------------------------------------------------//
struct MySpecialFunctor
{
    int res;
    int size;
    template<typename ComboPolicyTag>
    void operator()(ComboPolicyTag &exec)
    {
        // in this case we use an object
        // that is templated on a concrete tag
        // (like a RAJA Reduction Object)
        using thetag = typename ComboPolicyTag::for_policy;
        res = 0;
        MySpecialClass<thetag> s(10);
        conduit::execution::forall<thetag>(0, size, [=] (int i)
        {
            s.exec(i);
            res ++;
        });
    }
};

// //-----------------------------------------------------------------------------
// TEST(conduit_execution, test_forall)
// {
//     conduit_device_prepare();
//     const index_t size = 10;

//     index_t host_vals[size];
//     index_t *dev_vals_ptr = static_cast<index_t*>(device_alloc(sizeof(index_t) * size));

//     conduit::execution::ExecPolicy SerialPolicy(conduit::execution::policy::Serial);

//     conduit::execution::forall(SerialPolicy, 0, size, [=](index_t i)
//     {
//         dev_vals_ptr[i] = i;
//     });
//     // CONDUIT_DEVICE_ERROR_CHECK();
    
//     MagicMemory::copy(&host_vals[0], dev_vals_ptr, sizeof(index_t) * size);

//     for(index_t i=0;i<size;i++)
//     {
//         EXPECT_EQ(host_vals[i],i);
//     }

//     device_free(dev_vals_ptr);
// }

// // //-----------------------------------------------------------------------------
// // TEST(conduit_execution, test_reductions)
// // {
// //     Conduit::execution::ExecPolicy SerialPolicy(conduit::execution::policy::Serial);
// //     const index_t size = 4;
// //     index_t host_vals[size] = {0,-10,10, 5};
// //     index_t *dev_vals_ptr = static_cast<index_t*>(device_alloc(sizeof(index_t) * size));
// //     MagicMemory::copy(dev_vals_ptr, &host_vals[0], sizeof(index_t) * size);


// //     // sum
// //     // ascent::ReduceSum<reduce_policy,index_t> sum_reducer;
// //     using reduce_policy = typename conduit::execution::policy::Serial::reduce_policy;
// //     conduit::execution::forall<reduce_policy>(0, size, [=](index_t i)
// //     {
// //         sum_reducer += dev_vals_ptr[i];
// //     });
// //     // CONDUIT_DEVICE_ERROR_CHECK();

// //     EXPECT_EQ(sum_reducer.get(),5);


// //     // // min
// //     // ascent::ReduceMin<reduce_policy,index_t> min_reducer;
// //     // conduit::execution::forall<reduce_policy>(0, size, [=](index_t i)
// //     // {
// //     //     min_reducer.min(dev_vals_ptr[i]);
// //     // });
// //     // // CONDUIT_DEVICE_ERROR_CHECK();

// //     // EXPECT_EQ(min_reducer.get(),-10);

// //     // // minloc
// //     // ascent::ReduceMinLoc<reduce_policy,index_t> minloc_reducer;
// //     // conduit::execution::forall<reduce_policy>(0, size, [=](index_t i)
// //     // {
// //     //     minloc_reducer.minloc(dev_vals_ptr[i],i);
// //     // });
// //     // // CONDUIT_DEVICE_ERROR_CHECK();

// //     // EXPECT_EQ(minloc_reducer.get(),-10);
// //     // EXPECT_EQ(minloc_reducer.getLoc(),1);


// //     // // max
// //     // ascent::ReduceMax<reduce_policy,index_t> max_reducer;
// //     // conduit::execution::forall<reduce_policy>(0, size, [=](index_t i)
// //     // {
// //     //     max_reducer.max(dev_vals_ptr[i]);
// //     // });
// //     // // CONDUIT_DEVICE_ERROR_CHECK();

// //     // EXPECT_EQ(max_reducer.get(),10);

// //     // // maxloc
// //     // ascent::ReduceMaxLoc<reduce_policy,index_t> maxloc_reducer;
// //     // conduit::execution::forall<reduce_policy>(0, size, [=](index_t i)
// //     // {
// //     //     maxloc_reducer.maxloc(dev_vals_ptr[i],i);
// //     // });
// //     // // CONDUIT_DEVICE_ERROR_CHECK();

// //     // EXPECT_EQ(maxloc_reducer.get(),10);
// //     // EXPECT_EQ(maxloc_reducer.getLoc(),2);

// //     device_free(dev_vals_ptr);
// // }

//-----------------------------------------------------------------------------
// TEST(conduit_execution, cpp_magic_tests)
TEST(conduit_execution, justin_fun)
{
    std::cout << "forall cases!" << std::endl;

    conduit::execution::ExecutionPolicy serial = conduit::execution::ExecutionPolicy::serial();
#if defined(CONDUIT_USE_OPENMP)
    conduit::execution::ExecutionPolicy openmp = conduit::execution::ExecutionPolicy::openmp();
#endif
#if defined(CONDUIT_USE_RAJA)
    conduit::execution::ExecutionPolicy device = conduit::execution::ExecutionPolicy::device();
#endif

    int size = 4;

    conduit::execution::forall(serial, 0, size, [=] (int i)
    {
       std::cout << i << std::endl;
    });

#if defined(CONDUIT_USE_OPENMP)
    conduit::execution::forall(openmp, 0, size, [=] (int i)
    {
       std::cout << i << std::endl;
    });
#endif

#if defined(CONDUIT_USE_RAJA)
    conduit::execution::forall(device, 0, size, [=] (int i)
    {
       std::cout << i << std::endl;
    });
#endif

    std::cout << "functor cases!" << std::endl;

    MyFunctor func;
    func.size = size;
    conduit::execution::dispatch(serial, func);
    std::cout << func.res << std::endl;

#if defined(CONDUIT_USE_OPENMP)
    conduit::execution::dispatch(openmp, func);
    std::cout << func.res << std::endl;
#endif

#if defined(CONDUIT_USE_RAJA)
    conduit::execution::dispatch(device, func);
    std::cout << func.res << std::endl;
#endif

    MySpecialFunctor sfunc;
    sfunc.size = 4;
    conduit::execution::dispatch(serial, sfunc);
    std::cout << func.res << std::endl;

#if defined(CONDUIT_USE_OPENMP)
    conduit::execution::dispatch(openmp, sfunc);
    std::cout << func.res << std::endl;
#endif

#if defined(CONDUIT_USE_RAJA)
    conduit::execution::dispatch(device, sfunc);
    std::cout << func.res << std::endl;
#endif

    std::cout << "C++ 20" << std::endl;

    int res =0;
    /// c++ 20 allows us to double lambda instead of a functor

    // apparently this works just fine with cpp14...?

    conduit::execution::dispatch(serial, [&] <typename ComboPolicyTag>(ComboPolicyTag &exec)
    {
        using thetag = typename ComboPolicyTag::for_policy;
        MySpecialClass<thetag> s(10);
        conduit::execution::forall<thetag>(0, size, [=] (int i)
        {
            s.exec(i);
        });
        res = 10;
    });

#if defined(CONDUIT_USE_OPENMP)
    conduit::execution::dispatch(openmp, [&] <typename ComboPolicyTag>(ComboPolicyTag &exec)
    {
        using thetag = typename ComboPolicyTag::for_policy;
        MySpecialClass<thetag> s(10);
        conduit::execution::forall<thetag>(0, size, [=] (int i)
        {
            s.exec(i);
        });
        res = 10;
    });
#endif

#if defined(CONDUIT_USE_RAJA)
    conduit::execution::dispatch(device, [&] <typename ComboPolicyTag>(ComboPolicyTag &exec)
    {
        using thetag = typename ComboPolicyTag::for_policy;
        MySpecialClass<thetag> s(10);
        conduit::execution::forall<thetag>(0, size, [=] (int i)
        {
            s.exec(i);
        });
        res = 10;
    });
#endif
}


