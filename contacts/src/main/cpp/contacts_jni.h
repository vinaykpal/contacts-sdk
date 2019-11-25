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

    void callbackContactAddedStatus(std::string val);
    void callbackContactUpdated(std::string newContact, std::string oldContact);
}
}

#endif // CONTACTS_JNI_H_
