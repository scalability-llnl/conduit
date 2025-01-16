// Copyright (c) Lawrence Livermore National Security, LLC and other Conduit
// Project developers. See top-level LICENSE AND COPYRIGHT files for dates and
// other details. No copyright assignment is required to contribute to Conduit.

//-----------------------------------------------------------------------------
///
/// file: conduit_execution.cpp
///
//-----------------------------------------------------------------------------
#include "conduit_execution.hpp"

//-----------------------------------------------------------------------------
// conduit includes
//-----------------------------------------------------------------------------


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
/// policy constructor helpers
//-----------------------------------------------------------------------------
ExecutionPolicy
ExecutionPolicy::empty()
{
    return ExecutionPolicy(EMPTY_ID);
}

//---------------------------------------------------------------------------//
ExecutionPolicy
ExecutionPolicy::serial()
{
    return ExecutionPolicy(SERIAL_ID);
}

//---------------------------------------------------------------------------//
ExecutionPolicy
ExecutionPolicy::device()
{
    return ExecutionPolicy(DEVICE_ID);
}

//---------------------------------------------------------------------------//
ExecutionPolicy
ExecutionPolicy::cuda()
{
    return ExecutionPolicy(CUDA_ID);
}

//---------------------------------------------------------------------------//
ExecutionPolicy
ExecutionPolicy::hip()
{
    return ExecutionPolicy(HIP_ID);
}

//---------------------------------------------------------------------------//
ExecutionPolicy
ExecutionPolicy::openmp()
{
    return ExecutionPolicy(OPENMP_ID);
}

//=============================================================================
//-----------------------------------------------------------------------------
//
//
// -- begin conduit::execution::ExecutionPolicy public methods --
//
//
//-----------------------------------------------------------------------------
//=============================================================================

//-----------------------------------------------------------------------------
// Construction and Destruction
//-----------------------------------------------------------------------------
//---------------------------------------------------------------------------//
ExecutionPolicy::ExecutionPolicy()
: m_policy_id(PolicyID::EMPTY_ID)
{}

//---------------------------------------------------------------------------//
ExecutionPolicy::ExecutionPolicy(const ExecutionPolicy& exec_policy)
: m_policy_id(exec_policy.m_policy_id)
{}

//---------------------------------------------------------------------------//
ExecutionPolicy& ExecutionPolicy::operator=(const ExecutionPolicy& exec_policy)
{
    m_policy_id = exec_policy.m_policy_id;

    return *this;
}

//---------------------------------------------------------------------------//
ExecutionPolicy::ExecutionPolicy(PolicyID policy_id)
: m_policy_id(policy_id)
{}

//---------------------------------------------------------------------------//
ExecutionPolicy::ExecutionPolicy(const std::string &policy_name)
: m_policy_id(name_to_id(policy_name))
{}

//---------------------------------------------------------------------------//
ExecutionPolicy::~ExecutionPolicy()
{}

//-----------------------------------------------------------------------------
// Getters and info methods.
//-----------------------------------------------------------------------------

//---------------------------------------------------------------------------//
bool
ExecutionPolicy::is_empty() const
{
    return m_policy_id == EMPTY_ID;
}

//---------------------------------------------------------------------------//
bool
ExecutionPolicy::is_serial() const
{
    return m_policy_id == SERIAL_ID;
}

//---------------------------------------------------------------------------//
bool
ExecutionPolicy::is_device() const
{
    return m_policy_id == DEVICE_ID;
}

//---------------------------------------------------------------------------//
bool
ExecutionPolicy::is_cuda() const
{
    return m_policy_id == CUDA_ID;
}

//---------------------------------------------------------------------------//
bool
ExecutionPolicy::is_hip() const
{
    return m_policy_id == HIP_ID;
}

//---------------------------------------------------------------------------//
bool
ExecutionPolicy::is_openmp() const
{
    return m_policy_id == OPENMP_ID;
}

//-----------------------------------------------------------------------------
// PolicyID to string and string to PolicyID
//-----------------------------------------------------------------------------

//---------------------------------------------------------------------------//
conduit::index_t 
ExecutionPolicy::name_to_id(const std::string &policy_name)
{
    if (policy_name      == "empty")  return EMPTY_ID;
    else if (policy_name == "serial") return SERIAL_ID;
    else if (policy_name == "device") return DEVICE_ID;
    else if (policy_name == "cuda")   return CUDA_ID;
    else if (policy_name == "hip")    return HIP_ID;
    else if (policy_name == "openmp") return OPENMP_ID;
    return EMPTY_ID;
}

//---------------------------------------------------------------------------//
std::string 
ExecutionPolicy::id_to_name(conduit::index_t policy_id)
{
    if (policy_id      == EMPTY_ID)  return "empty";
    else if (policy_id == SERIAL_ID) return "serial";
    else if (policy_id == DEVICE_ID) return "device";
    else if (policy_id == CUDA_ID)   return "cuda";
    else if (policy_id == HIP_ID)    return "hip";
    else if (policy_id == OPENMP_ID) return "openmp";
    return "empty";
}

//---------------------------------------------------------------------------//
void
init_device_memory_handlers()
{
#if defined(CONDUIT_DEVICE_ENABLED)
    // we only need to override the mem handlers in the
    // presence of cuda or hip
    conduit::utils::set_memcpy_handler(MagicMemory::copy);
    conduit::utils::set_memset_handler(MagicMemory::set);
#endif
}

}
//-----------------------------------------------------------------------------
// -- end conduit::execution --
//-----------------------------------------------------------------------------

}
//-----------------------------------------------------------------------------
// -- end conduit:: --
//-----------------------------------------------------------------------------

