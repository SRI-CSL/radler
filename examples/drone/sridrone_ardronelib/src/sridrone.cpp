#include "ros/ros.h"
#include "sridrone.h"
#include "key.h" 
#include <iostream>

extern "C" {
#define FFMPEG_SUPPORT 
#define USE_LINUX

#include <ardrone_tool/ardrone_tool.h>
#include <ardrone_tool/ardrone_version.h>

//ARDroneLib
#include <utils/ardrone_time.h>
#include <ardrone_tool/Navdata/ardrone_navdata_client.h>
#include <ardrone_tool/Control/ardrone_control.h>
#include <ardrone_tool/UI/ardrone_input.h>
#include <ardrone_tool/ardrone_tool_configuration.h>

//Common
#include <config.h>
#include <ardrone_api.h>

//VP_SDK
#include <ATcodec/ATcodec_api.h>
#include <VP_Os/vp_os_print.h>
#include <VP_Api/vp_api_thread_helper.h>
#include <VP_Os/vp_os_signal.h>
#include <VP_Os/vp_os_delay.h>

#include <Maths/maths.h>

//Video 
#include <ardrone_tool/Video/video_stage_decoder.h>
#include <ardrone_tool/Video/video_stage.h>
#include <gtk/gtk.h>
#include <cairo.h>

//teleop 
#define _EPS 1.0e-6

bool needs_takeoff = false;
bool needs_land = false; 
bool needs_reset = false; 
float lx = 0.0, ly = 0.0, lz = 0.0; // linear 
float ax = 0.0, ay = 0.0, az = 0.0; // angular  
float old_left_right = 0.0;
float old_front_back = 0.0;
float old_up_down = 0.0;
float old_turn = 0.0;

vp_os_mutex_t twist_lock;

C_RESULT open_teleop(void)
{
  return C_OK;
}

C_RESULT update_teleop(void)
{
  vp_os_mutex_lock(&twist_lock);
  if (needs_reset)
  {
    ardrone_tool_set_ui_pad_select(1);
    needs_reset = false;
  }
  else  if (needs_takeoff)
  {
    ardrone_tool_set_ui_pad_start(1);
    needs_takeoff = false;
  }
  else if (needs_land)
  {
    ardrone_tool_set_ui_pad_start(0);
    needs_land = false;
  }
  else
  {
    float left_right = ly; 
    float front_back = lx ;
    float up_down = lz; 
    float turn = az; 

    bool is_changed = !(
                        (fabs(left_right - old_left_right) < _EPS) &&
                        (fabs(front_back - old_front_back) < _EPS) &&
                        (fabs(up_down - old_up_down) < _EPS) &&
                        (fabs(turn - old_turn) < _EPS));
    
    // These lines are for testing, they should be moved to configurations
    // Bit 0 of control_flag == 0: should we hover?
    // Bit 1 of control_flag == 1: should we use combined yaw mode?

    int32_t control_flag = 0x00;
    int32_t combined_yaw = 0x00;

    // Auto hover detection based on ~0 values for 4DOF cmd_vel
    int32_t hover = (int32_t)
                    ( (fabs(left_right) < _EPS) &&
                      (fabs(front_back) < _EPS) &&
                      (fabs(up_down) < _EPS) &&
                      (fabs(turn) < _EPS) &&
                      (fabs(ax) < _EPS) &&
                      (fabs(ay) < _EPS));

    control_flag |= ((1 - hover) << 0);
    control_flag |= (combined_yaw << 1);

    old_left_right = left_right;
    old_front_back = front_back;
    old_up_down = up_down;
    old_turn = turn;
    if ((is_changed) || (hover))
    {
      ardrone_tool_set_progressive_cmd(control_flag, left_right, front_back, up_down, turn, 0.0, 0.0);
    }
  }
  vp_os_mutex_unlock(&twist_lock);
  return C_OK;
} 

C_RESULT close_teleop(void)
{
  return C_OK;
}

input_device_t teleop =
{
  "Teleop",
  open_teleop,
  update_teleop,
  close_teleop
};

inline C_RESULT demo_navdata_client_init( void* data ) { return C_OK; }

const navdata_demo_t* nd;
inline C_RESULT demo_navdata_client_process( const navdata_unpacked_t* const navdata )
{
        nd = &navdata->navdata_demo;
  	return C_OK;
}

inline C_RESULT demo_navdata_client_release( void ) { return C_OK; }

// Video 
typedef struct _display_stage_cfg_ {
    	float bpp;
    	vp_api_picture_t *decoder_info;
    	uint8_t *frameBuffer;
    	GtkWidget *widget;
} display_stage_cfg_t;
display_stage_cfg_t dispCfg;

bool_t gtkRunning = FALSE; 

static gboolean
on_expose_event (GtkWidget *widget, GdkEventExpose *event, gpointer data)
{
    	display_stage_cfg_t *cfg = (display_stage_cfg_t *)data;
    	uint32_t stride = cfg->bpp * 640;

    	gtk_window_resize (GTK_WINDOW (widget), cfg->decoder_info->width, cfg->decoder_info->height);

    	cairo_t *cr = gdk_cairo_create (widget->window);
    	cairo_surface_t *surface = cairo_image_surface_create_for_data (cfg->frameBuffer, CAIRO_FORMAT_RGB16_565, 640, 360, stride);
    	cairo_set_source_surface (cr, surface, 0.0, 0.0);
    	cairo_paint (cr);
    	cairo_surface_destroy (surface);
    	cairo_destroy (cr);

    	return FALSE;
}

DEFINE_THREAD_ROUTINE(gtk, data)
{
    	GtkWidget *window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    	display_stage_cfg_t *cfg = (display_stage_cfg_t *)data;
    	cfg->widget = window;

    	g_signal_connect (window, "expose-event", G_CALLBACK (on_expose_event), data);
    	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

    	gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
    	gtk_window_set_default_size (GTK_WINDOW (window), 10, 10);
    	gtk_widget_set_app_paintable (window, TRUE);
    	gtk_widget_set_double_buffered (window, FALSE);

    	gtk_widget_show_all (window);
	gtkRunning = TRUE; 
	gtk_main(); 
	gtkRunning = FALSE; 
	
	sleep(5);
	exit(0);
	return (THREAD_RET)0;
}

inline C_RESULT display_stage_open(display_stage_cfg_t *cfg) 
{
	START_THREAD (gtk, cfg);
	return C_OK; 
}

inline C_RESULT display_stage_transform(display_stage_cfg_t *cfg, vp_api_io_data_t *in, vp_api_io_data_t *out)
{
        cfg->frameBuffer = (uint8_t *) vp_os_realloc (cfg->frameBuffer, in->size);
    	vp_os_memcpy (cfg->frameBuffer, in->buffers[in->indexBuffer], in->size);
	
	if (gtkRunning == TRUE) 
        	gtk_widget_queue_draw_area (cfg->widget, 0, 0, 640, 360);

    	out->size = 0;

        return C_OK;
}

inline C_RESULT display_stage_close(display_stage_cfg_t *cfg) 
{ 
	if (NULL != cfg->frameBuffer)
     	{
         	vp_os_free (cfg->frameBuffer);
         	cfg->frameBuffer = NULL;
     	}

	return C_OK; 
}

const vp_api_stage_funcs_t display_stage_funcs =
{
        NULL,
        (vp_api_stage_open_t)display_stage_open,
        (vp_api_stage_transform_t)display_stage_transform,
        (vp_api_stage_close_t)display_stage_close
};

PROTO_THREAD_ROUTINE (gtk, data);

BEGIN_THREAD_TABLE
  	THREAD_TABLE_ENTRY( ardrone_control, 20 )
  	THREAD_TABLE_ENTRY( navdata_update, 20 )
  	THREAD_TABLE_ENTRY( video_stage, 20 )
  	THREAD_TABLE_ENTRY( gtk, 20 )
END_THREAD_TABLE

BEGIN_NAVDATA_HANDLER_TABLE
    	NAVDATA_HANDLER_TABLE_ENTRY(demo_navdata_client_init, demo_navdata_client_process, demo_navdata_client_release, NULL)
END_NAVDATA_HANDLER_TABLE
}

