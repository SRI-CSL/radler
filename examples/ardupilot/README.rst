Advanced Fail Safe of Arducopter using MAVROS
=============================================

This demo shows the Radler code generation and its execution on SITL (software in the loop) simulator for the Arducopter advanced fail safe. In this demo MAVROS, ROS-based extendable communication node, on the companion computer communicates with ground control system.

Radler architecture consists of the logical and physical parts.  The logical part is specified in terms of node and topic similar to ROS. The nodes execute independently and periodically, and subscribe from and publish to topics. For example, battery node executes its step function with period of 100 milli seconds, subscribes from battery status topic, and publishes to mode change topic. Physical parts map nodes to the process on specific machines, in this case companion computer.
The step function of battery node controls mode to return to takeoff location when battery level below threshold.
The step function of gateway node forwards back-and-forth messages between Radler and ROS worlds on the companion computer.
Radler build process generates the glue code for scheduling, communication, and failure detection such as timeout or stale.

.. image:: rqt.png
  :scale: 10
  :height: 50

The above graph shows the nodes and topics used in this demo. Note that we are using ROS service to change the flight mode which is not shown here. Also gateway subscribes from the relative altitude topic which will be used for another Radler node for altitude-related control such as altitude hold.

More information on Ardupilot can be found from ArduPilot Development Site https://ardupilot.org/dev/index.html.

Set up SITL simulation environment (refer https://ardupilot.org/dev/docs/setting-up-sitl-using-vagrant.html).

::

  git clone https://github.com/ArduPilot/ardupilot.git
  cd ardupilot
  vagrant up
  vagrant ssh
  cd /vagrant
  git submodule update --init --recursive
  exit

Install ROS/MAVROS (refer https://ardupilot.org/dev/docs/ros-install.html).

::

  vagrant ssh
  sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu bionic main" > /etc/apt/sources.list.d/ros-latest.list'
  wget https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -O - | sudo apt-key add -
  sudo apt-get update
  sudo apt-get install -y ros-melodic-ros-base
  (echo ; echo "# Setup for ROS" ; echo "source /opt/ros/melodic/setup.bash" ) >> ~/.bashrc
  source ~/.bashrc
  sudo apt-get install -y ros-melodic-mavros ros-melodic-mavros-extras
  wget https://raw.githubusercontent.com/mavlink/mavros/master/mavros/scripts/install_geographiclib_datasets.sh
  chmod a+x install_geographiclib_datasets.sh
  sudo ./install_geographiclib_datasets.sh
  sudo apt-get install -y ros-melodic-rqt ros-melodic-rqt-common-plugins ros-melodic-rqt-robot-plugins
  sudo apt-get install -y python-catkin-tools


Start SITL simulator.

::

  vagrant ssh
  sim_vehicle.py -v ArduCopter --console --map -m --out=127.0.0.1:14550

Connect MAVROS with SITL (refer https://ardupilot.org/dev/docs/ros-sitl.html).

:: 

  vagrant ssh
  cd ~
  mkdir -p ardupilot_ws/src
  cd ardupilot_ws
  catkin init
  cd src
  mkdir launch
  cd launch
  roscp mavros apm.launch apm.launch
  cd ~/ardupilot_ws/src/launch
  roslaunch apm.launch fcu_url:="udp://127.0.0.1:14550@"

Left two windows of the below snapshot show the ground control console and map of the environment launched from the SITL simulator on the top right window. On the right bottom window, one can observe some verbose that reads the Arducopter's configuration, which indicates a connection.

.. image:: sitl_mavros.png  
   :height: 300

Generate Radler codes.  

::

  vagrant ssh
  mkdir -p /tmp/catkin_ws/src
  cd /path/to/radler
  ./radler.sh --ws_dir /tmp/catkin_ws/src compile examples/ardupilot/afs.radl --plant plant --ROS
  cd /tmp/catkin_ws
  catkin_make 

Launch Radler nodes (in different terminals for more clarity). 
The battery status topic published in the ROS side is subscribed by the gateway node which forwards it to the battery node on the Radler side via Radler pub/sub channel. 

::

  source ./devel/local_setup.bash
  ./devel/lib/afs/gateway
  ./devel/lib/afs/afs_battery

On the simulator side (upper right window of below snapshot), change the Arducopter's mode to GUIDED, arm throttle, then takeoff to an altitude (e.g., 30 meters) and one can observe the console window changing battery level and altitude.

::

  mode guided
  arm throttle
  takeoff 30

On the map (bottom left window), create a target position with altitude, then observe the Arducopter flying to the target.

.. image:: takeoff.png  
   :height: 300

When the battery level hits below threshold (i.e., 90%) the mode change to return to takeoff location is published by battery node. The gateway node subscribes from it and calls ROS service to set custom mode of the Arducopter. Note that the mode change to RTL on the simulator side.

On the map window of below snapshot, one can observe that the Arducopter heading to the takeoff location.

The altitude value on the ground control console indicates that the Arducopter landing to the takeoff location.

.. image:: rtl.png  
   :height: 300

For the inception of Java code in the step function, we provide a use-case with Java Native Interface (JNI). The step function of esp (event stream processing) node calculates point distance between two successive (x,y) positions. BeepBeep (https://liflab.github.io/beepbeep-3/) is used for event stream processing engine. The *afs.radl* includes *cmake_library* information for JNI. JVM creation should be in the class constructor (refer *afs\_esp.h*) and JNI calls in the step function (refer *afs\_esp.cpp*). 

To install JDK: 

:: 

  sudo apt-get install default-jdk
  export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib/jvm/java-11-openjdk-amd64/lib/server/

To install BeepBeep 3 examples:

::

  sudo apt-get install ant
  cd ~
  git clone https://github.com/liflab/beepbeep-3-examples.git
  cd beepbeep-3-examples
  edit config.xml
    <zip>https://github.com/liflab/beepbeep-3-palettes/releases/download/v20181124/beepbeep-3-palettes-v20181124.zip</zip>
    to 
    <zip>https://github.com/liflab/beepbeep-3-palettes/releases/download/v20190917/beepbeep-3-palettes-v20190917.zip</zip>
  ant download-deps
  mkdir Core/src
  mkdir doc
  ant

To compile Java-side code:

::

  cd /path/to/radler/examples/ardupilot/jni
  export CLASSPATH=~/beepbeep-3-examples/beepbeep-3-examples.jar
  javac PointDistance.java
 
To run, edit Java class path (*-Djava.class.path*) in *afs\_esp.cpp* and execute *catkin_make* if needed. The default is *vagrant* user.

::

  cd /tmp/catkin_ws
  catkin_make (if class path changed)
  ./devel/lib/afs/afs_esp
