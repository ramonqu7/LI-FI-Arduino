from tkinter import *
from basefunction import *
import tkinter.font as font
from tkinter.ttk import *
import threading
import tkinter.scrolledtext as tkst

root = Tk()
root.minsize(width=750,height=400)
root.maxsize(width=750,height=400)
root.title("Receiver Side")
#ser = serial_begin()

def PureText():
    mf.pack_forget()
    tf.pack()

    t = threading.Thread(target=text)
  #  threads.append(t)
    t.start()

def text():
    while (1):
        a = ser.readline()

        data = a
        print(data)
        if (str(data)[2:-5] == "00010"):
            #   print(2)
            while (1):
                a = ser.readline()
                data = a
                #  print(len(a))
                if (str(data)[2:-5] == "00011"):
                    #   print("END")
                    print()
                    tl.insert(INSERT,"\n")
                    break
                if (len(data) > 3):
                    print(chr(int(data, 2)), end="")
                    tl.insert(INSERT,chr(int(data, 2)))
                    sys.stdout.flush()




def Picture():
    mf.pack_forget()
    image_receive(ser)
    pf.pack()

def pic():
    flag = False
    while True:
        a = ser.readline()
        data = a

        if (len(a) > 0):
            if (not flag):
                n = int(a, 2)
                print(n)
                pic = ""
                picdata = ""
                count = 0
                while len(pic) < n * 8:
                    #  print("1")
                    a = ser.readline()
                    if (len(str(a)) > 15):
                        pic += str(a)[2:17]
                        #    print(str(a)[2:17])
                        count+=15 / n / 8 * 100
                        pl.set(str(count)+"%")
                    elif (len(str(a)) > 3):
                        pic += str(a)[2:-5]
                        # print(str(a)[2:-5])
                        count+=(len(str(a)) - 7) / n / 8 * 100
                        pl.set(str(count)+"%")

                print(pic)
                #   print(len(pic))


                i = 0
                print(pic)
                data = [pic[i:i + 8] for i in range(0, len(pic), 8)]
                print(len(data))
                for i in data:
                    data_part = i
                    x = int(data_part, 2)
                    message = chr(x)
                    picdata += message
                print(picdata)
                # picdata+="QBAEAQBAEAQBAEAQBAEAQBAEAQBAEAQBAEAQBAEAQBAf/2Q=="

                picdata = base64.standard_b64decode(picdata)

                fh = open("C:/Users/Ramon Qu/Desktop/vlc/untitled/img/imageToSave.jpg", "wb")
                fh.write(picdata)
                fh.close()
                img = mpimg.imread('C:/Users/Ramon Qu/Desktop/vlc/untitled/img/imageToSave.jpg')
                plt.imshow(img)
                plt.show()
s = Style()
s.configure('My.TFrame', background='#64ba69')
mf = ttk.Frame(root,padding="0 100 0 0",style="My.TFrame")
mf.grid(column = 0, row=0)
mf.columnconfigure(0,weight=1)
mf.rowconfigure(0,weight = 1)

buttonfont = font.Font(size=36,weight='bold')
pureTextButton = ttk.Button(mf,text="Text",width=20, font=buttonfont,command =PureText)
pureTextButton.pack(side="top")
PictureButton = ttk.Button(mf,text="Picture",command =Picture, width=20)
PictureButton.pack(side="top")
mf.pack(fill=BOTH,expand = 1)

buttonfont1 = font.Font(size=14,weight='bold')
tf = ttk.Frame(root,padding="0 100 0 0")
tl = tkst.ScrolledText(tf,font=buttonfont1,width=20,wrap=WORD)
tl.see(END)
tl.insert(INSERT,"TEXT Transmitting")
tl.pack()

pf = ttk.Frame(root,padding="0 100 0 0")
pl = StringVar()
pll = Label(pf,textvariable = pl,font=buttonfont,width=20)
pll.pack()
pl.set("Picture Transmitting")
root.mainloop()