while True:
    time = int(input())
    if 1 <= time <= 1000:
        break
    else:
        print('ENTER CORRECT VALUE')

for i in range(time):
        while True:
            foo, bar, baz = input().split()
            foo = int(foo)
            bar = int(bar)
            baz = int(baz)
            if 1 <= foo <= 1000 and 1 <= bar <= 1000 and 1 <= baz <= 1000:
                break
            else:
                print('ENTER CORRECT VALUE')

        if foo+bar+baz == 0 or foo+bar-baz == 0 or foo-bar+baz == 0 or bar+baz-foo == 0 or foo-bar-baz == 0 or bar-foo-baz == 0 or baz-foo-bar == 0:
            print('yes')
        else:
            print('no')