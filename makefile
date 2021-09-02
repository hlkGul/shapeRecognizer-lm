all:

	g++ main.cpp fourierDescriptor.cpp histogram.cpp InnerDistance.cpp hu.cpp statisticalDescriptor.cpp -o finalProject `pkg-config --cflags opencv` `pkg-config --libs opencv` 
	./finalProject
