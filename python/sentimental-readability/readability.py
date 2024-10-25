# Import file to get string
from cs50 import get_string

# get text input
text = get_string("Text: ")

# Count number of letters in text
X = 0
for a in range(len(text)):
    if (text[a].isalpha()) == True:
        X = X + 1
    else:
        X = X + 0

# Count number of words in text
Y = 0
for b in range(len(text)):
    if (text[b].isspace()) == True:
        Y = Y + 1
    else:
        Y = Y + 0
# add one more in Y
Y = Y + 1

# Count number of sentence in text
Z = 0
for c in range(len(text)):
    if text[c] == '.' or text[c] == '?' or text[c] == '!':
        Z = Z + 1
    else:
        Z = Z + 0

# L average number of letters per 100 words
L = (X / Y) * 100

# S average number of sentence per 100 words
S = (Z / Y) * 100

# Value of index as per formula
index = 0.0588 * L - 0.296 * S - 15.8

if index < 1.5:
    print("Before Grade 1")

elif index > 1.5 and index < 2.5:
    print("Grade 2")

elif index > 2.5 and index < 3.5:
    print("Grade 3")

elif index > 3.5 and index < 4.5:
    print("Grade 4")

elif index > 4.5 and index < 5.5:
    print("Grade 5")

elif index > 5.5 and index < 6.5:
    print("Grade 6")

elif index > 6.5 and index < 7.5:
    print("Grade 7")

elif index > 7.5 and index < 8.5:
    print("Grade 8")

elif index > 8.5 and index < 9.5:
    print("Grade 9")

elif index > 9.5 and index < 10.5:
    print("Grade 10")

elif index > 10.5 and index < 11.5:
    print("Grade 11")

elif index > 11.5 and index < 12.5:
    print("Grade 12")

elif index > 12.5 and index < 13.5:
    print("Grade 13")

elif index > 13.5 and index < 14.5:
    print("Grade 14")

elif index > 14.5 and index < 15.5:
    print("Grade 15")

else:
    print("Grade 16+")
