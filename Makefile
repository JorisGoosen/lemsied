src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)

lemsiedler: $(obj)
	g++ -std=c++11 -o $@ $^ -lSDL
	
.PHONY: clean
clean:
	rm -f $(obj) lemsiedler
