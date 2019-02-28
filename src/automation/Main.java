package com.media.automation.testing;



import java.net.MalformedURLException;
import java.net.URL;
import java.util.concurrent.ThreadLocalRandom;

import org.openqa.selenium.remote.DesiredCapabilities;
import org.openqa.selenium.remote.DriverCommand;
import org.openqa.selenium.remote.RemoteExecuteMethod;
import org.openqa.selenium.By;
import org.openqa.selenium.Dimension;
import org.openqa.selenium.JavascriptExecutor;
import org.openqa.selenium.NoSuchElementException;
import org.openqa.selenium.Platform;
import org.openqa.selenium.WebDriverException;
import org.openqa.selenium.WebElement;

import org.openqa.selenium.remote.RemoteWebDriver;
import org.openqa.selenium.support.ui.ExpectedConditions;
import org.openqa.selenium.support.ui.WebDriverWait;
import org.openqa.selenium.remote.CapabilityType;

import io.appium.java_client.MultiTouchAction;
import io.appium.java_client.TouchAction;
import org.openqa.selenium.Dimension;

import java.time.Duration;

import static io.appium.java_client.touch.TapOptions.tapOptions;
import static io.appium.java_client.touch.WaitOptions.waitOptions;
import static io.appium.java_client.touch.offset.ElementOption.element;
import static io.appium.java_client.touch.offset.PointOption.point;
import static java.time.Duration.ofMillis;
import static java.time.Duration.ofSeconds;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;

import io.appium.java_client.ios.IOSDriver;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Random;
import java.util.Scanner;
import java.util.concurrent.TimeUnit;

import io.appium.java_client.AppiumDriver;
import io.appium.java_client.MobileBy;
import io.appium.java_client.MobileElement;
import io.appium.java_client.TouchAction;
import io.appium.java_client.ios.IOSElement;
import io.appium.java_client.remote.MobileCapabilityType;

public class Main {
    
    
    public static List<String> SeTargets = new ArrayList<String>();
    
    
    @SuppressWarnings("rawtypes")
    public static AppiumDriver gdrv;
    public static URL url;
    public static int OSVersion;
    public static String udid;
    public static String URL_STRING;
    public static String wdurl;
    public static String dname;
    public static String apurl;
    public static String port;
    public static String Tar;
    public static int mode = 1;
    public static Boolean debug = false;
    
    
    
    public static void shuffleArray(List<String> a) {
        int n = a.size();
        Random random = new Random();
        random.nextInt();
        for (int i = 0; i < n; i++) {
            int change = i + random.nextInt(n - i);
            swap(a, i, change);
        }
    }
    
    
    private static void swap(List<String> a, int i, int change) {
        String helper = a.get(i);
        a.set(i, a.get(change));
        a.set(change ,helper);
    }
    
    
    
    public static void Argp(String[] args) {
        
        
        
        if (args.length==0) {
            
            OutPut(9);
            
        }
        
        else if (args.length<6) {
            
            
            for (String s1: args)
            {
                if (s1.contains("-help")) {
                    OutPut(13);
                }
            }
            
            OutPut(9);
            
        }
        
        else if ((6<=args.length)){
            
            for (String s1: args)
            {
                if (s1.contains("-help")) {
                    OutPut(13);
                }
            }
            
            Boolean g = false;
            
            
            for (String s1: args)
            {
                if (s1.contains("-help")) {
                    OutPut(13);
                }
                g = false;
            }
            
            for (String s1: args)
            {
                if (s1.contains("-wdurl=")) {
                    g = true;
                    wdurl = s1.replace("-wdurl=", "");
                    break;
                }
                g = false;
            }
            
            for (String s1: args)
            {
                if (s1.contains("-udid=")) {
                    g = true;
                    udid = s1.replace("-udid=", "");
                    break;
                }
                g = false;
            }
            
            for (String s1: args)
            {
                if (s1.contains("-osv=")) {
                    g = true;
                    OSVersion =  Integer.parseInt(s1.replace("-osv=", ""));
                    break;
                }
                g = false;
            }
            
            for (String s1: args)
            {
                if (s1.contains("-apurl=")) {
                    g = true;
                    apurl = s1.replace("-apurl=", "");
                    break;
                }
                g = false;
            }
            
            for (String s1: args)
            {
                if (s1.contains("-dname=")) {
                    g = true;
                    dname = s1.replace("-dname=", "");
                    break;
                }
                g = false;
            }
            
            
            for (String s1: args)
            {
                if (s1.contains("-BundleId=")) {
                    g = true;
                    Tar = s1.replace("-BundleId=", "");
                    break;
                }
                g = false;
            }
            
            
            
            
            
            
            if (g==false) {OutPut(9);}
            else{return;}
            
            
        }
        
        
        
        
    }
    
    
    private static void OutPut(int y) {
        
        if (y==13) {
            
            
            System.exit(0);
            
            
        }
        
        else if (y==9) {
            
            
            System.exit(0);
            
        }
        
        System.exit(0);
        
    }
    
    
    public static void main(
                            String[] args
                            )
    {
        
        
        Argp(args);
        
        int h = 0;
        
        
        
        while (true) {
            
            
            try {
                if (h==0) {
                    
                    
                    
                    LaunchApp(true);
                    
                }
                
                else {
                    LaunchApp(false);
                }
                
                h =1;
                
                
                
            } catch (MalformedURLException e) {
                System.out.println("\n\n");
                System.out.println(e);
                System.out.println("\n\n");
                e.printStackTrace();
            }
            
        }
    }
    
    
    @SuppressWarnings("rawtypes")
    private static void LaunchApp(boolean frstrun) throws MalformedURLException {
        
        if (frstrun) {
            
            URL URL;
            final String U_S = apurl + "/wd/hub";
            URL = new URL(U_S);
            String browserName = "mobileOS";
            DesiredCapabilities cap = new DesiredCapabilities(browserName, "", Platform.ANY);
            
            cap.setCapability("user", "root");
            cap.setCapability("password", "alpine");
            cap.setCapability("deviceName", dname);
            cap.setCapability("platformName", "iOS");
            cap.setCapability("udid", udid);
            cap.setCapability("automationName", "XCUITest");
            cap.setCapability("webDriverAgentUrl", wdurl);
            cap.setCapability("app", Tar);
            cap.setCapability("noReset", "true");
            cap.setCapability("newCommandTimeout", "0");
            
            
            gdrv = new AppiumDriver(URL, cap);
            try {
                Thread.sleep(30000);
            } catch (Exception er) {}
            
            
        }
        
        else {
            
            gdrv.launchApp();
            gdrv.resetApp();
            try {
                Thread.sleep(30000);
            } catch (Exception er) {}
        }
        
        
        
    }
    
    
}

