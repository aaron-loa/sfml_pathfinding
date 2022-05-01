all:compile link

compile:
	g++ -I include/ -c main.cpp hGlobals.cpp hNode.cpp hPath.cpp hRender.cpp
link:
	g++ main.o hGlobals.o hNode.o hPath.o hRender.o -o main -L build/lib -l sfml-graphics -l sfml-window -l sfml-system -l sfml-audio -l sfml-network
