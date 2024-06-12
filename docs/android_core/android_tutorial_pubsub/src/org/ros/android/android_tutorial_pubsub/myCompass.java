package org.ros.android.android_tutorial_pubsub;

import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;

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
public class myCompass extends AbstractNodeMain implements SensorEventListener {

  private SensorManager snmSensorManager; 
  private Sensor snsCompass;

  private Context myContext; 

  private int azimuth; 

  public myCompass(Context c) {
	myContext = c;
  } 

  @Override
  public GraphName getDefaultNodeName() {
    return GraphName.of("rosjava_tutorial_pubsub/compass");
  }

  public void onSensorChanged(SensorEvent event) {
    azimuth = Math.round(event.values[0]);
  }

  public void onAccuracyChanged(Sensor sensor, int accuracy) {
  }

  @Override
  public void onStart(final ConnectedNode connectedNode) {
    snmSensorManager = (SensorManager) myContext.getSystemService(Context.SENSOR_SERVICE);
    snsCompass = snmSensorManager.getDefaultSensor(Sensor.TYPE_ORIENTATION);
    snmSensorManager.registerListener(this, snsCompass, SensorManager.SENSOR_DELAY_NORMAL);

    final Publisher<std_msgs.String> publisher =
        connectedNode.newPublisher("android_compass", std_msgs.String._TYPE);
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
        str.setData(azimuth + ":");
        publisher.publish(str);
        sequenceNumber++;
        Thread.sleep(1000);
      }
    });
  }
}
