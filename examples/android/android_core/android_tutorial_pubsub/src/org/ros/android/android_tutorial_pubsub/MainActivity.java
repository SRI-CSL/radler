/*
 * Copyright (C) 2011 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */

package org.ros.android.android_tutorial_pubsub;

import android.os.Bundle;

import org.ros.android.MessageCallable;
import org.ros.android.RosActivity;
import org.ros.android.view.RosTextView;
import org.ros.node.NodeConfiguration;
import org.ros.node.NodeMainExecutor;

//import org.ros.android_tutorial_pubsub.myTalker;

/**
 * @author damonkohler@google.com (Damon Kohler)
 */
public class MainActivity extends RosActivity {//} implements OnMapReadyCallback { // implements LocatiListener {

  private RosTextView<std_msgs.String> rosTextView; //, rosTextView2;
//  private myTalker talker;
  private myCompass compass;
  private myGPS gps;
  private myTouch touch;
  private myListener listener;
  private mySpeaker speaker;

  public MainActivity() {
    // The RosActivity constructor configures the notification title and ticker
    // messages.
    super("Pubsub Tutorial", "Pubsub Tutorial");
  }

  @SuppressWarnings("unchecked")
  @Override
  public void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.main);
    rosTextView = (RosTextView<std_msgs.String>) findViewById(R.id.text);
    rosTextView.setTopicName("android_compass");
    rosTextView.setMessageType(std_msgs.String._TYPE);
    rosTextView.setMessageToStringCallable(new MessageCallable<String, std_msgs.String>() {
      @Override
      public String call(std_msgs.String message) {
        return message.getData();
      }
    });
  }

  @Override
  protected void init(NodeMainExecutor nodeMainExecutor) {
//    talker = new myTalker();
    compass = new myCompass(this);
    gps = new myGPS(this);
    touch = new myTouch(this);
    listener = new myListener(this);
    speaker = new mySpeaker(this);

    // At this point, the user has already been prompted to either enter the URI
    // of a master to use or to start a master locally.

    // The user can easily use the selected ROS Hostname in the master chooser
    // activity.
    NodeConfiguration nodeConfiguration = NodeConfiguration.newPublic(getRosHostname());
    nodeConfiguration.setMasterUri(getMasterUri());
//    nodeMainExecutor.execute(talker, nodeConfiguration);
    nodeMainExecutor.execute(compass, nodeConfiguration);
    nodeMainExecutor.execute(gps, nodeConfiguration);
    nodeMainExecutor.execute(touch, nodeConfiguration);
    nodeMainExecutor.execute(listener, nodeConfiguration);
    nodeMainExecutor.execute(speaker, nodeConfiguration);
    // The RosTextView is also a NodeMain that must be executed in order to
    // start displaying incoming messages.
    nodeMainExecutor.execute(rosTextView, nodeConfiguration);
  }
}
