Demos using AR.Drone on ROS/Secure\_ROS
=======================================

| Demos are available for two types of AR.Drone drivers: Demo \#1 with **ardronelib**
  (AR.Drone sdk) and Demo \#2 with **ardrone\_autonomy** (ROS driver).
| Both demos consists of at least three nodes **sridrone**, **led**, and
  **camera**, and three topics **navdata**, **led\_anim**, and
  **camera\_param**. The **sridrone** node publishes **navdata** and
  subscribes **led\_anim** and **camera\_param** to generate signals
  that control LED animation and video input. The **led** node
  subscribes **navdata** and publishes **led\_anim** to indicate
  unstable roll (LEFT\_GREEN\_RIGHT\_RED or LEFT\_RED\_RIGHT\_GREEN) or
  low battery level (BLINK\_RED). The **camera** node subscribes
  **navdata** and publishes **camera\_param** to toggle the video feed
  between front/bottom cameras.
| Demo \#1 additionaly supports for three other nodes: **key**, **timer**, and **landing**.  
  The **key** node provides drone flight control using keyboard. The **timer** node provides timer-based drone flight control, e.g., landing after 2 seconds of hovering over 50cm. 
  The **landing** node provides altitude-based landing, e.g., landing if the altitude is less than 50cm.  
| Each demo can run on **ROS** and **Secure\_ROS**.

.. image:: sridrone_rqt_graph.png  
   :alt: ""

.. image:: ../examples/drone/sridrone_rqt_graph.png  
   :width: 600px 
   :alt: ""

Some additional links:

-  AR.Drone Developer Guide
   http://www.msh-tools.com/ardrone/ARDrone\_Developer\_Guide.pdf
-  Parrot developer site for SDK
   http://developer.parrot.com/docs/SDK3/#how-to-build-the-sdk
-  Control the AR.Drone LEDs
   http://gauth.fr/2011/09/control-the-ar-drone-leds/

Demo #1 with sridrone\_ardronelib
---------------------------------

Compile up-to-date ardronelib sdk.

::

    git submodule update --init --recursive 
    cd examples/drone/sridrone_ardronelib/ardronelib
    make 
    sudo make install --makefile=../Makefile INSTALL_PREFIX=/usr/local

Edit *drone\_ip* in
*examples/drone/sridrone\_ardronelib/sridrone\_ardronelib.radl* with
your drone's IP if needed.

::

    DEFS 
       drone_ip: string "192.168.1.xxx" 

Run ROS master.

::

    roscore 

Run the sridrone\_ardronelib example.

::

    mkdir -p /tmp/catkin_ws/src
    cd /path/to/radler
    ./radler.sh --ws_dir /tmp/catkin_ws/src compile examples/drone/sridrone_ardronelib/sridrone_ardronelib.radl --plant plant --ROS  
    cd /tmp/catkin_ws  
    catkin_make 
    cd /tmp/catkin_ws/devel/lib/sridrone_ardronelib
    ./sridrone 
    ./led
    ./camera 
    ./key 
    ./timer 
    ./landing 

Demo #2 with sridrone\_ardrone\_autonomy
----------------------------------------

Download and install ROS ardrone\_driver from
https://github.com/AutonomyLab/ardrone\_autonomy.git.

::

    sudo apt-get install ros-indigo-ardrone-autonomy 

.. raw:: html

    <!--
    cd ~/catkin_ws/src
    git clone https://github.com/AutonomyLab/ardrone_autonomy.git -b indigo-devel
    cd ~/catkin_ws
    rosdep install --from-paths src -i 
    catkin_make 

    catkin_make install 
    source devel/setup.bash 
    export CPLUS_INCLUDE_PATH=~/catkin_ws/devel/include
    -->

Run ROS master and ardrone\_driver.

::

    roscore 
    rosrun ardrone_autonomy ardrone_driver 

