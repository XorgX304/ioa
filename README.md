# ioa
automating (fuzzing) native ios, using fb's wda..<br><br>

This project is a wrapper around fb's web driver agent.<br>
given an example that make's use of https://github.com/MTJailed/XNU-Kernel-Fuzzer , in order to fuzz the ios kernel.<br>
but we are not limited to this usage.<br><br>

i maid this interface in order to make the process of automating native ios easier.<br>
current platform and open source solutions can be a real headache to manage.<br><br>

with this interface you can easily install and configure native ios for fuzzing | automation.<br>

# Usage
<br>
install dependencies:<br><br>
download this directory and extract it some where.<br>
from the extracted directory open terminal and run:<br><br>

	$ bash wd/setup.sh

<br> 
if anything shows errors at the setup.sh, then open the file and run every line separately.<br>
The same is true for setup_helper.py (this is run automatically).<br>
Open a github issue at this repository so i can fix the error.
<br><br>
install java from https://www.oracle.com/technetwork/java/javase/downloads/index.html . <br>
install xcode from: https://developer.apple.com/xcode/ . <br><br>

open the .xcodeproj file at the '/wd/wda' directory.<br>
Change the bundleid to something else (for every sub project as well as the main one).<br>
follow: http://appium.io/docs/en/drivers/ios-xcuitest-real-devices/ , if in trouble.<br><br>

build the driver and test it on one device at least once:<br>
from the '/wd/wda' directory open terminal and run:<br><br>

	$ xcodebuild -project WebDriverAgent.xcodeproj -scheme WebDriverAgentRunner -destination 'id=<udid>' test

((replace <udid> with the device udid,<br>
run:<br>
instruments -s devices<br>
to get the udid))<br>
now only register every other device you would like to run (by changing the target for the build<br>
at xcode and clicking register device..)<br><br>
	
The difference from a paid developer account to a normal one is the amount of devices you can run:<br>
paid: 100<br>
normal: 4<br><br>

or jailbreak the device and install on your own.<br>
check out: https://github.com/akayn/IORe , on how to do that...<br>

<br>


