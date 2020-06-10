SOURCES = main.cpp x11context.cpp gcontext.cpp Image.cpp Shape.cpp Line.cpp Triangle.cpp Point.cpp MyDrawing.cpp matrix.cpp ViewContext.cpp
#converts cpp to .o
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = lab8

lab4: $(OBJECTS)
	g++ -o lab8 -lX11 $(OBJECTS)


	
clean:
	rm -f $(OBJECTS)
	rm -f $(EXECUTABLE)


