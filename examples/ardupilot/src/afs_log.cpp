#include "afs_log.h"

#include <jni.h>
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

string getEnvVar(string const& key)
{
    char const* val = getenv(key.c_str());
    return val == NULL ? string() : string(val);
}

AFS_Log::AFS_Log()
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

void AFS_Log::step(const radl_in_t * i, const radl_in_flags_t* i_f, radl_out_t * o, radl_out_flags_t* o_f) 
{
  double alt = i->altitude->data;

  jstring jstr;

  if (radl_is_stale(i_f->altitude))
    jstr = env->NewStringUTF("altitude is stale");
  if (radl_is_timeout(i_f->altitude))
    jstr = env->NewStringUTF("altitude is timeout");
  if (!radl_is_stale(i_f->altitude) && !radl_is_timeout(i_f->altitude)) {
    jstr = env->NewStringUTF(to_string(alt).c_str());
  }

  jclass lmcls = env->FindClass("org/apache/logging/log4j/LogManager");
  assert(lmcls);
  jmethodID gflmid = env->GetStaticMethodID(lmcls, "getFormatterLogger", "()Lorg/apache/logging/log4j/Logger;");
  assert(gflmid);
  jobject lobj = env->CallStaticObjectMethod(lmcls, gflmid);
  assert(lobj);
  jclass lcls = env->GetObjectClass(lobj);
  assert(lcls);
  jmethodID trmid = env->GetMethodID(lcls, "trace", "(Ljava/lang/String;)V");
  assert(trmid);
  cout << alt << endl;
  env->CallVoidMethod(lobj, trmid, jstr);
}
