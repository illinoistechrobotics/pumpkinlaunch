#!/usr/bin/env python 
import Tkinter as tk 
import time
import serial
import sys
class Application(tk.Frame):
    ser=None
    def __init__(self, master=None):
        tk.Frame.__init__(self, master)
	self.ser=serial.Serial()
	self.ser.port=sys.argv[1]
        self.ser.baudrate=57600
        self.ser.timeout=1
        self.ser.open()
        self.grid()
        self.createWidgets()
    def updatePower(self):
	out='@'+str(self.valueSlider.get())+'#'
	self.ser.write(out)
        #print(out)
        self.after(40,self.updatePower)
    def fire(self):
        out='@$$$#'
	self.ser.write(out)
	#print(out) 
    def createWidgets(self):
        self.valueSlider = tk.Scale(self, label='POWER', orient=tk.HORIZONTAL, length=600, to=500)
	self.valueSlider.grid()
	self.fireButton = tk.Button(self, text='FIRE!!', command=self.fire) 
        self.fireButton.grid()
	self.quitButton = tk.Button(self, text='Quit',
            command=self.quit) 
        self.quitButton.grid()
	self.updatePower()
app = Application()
app.master.title('Pumpkin Launch Controller')
app.mainloop()