Note. Use *-ip ${Your Drone's IP address}* if your drone does not have
the default IP address.

::

    rosrun ardrone_autonomy ardrone_driver -ip 192.168.1.xxx

Run the sridrone\_ardrone\_autonomy example.

::

    cd /path/to/radler 
    ./radler.sh --ws_dir /tmp/catkin_ws/src compile examples/drone/sridrone_ardrone_autonomy/sridrone_ardrone_autonomy.radl --plant plant --ROS 
    cd /tmp/catkin_ws  
    catkin_make 
    cd /tmp/catkin_ws/devel/lib/sridrone_ardrone_autonomy
    ./sridrone 
    ./led
    ./camera

Run ros image\_view node to check the camera feed.

::

    sudo apt-get install ros-indigo-image-view
    rosrun image_view image_view image:=/ardrone/front/image_raw
    rosrun image_view image_view image:=/ardrone/bottom/image_raw

Demo #3 on Secure_ROS
---------------------

.. raw:: html

   <!--
   Edit *vagrant/vagrant_configuration.yaml* to be on the same subnet with AR.Drone. The default AR.Drone IP address is 192.168.1.1.
   ```yaml
   ip_addr_prefix: 192.168.1
   ```
   Edit *vagrant/Vagrantfile* to set up a bridged network. 
   ```
   # machine.vm.network "private_network",  ip: ip_addr
   machine.vm.network "public_network", bridge: "en0: Wi-Fi (AirPort)",  ip: ip_addr
   ```

   Add two lines in *vagrant/Vagrantfile* to set up X11 forwarding. 
   ```
   Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|
      config.vm.box = "ubuntu/trusty64"
   +  config.ssh.forward_agent = true
   +  config.ssh.forward_x11 = true
   ```
   -->

Refer */tmp/catkin_\ws/src/ros/sros\_cfg.ymal* with the
list of IP addresses that are authorized to publish/subscribe each topic
if needed. For example, **navdata** is published by **sridrone**
(192.168.1.202) node and subscribed by **led** (192.168.1.203),  
**camera** (192.168.1.204), **timer** and **landing** (both 192.168.1.202) nodes. ROS master
is hosted on a node with IP address of 192.168.1.201.

::

    topics:
        - name: /sridrone_ardronelib/navdata_topic
          publishers: [192.168.1.202]
          subscribers: [192.168.1.202, 192.168.1.203, 192.168.1.204]
        - name: /sridrone_ardronelib/led_topic
          publishers: [192.168.1.203]
          subscribers: [192.168.1.202]
        - name: /sridrone_ardronelib/camera_topic
          publishers: [192.168.1.204]
          subscribers: [192.168.1.202]
        - name: /sridrone_ardronelib/key_topic
          publishers: [192.168.1.202]
          subscribers: [192.168.1.202]
        - name: /sridrone_ardronelib/timer_topic
          publishers: [192.168.1.202]
          subscribers: [192.168.1.202]
        - name: /sridrone_ardronelib/landing_topic
          publishers: [192.168.1.202]
          subscribers: [192.168.1.202]

Copy executables to the corresponding machines. 

::

    scp /tmp/catkin_ws/devel/lib/sridrone_ardronelib/sridrone 192.168.1.202:~  
    scp /tmp/catkin_ws/devel/lib/sridrone_ardronelib/led 192.168.1.203:~ 
    scp /tmp/catkin_ws/devel/lib/sridrone_ardronelib/camera 192.168.1.204:~  
    scp /tmp/catkin_ws/devel/lib/sridrone_ardronelib/key 192.168.1.202:~  
    scp /tmp/catkin_ws/devel/lib/sridrone_ardronelib/timer 192.168.1.202:~  
    scp /tmp/catkin_ws/devel/lib/sridrone_ardronelib/landing 192.168.1.202:~  

On machine 192.168.1.201: 

:: 

    ROS_AUTH_FILE=/path/to/sros_cfg.yaml roscore 

On each machine, run radler node(s). For example, on machine 192.168.1.202: 
 
:: 

    ./sridrone 
   
We use Wi-Fi Protected Access (WPA2) solution from https://github.com/daraosn/ardrone-wpa2 for the link between **sridrone** and AR.Drone.  
Refer "Hacking and securing the AR.Drone 2.0 quadcopter: investigations for improving the security of a toy" by Johann-Sebastian Pleban; Ricardo Band; Reiner Creutzburg, Proc. SPIE 9030, Mobile Devices and Multimedia: Enabling Technologies, Algorithms, and Applications 2014, 90300L (18 February 2014). 
