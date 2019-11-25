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

    // cached refs for later callbacks
    JavaVM * g_vm;
    jclass g_obj;
    jmethodID g_mid, g_mid_contactAddedStatus, g_mid_contactupdatedStatus;
    JNIEnv* g_env;

    //method to get version
    extern "C" JNIEXPORT jstring JNICALL Java_com_contacts_Contacts_nativeGetVersion(JNIEnv *env,
                                                                                     jclass jclass) {
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
        std::string sdk_version = contacts::Contacts::getVersion();
        auto sdk_version_str = convert.from_bytes(sdk_version);
        jstring jstr = env->NewString(reinterpret_cast<jchar const *>(sdk_version_str.c_str()),
                                      sdk_version_str.size());

        return jstr;
    }

    //method to start update timer. called once from Java onCreate()
    extern "C" JNIEXPORT void JNICALL Java_com_contacts_Contacts_nativeStartUpdateTimer(JNIEnv *env,
                                                                                    jclass jclass) {
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
        contacts::Contacts::startUpdateTimer();
    }

    //method to get List of contacts
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

    //method to add new contact to vector list
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
        LOGD("#### JNI_OnLoad");
        g_vm = vm;

    }

    // method to get method id for java functions
    extern "C" JNIEXPORT void JNICALL Java_com_contacts_Contacts_register
            (JNIEnv * env, jclass obj) {
        g_obj = reinterpret_cast<jclass>(env->NewGlobalRef(obj));
        g_env = env;
        env->GetJavaVM(&g_vm);

        LOGD("in register jni env:");
        jclass g_clazz = env->FindClass("com/contacts/Contacts");

        if (g_clazz == NULL) {
            LOGD("Failed to find class");
        }

        g_mid_contactAddedStatus = env->GetStaticMethodID(g_clazz, "callbackContactAddedStatus", "(Ljava/lang/String;)V");
        g_mid_contactupdatedStatus = env->GetStaticMethodID(g_clazz, "callbackContactUpdated", "(Ljava/lang/String;Ljava/lang/String;)V");

        if (g_mid == NULL) {
            LOGD("Unable texampleo get method ref");
        } else {
            LOGD("Found method-ID");
        }
    }

    void callbackContactAddedStatus (std::string strVal) {
        JavaVM* jvm;

        g_env->GetJavaVM(&jvm);
        //convert string
        const char * charVal = strVal.c_str();

        jstring  jstringVal = g_env->NewStringUTF(charVal);

        JNIEnv* myNewEnv;
        JavaVMAttachArgs args;

        args.name = NULL;
        args.group = NULL;
        jvm->AttachCurrentThread((JNIEnv**)&myNewEnv, &args);

        myNewEnv->CallStaticVoidMethod(g_obj, g_mid_contactAddedStatus, jstringVal);

        g_env->DeleteLocalRef(jstringVal);
        jstringVal = NULL;
    }

    void callbackContactUpdated (std::string newContact, std::string oldContact) {
        JNIEnv * env;

        int getEnvStat = g_vm->GetEnv((void **)&env, JNI_VERSION_1_6);
        if (getEnvStat == JNI_EDETACHED) {
            if (g_vm->AttachCurrentThread((JNIEnv **) &env, NULL) != 0) {
                LOGD("atached");
            }
        } else if (getEnvStat == JNI_OK) {
            //
        } else if (getEnvStat == JNI_EVERSION) {

        }

        jstring  jstringNewContact = env->NewStringUTF(newContact.c_str());
        if ((env)->ExceptionCheck()) {
         LOGD("exception in string");
        }
        jstring  jstringOldContact = env->NewStringUTF(oldContact.c_str());
        if ((env)->ExceptionCheck()) {
            LOGD("exception in string");
        }

        JNIEnv* myNewEnv;
        JavaVMAttachArgs args;

        args.name = NULL; // you might want to give the java thread a name
        args.group = NULL; // you might want to assign the java thread to a ThreadGroup

        g_vm->AttachCurrentThread((JNIEnv**)&myNewEnv, &args);

        myNewEnv->CallStaticVoidMethod(g_obj, g_mid_contactupdatedStatus, jstringNewContact, jstringOldContact);

        env->DeleteLocalRef(jstringNewContact);
        jstringNewContact = NULL;

        env->DeleteLocalRef(jstringOldContact);
        jstringOldContact = NULL;

    }

}
}