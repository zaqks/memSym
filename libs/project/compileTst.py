from os import system


PACKAGES = ["sdl2", "SDL2_ttf", "SDL2_image", "SDL2_mixer"]

COMP_DIST = "bin/"
RUN = True

def genArgs(lst):
    args = ""

    for i in lst:
        args += f"{i} "

    return args

system(
    f"gcc tst.c -lm $(pkg-config --cflags --libs {genArgs(PACKAGES)}) -o ../../bin/tst ; ../../bin/tst"
)

print("done")