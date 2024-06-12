#include "afs_esp.h"

#include <jni.h>
#include <iostream>
#include <string>

using namespace std;

string getEnvVar(string const& key)
{
    char const* val = getenv(key.c_str());
    return val == NULL ? string() : string(val);
}

AFS_esp::AFS_esp()
{
  vm_args.version = JNI_VERSION_1_2;
  JavaVMOption* options;
  options = new JavaVMOption[2];
  string cp = "-Djava.class.path=" + getEnvVar("CLASSPATH");
  options[0].optionString = const_cast<char*>(cp.c_str());
  options[1].optionString = "-Djava.compiler=NONE";
  vm_args.nOptions = 2;
  vm_args.options = options;
  vm_args.ignoreUnrecognized = JNI_TRUE;

  cout << "CreateJVM " << options[0].optionString << endl;

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
    //return;
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

  if(*RADL_THIS->daikon) {
    jclass cls = env->FindClass("daikon/Chicory");
    if (cls == 0) {
      cout << "FindClass daikon.Chicory failed" << endl;
      return;
    }

    jmethodID mid = env->GetStaticMethodID(cls, "main", "([Ljava/lang/String;)V");
    if (mid == 0) {
      cout << "GetStaticMethodID main failed" << endl;
      return;
    }

    jobjectArray args = env->NewObjectArray(5, env->FindClass("java/lang/String"), NULL);
    env->SetObjectArrayElement(args, 0, env->NewStringUTF("PointDistance"));
    env->SetObjectArrayElement(args, 1, env->NewStringUTF(to_string(prev_pos_x).c_str()));
    env->SetObjectArrayElement(args, 2, env->NewStringUTF(to_string(prev_pos_y).c_str()));
    env->SetObjectArrayElement(args, 3, env->NewStringUTF(to_string(pos_x).c_str()));
    env->SetObjectArrayElement(args, 4, env->NewStringUTF(to_string(pos_y).c_str()));
    env->CallStaticVoidMethod(cls, mid, args);
  }

  prev_pos_x = pos_x;
  prev_pos_y = pos_y;
}