SRIDrone::SRIDrone()
{
    	while (-1 == getDroneVersion (".", *RADL_THIS->drone_ip, &ardroneVersion))
    	{
        	std::cout << "Getting AR.Drone version ..." << std::endl;
        	vp_os_delay (250);
    	}

    	// Setup communication channels
    	C_RESULT res = C_FAIL;
    	res = ardrone_tool_setup_com( NULL );
    	if( FAILED(res) )
    	{
        	std::cout << "Wifi initialization failed" << std::endl;
    	}
    	else
    	{
        	res = ardrone_tool_init(*RADL_THIS->drone_ip, strlen(*RADL_THIS->drone_ip), NULL, "sridrone_ardronelib", "sridrone", NULL, NULL, 40, NULL);
    	}

    	// Drone needs enough time to init... 5sec here 
    	vp_os_delay (5000);

    	if ( SUCCEED(res) ) {
  		std::cout << "Initialized - " << *RADL_THIS->drone_ip << std::endl;
    	}
    	else {
       		std::cout << "Failed to initialize - " << *RADL_THIS->drone_ip << std::endl;
		exit(0); 
     	}

	vp_os_mutex_init(&twist_lock);
	ardrone_tool_input_add(&teleop); 

	if (*RADL_THIS->show_image) {
		int argc=1; 
		char **argv;
		gtk_init(&argc,&argv);

		ardrone_application_default_config.video_codec = (codec_type_t)H264_360P_CODEC;
		ardrone_application_default_config.video_channel = (ZAP_VIDEO_CHANNEL)ZAP_CHANNEL_HORI;
		ardrone_application_default_config.bitrate_ctrl_mode = 1;

    		specific_parameters_t *params = (specific_parameters_t *)vp_os_calloc (1, sizeof (specific_parameters_t));
    		specific_stages_t *example_pre_stages = (specific_stages_t *)vp_os_calloc (1, sizeof (specific_stages_t));
    		specific_stages_t *example_post_stages = (specific_stages_t *)vp_os_calloc (1, sizeof (specific_stages_t));
    		vp_api_picture_t *in_picture = (vp_api_picture_t *)vp_os_calloc (1, sizeof (vp_api_picture_t));
    		vp_api_picture_t *out_picture = (vp_api_picture_t *)vp_os_calloc (1, sizeof (vp_api_picture_t));
	
    		in_picture->width = 640; 
    		in_picture->height = 360; 

    		out_picture->framerate = 20; 
    		out_picture->format = PIX_FMT_RGB565; 
    		out_picture->width = in_picture->width;
    		out_picture->height = in_picture->height;

		uint32_t bpp = 2;
       		out_picture->y_buf = (uint8_t *)vp_os_malloc ( out_picture->width * out_picture->height * bpp );
       		out_picture->cr_buf = NULL;
       		out_picture->cb_buf = NULL;
       		out_picture->y_line_size = out_picture->width * bpp;
       		out_picture->cb_line_size = 0;
       		out_picture->cr_line_size = 0;
	
    		example_pre_stages->stages_list = (vp_api_io_stage_t *)vp_os_calloc (1, sizeof (vp_api_io_stage_t));
    		example_post_stages->stages_list = (vp_api_io_stage_t *)vp_os_calloc (1, sizeof (vp_api_io_stage_t));
 
		uint8_t stages_index = 0;

    		vp_os_memset (&dispCfg, 0, sizeof (display_stage_cfg_t));
    		dispCfg.bpp = bpp;
    		dispCfg.decoder_info = in_picture;

    		example_post_stages->stages_list[stages_index].name = "Decoded display"; 
    		example_post_stages->stages_list[stages_index].type = VP_API_OUTPUT_SDL; 
    		example_post_stages->stages_list[stages_index].cfg  = &dispCfg;
    		example_post_stages->stages_list[stages_index++].funcs  = display_stage_funcs;

    		example_post_stages->length = stages_index;

    		params->in_pic = in_picture;
    		params->out_pic = out_picture;
    		params->pre_processing_stages_list  = example_pre_stages;
    		params->post_processing_stages_list = example_post_stages;
    		params->needSetPriority = 0;
    		params->priority = 0;

		START_THREAD(video_stage, params);
		video_stage_init();
		video_stage_resume_thread(); 
	}
	else {
		std::cout << "show_image is disabled" << std::endl; 
	}
}

