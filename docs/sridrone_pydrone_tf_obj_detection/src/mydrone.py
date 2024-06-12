import tensorflow as tf
import numpy as np
import os, time, sys, re, cv2, ps_drone
import six.moves.urllib as urllib

from collections import defaultdict
from io import StringIO
from matplotlib import pyplot as plt
from PIL import Image

from object_detection.utils import label_map_util
from object_detection.utils import visualization_utils as vis_util

drone = ps_drone.Drone()                                     # Start using drone
detection_graph = tf.Graph()
    
MODEL_NAME = 'ssd_mobilenet_v1_coco_11_06_2017'
PATH_TO_CKPT = MODEL_NAME + '/frozen_inference_graph.pb'
PATH_TO_LABELS = os.path.join('data', 'mscoco_label_map.pbtxt')

NUM_CLASSES = 90

label_map = label_map_util.load_labelmap(PATH_TO_LABELS)
categories = label_map_util.convert_label_map_to_categories(label_map, max_num_classes=NUM_CLASSES, use_display_name=True)
category_index = label_map_util.create_category_index(categories)

#Loads mapping from string UID to integer node ID.
def id_to_label(index):
    node_id_to_uid = {}
    proto_as_ascii = tf.gfile.GFile(PATH_TO_LABELS).readlines()
    for line in proto_as_ascii:
        if line.startswith('  id:'):
        	target_class = int(line.split(': ')[1])
      	if line.startswith('  display_name:'):
        	target_class_string = line.split(': ')[1]
        	node_id_to_uid[target_class] = target_class_string[1:-2]

    return node_id_to_uid[index]

def load_image_into_numpy_array(image):
    (im_width, im_height) = image.size

    return np.array(image.getdata()).reshape((im_height, im_width, 3)).astype(np.uint8)

def mydrone_init():
    drone.startup()                                              # Connects to drone and starts subprocesses
    drone.reset()                                                # Sets drone's status to good (LEDs turn green when red)
    while (drone.getBattery()[0] == -1):      time.sleep(0.1)    # Waits until drone has done its reset
    print "Battery: "+str(drone.getBattery()[0])+"%  "+str(drone.getBattery()[1])   # Gives a battery-status
    drone.useDemoMode(True)                                  

    ##### Mainprogram begin #####
    drone.setConfigAllID()                                       # Go to multiconfiguration-mode
    drone.sdVideo()                                              # Choose lower resolution (hdVideo() for...well, guess it)
    drone.frontCam()                                             # Choose front view
    CDC = drone.ConfigDataCount
    while CDC == drone.ConfigDataCount:       time.sleep(0.0001) # Wait until it is done (after resync is done)
    drone.startVideo()                                           # Start video-function
#    drone.showVideo()                                           

    print "VideoReady: "+str(drone.VideoReady)
    print "VideoImageCount: "+str(drone.VideoImageCount)

    with detection_graph.as_default():
    	od_graph_def = tf.GraphDef()
    	with tf.gfile.GFile(PATH_TO_CKPT, 'rb') as fid:
        	serialized_graph = fid.read()
        	od_graph_def.ParseFromString(serialized_graph)
        	tf.import_graph_def(od_graph_def, name='')

def mydrone_mainloop():
    IMC = drone.VideoImageCount                               	# Number of encoded videoframes
    while drone.VideoImageCount == IMC: time.sleep(0.01)    	# Wait until the next video-frame
    IMC = drone.VideoImageCount
    print "VideoImageCount: "+str(drone.VideoImageCount)

    with detection_graph.as_default():
        with tf.Session(graph=detection_graph) as sess:
            image = Image.fromarray(drone.VideoImage)
    
            image_np = load_image_into_numpy_array(image)
            image_np_expanded = np.expand_dims(image_np, axis=0)
            image_tensor = detection_graph.get_tensor_by_name('image_tensor:0')
            boxes = detection_graph.get_tensor_by_name('detection_boxes:0')
            scores = detection_graph.get_tensor_by_name('detection_scores:0')
            classes = detection_graph.get_tensor_by_name('detection_classes:0')
            num_detections = detection_graph.get_tensor_by_name('num_detections:0')
            (boxes, scores, classes, num_detections) = sess.run([boxes, scores, classes, num_detections], feed_dict={image_tensor: image_np_expanded})
            vis_util.visualize_boxes_and_labels_on_image_array(image_np, np.squeeze(boxes), np.squeeze(classes).astype(np.int32), np.squeeze(scores), category_index, use_normalized_coordinates=True, line_thickness=8)
    
            image_np_a = np.asarray(image_np)  
            cv2.imshow("Drone Object Detection", image_np_a)
            cv2.waitKey(1)

    print id_to_label(np.squeeze(classes)[0].astype(np.int32)), np.squeeze(scores)[0]  

    return np.squeeze(classes)[0] 

def mydrone_led(id):
    drone.led(id, 4, 2)

if __name__ == '__main__':
    mydrone_init()
    mydrone_led(1)
    while True:
        mydrone_mainloop()
