import os
import time
import datetime
import sys, getopt

weekDays = ("Mon","Tue","Wed","Thu","Fri","Sat","Sun")

file_extensions = [
               '.c', 
               '.h', 
               ]

def file_len(fname):
    i = 0
    with open(fname, errors="ignore") as f:
        for i, l in enumerate(f):
            pass
    return i + 1

def main(argv):
    # Getting the current work directory (cwd)
    thisdir = os.getcwd()

    name_list = []

    ext_len = len(file_extensions)
    extension_list = ''
    index = 0
    for file_extension in file_extensions:
        extension_list = extension_list + "*" + file_extension
        index = index + 1
        if index < ext_len:
            extension_list = extension_list + ', '
    
    print ("Lines    Filename")
    print ("-------  -----------------------------------------------------------------------")
    total_files = 0;
    total_lines = 0;
    # r=root, d=directories, f = files
    mtimelatest = 0
    filelatest = ""
    for r, d, f in os.walk(thisdir):
        for file in f:
            # Find last occurence of '.' (extension)
            #print ("- " + file)
            position = file.rfind('.')
            extension = file[position:]
            #print ("-> " + extension)
            for file_extension in file_extensions:
                if file_extension == extension:
                    filename = os.path.join(r, file)
                    # Check file is not 0 bytes
                    file_size = os.stat(filename).st_size
                    if file_size != 0:
                        mtime = os.path.getmtime(filename)
                        if (mtimelatest < mtime):
                            mtimelatest = mtime
                            filelatest = filename
                        lines = file_len(filename)
                        if lines != 0:
                            total_lines += lines
                            total_files += 1
                            print ('{:7d}'.format(lines), "", filename)
                            name_list_entry = "{0} {1}".format(time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(mtime)), filename)
                            name_list.append(name_list_entry)

    no_of_entries = 20
    argc = len(argv)
    if (argc > 1):
        no_of_entries = int(argv[1])
    print ('{:7d}'.format(total_lines), "lines in", total_files, "files (" + extension_list + ")")
    print("Last {0} modified files:".format(no_of_entries))
    name_list.sort()
    list_count = len(name_list)
    list_index_start = list_count - no_of_entries
    index = 0
    text = ""
    for nl in name_list:
        if (index >= list_index_start):
            # 2019-12-04 15:36:49 c:\TrueStudio910\...
            nlsplit = nl.split()
            date = nlsplit[0].split("-")
            weekday = datetime.datetime(int(date[0]), int(date[1]), int(date[2]), 0, 0, 0, 0).weekday()
            line = weekDays[weekday] + " " + nl
            text += line + "\n"
            #print (line)
        index += 1

    #text = "" + time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(mtimelatest)) + " " + filelatest
    filename = "Latest_" + time.strftime('%Y%m%d_%H%M%S', time.localtime(mtimelatest)) + ".txt"
    #filename = "Latest.txt"
    f = open(filename, "w")
    f.write(text)
    f.close()
    #print("ext_list " + extension_list)

    #print ('Argument List:', str(sys.argv))
    #print (argv)
    #print ('Number of arguments:', len(argv))
    #print ("argv:", argv)

if __name__ == "__main__":
    #main(sys.argv[1:])
    
    main(sys.argv)
    
   
