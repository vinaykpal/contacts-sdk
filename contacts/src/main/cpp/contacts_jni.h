#include <jni.h>
#include <string>

#ifndef CONTACTS_JNI_H_
#define CONTACTS_JNI_H_


namespace contacts {
namespace jni {

extern "C" JNIEXPORT jstring JNICALL Java_com_contacts_Contacts_nativeGetVersion(JNIEnv *env,
                                                                                 jclass jclass);

    extern "C" JNIEXPORT void JNICALL Java_com_contacts_Contacts_nativeStartUpdateTimer(JNIEnv *env,
                                                                                           jclass jclas);
extern "C" JNIEXPORT jstring JNICALL Java_com_contacts_Contacts_nativeGetListContacts(JNIEnv *env,
                                                                                     jclass jclass);

extern "C" JNIEXPORT void JNICALL Java_com_contacts_Contacts_nativeAddNewCotact(JNIEnv *env,
                                                                                      jclass jclass,
                                                                                      jstring val);

extern "C" JNIEXPORT void JNICALL Java_com_contacts_Contacts_register(JNIEnv * env, jclass obj);

    void callback(std::string val);
    void callbackContactAddedStatus(std::string val);
    void callbackContactUpdated(std::string newContact, std::string oldContact);

    // cached refs for later callbacks
    static JavaVM * g_vm;
    static jclass g_obj;
    static jmethodID g_mid, g_mid_contactAddedStatus, g_mid_contactupdatedStatus;
    static JNIEnv* g_env;
}
}

#endif // CONTACTS_JNI_H_
