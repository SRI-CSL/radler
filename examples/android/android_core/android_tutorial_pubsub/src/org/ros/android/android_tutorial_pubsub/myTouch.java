package org.ros.android.android_tutorial_pubsub;

import android.app.Activity;
import android.content.Context;
import android.view.MotionEvent;
import android.view.View;
import android.widget.ImageView;
import android.view.WindowManager;
import android.view.Display;
import android.util.Log;

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
public class myTouch extends AbstractNodeMain { // implements View.OnTouchListener {

  private WindowManager windowManager;

  private Context myContext; 

  private int x = -1;
  private int y = -1;
  private int width = 1;
  private int height = 1;

  public myTouch(Context c) {
	myContext = c;
  } 

  @Override
  public GraphName getDefaultNodeName() {
    return GraphName.of("rosjava_tutorial_pubsub/touch");
  }

  @Override
  public void onStart(final ConnectedNode connectedNode) {
    windowManager = (WindowManager) myContext.getSystemService(Context.WINDOW_SERVICE);
    Log.i("touch ", "start");
    final Publisher<std_msgs.String> publisher =
        connectedNode.newPublisher("android_touch", std_msgs.String._TYPE);
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
        ImageView imageView = (ImageView) ((Activity) myContext).findViewById(R.id.imageView);
        imageView.setOnTouchListener(new View.OnTouchListener() {
          @Override
          public boolean onTouch(View v, MotionEvent e){
            Display display = windowManager.getDefaultDisplay();
            if (e.getAction() == e.ACTION_UP) {
              x = -1;
              y = -1;

              width = display.getWidth();
              height = display.getHeight();
            }
            else {
              x = (int) e.getX();
              y = (int) e.getY();

              width = display.getWidth();
              height = display.getHeight();
            }
            return true;
          }
        });

        std_msgs.String str = publisher.newMessage();
        str.setData(x + ":" + y + ":" + width + ":" + height);
        Log.i("touch ", Integer.toString(x));
        publisher.publish(str);
        sequenceNumber++;
        Thread.sleep(1000);
      }
    });
  }
}