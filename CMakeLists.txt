
project(rymdtrish)

add_executable(
    rymdtrish
    src/input.cpp
    src/projectile.cpp
    src/world.cpp
    src/ship.cpp
    src/ship.h
    src/body.cpp
    src/main.cpp
    src/projectile.h
    src/explosion.cpp
    src/spark.cpp
    src/asteroid.cpp
)

target_link_libraries(
    rymdtrish
    -lSDL2
    -lGL
    -lglut
    -lGLU
)
