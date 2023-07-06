#include <AMReX_PROB_AMR_F.H>
#include <AMReX_ParmParse.H>
#include "prob_parm.H"
#include "EBR.H"
#include "IndexDefines.H"

extern "C" {
    void amrex_probinit (const int* /*init*/,
                         const int* /*name*/,
                         const int* /*namelen*/,
                         const amrex_real* /*problo*/,
                         const amrex_real* /*probhi*/)
    {
        amrex::ParmParse pp("prob");

        pp.query("p_l", EBR::h_prob_parm->p_l);
        pp.query("p_r", EBR::h_prob_parm->p_r);
        pp.query("rho_l", EBR::h_prob_parm->rho_l);
        pp.query("rho_r", EBR::h_prob_parm->rho_r);
        pp.query("u_l", EBR::h_prob_parm->u_l);
        pp.query("u_r", EBR::h_prob_parm->u_r);

#ifdef AMREX_USE_GPU
        // Cannot use Gpu::copy because ProbParm is not trivailly copyable.
        Gpu::htod_memcpy_async(EBR::d_prob_parm, EBR::h_prob_parm, sizeof(ProbParm));
#else
        std::memcpy(EBR::d_prob_parm, EBR::h_prob_parm, sizeof(ProbParm));
#endif
        Gpu::streamSynchronize();
    }
}
