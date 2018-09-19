src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)

lemsiedler: $(obj)
	g++ -o $@ $^ -lSDL -lSDL_image -g
	
%.o: %.cpp
	g++ -c -o $@ $< -g
	
.PHONY: clean
clean:
	rm -f $(obj) lemsiedler
