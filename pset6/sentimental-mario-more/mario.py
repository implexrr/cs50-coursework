# Prompt user for input
while (True):
    try:
        height = (int(input("Height: ")))
        if height >= 1 and height <= 8:
            break
    except(ValueError):
        print("Not a integer!")

# Print pyramid
for i in range(height):
    print(" " * (height - (i + 1)), end="")
    print("#" * (i + 1), end="")
    print("  ", end="")
    print("#" * (i + 1), end="")
    print()

