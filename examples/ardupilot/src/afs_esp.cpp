#include "afs_esp.h"

#include <jni.h>
#include <iostream>
#include <string>

using namespace std;

AFS_esp::AFS_esp()
{
	vm_args.version = JNI_VERSION_1_2;
  JavaVMOption* options;
  options = new JavaVMOption[2];
  options[0].optionString =
    "-Djava.class.path=/home/vagrant/radler/examples/ardupilot/jni:/home/vagrant/beepbeep-3-examples/beepbeep-3-examples.jar";
  options[1].optionString = "-Djava.compiler=NONE";
  vm_args.nOptions = 2;
  vm_args.options = options;
  vm_args.ignoreUnrecognized = 1;

	// Construct a VM
	jint res = JNI_CreateJavaVM(&vm, (void **)&this->env, &this->vm_args);
	if (res != JNI_OK) 
		cout << "JVM creation failed with ERROR CODE " << res << endl;
}

static double prev_pos_x = 0;
static double prev_pos_y = 0;

void AFS_esp::step(const radl_in_t * i, const radl_in_flags_t* i_f, radl_out_t * o, radl_out_flags_t* o_f) 
{
  if (radl_is_stale(i_f->position) || radl_is_timeout(i_f->position)) {
    if (radl_is_stale(i_f->position))
      cout << "position is stale" << endl;	
    if (radl_is_timeout(i_f->position))
      cout << "position is timeout" << endl;
    return;
  }

	double pos_x = i->position->x;
	double pos_y = i->position->y;

  jclass cls = env->FindClass("PointDistance");
  if (cls == 0) {
    cout << "FindClass PointDistance failed" << endl;
    return;
  }

  jmethodID mid = env->GetStaticMethodID(cls, "getPointDistance", "(FFFF)V");
  if (mid == 0) {
    cout << "GetStaticMethodID getPointDistance failed" << endl;
    return;
  } 

  env->CallStaticVoidMethod(cls, mid, jfloat(prev_pos_x), jfloat(prev_pos_y), jfloat(pos_x), jfloat(pos_y));

  prev_pos_x = pos_x;
  prev_pos_y = pos_y;
}