void SRIDrone::step(const radl_in_t * in, const radl_in_flags_t* iflags,
                    radl_out_t * out, radl_out_flags_t * oflags) 
{
	if ( *RADL_THIS->print_data ) {
		std::cout << "-----------------------------------" << std::endl;
	}

        C_RESULT res = ardrone_tool_update();
        while( FAILED(res) ) 
        {
            	res = ardrone_tool_update();
        }
	// Orientation
        double roll  = nd->phi * 0.001 * DEG_TO_RAD; 
        double pitch = -nd->theta * 0.001 * DEG_TO_RAD; 
        double yaw   = -nd->psi * 0.001 * DEG_TO_RAD; 

        // Altitude
        double altitude = nd->altitude;

        // Velocity
	double v_x = nd->vx;
	double v_y = nd->vy;
	double v_z = nd->vz;

        // Battery
        int battery = nd->vbat_flying_percentage;

	out->navdata->roll = roll; 
	out->navdata->pitch = pitch; 
	out->navdata->yaw = yaw; 

	out->navdata->altitude = altitude;
	out->navdata->vx = v_x;
	out->navdata->vy = v_y;
	out->navdata->vz = v_z;

	out->navdata->battery = battery;

	radl_turn_off( radl_TIMEOUT, &oflags->navdata );
	radl_turn_off( radl_STALE, &oflags->navdata );

	if ( *RADL_THIS->check_iflags ) {
		if ( radl_is_stale(iflags->led_anim) ) 
			std::cout << "led_anim is stale" << std::endl;
		if ( radl_is_timeout(iflags->led_anim) ) 
			std::cout << "led_anim is timeout" << std::endl;
		if ( radl_is_stale(iflags->camera_param) ) 
			std::cout << "camera_param is stale" << std::endl;
		if ( radl_is_timeout(iflags->camera_param) ) 
			std::cout << "camera_param is timeout" << std::endl;
		if ( radl_is_stale(iflags->key_input) ) 
			std::cout << "key_input is stale" << std::endl;
		if ( radl_is_timeout(iflags->key_input) ) 
			std::cout << "key_input is timeout" << std::endl;
		if ( radl_is_stale(iflags->timer_input) ) 
			std::cout << "timer_input is stale" << std::endl;
		if ( radl_is_timeout(iflags->timer_input) ) 
			std::cout << "timer_input is timeout" << std::endl;
	}

	if ( !radl_is_stale(iflags->landing_input) && !radl_is_timeout(iflags->landing_input) ) {  
	    if (in->landing_input->nearground) {
		vp_os_mutex_lock(&twist_lock);
		needs_land = true; 
		vp_os_mutex_unlock(&twist_lock);
		std::cout << "landing by nearground" << std::endl; 	
	    }  
	}

	if ( !radl_is_stale(iflags->timer_input) && !radl_is_timeout(iflags->timer_input) ) {  
	    if (in->timer_input->expiry) {
		vp_os_mutex_lock(&twist_lock);
		needs_land = true; 
		vp_os_mutex_unlock(&twist_lock);
		std::cout << "landing by timer" << std::endl; 	
	    }
	}  

	if ( !radl_is_stale(iflags->key_input) && !radl_is_timeout(iflags->key_input) ) {  
	    switch (in->key_input->key) { 
	    case KEY_TAKEOFF: // takeoff '+'
		vp_os_mutex_lock(&twist_lock);
		needs_takeoff = true; 
		vp_os_mutex_unlock(&twist_lock);
		std::cout << "takeoff by teleop" << std::endl; 	
		break;
	    case KEY_LANDING: // landing '-'
		vp_os_mutex_lock(&twist_lock);
		needs_land = true; 
		vp_os_mutex_unlock(&twist_lock);
		std::cout << "landing by teleop" << std::endl; 	
		break;
	    case KEY_RESET: // reset ' ' 
		vp_os_mutex_lock(&twist_lock);
		needs_reset = true; 
		vp_os_mutex_unlock(&twist_lock);
		std::cout << "reset by teleop" << std::endl; 	
		break;
	    case KEY_UP: // up 'u' 
		vp_os_mutex_lock(&twist_lock);
		lx = 0.0; ly = 0.0; lz = 0.1; ax = 0.0; ay = 0.0; az = 0.0;
		vp_os_mutex_unlock(&twist_lock);
		std::cout << "up by teleop" << std::endl; 	
		break;
	    case KEY_DOWN: // down 'd' 
		vp_os_mutex_lock(&twist_lock);
		lx = 0.0; ly = 0.0; lz = -0.1; ax = 0.0; ay = 0.0; az = 0.0;
		vp_os_mutex_unlock(&twist_lock);
		std::cout << "down by teleop" << std::endl; 	
		break;
	    case KEY_FORWARD: // forward 'f' 
		vp_os_mutex_lock(&twist_lock);
		lx = 0.1; ly = 0.0; lz = 0.0; ax = 0.0; ay = 0.0; az = 0.0;
		vp_os_mutex_unlock(&twist_lock);
		std::cout << "forward by teleop" << std::endl; 	
		break;
	    case KEY_BACKWARD: // backward 'b' 
		vp_os_mutex_lock(&twist_lock);
		lx = -0.1; ly = 0.0; lz = 0.0; ax = 0.0; ay = 0.0; az = 0.0;
		vp_os_mutex_unlock(&twist_lock);
		std::cout << "backward by teleop" << std::endl; 	
		break;
	    case KEY_LEFT: // left 'l' 
		vp_os_mutex_lock(&twist_lock);
		lx = 0.0; ly = 0.1; lz = 0.0; ax = 0.0; ay = 0.0; az = 0.0;
		vp_os_mutex_unlock(&twist_lock);
		std::cout << "left by teleop" << std::endl; 	
		break;
	    case KEY_RIGHT: // right 'r' 
		vp_os_mutex_lock(&twist_lock);
		lx = 0.0; ly = -0.1; lz = 0.0; ax = 0.0; ay = 0.0; az = 0.0;
		vp_os_mutex_unlock(&twist_lock);
		std::cout << "right by teleop" << std::endl; 	
		break;
	    case KEY_TURNLEFT: // turn left '[' 
		vp_os_mutex_lock(&twist_lock);
		lx = 0.0; ly = 0.0; lz = 0.0; ax = 0.0; ay = 0.0; az = 0.1;
		vp_os_mutex_unlock(&twist_lock);
		std::cout << "turn left by teleop" << std::endl; 	
		break;
	    case KEY_TURNRIGHT: // turn right ']' 
		vp_os_mutex_lock(&twist_lock);
		lx = 0.0; ly = 0.0; lz = 0.0; ax = 0.0; ay = 0.0; az = -0.1;
		vp_os_mutex_unlock(&twist_lock);
		std::cout << "turn right by teleop" << std::endl; 	
		break;
	    case KEY_HOVER: // hover '=' 
		vp_os_mutex_lock(&twist_lock);
		lx = 0.0; ly = 0.0; lz = 0.0; ax = 0.0; ay = 0.0; az = 0.0;
		vp_os_mutex_unlock(&twist_lock);
		std::cout << "hover by teleop" << std::endl; 	
		break;
	    default: 
		break;
	    }
	}

	// set led animation 
	if ( !radl_is_stale(iflags->led_anim) && !radl_is_timeout(iflags->led_anim) )    
    		ardrone_at_set_led_animation((LED_ANIMATION_IDS) in->led_anim->id, (float) fabs(in->led_anim->freq), (uint32_t) abs(in->led_anim->span));

	// select cam channel 
	static int32_t current_video_channel = 0;
	if ( !radl_is_stale(iflags->camera_param) && !radl_is_timeout(iflags->camera_param) )    
	{
	    int32_t channel = in->camera_param->mode; 
	    if ( current_video_channel != channel ) 
    		ARDRONE_TOOL_CONFIGURATION_ADDEVENT (video_channel, &channel, NULL);
	    current_video_channel = channel; 
	}

	if ( *RADL_THIS->print_data ) {
		std::cout << "ardrone.roll  = " << roll  * RAD_TO_DEG << " [deg]" << std::endl;
		std::cout << "ardrone.pitch = " << pitch * RAD_TO_DEG << " [deg]" << std::endl;
		std::cout << "ardrone.yaw   = " << yaw   * RAD_TO_DEG << " [deg]" << std::endl;
		std::cout << "ardrone.altitude = " << altitude * 0.001 << " [m]" << std::endl;
		std::cout << "ardrone.vx = " << v_x << " [m/s]" << std::endl;
		std::cout << "ardrone.vy = " << v_y << " [m/s]" << std::endl;
		std::cout << "ardrone.vz = " << v_z << " [m/s]" << std::endl;
		std::cout << "ardrone.battery = " << battery << " [%]" << std::endl;
		std::cout << "ardrone.setAnimation = " << in->led_anim->id << std::endl;
	}
}
