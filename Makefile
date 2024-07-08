OBJ = src/main.o src/projectile.o src/asteroid.o src/body.o src/world.o src/input.o src/ship.o src/explosion.o src/spark.o
BIN = rymdtrish
LIBS = -lGL -lGLU

all: $(BIN)
clean:
	rm -f $(OBJ)

$(BIN): clean $(OBJ)
	g++ -o $(BIN) $(OBJ) $(LIBS)
run: $(BIN)
	./$(BIN)
%.o: %.h
