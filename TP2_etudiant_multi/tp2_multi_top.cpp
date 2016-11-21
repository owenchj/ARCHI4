#include <systemc>
#include <limits>

#include "vci_gcd_master.h"
#include "vci_gcd_coprocessor.h"
#include "vci_signals.h"
#include "vci_param.h"
#include "mapping_table.h"
#include "vci_vgsb.h"

#define GCD_BASE_0        0x01000000
#define GCD_SIZE_0        0xF

#define GCD_BASE_1        0x02000000
#define GCD_SIZE_1        0xF

#define GCD_BASE_2        0x03000000
#define GCD_SIZE_2        0xF

int sc_main(int argc, char *argv[])
{
        using namespace sc_core;
        using namespace soclib::caba;
        using namespace soclib::common;

        // VCI fields width definition
        //        cell_size        = 4;
        //         plen_size        = 8;
        //         addr_size        = 32;
        //         rerror_size        = 1;
        //         clen_size        = 1;
        //         rflag_size        = 1;
        //         srcid_size        = 12;
        //         trdid_size        = 1;
        //         pktid_size        = 1;
        //         wrplen_size        = 1;

        typedef VciParams<4, 8, 32, 1, 1, 1, 12, 1, 1, 1 > vci_param;

        ///////////////////////////////////////////////////////////////////////////
        // simulation arguments : number of cycles & seed for the random generation
        ///////////////////////////////////////////////////////////////////////////
        int ncycles = std::numeric_limits<int>::max();
        int seed    = 123456789;
        if (argc > 1) ncycles = atoi(argv[1]) ;
        if (argc > 2) seed = atoi(argv[2]) ;

        //////////////////////////////////////////////////////////////////////////
        // Mapping Table
        //////////////////////////////////////////////////////////////////////////
        MappingTable maptab(32, IntTab(8), IntTab(8), 0x03000000);

        maptab.add(soclib::common::Segment("GCD_0", GCD_BASE_0, GCD_SIZE_0, IntTab(0), true));
        maptab.add(soclib::common::Segment("GCD_1", GCD_BASE_1, GCD_SIZE_1, IntTab(1), true));
        maptab.add(soclib::common::Segment("GCD_2", GCD_BASE_2, GCD_SIZE_2, IntTab(2), true));
        std::cout << std::endl << maptab << std::endl;

        //////////////////////////////////////////////////////////////////////////
        // Signals
        //////////////////////////////////////////////////////////////////////////
        sc_clock                               signal_clk("signal_clk", sc_time( 1, SC_NS ), 0.5 );
        sc_signal<bool>                        signal_resetn("signal_resetn");

        VciSignals<vci_param>                  signal_vci_m_0("signal_vci_m_0");
        VciSignals<vci_param>                  signal_vci_m_1("signal_vci_m_1");
        VciSignals<vci_param>                  signal_vci_m_2("signal_vci_m_2");

        VciSignals<vci_param>                  signal_vci_c_0("signal_vci_c_0");
        VciSignals<vci_param>                  signal_vci_c_1("signal_vci_c_1");
        VciSignals<vci_param>                  signal_vci_c_2("signal_vci_c_2");

        //////////////////////////////////////////////////////////////////////////
        // Components
        //////////////////////////////////////////////////////////////////////////
        VciVgsb<vci_param>   vgsb("vgsb", maptab, 3, 3);

        VciGcdMaster<vci_param>         master_0("master_0", 0, maptab, seed + 0, GCD_BASE_0);
        VciGcdCoprocessor<vci_param>    coproc_0("coprocessor_0", 0, maptab);

        VciGcdMaster<vci_param>         master_1("master_1", 1, maptab, seed + 1, GCD_BASE_1);
        VciGcdCoprocessor<vci_param>    coproc_1("coprocessor_1", 1, maptab);

        VciGcdMaster<vci_param>         master_2("master_2", 2, maptab, seed + 2, GCD_BASE_2);
        VciGcdCoprocessor<vci_param>    coproc_2("coprocessor_2", 2, maptab);

        //////////////////////////////////////////////////////////////////////////
        // Net-List
        //////////////////////////////////////////////////////////////////////////

        // 0
        master_0.p_clk(signal_clk);
        master_0.p_resetn(signal_resetn);
        master_0.p_vci(signal_vci_m_0);

        coproc_0.p_clk(signal_clk);
        coproc_0.p_resetn(signal_resetn);
        coproc_0.p_vci(signal_vci_c_0);

        // 1
        master_1.p_clk(signal_clk);
        master_1.p_resetn(signal_resetn);
        master_1.p_vci(signal_vci_m_1);

        coproc_1.p_clk(signal_clk);
        coproc_1.p_resetn(signal_resetn);
        coproc_1.p_vci(signal_vci_c_1);

        // 2
        master_2.p_clk(signal_clk);
        master_2.p_resetn(signal_resetn);
        master_2.p_vci(signal_vci_m_2);

        coproc_2.p_clk(signal_clk);
        coproc_2.p_resetn(signal_resetn);
        coproc_2.p_vci(signal_vci_c_2);

        // interconnection
        vgsb.p_clk(signal_clk);
        vgsb.p_resetn(signal_resetn);
        // master
        vgsb.p_to_initiator[0](signal_vci_m_0);
        vgsb.p_to_initiator[1](signal_vci_m_1);
        vgsb.p_to_initiator[2](signal_vci_m_2);
        // slave
        vgsb.p_to_target[0](signal_vci_c_0);
        vgsb.p_to_target[1](signal_vci_c_1);
        vgsb.p_to_target[2](signal_vci_c_2);

        //////////////////////////////////////////////////////////////////////////
        // simulation
        //////////////////////////////////////////////////////////////////////////
        signal_resetn = false;
        sc_start( sc_time( 1, SC_NS ) ) ;

        signal_resetn = true;
        for ( int n=1 ; n<ncycles ; n++) sc_start( sc_time( 1, SC_NS ) ) ;

        return(0);

} // end sc_main
