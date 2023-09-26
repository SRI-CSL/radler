Demo with ETB2 
--------------

This demo shows how to write an ETB2 script for the Radler build. 
ETB2 is a framework for defining and executing distributed workflows that produce claims supported by evidence. ETB2 uses Datalog as the workflow scripting language. You can find more information and follow the instructions for ETB2 on its GitHub repository: https://github.com/SRI-CSL/ETB2.

Once ETB2 is installed, prepare files for an ETB node in a specified directory. Copy the files needed for the Ardupilot example to the clean directory (e.g., *~/ETB2-radler-demo*). Make sure that the directory is not part of an existing repository.

:: 
  
  mkdir ~/ETB2-radler-demo        
  cp -r * ~/ETB2-radler-demo
  cp ../afs.radl ~/ETB2-radler-demo
  cp -r ../src ~/ETB2-radler-demo

Initialize an ETB node by running the ``etb2 init --path=<nodeSpec>`` command in the directory. 
Since ETB nodes are identified by their IP address and port number, you will need to provide a JSON file containing this information during the initialization step. After completing this step, you should see the 'claims' and 'wrappers' directories.

:: 

  cd ~/ETB2-radler-demo
  etb2 init --path=node.json

To add a service to an ETB node, use the command ``etb2 add-service --path=<serviceSpec>``. 
In this demo, we will add two services for Radler compile and Colcon build with IDs of ``radler`` and ``colcon``. 
Radler generates files from the RADL file into the ROS2 structure, and a subsequent call to Colcon build will generate the executables as usual.

::
 
  etb2 add-service --path=svc_radler_compile.json
  etb2 add-service --path=svc_colcon_build.json

When a service is added, ETB2 auto-generates a wrapper for the service in wrappers/src/<serviceID>WRP.java code.
The user needs to add the intended functionalities into the run() method. Please find below the contents of a fully developed wrapper for the Radler and Colcon services.

::

  mv radlerWRP.java wrappers/src/
  mv colconWRP.java wrappers/src/

After making such changes, the wrapper should be recompiled, and ETB2 should be made aware of the new version of the service.
This is done from within ETB2 by running the command ``etb2 update-service --id=<serviceID>``.

::

  git add wrappers/src/radlerWRP.java
  git add wrappers/src/colconWRP.java
  git commit -m "svc update"
  etb2 update-service --id=radler
  etb2 update-service --id=colcon

ETB uses Datalog as a scripting language to define workflows that employ services to accomplish integrated analysis, verification and assurance activities. A workflow can be added into an ETB node using the command ``etb2 add-workflow --path=<workflowSpec>``.

::

  etb2 add-workflow --path=workflow.json

The Datalog script is provided below for your reference.

:: 

  radler_build(RADL, WS, BUILD) :- radler_compile(RADL, WS, COMPILE), colcon_build(WS, BUILD).
  radler_compile(RADL, WS, RES) :- radler(RADL, WS, RES), equals(RES, "compiled").
  colcon_build(WS, RES) :- colcon(WS, RES), equals(RES, "built").

To add a claim to an ETB node, use the command ``etb2 add-claim --query=<query>``, where ``<query>`` represents the input query for which ETB2 will compute its corresponding claim and add it to the node. In this example, we assume that you have copied 'afs.radl' and the associated user code under the 'src' directory, and we assume the 'ros2_ws' workspace directory is located at '/tmp/'.

::

  etb2 add-claim --query="radler_build('afs', 'ros2_ws', A)" verbose --level=debug
  etb2 show-info

Below is an example demonstrating a successful addition of the claim.

::

  -------------------------------
    ETB2 node: [192.168.178.49:4120]
  -------------------------------
  => git repo: /home/vagrant/ETB2-radler-demo
  => #claims: 7
  -> claim 1 [1800427745]
    -> claim : equals(compiled, compiled)++
    -> query : equals(compiled, compiled)++
    -> derivService : equals([string, string])[++]
  -> claim 2 [-156178366]
    -> claim : radler(afs, ros2_ws, compiled)+++
    -> query : radler(afs, ros2_ws, V2_1162991781)++-
    -> derivService : radler([string, string, string])[++-]
  -> claim 3 [563463478]
    -> claim : radler_compile(afs, ros2_ws, compiled)+++
    -> query : radler_compile(afs, ros2_ws, COMPILE)++-
    -> derivRule : radler_compile(RADL, WS, RES)--- :- radler(RADL, WS, RES)---, equals(RES, compiled)-+
    -> subClaims2 : [-156178366, 1800427745]
  -> claim 4 [121070431]
    -> claim : colcon(ros2_ws, built)++
    -> query : colcon(ros2_ws, V1_-1376502576)+-
    -> derivService : colcon([string, string])[+-]
  -> claim 5 [-1107292997]
    -> claim : equals(built, built)++
    -> query : equals(built, built)++
    -> derivService : equals([string, string])[++]
  -> claim 6 [-1282407602]
    -> claim : colcon_build(ros2_ws, built)++
    -> query : colcon_build(ros2_ws, V2_1439050272)+-
    -> derivRule : colcon_build(WS, RES)-- :- colcon(WS, RES)--, equals(RES, built)-+
    -> subClaims2 : [121070431, -1107292997]
  -> claim 7 [1533145246]
    -> claim : radler_build(afs, ros2_ws, built)+++
    -> query : radler_build(afs, ros2_ws, A)++-
    -> derivRule : radler_build(RADL, WS, BUILD)--- :- radler_compile(RADL, WS, COMPILE)---, colcon_build(WS, BUILD)--
    -> subClaims2 : [563463478, -1282407602]
  => #workflows : 1
  -> workflow 1 [a2997d5cb0f216fb4fb9b3f8edaed572c0416159]
    -> script path: radler_wf
    -> queries: [<radler_build[string, string, string] ++->, <colcon[string, string] +->, <radler[string, string, string] ++->]
  => #wrappers : 2
    -> radler([string, string, string])[++-]
    -> colcon([string, string])[+-]
  => util services
  => #wrappers : 3
    -> nil([string_list])[-]
    -> equals([string, string])[++]
    -> cons([string, string_list, string_list])[++-]
  => #servers: 0
  -----------------------------------
             ETB2 options
  -----------------------------------
   -> verbose level: debug
   -> stepper: disabled
  -----------------------------------

To start from a clean slate, remove all the claims for a given ETB2 node and delete files from the workspace.

::

  etb2 clean-claims 
  rm -rf /tmp/ros2_ws/*
  mkdir /tmp/ros2_ws/src
