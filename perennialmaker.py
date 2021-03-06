import os
import sys
import time

if not sys.stdout.isatty():
    import tkinter
    from tkinter import messagebox
    root = tkinter.Tk()
    root.withdraw()
    messagebox.showinfo("Uh... This is awkward.","We've detected a GUI.\nPerennialMake-r can't be run in a GUI.\nyet...")
    exit(-1)


def ProcessFile(path):
    file = open(path,'r')
    filelines = file.readlines()

    compileargs = []
    paths = []

    for linen in range(len(filelines)):
        line=filelines[linen].strip()
        if line == '':
            continue
        elif line[0:2] == '//':
            continue
        elif line[0] == '$':
            compileargs.append(line.replace('$',''))
        elif line[0:2] == '-f': 
            paths.append(line[3:].replace('*',''))
        else:
            print("Syntax Error "+path+":"+str(linen)+"\nUnexpected "+line)
            return [[],[]]
            
        #print(line)

    print(compileargs)
    print(paths)
    file.close()
    return paths,compileargs

def clearscreen():
    os.system('clear' if not os.name == 'nt' else 'clear')

def SearchThrough(path):
    contents = os.listdir(path)
    cpp = []
    for filen in range(len(contents)):
        file = contents[filen]
        sys.stdout.write("\r%d%%"%(100*(filen/len(contents))))
        sys.stdout.flush()
        try:
            sys.stdout.write(path+'/'+file+'\n')
            sys.stdout.flush()
            if os.path.isdir(path+'/'+file):
                cpp+=SearchThrough(path+'/'+file)
            elif file[-4:] == ".cpp" or file[-2:] == ".c":
                cpp.append(path+'/'+file)
        except:
            continue
    return cpp

def main():
    clearscreen()
    print("PerennialMake-r Starting....")
    
    projects = os.listdir('./projects/')
    if not projects:
        print("Projects weren't detected!")
        return -1

    print("Detected Projects")
    print(', '.join(projects))

    print("What Project?")
    project = ""
    while not project in projects:
        project = input("> ")
    print("Starting for Project ''%s''..."%(project))

    source = os.listdir('./game/%s/src'%(project))
    print("Getting .cpp Files...")
    final = SearchThrough(os.path.abspath('./projects/%s/src'%(project)))
    clearscreen()
    windows = (os.name == 'nt')
    command = ''
    

main()
