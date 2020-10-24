GUI:
	g++-10 src/GUI.cpp src/move.cpp src/pokemon.cpp src/trainer.cpp src/battle.cpp -o bin/main -I include -L lib -l SDL2-2.0.0 -l SDL2_image -l SDL2_ttf -std=c++20
	clear
	bin/./main
def:
	g++-10 src/def.cpp src/move.cpp src/pokemon.cpp src/trainer.cpp -o bin/main-def -std=c++20
	bin/./main-def