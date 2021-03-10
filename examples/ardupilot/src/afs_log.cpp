#include "afs_log.h"

#include <jni.h>
#include <iostream>
#include <string>

using namespace std;

AFS_Log::AFS_Log()
{
	vm_args.version = JNI_VERSION_1_2;
	vm_args.nOptions = 0;
	vm_args.ignoreUnrecognized = 1;

	// Construct a VM
	jint res = JNI_CreateJavaVM(&vm, (void **)&this->env, &this->vm_args);
	if (res != JNI_OK) 
		cout << "JVM creation failed with ERROR CODE " << res << endl;

  auto t = std::time(nullptr);
  auto tm = *std::localtime(&t);
  std::ostringstream oss;
  oss << std::put_time(&tm, "afs.log-%m-%d-%Y-%H-%M-%S");
  auto fn = oss.str();

  jclass cls;
  jfieldID fid;
  jobject obj;
  jmethodID mid;
  jstring jstr;

  jstr = env->NewStringUTF(fn.c_str());

  cls = env->FindClass("java/lang/System");
  if (cls == 0) {
    cout << "FindClass java/lang/System failed" << endl;
    return;
  }
  fid = env->GetStaticFieldID(cls, "out", "Ljava/io/PrintStream;");
  if (fid == 0) {
    cout << "GetStaticFieldID out java/io/PrintStream failed" << endl;
    return;
  }
  obj = env->GetStaticObjectField(cls, fid);
  if (obj == 0) {
    cout << "GetStaticObjectField failed" << endl;
    return;
  }
  cls = env->GetObjectClass(obj);
  if (cls == 0) {
    cout << "GetObjectClass failed" << endl;
    return;
  }
  mid = env->GetMethodID(cls, "<init>", "(Ljava/lang/String;)V");
  if (mid == 0) {
    cout << "GetMethodID <init> failed" << endl;
    return;
  }
  env->CallVoidMethod(obj, mid, jstr);
}

void AFS_Log::step(const radl_in_t * i, const radl_in_flags_t* i_f, radl_out_t * o, radl_out_flags_t* o_f) 
{
	double alt = i->altitude->data;

	jclass cls;
	jfieldID fid;
	jobject obj;
	jmethodID mid;
	jstring jstr;

	if (radl_is_stale(i_f->altitude))
		jstr = env->NewStringUTF("altitude is stale");	
	if (radl_is_timeout(i_f->altitude))
		jstr = env->NewStringUTF("altitude is timeout");
	if (!radl_is_stale(i_f->altitude) && !radl_is_timeout(i_f->altitude)) {
		jstr = env->NewStringUTF(to_string(alt).c_str());
	}

	cls = env->FindClass("java/lang/System");
	if (cls == 0) {
		cout << "FindClass java/lang/System failed" << endl;
		return;
	}
	fid = env->GetStaticFieldID(cls, "out", "Ljava/io/PrintStream;");
	if (fid == 0) {
		cout << "GetStaticFieldID out java/io/PrintStream failed" << endl;
		return;
	}
	obj = env->GetStaticObjectField(cls, fid);
	if (obj == 0) {
		cout << "GetStaticObjectField failed" << endl;
		return;
	}
	cls = env->GetObjectClass(obj);
	if (cls == 0) {
		cout << "GetObjectClass failed" << endl;
		return;
	}
	mid = env->GetMethodID(cls, "println", "(Ljava/lang/String;)V");
	if (mid == 0) {
		cout << "GetMethodID println failed" << endl;
		return;
  }
  env->CallVoidMethod(obj, mid, jstr);
}
