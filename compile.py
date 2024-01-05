# system(f"gcc {name}.c $(pkg-config --cflags --libs sdl2) -o bin/{name}; ./bin/{name}")

from os import system
import time

CURRENT = 0
PACKAGES = ["sdl2", "SDL2_ttf", "SDL2_image", "SDL2_mixer"]

COMP_DIST = "bin/"
RUN = True

def genArgs(lst):
    args = ""

    for i in lst:
        args += f"{i} "

    return args


name = input("tst num: ")
if name == "":
    name = CURRENT


name = f"tst{name}"

name = "main"

print(f"compiling and running {name}.c")
#
start = time.time()
system(
    f"gcc {name}.c -lm $(pkg-config --cflags --libs {genArgs(PACKAGES)}) -o {COMP_DIST}{name}"
)
end = time.time()
print(f"compiled in {round(end - start, 3)}s")
if RUN:
    start = time.time()
    system(f"./{COMP_DIST}{name}")
    end = time.time()
    print(f"executed in {round(end - start, 3)}s")
