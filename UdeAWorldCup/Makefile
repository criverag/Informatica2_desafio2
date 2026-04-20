# Makefile — UdeAWorldCup
# Compilador y flags básicos para el curso

CXX      = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -I include/

# Archivos fuente
SRCS = src/main.cpp src/Seleccion.cpp src/LectorCSV.cpp

# Nombre del ejecutable
TARGET = UdeAWorldCup

CXXFLAGS = -I./include

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)
