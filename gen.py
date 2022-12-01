for i in range(1, 26):
    with open('in/input{}.txt'.format(i), 'w') as f:
        f.write(str(i))
    with open('out/output{}.txt'.format(i), 'w') as f:
        f.write("TesT {} passEd\nEof".format(i))
