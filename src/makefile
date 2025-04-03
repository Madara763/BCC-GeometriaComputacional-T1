CC = g++ -g
SOURCES = geometry.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXEC = main

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp geometry.hpp
	$(CC) $(CFLAGS) -c $< -o $@

# caso queria testar a intersecao entre dois segmentos
intersecao: test_intersecao.cpp $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# mensagens de debug
debug: CFLAGS += -DDEBUG
debug: all

clean:
	rm -f $(OBJECTS) $(EXEC) intersecao


