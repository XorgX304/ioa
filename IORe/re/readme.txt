

to hook patch the kernel we first need to diassamble it.
there are two ways to go:

  live dump:
    you can use the tool i wrote for this.
    but its not reliable as apple can add more mitigations to fight kernel patching..
    and this can lead to my tool disfunction.

    (basiclly im reading the kernel memory to get the kernel base ((or any other loaded module,
    based on binary values)) and then we can just hex dump the memory into a file and load it to ida/hopper))

    but its like the chiken and egg cuz to find a module by sig you need to know the sig first, so u have to 
    diassmble first.

    the main attraction for this mathod is that u don't need to decrypt the kernel.
    and you dont really need offsets.
    if your good with asseambly then you can simply open the binary in an hex editor and enter the first instructions,
    to find a function or var..
    
 decrypt and unzip the module from an ipsw or an image:
 
   ipsw are kernel updates that apple push regularly to users to update there system.
   we can unzipp the content and inside you can find the entire system.
   the problem is (and this can be a big pain), is that you have to decrypt and unzipp it.
   if its ios < ios5s then the image is encrypted with img3 type, later then that is img4.
   unfortunately not all keys to all the kernels are available and not all kernel images are available.
   
   so what you need to do is like this:
    go to: https://ipsw.me/#download
    there you can find both complete images and ipsw update images.
    unzip the image,
    locate the kernelcache file that looks like: kernelchache.release.n****
    (or any other module you want to patch..)
    
    (all the binarys are compiled and works on apple you can find them in this library..)
    
    for iphone <= iphone 5c (5,3):
      run (put the tools and the kernelchache at the same directory):
      
      
      
      now: its very important to note that every kernel is different, and there are many ver
      for every kernel so make sure its the right key and iv and the right kernel, otherwise you'll
      waist a shit load of time, like i did.
      
      keys and ivs can be located at:
        https://www.theiphonewiki.com/wiki/Firmware_Keys/7.x
        and an example of a good way to work is to download the firmware directlly like at this page:
          https://www.theiphonewiki.com/wiki/Sochi_11D167_(iPhone5,3)
          and then you know that you got the right keys for it..
          
      after you make sure everything is right then run:
          
          
      ./xpwntool kernelcache.release.n48 kernel.n48.decrypted5 -k [key] -iv [iv] -decrypt 
      
      you can make sure that the command completed good if you open the file in an hex editor.
      if there are zeros (like 4-7 lines) and then facefeed or something similar then you'r good.
      if there are a lot of %20 or the binary simply start from the beggining then you did something wrong,
      probably you trying with the wrong key-iv combination for this kernel.
      
      when your done open the decrypted kernel with hex editor and find the offset for facefeed or other variants,
      
      and run:
      
      ./lzssdec -o OFFSET < kernel.decrypted > kernel.maco.armv
      
      if you did everything right then loading the image to a diassambler should result in the image being recognized,
      as a maco executable for arm,
      and the first strings in the kernel would be the kernel ver..
      maybe you have to wait a few minutes till the diassambler will make progress,
      
      --if its not there then you did something wrong!!!
      
      
   for iphone > iphone 5c (5,3):
   
        repeat the exact same steps but with img4:
        
        instead on xpwntool use:
        
        ./img4 -image infile outfile ivkey
        
        where ivkey is the string of the iv followed by the key (connected)..
        
        all other is the same..
        
        
        yoo can find img4, xpwntool, and lzssdec here..
        
        you can also find an encrypted a decrypted and a dec+decompressed kernels here..
   
   
   
   
   
   
   
