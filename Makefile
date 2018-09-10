src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)

lemsiedler: $(obj)
	g++ -o $@ $^ -lSDL -lSDL_image
	
.PHONY: clean
clean:
	rm -f $(obj) lemsiedler
