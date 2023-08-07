# Left4Dead2-Autobhop/求生之路2自动连跳插件
This cheat makes you autobhop when you hold down the spacebar in Left 4 Dead 2./此程序可以帮助你在求生之路2中实现自动连跳
## Disclaimer
I am not responsible for bans that are a result of using this software. If you choose to use this software and you get banned its on you not me.  

您不应该在VAC服务器上使用该程序，对于因使用此软件而导致的禁令，我概不负责。
## Content
Thanks to https://github.com/KnifeLemon/Left4Dead2-Autobhop-CSharp. I made a modification based on this, fixed player_base_offset and m_flags_offset in the program, and changed Left 4 Dead 2 to Left 4 Dead 2 - Direct3D 9
For the sake of beauty, I hide the console and end the program together when the program exits.   
在此感谢https://github.com/KnifeLemon/Left4Dead2-Autobhop-CSharp. 我在此基础上做了修改，将player_base_offset与m_flags_offset固定在程序内，并将Left 4 Dead 2更改成Left 4 Dead 2 - Direct3D 9
为了美观我将控制台隐藏，并在程序退出时将此程序一起结束。 
## Running
After compiling with 64x Release, double-click to run it.  
使用64x Release编译后直接双击即可运行。  
This is what I'm using on 07/08/2023 and it works fine, if the game gets updated it may change and need to be re-crawled.  
这是我在2023年8月7日使用的，它正常工作，如果游戏更新可能会变化，需要重新抓取。 
 ```
 player base = 0x724B58
 mFlags offset = 0xF0 
 ```
## Building 
 Open this project in Visual Studio 2022. Select the configuration and platform and hit build.  
 在Visual Studio 2022中打开此项目。选择配置和平台并点击构建。
