OBJ = main.o projectile.o asteroid.o body.o world.o input.o ship.o explosion.o spark.o
BIN = rymdtrish
LIBS = -lGL -lGLU -lglut

all: $(BIN)
clean:
	rm -f $(OBJ)

$(BIN): clean $(OBJ)
	g++ -o $(BIN) $(OBJ) $(LIBS)
run: $(BIN)
	./$(BIN)
%.o: %.h
