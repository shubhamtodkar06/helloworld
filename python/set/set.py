from cs50 import SQL


db = SQL('sqlite:///book1.db')
db1 = SQL('sqlite:///books.db')
r = open('book1.db', encoding='latin')
for line in r:
  print(r.read())
