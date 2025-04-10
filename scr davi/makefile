CXX = g++

CXXFLAGS = -std=c++17 -Wall
SRCS = main.cpp raycast.hpp poligono.hpp
OBJS = $(SRCS:.hpp=.o)

# Nome do executável
EXEC = programa

# Regra padrão
all: $(EXEC)

# Como construir o executável
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# mensagens de debug
debug: CFLAGS += -DDEBUG
debug: $(EXEC)

# Regra para limpar os arquivos compilados
clean:
	rm -f $(OBJS) $(EXEC)
