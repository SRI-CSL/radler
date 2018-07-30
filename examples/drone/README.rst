Demos using AR.Drone on ROS
=======================================

| Demos are available for three types of AR.Drone drivers: Demo \#1 with **ardronelib**
  (AR.Drone sdk), Demo \#2 with **ardrone\_autonomy** (ROS driver), and Demo \#3 with **ps\_drone** (Python).
| 
  Demos \#1 and \#2 consist of at least three nodes **sridrone**, **led**, and
  **camera**, and three topics **navdata**, **led\_anim**, and
  **camera\_param**. The **sridrone** node publishes **navdata** and
  subscribes to **led\_anim** and **camera\_param** to generate signals
  that control LED animation and video input. The **led** node
  subscribes to **navdata** and publishes **led\_anim** to indicate
  unstable roll (LEFT\_GREEN\_RIGHT\_RED or LEFT\_RED\_RIGHT\_GREEN) or
  low battery level (BLINK\_RED). The **camera** node subscribes to 
  **navdata** and publishes **camera\_param** to toggle the video feed
  between front/bottom cameras.
  Demo \#1 additionally supports for three other nodes: **key**, **timer**, and **landing**.  
  The **key** node provides drone flight control using keyboard. The **timer** node provides timer-based drone flight control, e.g., landing after 2 seconds of hovering over 50cm. 
  The **landing** node provides altitude-based landing, e.g., landing if the altitude is less than 50cm.  
| 
  Demo \#3 consists of two nodes **sridrone** and **led** to perform object detection using TensorFlow. 
  The **sridrone** node publishes **object_detection** and subscribes to **led\_anim** to generate signals that indicate certain objects (e.g., person, dog, cat, or teddy bear) being detected. 

.. image:: sridrone_rqt_graph.png  
   :height: 300

This application uses code snippets from the following open source projects. 

- ROS driver for Parrot AR-Drone 1.0 and 2.0 quadrocopters
  https://github.com/AutonomyLab/ardrone_autonomy
- Modified ARDroneLib based on official ARDroneSDK 2.0.1
  https://github.com/AutonomyLab/ardronelib
- AR.FreeFlight/AR.Drone 2.0 SDK
  https://github.com/yolanother/AR.FreeFlight
- OpenCV
  https://github.com/opencv/opencv
- TensorFlow object detection
  https://github.com/tensorflow/models/tree/master/research/object_detection
- PS-Drone 
  http://www.playsheep.de/drone

Some additional links:

-  AR.Drone Developer Guide
   http://www.msh-tools.com/ardrone/ARDrone\_Developer\_Guide.pdf
-  Parrot developer site for SDK
   http://developer.parrot.com/docs/SDK3/#how-to-build-the-sdk
-  Control the AR.Drone LEDs
   http://gauth.fr/2011/09/control-the-ar-drone-leds/

For Demos \#1 and \#2, OpenCV is required to find line with the Hough transform. In *.radl* file, edit *opencv\_houghline* to enable line detection. 

::

    git clone https://github.com/opencv/opencv.git or download source from https://github.com/opencv/opencv/releases/tag/3.4.2
    cd /path/to/opencv
    mkdir build
    cd build
    cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local ..
    make
    sudo make install

Demo #1 with sridrone\_ardronelib
---------------------------------

Compile up-to-date ardronelib sdk.

::

    sudo apt-get install libsdl1.2-dev
    sudo apt-get install libgtk2.0
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
    sudo apt-get install ros-indigo-image-view

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

You can also run ros **image\_view** node to check the camera feed or record it.

::

    rosrun image_view image_view image:=/ardrone/front/image_raw
    rosrun image_view image_view image:=/ardrone/bottom/image_raw
    rosrun image_view video_recorder image:="/ardrone/front/image_raw" _filename:="/tmp/video_front_camera.avi"

Demo #3 object detection with PS-Drone and TensorFlow
-----------------------------------------------------

