
old : tp6_top.desc tp6_top.cpp
	soclib-cc -P -p tp6_top.desc -o simulator.x

advanced : tp6_top_advanced.desc tp6_top_advanced.cpp
	soclib-cc -P -p tp6_top_advanced.desc -o simulator_advanced.x -I vci_xcache_wrapper_advanced

clean:
	rm -f *.o *.x core tmp *.deps stats trace 
	soclib-cc -x -X -p tp6_top.desc  

clean_advanced:
	rm -f *.o *.x core tmp *.deps stats trace tty
	soclib-cc -x -X -p tp6_top_advanced.desc  
