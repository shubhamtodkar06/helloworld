input=open('input.txt','r')
output=open('output.txt','w')

for letter in input:
    letter = letter.swapcase()
    letter = letter.replace('.',',')
    output.write(letter)

input.close()
output.close()

read = open('output.txt', 'r')
print(read.read())
read.close