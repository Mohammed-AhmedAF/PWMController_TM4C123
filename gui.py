from tkinter import *
import tkinter as tk
from tkinter import ttk
import platform
from typing import List
import serial
import time
from functools import partial

def sendPWM(pwmID):
    pwmVarInt = int(pwmList[pwmID].get())
    try:
        ser.write(pwmID.to_bytes(1,'little'))
        time.sleep(0.1)
        ser.write(pwmVarInt.to_bytes(1,'little'))
    except serial.serialutil.SerialException:
        statusLabel['text'] = "Serial port is not opened!"



def connectByUART() -> None:
    global ser
    global baudrate
    if (platform.system().startswith("Win")):
        port = portCmbox.get()
    else:
        port = "dev/ttypUSB0"
    if not ser.is_open:
        try:
            baudrate = baudrateCmbox.get()
            ser = serial.Serial(port,baudrate)
            statusLabel['text'] = "Connection established!"
        except:
            statusLabel['text'] = "Connection could not be established."
    else:
        if baudrate != baudrateCmbox.get():
            ser.close()
            connectByUART()
        else:
            statusLabel['text'] = "Connection already opened!"

def disconnectUART():
    global ser
    ser.close()

#Global variables
ser = serial.Serial()
baudrate = 0


root = tk.Tk()
root.title("PWM Controller")
root.resizable(width=True,height=False)

statusLabel = Label(root,text="",relief=SUNKEN,anchor=W)
osLabel = Label(root,text=platform.system(),relief=SUNKEN,anchor=W)

connectionFrame = LabelFrame(root,text="Connection")
controlFrame = LabelFrame(root,text="Control")

baudrateCmbox = ttk.Combobox(connectionFrame,values=[9600,19200,38400,57600,115200],state="readonly")
baudrateCmbox.current(0)
portCmbox = ttk.Combobox(connectionFrame,values=["COM3","COM4","COM5","COM6","COM7","COM8","COM9","COM10","COM11","COM12","COM13"],state="readonly")
portCmbox.current(1)
connectBtn = Button(connectionFrame,text="Connect",command=connectByUART)
disconnectBtn = Button(connectionFrame,text="Disconnect",command=disconnectUART)

PWM1Frame = LabelFrame(controlFrame,text="PWM1")
PWM1SendButton = Button(PWM1Frame,text="Send",command=partial(sendPWM,0))
PWM2Frame = LabelFrame(controlFrame,text="PWM2") 
PWM2SendButton = Button(PWM2Frame,text="Send",command=partial(sendPWM,1))
pwm1Var = DoubleVar()
pwmList = [DoubleVar(), DoubleVar()]
PWM1Scale = Scale(PWM1Frame,variable=pwmList[0],from_=1,to=100,orient=HORIZONTAL)
pwm2Var = DoubleVar()
PWM2Scale = Scale(PWM2Frame,variable=pwmList[1],from_=1,to=100,orient=HORIZONTAL)
connectionFrame.grid(row=0,column=3,sticky=W+S+N+E,padx=5)
controlFrame.grid(row=0,column=0,sticky=W+S+N+E,padx=5,columnspan=3)

connectBtn.grid(row=2,column=0,sticky=W+E,padx=5,pady=5)
disconnectBtn.grid(row=3,column=0,stick=W+E,padx=5,pady=5)
baudrateCmbox.grid(row=1,column=0,sticky=W+E,padx=5,pady=5)
portCmbox.grid(row=0,column=0,sticky=W+E,padx=5,pady=5)

PWM1Frame.grid(row=0,column=0)
PWM1SendButton.grid(row=0,column=1)
PWM1Scale.grid(row=0,column=0)
PWM2Frame.grid(row=1,column=0)
PWM2SendButton.grid(row=0,column=1)
PWM2Scale.grid(row=0,column=0)

statusLabel.grid(row=2,column=0,sticky=W+E,columnspan=3,padx=5)

root.mainloop()