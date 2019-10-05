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
            elif file[-4:] == ".cpp":
                cpp.append(path+'/'+file)
        except:
            continue
    return cpp

def main():
    clearscreen()
    print("PerennialMake-r Starting....")
    
    projects = os.listdir('./game/')
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
    final = SearchThrough(os.path.abspath('./game/%s/src'%(project)))
    clearscreen()
    windows = (os.name == 'nt')
    command = ''
    if windows:
        clearscreen()
        print("Detected Windows System, Please specify your Terminal command you use to compile!")
        print("WARNING: May not work, this is setup for GCC!")
        print("I'm not even sure that windows supports make..")
        command = input('> ')
    else:
        clearscreen()
        print("Detected Linux/Mac, assuming GCC as compiler.")
        command = 'gcc'
    print("Done!")
    print("Generating makefile...")
    makefile = open('./game/%s/makefile'%(project),'w+')

    lines = ['','','','','','']
    lines[0] = "COMPILER="+command
    lines[1] = "\nPROJECT="+project
    lines[2] = "\nSRCDIR="+os.path.abspath('./game/%s/src'%(project))
    lines[3] = "\nRESULT=main.app\n"

    lines[4] = "all: ; "
    lines[5] = "$(COMPILER) -g -std=c++11 "+' '.join(final)+" -o $(RESULT) -I $(SRCDIR)/include -I $(SRCDIR) -lGl -lglfw -lX11 -lpthread -ldl"

    makefile.writelines(lines)
    makefile.close()
    print("Done!")

main()
