g++ -c -w main.cpp
g++ main.o -o game -lsfml-graphics -lsfml-window -lsfml-system
./game

rm main.o
rm game