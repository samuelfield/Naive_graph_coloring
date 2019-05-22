graphmake: main.cc graph_CSR.cc graph_CSR.hh coloring.cc coloring.hh
	g++ -Wall -o graph_example main.cc graph_CSR.cc graph_CSR.hh coloring.cc coloring.hh