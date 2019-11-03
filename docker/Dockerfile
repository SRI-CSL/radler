# This is an auto generated Dockerfile for ros:ros-base
# generated from docker_images/create_ros_image.Dockerfile.em
FROM ros:melodic-ros-core-bionic

# install ros packages
RUN apt-get update && apt-get install -y \
    ros-melodic-ros-base=1.4.1-0* \
    && rm -rf /var/lib/apt/lists/*

# install basics
RUN apt-get update && apt-get install -y tmux net-tools iputils-ping openssh-server openssh-client
RUN apt-get install -y --no-install-recommends vim-tiny

# install radler packages
RUN apt-get update -y
RUN apt-get install -y cmake python3-pip
RUN pip3 install tarjan pyyaml pydot

RUN cd ~ ; git clone https://github.com/SRI-CSL/radler.git
RUN cd ~/radler ; git submodule update --init --recursive

# setup ros_ws 
ENV ROS_WS /tmp/catkin_ws
RUN mkdir -p $ROS_WS/src

# setup entrypoint
ENV ROS_DISTRO melodic 
ENV ROS_PREFIX /opt/ros
WORKDIR $ROS_WS

COPY ./ros_entrypoint.sh /
ENTRYPOINT ["/ros_entrypoint.sh"]
CMD ["bash"]

