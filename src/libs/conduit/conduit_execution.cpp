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
    return ExecutionPolicy(PolicyID::EMPTY_ID);
}

//---------------------------------------------------------------------------//
ExecutionPolicy
ExecutionPolicy::defaultPolicy()
{
    return ExecutionPolicy(PolicyID::DEFAULT_ID);
}

//---------------------------------------------------------------------------//
ExecutionPolicy
ExecutionPolicy::serial()
{
    return ExecutionPolicy(PolicyID::SERIAL_ID);
}

//---------------------------------------------------------------------------//
ExecutionPolicy
ExecutionPolicy::device()
{
    return ExecutionPolicy(PolicyID::DEVICE_ID);
}

//---------------------------------------------------------------------------//
ExecutionPolicy
ExecutionPolicy::cuda()
{
    return ExecutionPolicy(PolicyID::CUDA_ID);
}

//---------------------------------------------------------------------------//
ExecutionPolicy
ExecutionPolicy::hip()
{
    return ExecutionPolicy(PolicyID::HIP_ID);
}

//---------------------------------------------------------------------------//
ExecutionPolicy
ExecutionPolicy::openmp()
{
    return ExecutionPolicy(PolicyID::OPENMP_ID);
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
: m_policy_id(name_to_policy_id(policy_name))
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
    return m_policy_id == PolicyID::EMPTY_ID;
}

//---------------------------------------------------------------------------//
bool
ExecutionPolicy::is_default() const
{
    return m_policy_id == PolicyID::DEFAULT_ID;
}

//---------------------------------------------------------------------------//
bool
ExecutionPolicy::is_serial() const
{
    return m_policy_id == PolicyID::SERIAL_ID;
}

//---------------------------------------------------------------------------//
bool
ExecutionPolicy::is_device() const
{
    return m_policy_id == PolicyID::DEVICE_ID;
}

//---------------------------------------------------------------------------//
bool
ExecutionPolicy::is_cuda() const
{
    return m_policy_id == PolicyID::CUDA_ID;
}

//---------------------------------------------------------------------------//
bool
ExecutionPolicy::is_hip() const
{
    return m_policy_id == PolicyID::HIP_ID;
}

//---------------------------------------------------------------------------//
bool
ExecutionPolicy::is_openmp() const
{
    return m_policy_id == PolicyID::OPENMP_ID;
}

//---------------------------------------------------------------------------//
bool
ExecutionPolicy::is_host_policy() const
{
    // TODO DANGER - for now we are letting default be on the host
    // we may with to change this in the future.
    return is_serial() || is_openmp() || is_default();
}

//---------------------------------------------------------------------------//
bool
ExecutionPolicy::is_device_policy() const
{
    return is_device() || is_cuda() || is_hip();
}

//-----------------------------------------------------------------------------
// PolicyID to string and string to PolicyID
//-----------------------------------------------------------------------------

//---------------------------------------------------------------------------//
ExecutionPolicy::PolicyID
ExecutionPolicy::name_to_policy_id(const std::string &policy_name)
{
    if (policy_name      == "empty")   return PolicyID::EMPTY_ID;
    else if (policy_name == "serial")  return PolicyID::SERIAL_ID;
    else if (policy_name == "default") return PolicyID::DEFAULT_ID;
    else if (policy_name == "device")  return PolicyID::DEVICE_ID;
    else if (policy_name == "cuda")    return PolicyID::CUDA_ID;
    else if (policy_name == "hip")     return PolicyID::HIP_ID;
    else if (policy_name == "openmp")  return PolicyID::OPENMP_ID;
    return PolicyID::EMPTY_ID;
}

//---------------------------------------------------------------------------//
std::string 
ExecutionPolicy::policy_id_to_name(const PolicyID policy_id)
{
    if (policy_id      == PolicyID::EMPTY_ID)   return "empty";
    else if (policy_id == PolicyID::SERIAL_ID)  return "serial";
    else if (policy_id == PolicyID::DEFAULT_ID) return "default";
    else if (policy_id == PolicyID::DEVICE_ID)  return "device";
    else if (policy_id == PolicyID::CUDA_ID)    return "cuda";
    else if (policy_id == PolicyID::HIP_ID)     return "hip";
    else if (policy_id == PolicyID::OPENMP_ID)  return "openmp";
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

