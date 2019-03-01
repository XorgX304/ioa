# ioa
automating (fuzzing) native ios, using fb's wda..<br><br>

This project is a wrapper around fb's web driver agent.<br>
given an example that make's use of https://github.com/MTJailed/XNU-Kernel-Fuzzer , in order to fuzz the ios kernel.<br>
but we are not limited to this usage.<br><br>

i maid this interface in order to make the process of automating native ios easier.<br>
current platforms and open source solutions can be a real headache to manage (imho).<br><br>

with this interface you can easily install and configure native ios for fuzzing | automation.<br><br><br>

# installation
**This is meant to be used on MacOS**
<br><br>
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
follow: http://appium.io/docs/en/drivers/ios-xcuitest-real-devices/ , if in trouble.<br>
Make sure that iTunes is installed and that the devices are trusted by the computer and vice versa.
unable UIAutomations, http services and disable rate limiting under the 'developer options'<br>
((at the device settings))<br><br>

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

# Usage
**after installation ofc..**<br>
((exampled here a fuzzing setup using mtjialed xnufuzzer))<br><br>

go to the '/bin' directory.<br>
install CydiaImpactor and open it.<br>
Choose the device that you would like to run, and drag the Fuzzer.ipa to the impactor tab.<br>
enter some appleid (not a paid developer one!) and approve the profile on the device.<br>
open a terminal and cd to the '/wd/wda' directory.<br>
run:<br><br>

	$ python master.py
	
<br>
follow the onscreen instruction.<br>
if you did everything right then you should be able to run:<br><br>

	>run [device name] [BundleId]
	>stop [device name]
	
EXAMPLE:<br><br>

	>run iPhone ml.jailed.XNUFuzzer
	
# Contributing | Extending

to change the automation functionality:<br>
load the ioa eclipse project (zipped at '/bin/ioa.zip')<br>
and change the java code (look at the '/src/examples')<br>

**open a github issue for any inquiries**
