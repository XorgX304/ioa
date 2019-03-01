# ioa
automating (fuzzing) native ios, using fb's wda..<br><br>

This project is a wrapper around fb's web driver agent.<br>
given an example that make's use of https://github.com/MTJailed/XNU-Kernel-Fuzzer , in order to fuzz the ios kernel.<br>
but we are not limited for this usage.<br><br>

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
Open a github issue at this repository so i can fix the error.
<br><br>
install java from https://www.oracle.com/technetwork/java/javase/downloads/index.html . <br>
install xcode from: https://developer.apple.com/xcode/ . <br><br>


