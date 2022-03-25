# CubeRobot
In 2017, Zeguang Chang and I built a cube robot using DSP and STM32. We open source all the code of CubeRobot in this repository.   
You can find the complete restore process on [BiliBili](https://www.bilibili.com/video/BV1v3411p71n/).  

<div align=center>
<img src=./others/img.png height=320 />
</div>

- In terms of hardware, we adopt a four-axis structure, with four mechanical arms to complete the blessing and rotation of the cube.
- In terms of software, the robot consists of two subsystems: sensing system and control system.  

We use both **DSP** development board ([TMS320C6748](https://item.taobao.com/item.htm?spm=a230r.1.14.136.6f9cd3d7T6jq1c&id=35497623592&ns=1&abbucket=10#)) and **STM32** development board ([STM32F407ZGT6 ARM](https://detail.tmall.com/item.htm?id=609294673401&ali_refid=a3_430582_1006:1267360122:N:rwYulnb0YUXHh1bSqNmuYA==:0b03e6be02c07ba1ad753cf8e7ee17b3&ali_trackid=1_0b03e6be02c07ba1ad753cf8e7ee17b3&spm=a230r.1.14.8)).
The **DSP system** is equipped with an ov5640 camera, which can complete the color recognition task, while the **STM32 system** controls 4 steering gears and 4 stepping motors to complete all actions of cube restoration.

## DSP (Sensing System)
In the `CubeRobot_DSP` directory, we release all code of the sensing system. The `src/main_camera.c` contains the main function, and the `inc/` contains all subfunctions and head files. 
- Note that the `inc/color.c` is the most important file because it performs the **Color Recognition Task** and **Cube Solving Task**.  
- The `src/main_camera.c` performs communication with STM32 and basic logic of trigger the solving action.  

As we developed this project in [CCS5.5 IDE environment](https://blog.csdn.net/u010398722/article/details/78298948), we have also provide the original CCS project files in `others/CubeRobot_CCS-5.5_Project.zip`.

## STM32 (Control System)
In the `CubeRobot_STM32` directory, we release all code of the control system. These code aims to control the coordination of 4 stepping motors and 4 steering gears. The steering gear controls the forward and backward movement of the mechanical arm, and the stepping motor controls the rotation angle.

## Acknowledge
This project was completed by me and Zeguang Chang. Thank him for working side by side all the time. 
I also thank for joining the Linear Motor Laboratory leaded by Jiwen Zhao during my undergraduate period, where I spent four years of unforgettable time.
