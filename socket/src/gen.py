import os
from os import listdir
from os.path import isfile, join


def main():
    mypath = os.getcwd()
    mypath += '/template/'
    onlyfiles = [ f for f in listdir(mypath) if isfile(join(mypath,f)) ]
    for item in onlyfiles:
        if item[len(item)-5] == 'c':
            newname = item[9:len(item)-5]+'.c'
            oldfile = 'template/'+item
            with open(oldfile, 'r') as old:
                with open(newname,'w+') as new:
                    for line in old:
                        new.write(line)
        elif item[len(item)-5] == 'h':
            newname = item[9:len(item)-5]+'.h'
            oldfile = 'template/'+item
            with open(oldfile, 'r') as old:
                with open(newname,'w+') as new:
                    for line in old:
                        new.write(line)

if __name__ == "__main__":
    main()