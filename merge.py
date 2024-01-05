importsFilePath = "libs/project/imports.h"

with open(importsFilePath, "r") as f:
    importsList = f.readlines()
    f.close()

includes = []
resultLines = []

for i in importsList:
    if i != "\n":
        if not (i.__contains__("<") or i.__contains__(">")):
            # get the fil path
            currentPath = i.split("#include ")[1]
            currentPath = currentPath.replace('"', "")
            currentPath = currentPath.replace("\n", "")

            currentPath = f"libs/project/{currentPath}"
            print(currentPath)

            # copy the content
            with open(currentPath, "r") as f:
                for i in f.readlines():
                    if not includes.__contains__(i):
                        if i.__contains__("#include"):
                            includes.append(i)

                        resultLines.append(i)
                        if i.__contains__("#define"):
                            resultLines.append("\n")

                f.close()
        resultLines.append("\n")


# add the main.c
resultLines.append("\n")
with open("main.c", "r") as f:
    for i in f.readlines():
        if not i.__contains__(importsFilePath):
            resultLines.append(i)

    f.close()

with open("result.c", "w") as f:
    f.writelines(resultLines)
    f.close()
