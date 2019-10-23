import sys #Standard Module
import getopt #Not sure.
import os #definitely sure.

#Feel free to upscale.
ignoreList = ['.c','.hpp','.jpg','.png','.swp','.inl']

dBug = False

def main(argv):
    file = False
    override = True
    inputpath = ''

    try:
        opts, args = getopt.getopt(argv,'h',['folder=','file=','no-override-file'])
    except getopt.GetoptError:
        print("spacetotab.py -f <folder>")
        sys.exit(2)
    for opt, arg in opts:
        if opt == '-h':
            print('test.py --folder <folder>')
            print('OR\ntest.py --file <filepath>')
            print('OR\ntest.py --file <filepath> --no-override-file')
            sys.exit()
        elif opt in ('--folder'):
            inputpath = os.path.abspath(arg)
        elif opt in ('--file'): #if they've specified a file, then it's a file.
            inputpath = os.path.abspath(arg)
            file = True
        elif opt in ('-nof','--no-override-file'):
            override = False

    print(inputpath,override,file)

    if not file: print("working on",inputpath)
    else: print("working on file",inputpath)

    Proccess(inputpath,override)

def Proccess(path,shouldOverride):
    print('\u001b[35m',path,'\u001b[0m')
    if not os.path.isdir(path):
        #print("working on a file, skipping to processing.")
        ProccessFile(path,shouldOverride)
        return

    for thing in os.listdir(path):
        print("\u001b[33m",os.path.abspath(path+'/'+thing),'\u001b[0m')
        Proccess(os.path.abspath(path+'/'+thing),shouldOverride)

def ProccessFile(path,shouldOverride):
    try: File = open(path,'r+')
    except FileNotFoundError: return #print("what?",path,"Doesn't exist, somehow.") ; return #No file, return.
    if not shouldOverride: OutFile = open(path+'-tabbed','w+')
    else: OutFile = File

    _, ext = os.path.splitext(path)
    if ext in ignoreList:
        print("\u001b[33m","Ignoring!!",'\u001b[0m')
        return
    
    FileLines = File.readlines()
    EndFileLines = []

    print('\u001b[44;1m',path,'\u001b[0m')
    
    for FileLine in FileLines:
        print("\u001b[41;1m",FileLine.replace('\n',''),'\u001b[0m')
        print("\u001b[42;1m",FileLine.replace('    ','<T>').strip(),'\u001b[0m')
        EndFileLines.append(FileLine.replace('    ','\t'))
        

    OutFile.writelines(EndFileLines)
        
if __name__ == "__main__":
    if not dBug: main(sys.argv[1:]) #Send the main function everything BUT the first argument, as that's always the name of the script.
    else: main(['-file','./test.txt','--no-verride-file'])