Install Python OpenCV2. 

::

    sudo apt-get install python-opencv

Download `ps\_drone.py <https://sourceforge.net/projects/ps-drone/files/ps_drone.py/download>`_ and `firstVideo.py <http://www.playsheep.de/drone/prgs/firstVideo.py>`_ from http://www.playsheep.de/drone to the same directory (e.g., ps\_drone). Test video streaming from AR. Drone using firstVideo.py. A window named PS-Drone with front camera feed should show up. We tested on Ubuntu 14.04.

::

    cd /path/to/ps_drone
    python firstVideo.py

Install TensorFlow and related packages. For details, refer https://www.tensorflow.org/install/install_linux.

::

    sudo apt-get install python3-pip
    sudo pip3 install -U pip
    sudo pip install --upgrade setuptools
    sudo pip install --upgrade --target=/usr/lib/python2.7/dist-packages tensorflow
    sudo apt-get install --fix-missing python-matplotlib

Download models built with TensorFlow. 

::

    git clone https://github.com/tensorflow/tensorflow.git
    cd tensorflow
    git clone https://github.com/tensorflow/models.git
    
Download a Single Shot Multibox Detector (SSD) with MobileNet model from `here <http://download.tensorflow.org/models/object_detection/ssd_mobilenet_v1_coco_11_06_2017.tar.gz>`_, and untar to /path/to/tensorflow/models/research/object\_detection directory. 

::
    
    tar zxvf ssd_mobilenet_v1_coco_11_06_2017.tar.gz -C /path/to/tensorflow/models/research/object_detection

Download and install Protobuf.

::

    git clone https://github.com/google/protobuf.git
    sudo apt-get install autoconf libtool
    cd protobuf
    ./autogen.sh
    ./configure
    make
    sudo make install

Compile Protobuf libraries. 

::

    export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
    cd /path/to/tensorflow/models/research
    protoc object_detection/protos/*.proto --python_out=.

Add to PYTHONPATH. 

::

    export PYTHONPATH=/path/to/ps_drone:/path/to/radler/examples/drone/sridrone_pydrone_tf_obj_detection/src:/path/to/tensorflow/models:/usr/lib/python2.7/dist-packages:$PYTHONPATH

Compile up-to-date ardronelib sdk. Skip this step if you already installed ardronelib sdk for Demo \#1.

::

    git submodule update --init --recursive
    cd examples/drone/sridrone_ardronelib/ardronelib
    make
    sudo make install --makefile=../Makefile INSTALL_PREFIX=/usr/local

Edit *drone\_ip* in
*examples/drone/sridrone\_pydrone\_tf\_obj\_detection/sridrone\_pydrone\_tf\_obj\_detection.radl* with
your drone's IP if needed.

::

    DEFS
       drone_ip: string "192.168.1.xxx"

Run ROS master.

::

    roscore

Compile the sridrone\_pydrone\_tf\_obj\_detection example.

::

    mkdir -p /tmp/catkin_ws/src
    cd /path/to/radler
    ./radler.sh --ws_dir /tmp/catkin_ws/src compile examples/drone/sridrone_pydrone_tf_obj_detection/sridrone_pydrone_tf_obj_detection.radl --plant plant --ROS 
    cd /tmp/catkin_ws 
    catkin_make

Create symbolic links to find model and label.

::

    cd /tmp/catkin_ws/devel/lib/sridrone_sridrone_pydrone_tf_obj_detection
    ln -s /path/to/tensorflow/models/object_detection/data .
    ln -s /path/to/tensorflow/models/object_detection/ssd_mobilenet_v1_coco_11_06_2017 .

Run the example.

::

    ./sridrone
    ./led

Even though the models can detect multiple objects simultaneously, **led_anim** topic only considers the object with the highest score. 
Led lights are blinking green (or red) when person (or teddy bear) is detected with the highest score. When dog (or cat) is detected with the highest score, the right (or left) led lights turn red. 
