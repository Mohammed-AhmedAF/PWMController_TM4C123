from tkinter import *
import tkinter as tk
from tkinter import ttk
import platform
import serial
import time

def sendPWM1():
    pwmVarInt = int(pwm1Var.get())
    print(pwmVarInt)
    ser.write(b'a')
    time.sleep(0.20)
    ser.write(pwmVarInt.to_bytes(1,'little'))

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

PWM1Frame = LabelFrame(controlFrame,text="PWM1")
PWM1SendButton = Button(PWM1Frame,text="Send",command=sendPWM1)
PWM2Frame = LabelFrame(controlFrame,text="PWM2")
PWM2SendButton = Button(PWM2Frame,text="Send")
pwm1Var = DoubleVar()
PWM1Scale = Scale(PWM1Frame,variable=pwm1Var,from_=1,to=100,orient=HORIZONTAL)
pwm2Var = DoubleVar()
PWM2Scale = Scale(PWM2Frame,variable=pwm2Var,from_=1,to=100,orient=HORIZONTAL)
connectionFrame.grid(row=0,column=3,sticky=W+S+N+E,padx=5)
controlFrame.grid(row=0,column=0,sticky=W+S+N+E,padx=5,columnspan=3)

connectBtn.grid(row=2,column=0,sticky=W+E,padx=5,pady=5)
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