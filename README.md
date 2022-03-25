# CubeRobot
In 2017, Zeguang Chang and I built a cube robot using DSP and STM32. We open source all the code of CubeRobot in this repository.   
You can find the complete restore process on [BiliBili](https://www.bilibili.com/video/BV1v3411p71n/).  
<img src=./Others/img.png height=40% />

- In terms of hardware, we adopt a four-axis structure, with four mechanical arms to complete the blessing and rotation of the cube.
- In terms of software, the robot consists of two subsystems: sensing system and control system.  

We use both **DSP** development board and **STM32** development board.
The **DSP system** is equipped with an ov5640 camera, which can complete the color recognition task, while the **STM32 system** controls 4 steering gears and 4 stepping motors to complete all actions of cube restoration.

## DSP (sensing system)
<!-- 完整的还原过程请见如下网址。在此仓库中我们开放了所有代码。

    1、DSP：颜色识别与复原过程解算

    2、STM32：控制电机

 -->

## STM32 (control system)

