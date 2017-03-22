package org.ros.android.android_tutorial_pubsub;

import android.app.Activity;
import android.content.Context;
import android.widget.TextView;

import org.ros.message.MessageListener;
import org.ros.namespace.GraphName;
import org.ros.node.AbstractNodeMain;
import org.ros.node.ConnectedNode;
import org.ros.node.NodeMain;
import org.ros.node.topic.Subscriber;

/**
 * A simple {@link Subscriber} {@link NodeMain}.
 * 
 * @author damonkohler@google.com (Damon Kohler)
 */
public class myListener extends AbstractNodeMain {

  private Context myContext;

  public myListener(Context c) {
    myContext = c;
  }

  @Override
  public GraphName getDefaultNodeName() {
    return GraphName.of("rosjava_tutorial_pubsub/listener");
  }

  @Override
  public void onStart(ConnectedNode connectedNode) {
    //final Log log = connectedNode.getLog();
    Subscriber<std_msgs.String> subscriber = connectedNode.newSubscriber("android_gps", std_msgs.String._TYPE);
    subscriber.addMessageListener(new MessageListener<std_msgs.String>() {
      @Override
      public void onNewMessage(final std_msgs.String message) {
        ((Activity) myContext).runOnUiThread(new Runnable() {
          @Override
          public void run() {
            TextView textView = (TextView) ((Activity) myContext).findViewById(R.id.textView2);
            textView.setText(message.getData());
          }
        });
      }
    });
  }
}

