# IOResearch

there are several parts here:<br><br><br>

1st:<br>
there are some basic explanations about compiling and running native code on jb ios.<br>
this includes patching the kernel, locating the kernel base.. etc etc<br><br>
  
  
2nd:<br>
at the "release", there is another repo there-> to run automations (fuzzers or wtvr) on ios using fb's WebDriverAgent,<br>
i wrote this for a client in java, but you can extend this to whatever you like. with that setup u are only limited <br>
to the amount of usb connections you can manage.<br>
in short: this driver uses the XCUITest platform given by apple to debug|control applications-> you can read memory-><br>
modify memory or write kernel fuzzers like this. you can also write maleware or do whatever you like.<br>
this was tested on an old macbook with 6 iphone's connected.<br><br>


3rd:<br>
there is a short explanation about hooking with CydiaSubstrate and installing unsinged apps on jb ios.<br><br>



4th:<br>
some tools and expl on how to reverse engineer the ios kernel, or ios binarys...<br><br><br><br>
