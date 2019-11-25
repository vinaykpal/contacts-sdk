#include "contacts_jni.h"
#include "contacts.h"

#include <codecvt>
#include <locale>

#include <android/log.h>

#define  LOG_TAG    "contacs-sdk"

#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)


namespace contacts {
namespace jni {

    extern "C" JNIEXPORT jstring JNICALL Java_com_contacts_Contacts_nativeGetVersion(JNIEnv *env,
                                                                                     jclass jclass) {
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
        std::string sdk_version = contacts::Contacts::getVersion();
        auto sdk_version_str = convert.from_bytes(sdk_version);
        jstring jstr = env->NewString(reinterpret_cast<jchar const *>(sdk_version_str.c_str()),
                                      sdk_version_str.size());

        return jstr;
    }

    extern "C" JNIEXPORT void JNICALL Java_com_contacts_Contacts_nativeStartUpdateTimer(JNIEnv *env,
                                                                                    jclass jclass) {
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
        contacts::Contacts::startUpdateTimer();
    }


    extern "C" JNIEXPORT jstring JNICALL
    Java_com_contacts_Contacts_nativeGetListContacts(JNIEnv *env,
                                                     jclass jclass) {

        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
        std::string list_contacts = contacts::Contacts::getListContacts();

        auto list_contacts_str = convert.from_bytes(list_contacts);
        jstring jstr = env->NewString(reinterpret_cast<jchar const *>(list_contacts_str.c_str()),
                                      list_contacts_str.size());

        return jstr;
    }

    std::string jstring2string(JNIEnv *env, jstring jStr) {
        if (!jStr)
            return "";

        const jclass stringClass = env->GetObjectClass(jStr);
        const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes",
                                                    "(Ljava/lang/String;)[B");
        const jbyteArray stringJbytes = (jbyteArray) env->CallObjectMethod(jStr, getBytes,
                                                                           env->NewStringUTF(
                                                                                   "UTF-8"));

        size_t length = (size_t) env->GetArrayLength(stringJbytes);
        jbyte *pBytes = env->GetByteArrayElements(stringJbytes, NULL);

        std::string ret = std::string((char *) pBytes, length);

        env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);

        env->DeleteLocalRef(stringJbytes);
        env->DeleteLocalRef(stringClass);

