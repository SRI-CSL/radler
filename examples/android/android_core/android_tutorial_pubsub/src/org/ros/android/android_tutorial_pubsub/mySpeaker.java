package org.ros.android.android_tutorial_pubsub;

import android.content.Context;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.media.RingtoneManager;
import android.net.Uri;
import android.util.Log;

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
public class mySpeaker extends AbstractNodeMain {

  private AudioManager audioManager;
  private MediaPlayer mediaPlayer;

  private int maxVolume;

  private Context myContext;

  public mySpeaker(Context c) {
    myContext = c;
  }

  @Override
  public GraphName getDefaultNodeName() {
    return GraphName.of("rosjava_tutorial_pubsub/speaker");
  }

  @Override
  public void onStart(ConnectedNode connectedNode) {
    //final Log log = connectedNode.getLog();

    audioManager = (AudioManager) myContext.getSystemService(Context.AUDIO_SERVICE);

    maxVolume = audioManager.getStreamMaxVolume(AudioManager.STREAM_MUSIC);
    Log.i("volume max ", Integer.toString(maxVolume));

    Uri notification = RingtoneManager.getDefaultUri(RingtoneManager.TYPE_NOTIFICATION);
    mediaPlayer = MediaPlayer.create(myContext, notification);

    Subscriber<std_msgs.String> subscriber = connectedNode.newSubscriber("speaker_control", std_msgs.String._TYPE);
    subscriber.addMessageListener(new MessageListener<std_msgs.String>() {
      @Override
      public void onNewMessage(final std_msgs.String message) {
        Log.i("volume control ", message.getData());
        double c = Double.parseDouble(message.getData());
        if (c > 0) {
          int vol = (int)((double) maxVolume * c) + 1;
          Log.i("volume set ", Integer.toString(vol));
          audioManager.setStreamVolume(AudioManager.STREAM_MUSIC, vol, 0);
          mediaPlayer.start();
        }
      }
    });
  }
}