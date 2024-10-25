word1 = input("Enter The First Word       : ").strip()
word2 = input("Enter The Second Word      : ").strip()

print(f'Letters in The First Word          : {len(word1)}')
print(f'Letters in The Second Word         : {len(word2)}')
print(f'The First Word in a Reversed Order  : {word1[::-1]}')
print(f'The Second Word in a Reversed Order : {word2[::-1]}')
if word1 == word2:
    print('Both The First and The Second words are the same!!!')
elif (word1 in word2) or (word2 in word1):
    print('Both The First Word and The Second words are NOT the same!!!')
    if word1 in word2:
            print('The First Word is substring of The Second Word!!!')
    else:
        if word2 in word1:
                print('The Second Word is a substring of The First Word!!!')
        else:
                print('Both Words are NOT a substring of each other!!!')

if word1 == word1[::-1]:
    print('The First Word is a Palindrome Word!!!')
else:
    print('The First Word is NOT a Palindrome Word!!!')
if word2 == word2[::-1]:
    print('The Second Word is a Palindrome Word!!!')
else:
    print('The Second Word is NOT a Palindrome Word!!!')


