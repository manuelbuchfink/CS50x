height = 4

for i in range(height):
    for l in range (height - i):
        print(" ",end="")
    for j in range(i + 1):
        print("#",end="")
    print("")
