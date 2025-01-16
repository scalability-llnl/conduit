// Copyright (c) Lawrence Livermore National Security, LLC and other Conduit
// Project developers. See top-level LICENSE AND COPYRIGHT files for dates and
// other details. No copyright assignment is required to contribute to Conduit.

//-----------------------------------------------------------------------------
///
/// file: conduit_execution.hpp
///
//-----------------------------------------------------------------------------

#ifndef CONDUIT_EXECUTION_HPP
#define CONDUIT_EXECUTION_HPP


//-----------------------------------------------------------------------------
// conduit lib includes
//-----------------------------------------------------------------------------
#include "conduit_config.h"
#include "conduit_execution_serial.hpp"
#if defined(CONDUIT_USE_OPENMP)
#include "conduit_execution_omp.hpp"
#endif

//-----------------------------------------------------------------------------
// -- begin conduit --
//-----------------------------------------------------------------------------
namespace conduit
{

//-----------------------------------------------------------------------------
// -- begin conduit::execution --
//-----------------------------------------------------------------------------
namespace execution
{

//-----------------------------------------------------------------------------
// -- begin conduit::execution::ExecutionPolicy --
//-----------------------------------------------------------------------------
///
/// class: conduit::execution::ExecutionPolicy
///
/// description:
///  ExecutionPolicy is a runtime policy object.
///
//-----------------------------------------------------------------------------
class CONDUIT_API ExecutionPolicy
{
public:
//-----------------------------------------------------------------------------
/// Policy is an Enumeration used to describe the policy cases supported
///  by conduit:
//-----------------------------------------------------------------------------
    enum class PolicyID : conduit::index_t
    {
        EMPTY_ID,
        SERIAL_ID,
        DEVICE_ID,
        CUDA_ID,
        HIP_ID,
        OPENMP_ID
    };

// //-----------------------------------------------------------------------------
// // -- begin conduit::execution::ExecutionPolicy Constructor Helpers --
// //-----------------------------------------------------------------------------
//     static ExecutionPolicy empty();

//     static ExecutionPolicy serial();
    
//     static ExecutionPolicy device();
    
//     static ExecutionPolicy cuda();
    
//     static ExecutionPolicy hip();
    
//     static ExecutionPolicy openmp();

// //-----------------------------------------------------------------------------
// // -- end conduit::execution::ExecutionPolicy Constructor Helpers --
// //-----------------------------------------------------------------------------

// //-----------------------------------------------------------------------------
// //
// // -- conduit::execution::ExecutionPolicy public methods --
// //
// //-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Construction and Destruction
//-----------------------------------------------------------------------------
    /// standard constructor
    ExecutionPolicy();
    /// copy constructor
    ExecutionPolicy(const ExecutionPolicy& exec_policy);
    /// Assignment operator
    ExecutionPolicy& operator=(const ExecutionPolicy& exec_policy);
    /// Construct from given policy id
    ExecutionPolicy(PolicyID policy_id);
    /// Construct from policy name
    ExecutionPolicy(const std::string &policy_name);
    /// destructor
    ~ExecutionPolicy();

// //-----------------------------------------------------------------------------
// // Setters
// //-----------------------------------------------------------------------------
//     void set_policy(PolicyID policy_id)
//         { m_policy_id = policy_id; }

// //-----------------------------------------------------------------------------
// // Getters and info methods.
// //-----------------------------------------------------------------------------
//     PolicyID    policy_id()    const { return m_policy_id; }
//     std::string policy_name()  const { return policy_id_to_name(m_policy_id); }

//     bool        is_empty()     const;
//     bool        is_serial()    const;
//     bool        is_device()    const;
//     bool        is_cuda()      const;
//     bool        is_hip()       const;
//     bool        is_openmp()    const;

// //-----------------------------------------------------------------------------
// // Helpers to convert PolicyID Enum Values to human readable strings and 
// // vice versa.
// //-----------------------------------------------------------------------------

//     static conduit::index_t name_to_policy_id(const std::string &name);
//     static std::string      policy_id_to_name(const PolicyID policy_id);

private:
//-----------------------------------------------------------------------------
//
// -- conduit::execution::ExecutionPolicy private data members --
//
//-----------------------------------------------------------------------------
    PolicyID m_policy_id;
};
//-----------------------------------------------------------------------------
// -- end conduit::execution::ExecutionPolicy --
//-----------------------------------------------------------------------------

// // registers the fancy conduit memory handlers for
// // magic memset and memcpy
// static void init_device_memory_handlers();



struct EmptyPolicy
{};

#if defined(CONDUIT_USE_RAJA)
//---------------------------------------------------------------------------//
// RAJA_ON policies for when raja is on
//---------------------------------------------------------------------------//
struct SerialExec
{
    using for_policy = RAJA::seq_exec;
#if defined(CONDUIT_USE_CUDA)
    // the cuda/hip policy for reductions can be used
    // by other backends, and this should suppress
    // erroneous host device warnings
    using reduce_policy = RAJA::cuda_reduce;
#elif  defined(CONDUIT_USE_HIP)
    using reduce_policy = RAJA::hip_reduce;
#else
    using reduce_policy = RAJA::seq_reduce;
#endif
    using atomic_policy = RAJA::seq_atomic;
    using sort_policy = EmptyPolicy;
    static std::string memory_space;
};

// cuda, hip, openMP, we might alias one of these to be device (cuda or hip)

//---------------------------------------------------------------------------
#if defined(CONDUIT_USE_CUDA) // TODO who is this
struct CudaExec
{
    using for_policy    = RAJA::cuda_exec<CUDA_BLOCK_SIZE>;
    using reduce_policy = RAJA::cuda_reduce;
    using atomic_policy = RAJA::cuda_atomic;
    using sort_policy = EmptyPolicy;
    static std::string memory_space;
};
#endif

#if defined(CONDUIT_USE_HIP)
//---------------------------------------------------------------------------
struct HipExec
{
    using for_policy    = RAJA::hip_exec<HIP_BLOCK_SIZE>;
    using reduce_policy = RAJA::hip_reduce;
    using atomic_policy = RAJA::hip_atomic;
    using sort_policy = EmptyPolicy;
    static std::string memory_space;
};
#endif

#if defined(CONDUIT_USE_OPENMP)
//---------------------------------------------------------------------------
struct OpenMPExec
{
    using for_policy = RAJA::omp_parallel_for_exec;
#if defined(CONDUIT_USE_CUDA)
    // the cuda policy for reductions can be used
    // by other backends, and this should suppress
    // erroneous host device warnings
    using reduce_policy = RAJA::cuda_reduce;
#elif defined(CONDUIT_USE_HIP)
    using reduce_policy = RAJA::hip_reduce;
#else
    using reduce_policy = RAJA::omp_reduce;
#endif
    using atomic_policy = RAJA::omp_atomic;
    using sort_policy = EmptyPolicy;
    static std::string memory_space;
};
#endif


#else
//---------------------------------------------------------------------------//
// RAJA_OFF policies for when raja is OFF
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------
struct SerialExec
{
    using for_policy = seq::for_policy;
    using reduce_policy = EmptyPolicy;
    using atomic_policy = EmptyPolicy;
    using sort_policy = seq::sort_policy;
    static std::string memory_space;
};

// TODO do we want this to be an option when RAJA is off?
// TODO decide about if we want to provide this as an option when RAJA is on as well
#if defined(CONDUIT_USE_OPENMP)
//---------------------------------------------------------------------------
struct OpenMPExec
{
    using for_policy = omp::for_policy;
    using reduce_policy = EmptyPolicy;
    using atomic_policy = EmptyPolicy;
    using sort_policy = omp::sort_policy;
    static std::string memory_space;
};
#endif

#endif

// //---------------------------------------------------------------------------//
// // invoke functor with concrete template tag
// //---------------------------------------------------------------------------//
// template <typename ExecPolicyTag, typename Function>
// inline void invoke(ExecPolicyTag &exec, Function&& func) noexcept
// {
//     func(exec);
// }

// //---------------------------------------------------------------------------//
// // runtime to concrete template tag dispatch of a functor
// //---------------------------------------------------------------------------//
// template <typename Function>
// void
// dispatch(ExecutionPolicy policy, Function&& func)
// {
//     if (policy.is_serial())
//     {
//         SerialExec se;
//         invoke(se, func);
//     }
//     else if (policy.is_device())
//     {
// #if defined(CONDUIT_USE_RAJA) && defined(CONDUIT_USE_CUDA)
//         CudaExec ce;
//         invoke(ce, func);
// #elif defined(CONDUIT_USE_RAJA) && defined(CONDUIT_USE_HIP)
//         HipExec he;
//         invoke(he, func);
// #else
//         CONDUIT_ERROR("Conduit was built with neither CUDA nor HIP.");
// #endif
//     }
//     else if (policy.is_cuda())
//     {
// #if defined(CONDUIT_USE_RAJA) && defined(CONDUIT_USE_CUDA)
//         CudaExec ce;
//         invoke(ce, func);
// #else
//         CONDUIT_ERROR("Conduit was not built with CUDA.");
// #endif
//     }
//     else if (policy.is_hip())
//     {
// #if defined(CONDUIT_USE_RAJA) && defined(CONDUIT_USE_HIP)
//         HipExec he;
//         invoke(he, func);
// #else
//         CONDUIT_ERROR("Conduit was not built with HIP.");
// #endif
//     }
//     else if (policy.is_openmp())
//     {
// #if defined(CONDUIT_USE_OPENMP)
//         OpenMPExec ompe;
//         invoke(ompe, func);
// #else
//         CONDUIT_ERROR("Conduit was not built with OpenMP.");
// #endif
//     }
//     else // policy.is_empty()
//     {
//         CONDUIT_ERROR("Cannot invoke with an empty policy.");
//     }
// }

// //---------------------------------------------------------------------------//
// // mock up of a raja like forall implementation 
// //---------------------------------------------------------------------------//
// template <typename ExecutionPolicy,typename Kernel>
// inline void
// new_forall_exec(const int& begin,
//                 const int& end,
//                 Kernel&& kernel) noexcept
// {
//     std::cout << typeid(ExecutionPolicy).name() << "  START" << std::endl;
//     for (int i = begin; i < end; i ++)
//     {
//         kernel(i);
//     }
//     std::cout << typeid(ExecutionPolicy).name() << "  END" << std::endl;
// }


// //---------------------------------------------------------------------------//
// // invoke forall with concrete template tag
// //---------------------------------------------------------------------------//
// template <typename ExecutionPolicy, typename Kernel>
// inline void
// new_forall(const int& begin,
//            const int& end,
//            Kernel&& kernel) noexcept
// {
//     new_forall_exec<ExecutionPolicy>(begin, end, std::forward<Kernel>(kernel));
// }

// //---------------------------------------------------------------------------//
// // runtime to concrete template tag dispatch of a forall
// //---------------------------------------------------------------------------//
// template <typename Kernel>
// inline void
// new_forall(ExecutionPolicy &policy,
//            const int& begin,
//            const int& end,
//            Kernel&& kernel) noexcept
// {
//     if (policy.is_serial())
//     {
//         new_forall<SerialExec>(begin, end, std::forward<Kernel>(kernel));
//     }
//     else if (policy.is_device())
//     {
// #if defined(CONDUIT_USE_RAJA) && defined(CONDUIT_USE_CUDA)
//         new_forall<CudaExec>(begin, end, std::forward<Kernel>(kernel));
// #elif defined(CONDUIT_USE_RAJA) && defined(CONDUIT_USE_HIP)
//         new_forall<HipExec>(begin, end, std::forward<Kernel>(kernel));
// #else
//         CONDUIT_ERROR("Conduit was built with neither CUDA nor HIP.");
// #endif
//     }
//     else if (policy.is_cuda())
//     {
// #if defined(CONDUIT_USE_RAJA) && defined(CONDUIT_USE_CUDA)
//         new_forall<CudaExec>(begin, end, std::forward<Kernel>(kernel));
// #else
//         CONDUIT_ERROR("Conduit was not built with CUDA.");
// #endif
//     }
//     else if (policy.is_hip())
//     {
// #if defined(CONDUIT_USE_RAJA) && defined(CONDUIT_USE_HIP)
//         new_forall<HipExec>(begin, end, std::forward<Kernel>(kernel));
// #else
//         CONDUIT_ERROR("Conduit was not built with HIP.");
// #endif
//     }
//     else if (policy.is_openmp())
//     {
// #if defined(CONDUIT_USE_OPENMP)
//         new_forall<HipExec>(begin, end, std::forward<Kernel>(kernel));
// #else
//         CONDUIT_ERROR("Conduit was not built with OpenMP.");
// #endif
//     }
//     else // policy.is_empty()
//     {
//         CONDUIT_ERROR("Cannot call for_all with an empty policy.");
//     }
// }

// OLD BRAD STUFF below

//---------------------------------------------------------------------------
template <typename ExecPolicy, typename Func>
inline void
for_all(size_t begin, size_t end, Func &&func)
{
    using policy = typename ExecPolicy::for_policy;
    policy exec;
    exec(begin, end, func);
}

template <typename ExecPolicy, typename Iterator>
inline void
sort(Iterator begin, Iterator end)
{
    using policy = typename ExecPolicy::sort_policy;
    policy exec;
    exec(begin, end);
}

template <typename ExecPolicy, typename Iterator, typename Predicate>
inline void
sort(Iterator begin, Iterator end, Predicate &&predicate)
{
    using policy = typename ExecPolicy::sort_policy;
    policy exec;
    exec(begin, end, predicate);
}

}
//-----------------------------------------------------------------------------
// -- end conduit::execution --
//-----------------------------------------------------------------------------

}
//-----------------------------------------------------------------------------
// -- end conduit:: --
//-----------------------------------------------------------------------------

#endif
