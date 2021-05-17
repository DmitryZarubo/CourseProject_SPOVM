FILES_CPU=CPU/Bus.cpp CPU/Bus.h CPU/cpu6502.cpp CPU/cpu6502.h
FILES_MAIN=main.cpp olcPixelEngine/olcPixelGameEngine.h
FILES_PPU=PPU/Cartridge.cpp PPU/Cartridge.h PPU/ppu2C02.cpp PPU/ppu2C02.h
FILES_MAPPERS=Mappers/Mapper.cpp Mappers/Mapper.h Mappers/Mapper_000.cpp Mappers/Mapper_000.h
CC=g++
FLAGS=-lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17
CFLAGS=-c
OUTPUT=out/test
#all: test

#Bus.o: CPU/Bus.cpp CPU/Bus.h
#			$(CC) $(CFLAGS) -o Bus.o CPU/Bus.cpp CPU/Bus.h

#cpu6502.o: CPU/cpu6502.cpp CPU/cpu6502.h
#			$(CC) $(CFLAGS) -o cpu6502.o CPU/cpu6502.cpp CPU/cpu6502.h
#main.o: main.cpp olcPixelEngine/olcPixelGameEngine.h
#		$(CC) $(CFLAGS) $(FLAGS) -o main.o main.cpp olcPixelEngine/olcPixelGameEngine.h
#test: main.o Bus.o cpu6502.o
#		$(CC) $(FLAGS) -o test main.o cpu6502.o Bus.o

test: $(FILES_CPU) $(FILES_MAIN) $(FILES_MAPPERS) $(FILES_PPU)
		$(CC) -o $(OUTPUT) $(FILES_CPU) $(FILES_MAIN) $(FILES_MAPPERS) $(FILES_PPU) $(FLAGS)
