LDFLAGS= -lglfw3 -lopengl32 -lglu32 -lgdi32  
CC = g++
TARGET = main.o framework/support/Shader.o framework/support/Texture.o \
framework/defprefab/Camera.o framework/support/stb_image.o glad.o \
framework/gui/UIElement.o
OUT = main

all: $(OUT) clean
$(OUT): $(TARGET)
	$(CC) $(TARGET) -o $(OUT) $(LDFLAGS)

clean:
	rm $(TARGET)