'''
Li-Fi VIsible Light Communication System. Yiren Ramon Qu, Lyndon Institute, VT
MIT License
Copyright (c) 2017 Yiren Qu

Li-Fi Receiver Side
'''
import serial
import binascii
import sys
import base64
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
from tqdm import tqdm

ser = serial.Serial('COM3', 115200, timeout=.1) # Start the serial connectiion


print("######################################################\n"
      "##--------------------START-------------------------##\n"
      "######################################################\n"
      "##-------------------Receiver-----------------------##\n"
      "##---------------------Side-------------------------##\n"
      "##----------------Start Receiving ------------------##\n"
      "##--------------------------------------------------##\n"
      "######################################################\n"
      )
a = input()
'''
Input 's' or 't'
's'  - Receving the image
't'  -  Receving the text
'''
if (a == "s"):
    print(
      "##-------------Receiving Image Mode--------------##\n"
      "##--------------------------------------------------##\n"
      "||||||||||||||||||||||||||||||||||||||||||||||||||||||\n"
      "VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV\n"
      "                                                      \n"
     )
    flag = False
    while True:
        a = ser.readline()
        data = a
        if (len(a) > 0):
            pbar = tqdm(total=100)
            if (not flag):
                n = int(a, 2)
                # n is the number of packets need to be received
                print(n)
                pic = ""
                picdata = ""
                count = 0
                while len(pic) < n * 8:
                    # Receive the packet and save back to a complete binary string
                    a = ser.readline()
                    if (len(str(a)) > 15):
                        pic += str(a)[2:17]
                        pbar.update(15 / n / 8 * 100)
                    elif (len(str(a)) > 3):
                        pic += str(a)[2:-5]
                        pbar.update((len(str(a)) - 7) / n / 8 * 100)
                print(pic)
                i = 0
                #Parse the image to 8 bits/group and convert back to character
                data = [pic[i:i + 8] for i in range(0, len(pic), 8)]
                print(len(data))
                for i in data:
                    data_part = i
                    x = int(data_part, 2)
                    message = chr(x)
                    picdata += message
                print(picdata)
                #The string is a base-64 string representing an image
                picdata = base64.standard_b64decode(picdata)
                #Save this image and open it with plot library
                fh = open("C:/Users/Ramon Qu/Desktop/vlc/pypic/img/imageToSave.jpg", "wb")
                fh.write(picdata)
                fh.close()
                img = mpimg.imread('C:/Users/Ramon Qu/Desktop/vlc/pypic/img/imageToSave.jpg')
                plt.imshow(img)
                plt.show()
if a=="t" :
    print(
        "##-------------Receiving Text Mode---------------##\n"
        "##--------------------------------------------------##\n"
        "||||||||||||||||||||||||||||||||||||||||||||||||||||||\n"
        "VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV\n"
        "                                                      \n"
    )
    count = 0
    while(1):
        a = ser.readline()
        data = a
        if(str(data)[2:-5]=="00010"):
            #Detect whether received a start signal binary
         print("----------------> No."+(str(count)),end="")
         while(1):
                a = ser.readline()
                data = a
                if(str(data)[2:-5]=="00011"):
                    #If detecting the end signal, exit and wait a new start.
                    print()
                    count+=1
                    break
                if(len(data)>3):
                    #If it is a character, print this character on the same line.
                    print(chr(int(data,2)),end="")
                    sys.stdout.flush()

