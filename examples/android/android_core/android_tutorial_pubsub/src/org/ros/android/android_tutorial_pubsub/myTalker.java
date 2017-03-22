package org.ros.android.android_tutorial_pubsub;

import org.ros.concurrent.CancellableLoop;
import org.ros.namespace.GraphName;
import org.ros.node.AbstractNodeMain;
import org.ros.node.ConnectedNode;
import org.ros.node.NodeMain;
import org.ros.node.topic.Publisher;

/**
 * A simple {@link Publisher} {@link NodeMain}.
 * 
 * @author damonkohler@google.com (Damon Kohler)
 */
public class myTalker extends AbstractNodeMain {

  @Override
  public GraphName getDefaultNodeName() {
    return GraphName.of("rosjava_tutorial_pubsub/talker");
  }

  @Override
  public void onStart(final ConnectedNode connectedNode) {
    final Publisher<std_msgs.String> publisher =
        connectedNode.newPublisher("chatter", std_msgs.String._TYPE);
    // This CancellableLoop will be canceled automatically when the node shuts
    // down.
    connectedNode.executeCancellableLoop(new CancellableLoop() {
      private int sequenceNumber;

      @Override
      protected void setup() {
        sequenceNumber = 0;
      }

      @Override
      protected void loop() throws InterruptedException {
        std_msgs.String str = publisher.newMessage();
        str.setData("Bye world! " + sequenceNumber);
        publisher.publish(str);
        sequenceNumber++;
        Thread.sleep(1000);
      }
    });
  }
}

