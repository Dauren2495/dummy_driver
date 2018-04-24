Files in this directory are taken from this links [1](https://www.codeproject.com/Articles/112474/A-Simple-Driver-for-Linux-OS) and
[2](http://derekmolloy.ie/writing-a-linux-kernel-module-part-2-a-character-device/).

Sorry, for not writing the code by myself,but I thought these links give more clean and easy to understand code. Also, the tutorials itself are very concise and much easier to follow compared to LDD book.

To run this code we need to to the following steps

```shell
cd  /lib/modules/`uname -r`/build  
make modules_prepare  
cd path-to-driver-directory  
make load  
mknod /dev/dummy-driver c  250 0  

```  


