# This is an auto generated Dockerfile for ros2:devel
# generated from docker_images_ros2/devel/create_ros_image.Dockerfile.em
ARG FROM_IMAGE=ubuntu:focal
FROM $FROM_IMAGE

# setup timezone
RUN echo 'Etc/UTC' > /etc/timezone && \
    ln -s /usr/share/zoneinfo/Etc/UTC /etc/localtime && \
    apt-get update && apt-get install -q -y tzdata && rm -rf /var/lib/apt/lists/*

# install packages
RUN apt-get update && apt-get install -q -y \
    bash-completion \
    dirmngr \
    gnupg2 \
    lsb-release \
    python3-pip \
    && rm -rf /var/lib/apt/lists/*

# setup keys
RUN apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654

# setup sources.list
RUN echo "deb http://packages.ros.org/ros2/ubuntu `lsb_release -sc` main" > /etc/apt/sources.list.d/ros2-latest.list

# setup environment
ENV LANG C.UTF-8
ENV LC_ALL C.UTF-8

# install bootstrap tools
RUN apt-get update && apt-get install --no-install-recommends -y \
    git \
    python3-rosdep \
    python3-vcstool \
    && rm -rf /var/lib/apt/lists/*

# install python packages
RUN pip3 install -U \
    argcomplete \
    colcon-common-extensions \
    colcon-mixin \
    flake8 \
    flake8-blind-except \
    flake8-builtins \
    flake8-class-newline \
    flake8-comprehensions \
    flake8-deprecated \
    flake8-docstrings \
    flake8-import-order \
    flake8-quotes \
    pytest-repeat \
    pytest-rerunfailures

# FIXME This is a workaround for pytest not found causing builds to fail
# Following RUN statements tests for regression of https://github.com/ros2/ros2/issues/722
RUN pip3 freeze | grep pytest \
    && python3 -m pytest --version

# bootstrap rosdep
RUN rosdep init \
    && rosdep update

# setup colcon mixin and metadata
RUN colcon mixin add default \
      https://raw.githubusercontent.com/colcon/colcon-mixin-repository/master/index.yaml && \
    colcon mixin update && \
    colcon metadata add default \
      https://raw.githubusercontent.com/colcon/colcon-metadata-repository/master/index.yaml && \
    colcon metadata update

# install ros2 dashing 
RUN apt-get update -y
RUN apt-get install -y ros-foxy-desktop

# install basics
RUN apt-get install -y tmux 
RUN apt-get install -y net-tools iputils-ping
RUN apt-get install -y openssh-server openssh-client
RUN apt-get install -y libncurses5-dev
RUN apt-get install -y --no-install-recommends vim-tiny

# install radler packages
RUN apt-get update -y
RUN apt-get install -y cmake python3-pip
RUN pip3 install tarjan pyyaml pydot
RUN apt-get install -y software-properties-common
RUN add-apt-repository ppa:deadsnakes/ppa
RUN apt install -y python3.6
RUN python3.6 -m pip install tarjan
RUN apt-get install -y default-jdk

RUN cd ~ ; git clone https://github.com/SRI-CSL/radler.git
RUN cd ~/radler ; git checkout ros2 ; git submodule update --init --recursive

# setup ros2_ws 
ENV ROS2_WS /tmp/ros2_ws
RUN mkdir -p $ROS2_WS/src

# setup entrypoint
ENV ROS2_DISTRO foxy
ENV ROS2_PREFIX /opt/ros
WORKDIR $ROS2_WS

COPY ./ros2_entrypoint.sh /
ENTRYPOINT ["/ros2_entrypoint.sh"]
CMD ["bash"]

