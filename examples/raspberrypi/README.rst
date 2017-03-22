Demos using Raspberry Pi 2/B+ 
=============================

| The demo consists of two nodes **led**, and
  **button**, and one topic **button\_status**. The **button** node publishes **button\_status** and
  the **led** node
  subscribes it to turn the led light when the button is pressed. 

Some additional links:

-  Raspberry Pi wifi connection  
   https://learn.adafruit.com/adafruits-raspberry-pi-lesson-3-network-setup/setting-up-wifi-with-raspbian
-  RPi easy SD card setup  
   http://elinux.org/RPi_Easy_SD_Card_Setup
-  Raspberry Pi GPIO 
   https://www.raspberrypi.org/documentation/usage/gpio-plus-and-raspi2/
-  Python on Debian Wheezy 
   http://www.extellisys.com/articles/python-on-debian-wheezy

Preparing your Raspberry Pi
---------------------------

On your host Linux machine, insert the microSD card that comes with Raspberry Pi to extract its disk image.   

::

    lsblk 
    sudo dd bs=4M if=/dev/sdb | gzip > raspbian.img.gz 
    
Now eject the microSD card that comes with Raspberry Pi, and insert a larger microSD card to copy the disk image.  

::

    unzip --stdout raspbian.img.gz | sudo dd bs=4M of=/dev/sdb
    sudo sync

Boot with a larger microSD to provide enough disk space for this demo (we recommend 16GBytes). Run the following command to expand the disk space. 

::

    sudo raspi-config 

Preparing LED and Button
------------------------

Understand GPIO on Raspberry Pi. We use GPIO 4 and 17 for the LED output and for the Button input, respectively.  

We use GPIOClass from http://www.hertaville.com/introduction-to-accessing-the-raspberry-pis-gpio-in-c.html. 

Installing Radler on Raspberry Pi
---------------------------------

Install Python 3.4 on the Raspberry Pi. 

:: 

    sudo apt-get install libncurses5-dev libncursesw5-dev libreadline6-dev
    tar -zxf /path/to/your/Python-3.4.3.tgz
    cd Python-3.4.3
    ./configure --prefix=/usr/local/opt/python-3.4.3
    make
    sudo make install
    export PATH=$PATH:/usr/local/opt/python-3.4.3/bin 

Install tarjan and pyyaml on the Raspberry Pi.  

:: 

    sudo pip3.4 install tarjan 
    sudo pip3.4 install pyyaml 

Install ROS Indigo on the Raspberry Pi. 

Follow the instructions in Step 2 at http://wiki.ros.org/ROSberryPi.

We recommend to increase the swapfile size of Raspberry Pi to 800MBytes (default is 100MBytes) by editing *CONF_SWAPSIZE* in */etc/dphys-swapfile*, and restart dphys-swapfile. 

:: 

    /etc/init.d/dphys-swapfile stop
    /etc/init.d/dphys-swapfile start 

CMake 2.8.12 or higher is required on the Raspberry Pi.

:: 

    wget http://www.cmake.org/files/v3.2/cmake-3.2.2.tar.gz
    tar xf cmake-3.2.2.tar.gz
    cd cmake-3.2.2
    ./configure
    make
    sudo apt-get install checkinstall
    sudo checkinstall
    dpkg -i ~/cmake-3.2.2/cmake_3.2.2-1_armhf.deb 

Run ROS master on the Raspberry Pi. 

::

    export ROS_MASTER_URI=http://localhost:11311
    roscore 

Run the raspberrypi example.  

::

    mkdir -p /tmp/catkin_ws/src
    cd /path/to/radler 
    ./radler.sh --ws_dir /tmp/catkin_ws/src compile examples/raspberrypi/raspberrypi.radl --plant plant --ROS 
    cd /tmp/catkin_ws 
    catkin_make 
    cd /tmp/catkin_ws/devel/lib/raspberrypi
    sudo chown -v root.root led 
    sudo chmod 4755 led 
    ./led
    ./button  
