import os
import sys
import time

import tkinter
from tkinter.ttk import Progressbar
from tkinter import messagebox

class GuiPerennialMaker:

    def __init__(self,parent):

        self.root = parent
        self.root.resizable(False,False)
        self.root.title("Perennial Make-r")
        self.frame = tkinter.Frame(parent)
        self.frame.pack()

        self.lblTitle = tkinter.Label(self.frame, text="Perennial Make-r")
        self.lblTitle.grid(row=0)
        #lblTitle.pack()

        self.lblCurFile = tkinter.Label(self.frame, text="")
        self.lblCurFile.grid(row=2,column=0)

        self.prgProgress = Progressbar(self.frame)
        self.prgProgress.grid(row=3,column=0)

        self.lstProjects = tkinter.Listbox(self.frame)
        self.lstProjects.grid(row=1,column=0)
        self.projects = os.listdir('./game/')
        messagebox.showinfo("Info","Detected %s Projects."%(str(len(self.projects))))
        for i in range(len(self.projects)):
            self.lstProjects.insert(i+1,self.projects[i])
        self.cmdMake = tkinter.Button(self.frame, text="Make Makefile",command=self.do_it_all)
        self.cmdMake.grid(row=4,column=0)
        #cmdTest.pack()

    def hide(self):
        self.root.withdraw()

    def show(self):
        self.root.update()
        self.root.deiconify()
        
    def do_it_all(self):
        if not self.lstProjects.curselection():
            messagebox.showerror("Woops!","No selected Project!")
            return
        project = self.projects[self.lstProjects.curselection()[0]]
        source = os.listdir('./game/%s/src'%(project))
        self.prgProgress["maximum"] = GetSize('./game/%s/src'%(project))
        final = SearchThrough(os.path.abspath('./game/%s/src'%(project)),self.prgProgress,self.lblCurFile)
        makefile = open('./game/%s/makefile'%(project),'w+')

        windows = (os.name == "nt")

        if windows:
            messagebox.showinfo("Hmm...","We've detected a windows system.\nMakefile may not work!\n(It requires GCC!)")

        command='g++'
        
        lines = ['','','','','','']
        lines[0] = "COMPILER="+command
        lines[1] = "\nPROJECT="+project
        lines[2] = "\nSRCDIR="+os.path.abspath('./game/%s/src'%(project))
        lines[3] = "\nRESULT=main.app\n"

        lines[4] = "all: ; "
        lines[5] = "$(COMPILER) -g -std=c++11 "+' '.join(final)+" -o $(RESULT) -I $(SRCDIR)/include -I $(SRCDIR) -lGL -lglfw -lX11 -lpthread -ldl"

        makefile.writelines(lines)
        makefile.close()

        self.lblCurFile["text"] = ""

        messagebox.showinfo("Info","Done!")

def clearscreen():
    os.system('clear' if not os.name == 'nt' else 'clear')

def GetSize(path):
    contents = os.listdir(path)
    val=0
    for i in range(len(contents)):
        val+=1
        file = contents[i]
        if os.path.isdir(path+'/'+file):
            val+=GetSize(path+'/'+file)

    return val

def SearchThrough(path,prgProgress,lblCurFile):
    contents = os.listdir(path)
    cpp = []
    for filen in range(len(contents)):
        prgProgress.step()
        prgProgress.update()
        lblCurFile["text"] = contents[filen]
        file = contents[filen]
        #sys.stdout.write("\r%d%%"%(100*(filen/len(contents))))
        #sys.stdout.flush()
        print(path+'/'+file)
        try:
            #sys.stdout.write(path+'/'+file+'\n')
            #sys.stdout.flush()
            if os.path.isdir(path+'/'+file):
                cpp+=SearchThrough(path+'/'+file,prgProgress,lblCurFile)
            elif file[-4:] == ".cpp" or file[-2:] == ".c":
                cpp.append(path+'/'+file)
        except:
            continue
    return cpp

def main():
    root = tkinter.Tk()
    root.geometry("250x280")
    app = GuiPerennialMaker(root)
    root.mainloop()
    
    """clearscreen()
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
    print("Done!")"""

main()
