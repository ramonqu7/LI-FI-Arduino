import serial
import binascii
import sys
import base64
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
from tqdm import tqdm

from tkinter import *
from tkinter import ttk
def serial_begin():
    ser = serial.Serial('COM3', 115200, timeout=.1)
    return ser


def image_receive(ser):
    flag = False
    while True:
        a = ser.readline()
        data = a
        if (len(a) > 0):
            pbar = tqdm(total=100)
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
                        pbar.update(15 / n / 8 * 100)
                    elif (len(str(a)) > 3):
                        pic += str(a)[2:-5]
                        # print(str(a)[2:-5])
                        pbar.update((len(str(a)) - 7) / n / 8 * 100)

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

def text_receive(ser,tl):
    while (1):
        a = ser.readline()

        data = a
        if (str(data)[2:-5] == "00010"):
            #   print(2)
            while (1):
                a = ser.readline()
                data = a
                #  print(len(a))
                if (str(data)[2:-5] == "00011"):
                    #   print("END")
                    print()
                    tl.insert(INSERT,"\t")
                    break
                if (len(data) > 3):
                    print(chr(int(data, 2)), end="")
                    tl.insert(INSERT,chr(int(data, 2)))
                    sys.stdout.flush()