graphmake: main.cc graph_CSR.cc graph_CSR.hh coloring.cc coloring.hh schedule.cc schedule.hh
	g++ -Wall -fcilkplus -o graph_example main.cc graph_CSR.cc graph_CSR.hh coloring.cc coloring.hh schedule.cc schedule.hh