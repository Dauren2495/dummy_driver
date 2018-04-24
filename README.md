Files in this repository are the mixture from these two links [1](https://www.codeproject.com/Articles/112474/A-Simple-Driver-for-Linux-OS) and
[2](http://derekmolloy.ie/writing-a-linux-kernel-module-part-2-a-character-device/).

Sorry, for not writing the code by myself, I thought these links give more clean and easy to understand code. Also, the tutorials itself are very concise and much easier to follow compared to LDD book.

To run this module we need to do the following steps

```shell
cd  /lib/modules/`uname -r`/build  
make modules_prepare  
cd  
git clone https://github.com/Dauren2495/dummy_driver.git  
cd dummy_driver    
make load  
mknod /dev/dummy-driver c  250 0  
```  
If successful you must get the following output

```shell
$ ./test
 Starting device test code example...
 Type in a short string to send to the kernel module:
 [Message you typed]
 Writing message to the device [Message you typed].
 Press ENTER to read back from the device...
 Reading from the device...
 The received message is: [Message you typed([length of 'message'] letters)]
 End of the program
```

However, as I said I could't get this output because of some Ubuntu issue with [not complete build of kernel](https://stackoverflow.com/questions/39107811/no-rule-to-make-target-arch-x86-entry-syscalls-syscall-32-tbl-needed-by-arch)