        return ret;
    }


    extern "C" JNIEXPORT void JNICALL Java_com_contacts_Contacts_nativeAddNewCotact(JNIEnv *env,
                                                                                       jclass jclass  ,
                                                                                       jstring val) {
        const char *newContact = env->GetStringUTFChars(val , NULL ) ;

        std::string addNewContact = newContact;
        contacts::Contacts::addNewContact(addNewContact);
    }

    JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* aReserved)
    {
        // cache java VM
        LOGD("VP #### JNI_OnLoad");
        g_vm = vm;

    }

    extern "C" JNIEXPORT void JNICALL Java_com_contacts_Contacts_register
            (JNIEnv * env, jclass obj) {
        bool returnValue = true;
        // convert local to global reference
        // (local will die after this method call)
        g_obj = reinterpret_cast<jclass>(env->NewGlobalRef(obj));
        g_env = env;
        env->GetJavaVM(&g_vm);

        LOGD("in register jni env:");
        // save refs for callback
        //jclass g_clazz = env->GetObjectClass(g_obj);

        //jclass g_clazz = env->FindClass("com/contacts/app/ContactsActivity");
        jclass g_clazz = env->FindClass("com/contacts/Contacts");

        if (g_clazz == NULL) {
            LOGD("Failed to find class");
        }


        g_mid = env->GetStaticMethodID(g_clazz, "callback", "(Ljava/lang/String;)V");
        g_mid_contactAddedStatus = env->GetStaticMethodID(g_clazz, "callbackContactAddedStatus", "(Ljava/lang/String;)V");
        g_mid_contactupdatedStatus = env->GetStaticMethodID(g_clazz, "callbackContactUpdated", "(Ljava/lang/String;Ljava/lang/String;)V");


        if (g_mid == NULL) {
            LOGD("Unable texampleo get method ref");
        } else {
            LOGD("Found method-ID");
        }

        //return (jboolean)returnValue;
    }

    /*void sendMessage(char* buffer, int bufferlen) {
        JNIEnv *env = NULL;
        jmethodID mid = NULL;
        jbyteArray message;
        JavaVM* jjvm;

        jint res = (jjvm->AttachCurrentThread(&env, NULL));

        if (res >= 0) {
            message = (*env)->NewByteArray(env, bufferlen);
            (*env)->SetByteArrayRegion(env, message, 0, bufferlen, (const jbyte *) ((BYTE*) buffer));
            mid = (*env)->GetStaticMethodID(env, jcls, "sendMessage", "([B)V");

            // Mid <= 0 ? Not found : OK
            if (mid > 0) {
                (*env)->CallStaticVoidMethod(env, jcls, mid, message);
            }
        }
    }*/

    void callbackContactAddedStatus (std::string strVal) {
        JavaVM* jvm;

        g_env->GetJavaVM(&jvm);

        //convert string
        const char * charVal = strVal.c_str();

        jstring  jstringVal = g_env->NewStringUTF(charVal);

        // in the new thread:
        JNIEnv* myNewEnv;
        JavaVMAttachArgs args;

        args.name = NULL; // you might want to give the java thread a name
        args.group = NULL; // you might want to assign the java thread to a ThreadGroup
        jvm->AttachCurrentThread((JNIEnv**)&myNewEnv, &args);

        myNewEnv->CallStaticVoidMethod(g_obj, g_mid_contactAddedStatus, jstringVal);

       // jvm->DetachCurrentThread();
    }


    void callbackContactUpdated (std::string newContact, std::string oldContact) {
        JavaVM* jvm;

        //g_env->GetJavaVM(&jvm);

        //***

         JNIEnv * g_env;
        // double check it's all ok
        int getEnvStat = g_vm->GetEnv((void **)&g_env, JNI_VERSION_1_6);
        if (getEnvStat == JNI_EDETACHED) {
            //std::cout << "GetEnv: not attached" << std::endl;
            if (g_vm->AttachCurrentThread((JNIEnv **) &g_env, NULL) != 0) {
                LOGD("atached");
            }
        } else if (getEnvStat == JNI_OK) {
            //
        } else if (getEnvStat == JNI_EVERSION) {
            //std::cout << "GetEnv: version not supported" << std::endl;
        }
        //****

        //convert string
        const char * charNewContact = newContact.c_str();
        const char * charOldContact = oldContact.c_str();

        jstring  jstringNewContact = g_env->NewStringUTF(charNewContact);
        jstring  jstringOldContact = g_env->NewStringUTF(charOldContact);

        // in the new thread:
        JNIEnv* myNewEnv;
        JavaVMAttachArgs args;

        args.name = NULL; // you might want to give the java thread a name
        args.group = NULL; // you might want to assign the java thread to a ThreadGroup

        g_vm->AttachCurrentThread((JNIEnv**)&myNewEnv, &args);

        myNewEnv->CallStaticVoidMethod(g_obj, g_mid_contactupdatedStatus, jstringNewContact, jstringOldContact);
        //g_vm->DetachCurrentThread();

    }
    void callback(std::string strVal) {
        JavaVM* jvm;

        g_env->GetJavaVM(&jvm);

        //convert string
        const char * charVal = strVal.c_str();

        jstring  jstringVal = g_env->NewStringUTF(charVal);

        // in the new thread:
        JNIEnv* myNewEnv;
        JavaVMAttachArgs args;
        //args.version = JNI_VERSION_1_6; // choose your JNI version
        args.name = NULL; // you might want to give the java thread a name
        args.group = NULL; // you might want to assign the java thread to a ThreadGroup
        jvm->AttachCurrentThread((JNIEnv**)&myNewEnv, &args);

        myNewEnv->CallStaticVoidMethod(g_obj, g_mid, jstringVal);
        // And now you can use myNewEnv

    //*******************

       // JNIEnv * g_env;
        // double check it's all ok
        /*int getEnvStat = g_vm->GetEnv((void **)&g_env, JNI_VERSION_1_6);
        if (getEnvStat == JNI_EDETACHED) {
            //std::cout << "GetEnv: not attached" << std::endl;
            if (g_vm->AttachCurrentThread((JNIEnv **) &g_env, NULL) != 0) {
                //std::cout << "Failed to attach" << std::endl;
            }
        } else if (getEnvStat == JNI_OK) {
            //
        } else if (getEnvStat == JNI_EVERSION) {
            //std::cout << "GetEnv: version not supported" << std::endl;
        }
*/
    /*    g_vm->AttachCurrentThread((JNIEnv **) &g_env, NULL);
        g_env->CallVoidMethod(g_obj, g_mid, val);

        if (g_env->ExceptionCheck()) {
            g_env->ExceptionDescribe();
        }

        g_vm->DetachCurrentThread();*/
    }

}
}