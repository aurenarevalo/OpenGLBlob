LDFLAGS= -lglfw3 -lopengl32 -lglu32 -lgdi32  
CC = g++
TARGET = main.o glad.o
OUT = main

all: $(OUT) clean
$(OUT): $(TARGET)
	$(CC) $(TARGET) -o $(OUT) $(LDFLAGS)

clean:
	rm $(TARGET)