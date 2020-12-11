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
		cout << "java/lang/System lookup failed" << endl;
		return;
	}
	fid = env->GetStaticFieldID(cls, "out", "Ljava/io/PrintStream;");
	if (fid == 0) {
		cout << "java/lang/System::out lookup failed" << endl;
		return;
	}
	obj = env->GetStaticObjectField(cls, fid);
	if (obj == 0) {
		cout << "GetStaticObjectField call failed" << endl;
		return;
	}
	cls = env->GetObjectClass(obj);
	if (cls == 0) {
		cout << "GetObjectClass(out) failed" << endl;
		return;
	}
	mid = env->GetMethodID(cls, "println", "(Ljava/lang/String;)V");
	if (mid == 0) {
		cout << "println method lookup failed" << endl;
		return;
	}
	env->CallVoidMethod(obj, mid, jstr);
}
