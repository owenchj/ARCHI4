#include <systemc>
#include <limits>
#include <stdint.h>

#include "fifo_gcd_master.h"
#include "fifo_gcd_coprocessor.h"
#include "fifo_ports.h"
#include "fifo_signals.h"

int sc_main(int argc, char *argv[])
{
        using namespace sc_core;
	using namespace soclib::caba;

	/////////////////////////////////////////////////////////////////
	// Arguments : number of cycles & seed for the random generation
	/////////////////////////////////////////////////////////////////
	int ncycles = std::numeric_limits<int>::max();
        int seed    = 123456789;
	if (argc > 1) ncycles = atoi(argv[1]) ;
	if (argc > 2) seed = atoi(argv[2]) ;

	/////////////////////////////////////////////////////////////////
        // Signals
	/////////////////////////////////////////////////////////////////
        sc_clock                		signal_clk("signal_clk", sc_time( 1, SC_NS ), 0.5 );
        sc_signal<bool> 			signal_resetn("signal_resetn");
        FifoSignals<uint32_t> 			signal_fifo_m2c("signal_m2c");
        FifoSignals<uint32_t> 			signal_fifo_c2m("signal_c2m");

	/////////////////////////////////////////////////////////////////
	// Components
	/////////////////////////////////////////////////////////////////
        FifoGcdMaster 				master("fifo_gcd_master", seed);
	FifoGcdCoprocessor			coproc("fifo_gcd_coprocessor");

	/////////////////////////////////////////////////////////////////
	// Net-List
	/////////////////////////////////////////////////////////////////
	master.p_clk(signal_clk); 
	master.p_resetn(signal_resetn);
	master.p_in(signal_fifo_c2m);
	master.p_out(signal_fifo_m2c);

	coproc.p_clk(signal_clk); 
	coproc.p_resetn(signal_resetn);
	coproc.p_in(signal_fifo_m2c);
	coproc.p_out(signal_fifo_c2m);

        	/////////////////////////////////////////////////////////////////
	// Trace
	/////////////////////////////////////////////////////////////////

        sc_trace_file* tfp = sc_create_vcd_trace_file("gcd");
	sc_trace(tfp, signal_clk, signal_clk.name());
        sc_trace(tfp, signal_resetn, signal_resetn.name());
        signal_fifo_c2m.trace(tfp, "signal_fifo_c2m");
        signal_fifo_m2c.trace(tfp, "signal_fifo_m2c");

	/////////////////////////////////////////////////////////////////
	// simulation
	/////////////////////////////////////////////////////////////////
	sc_start(signal_clk.period());

	signal_resetn = false;
	sc_start( sc_time( 1, SC_NS ) ) ;

	signal_resetn = true;
	for (int n=1 ; n<ncycles ; n++ )  sc_start( sc_time( 1, SC_NS ) ) ;

        sc_close_vcd_trace_file(tfp);
        
	return(0);

} // end sc_main












