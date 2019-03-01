#!/usr/bin/env bash
unzip automation.zip
unzip wda.zip
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
brew update
brew uninstall --ignore-dependencies libimobiledevice
brew uninstall --ignore-dependencies usbmuxd
brew install --HEAD usbmuxd
brew unlink usbmuxd & brew link usbmuxd
brew install --HEAD libimobiledevice
brew link --overwrite libimobiledevice
brew install ideviceinstaller
brew link --overwrite ideviceinstaller
brew install ios-webkit-debug-proxy
brew install node
brew install ideviceinstaller
npm install -g appium
brew install carthage
npm install -g ios-deploy
npm install -g deviceconsole
npm install iproxy
python setup_helper.py

