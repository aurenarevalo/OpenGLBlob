SUPPORT = framework/support/
PREFAB = framework/default_prefab/
PREFAB2D = ${PREFAB}2D/

GUI = framework/gui_elements/
BUTTONS = ${GUI}buttons/

SOURCEDIR= ./
CFILES = glad.o


SUPPORTFILES = $(patsubst %.cpp,%.o,$(wildcard ${SUPPORT}*.cpp))
PREFABFILES = $(patsubst %.cpp,%.o,$(wildcard ${PREFAB2D}*.cpp))
GUIFILES = $(patsubst %.cpp,%.o,$(wildcard ${GUI}*.cpp)) $(patsubst %.cpp,%.o,$(wildcard ${BUTTONS}*.cpp))




LDFLAGS= -lglfw3 -lopengl32 -lglu32 -lgdi32  
CC = g++
TARGET = main.o ${CFILES} ${SUPPORTFILES} ${PREFABFILES} ${GUIFILES}

OUT = main

all: $(OUT) clean 
$(OUT): $(TARGET)
	$(CC) $(TARGET) -o $(OUT) $(LDFLAGS)

test:
	echo ${SUPPORTFILES}

clean:
	rm $(TARGET)