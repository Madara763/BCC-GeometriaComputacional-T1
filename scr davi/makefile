CXX = g++

CXXFLAGS = -std=c++17 -Wall
SRCS = main.cpp raycast.hpp poligono.hpp
OBJS = $(SRCS:.cpp=.o)

# Nome do executável
EXEC = programa

# Regra padrão
all: $(EXEC)

# Como construir o executável
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# mensagens de debug
debug: CXXFLAGS += -DDEBUG
debug: all

# Regra para limpar os arquivos objetos
clean:
	rm -f *.o

purge:
	rm -f  $(EXEC) *.o
