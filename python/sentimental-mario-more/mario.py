# TODO
# Get height from user
while True:
    try:
        height = int(input("Height: "))
        if 0 < height < 9:
            break
    except ValueError:
        print("no")

# Use for loop
for x in range(height):
    for y in range(height - x - 1):
        print(" ", end='')

    for z in range(x + 1):
        print("#", end='')

    print("  ", end="")

    for z in range(x + 1):
        print("#", end='')
    # print on new line
    print()