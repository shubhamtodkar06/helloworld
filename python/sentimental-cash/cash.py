# Import function from CS50 liabrary
from cs50 import get_float

# check for correct input value
while True:
    try:
        change = get_float("Change owed: ")
        if change > 0:
            break
    except ValueError:
        print("Integer Value")

change = change * 100
# count for quarters of value 0.25
quarters = 0
while change >= 25:
    quarters += 1
    change -= 25

# count for dimes of value 0.1
dimes = 0
while change >= 10:
    dimes += 1
    change -= 10


# count for nickels of value 0.05
nickels = 0
while change >= 5:
    nickels += 1
    change -= 5

# equate pennies with remaining change
pennies = change

coins = quarters + dimes + nickels + pennies

print(coins)