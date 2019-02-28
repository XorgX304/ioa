# install and recompile other ppl's package on jb ios

if you encounter problems on double installations goto:
http://oldmanlab.blogspot.com/2014/11/trying-to-overwrite-applicationsdsstore.html

if you cannot register the phone as an apple developer (gray work),
then you need to install every single component on your own.

so first you need to compile it.

using the latest Xcode (V 10.1)
you can set the build system as new and not lagacy..
the new system dont requere you to sign the package.

otherwise go to:

http://iphonedevwiki.net/index.php/Xcode

and copy the xcodebuild command to build from the terminal..
make sure to specify the right arch.. ((and to change the info.plist with a plist editor
to include a CFBundleIdentifier -- otherwise dpkg cannot install it!!!! -- for gui programs..))
otherwise the program will segfault..


so you have to build the package with a CFBundle identifier (in project settings: double click the project
in the gui)

then build for testing, running and profiling..
go to build directory /products/release/ and use the .app file..
go inside the .app file (right click show package contents and copy info.plist,
when you create installdeamons then use this file as written later here..)

after this you need to go to:

http://www.saurik.com/id/7

and to:

https://gist.github.com/akayn/d9c618921eac64cd3cbe68ccbb9749d7

and follow the steps one by one (otherwise it wont work)..

(( the content of com.something.somthing.plist is the same as info.plist inside the .app file ..))

when you7r finished you should ssh ((or open terminal)) at the ios and run:

dpkg -i someshit.deb
su mobile -c uicache

a sample .deb is provided here..

good luck = )
