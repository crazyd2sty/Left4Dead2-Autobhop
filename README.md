# Left4Dead2-Autobhop/求生之路2自动连跳外置插件
This cheat makes you autobhop when you hold down the spacebar in Left 4 Dead 2.  
此程序可以帮助你在求生之路2中实现自动连跳
## Disclaimer
You should not use this program on the VAC server, there is a chance that this program will be banned by VAC!  
您不应该在VAC服务器上使用该程序，此程序会有概率遭到VAC封禁！
## Content
Thank the [https://github.com/KnifeLemon/Left4Dead2-Autobhop-CSharp](https://github.com/mads256h/l4d2-autobhop) project and adapt it to the latest game version.  
在此感谢[https://github.com/KnifeLemon/Left4Dead2-Autobhop-CSharp](https://github.com/mads256h/l4d2-autobhop)项目,并适配最新的游戏版本.  
 ```
Original process starts
├─Generate a random copy
├─Start the copy process
└─Exit

Copy process starts
├─Delete the original .exe
├─Wait for the game window to appear
├─Get game memory data
├─Hide the console
└─Enter a continuous jump loop
├─Detect the space bar
├─Read the player status
├─Send a key message
└─Window survival detection
 ```
## Running
After compiling with 64x Release, double-click to run it.  
使用64x Release编译后直接双击即可运行。  
 ```
 player base = 0x726BD8
 mFlags offset = 0xF0 
 ```
Currently available player base offsets are:  
目前可用的 player base偏移为:  
 ```
0x726BD8, 0x73A574, 0x7C4424, 0x7C4450, 0x7C4644  
 ```
## Building 
 Open this project in Visual Studio 2022. Select the configuration and platform and hit build.  
 在Visual Studio 2022中打开此项目。选择配置和平台并点击构建。  
## Warn
 If you want to play on a VAC server, please use the Random_name version. (What if it works?)  
 如果想要在VAC服务器上游玩，请使用Random_name版本。（不确定是否工作？）  
 
 Updated on March 28, 2025,Enjoy！
