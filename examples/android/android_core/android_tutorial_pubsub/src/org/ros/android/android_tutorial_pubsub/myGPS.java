package org.ros.android.android_tutorial_pubsub;

import android.app.Activity;
import android.content.Context;
import android.hardware.GeomagneticField;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Bundle;
import android.util.Log;

import org.ros.concurrent.CancellableLoop;
import org.ros.namespace.GraphName;
import org.ros.node.AbstractNodeMain;
import org.ros.node.ConnectedNode;
import org.ros.node.NodeMain;
import org.ros.node.topic.Publisher;

import java.util.Date;

/**
 * A simple {@link Publisher} {@link NodeMain}.
 * 
 * @author damonkohler@google.com (Damon Kohler)
 */
public class myGPS extends AbstractNodeMain implements LocationListener {

  private LocationManager lnmLocationManager; 

  private Context myContext; 

  private double lat = 0.0;
  private double lon = 0.0;
  private boolean showTrueNorth = true; 
  private boolean isGPSEnabled = false;
  private float declination = 0;

  private int GPS_REFRESH_TIME = 5; //seconds
  private int GPS_REFRESH_DISTANCE = 5; //meters

  public myGPS(Context c) {
	myContext = c;
  } 

  @Override
  public GraphName getDefaultNodeName() {
    return GraphName.of("rosjava_tutorial_pubsub/GPS");
  }

  public void onProviderDisabled(String provider) {
    if (provider.equals(LocationManager.GPS_PROVIDER)) {
        isGPSEnabled=false;
    }
  }

  public void onProviderEnabled (String provider) {
    if (provider.equals(LocationManager.GPS_PROVIDER)) {
        isGPSEnabled=true;
    }
  }

  public void onStatusChanged (String provider, int status, Bundle extras) { }

  public void onLocationChanged (Location location) {
    if(location.getProvider().equals(LocationManager.GPS_PROVIDER)) {
        lat = location.getLatitude();
        lon = location.getLongitude();
        declination = getDeclination(location);
    } else {
        declination = getDeclination(location);
    }
  }

  private float getDeclination(Location current) {
    float dec = 0;

    if(showTrueNorth && current != null) {
        Date now = new Date();
        GeomagneticField geoPos = new GeomagneticField(new Float(current.getLatitude()), new Float(current.getLongitude()), new Float(current.getAltitude()), now.getTime());
        dec = geoPos.getDeclination();
    }

    return dec;
  }

  @Override
  public void onStart(final ConnectedNode connectedNode) {
    lnmLocationManager = (LocationManager) myContext.getSystemService(myContext.LOCATION_SERVICE);
    if (lnmLocationManager == null) 
       Log.i("myGPS", "Null Location Manager");
        
    ((Activity)myContext).runOnUiThread(new Runnable() {
       @Override
       public void run() {
       	  isGPSEnabled = lnmLocationManager.isProviderEnabled(LocationManager.GPS_PROVIDER);

    	  if (isGPSEnabled) 
              lnmLocationManager.requestLocationUpdates(LocationManager.GPS_PROVIDER, GPS_REFRESH_TIME * 1000, GPS_REFRESH_DISTANCE, myGPS.this);
       }
    });

    final Publisher<std_msgs.String> publisher =
        connectedNode.newPublisher("android_gps", std_msgs.String._TYPE);
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
        str.setData(lat + ":" + lon);
        publisher.publish(str);
        sequenceNumber++;
        Thread.sleep(1000);
      }
    });
  }
}
