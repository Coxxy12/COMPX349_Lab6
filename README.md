# Table of Contents
1. [General Info](#general-info)
2. [Images](#images)
3. [Technologies](#technologies)
4. [Installation](#installation)
5. [Run](#run)
6. [Collaboration](#collaboration)
7. [Repository overview](#repository-overview)
8. [License](#license)
### General Info
***
**Lab 5**

The micro:bit serial port is to be used by the lab for debugging. 

***Setup***

There is no physical setup required beyond the standard plugging in because the micro:bit serial port runs over the usb connection.
A terminal software is required on the host in order to connect to the serial device.

When you plug the micro:bit in, the serial device ought to be formed immediately. 

* Minicom is the most popular application for Linux, and /dev/ttyACM0 should be used as the serial device.
On the lab computers, start this by typing $ minicom -D /dev/ttyACM0.

* The serial device on a Mac will look like this: /dev/ttyusbmodem145102.
Any serial programme will work to connect.
A decent free one is CoolTerm.

* Use a terminal emulator on Windows, such as Teraterm or Hyperterminal.
A USB serial device should be found. 

The micro:standard bit's serial speed is 115200, and its default parameters are 8-N-1, which are typical for serial devices. 

***Task***

The serial port can be used to read and write messages.
Similar to how printf() is used while programming on a host computer, messages to the serial port can be used for debugging.

Download and build the programme print ser.cpp.
Messages submitted to the micro:bit over the serial port will be shown on the micro:bit screen by this programme.
Connect to the micro:bit serial port once it's operating to make sure you're seeing written messages on the screen.

Create a programme modification that sends typed messages back to the terminal. 

Utilize a programme you created for lab 4 or lab 5 and add serial output so that messages are displayed to the console when events occur, such as a pixel nearing the border of the screen. 

***Marks***

* This lab is worth 2% of the final grade.

***Outcomes***

Once this lab is compleate you should have gain experience with the micro:bit serial port that is to be used by the lab for debugging I have learned alot inregard to the 
C programming language and how multi-threaded tasks are handled accross multi-paged programs. However, due to personal family matters and a change of circumstances, I was unable to 
fix the remaining memory issues which I believed to have caused the results below.

### Images
***
***Task***

![Debug pic](/images/debug.png)

* As you can see when you run the program, a message comes to the serial port window when you push a button.


## Technologies
***
A list of technologies used within the project:
* [gcc](https://gcc.gnu.org/): Version 9.4.0
* [nano](https://nano-editor.org/): Version 4.8

## Installation
***
A little intro about the installation. 
```
$ git clone https://github.com/lancaster-university/microbit-dal.git
```
## Run
***
**How to run**

To edit the code:
```
$ cd micro\:bit/
$ cd microbit-v2-samples/
$ source/
$ nano main.cpp
```
In a different termial, to compile the code:
```
$ cd micro\:bit/
$ cd microbit-v2-samples/
$ cd build
$ make
```
From this it will make a .hex file that you just need to drag onto the micro:bit which is located in:
```
$ cd micro\:bit/
$ cd microbit-v2-samples/
~"MICROBIT.hex"
```

## Collaboration
***
Just do what you want with this.
> Do what you want, whats done is done. 
## Repository overview
An overview of the directory structure and files:
```
.
├── images
│   └── debug.png
├── README.md
└── src
    ├── main.cpp
    ├── MICROBIT.hex
    └── print_ser.cpp

2 directories, 5 files


```
## License
MIT License

Copyright (c) 2022 Cameron Cox

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

https://github-readme-stats.vercel.app/api?username=coxxy12
