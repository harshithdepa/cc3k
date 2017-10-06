CXX=g++-5
CXXFLAGS= -std=c++14 -Wall -Werror=vla
SRC = ${shell find src -name '*.cc'}
OBJECTS= ${SRC:.cc=.o}
DEPENDS= ${OBJECTS:.o=.d}
EXEC=cc3k

$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC)

-include $(DEPENDS)

clean:
	rm *.o $(EXEC)

.PHONY: clean
