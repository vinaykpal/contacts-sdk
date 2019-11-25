#include "contacts.h"
#include <android/log.h>
#include <chrono>
#include "contacts_jni.h"

#include "Updatetimer.h"

#define  LOG_TAG    "contacs-sdk"

#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)


namespace contacts {

const std::string Contacts::kSdkVersion = "0.1.0";

/*
 * You may store all of a users contacts in memory and use this list to seed the users's initial
 * contact list.
 */
std::string newContactUpdate = "{\"first\" : \"Bill\",\"last\" : \"Mai\",\"phone\" : \"+000000000\"}";
std::string oldContactUpdate = "{\"first\" : \"John\",\"last\" : \"Baird\",\"phone\" : \"+4408458591006\"}";

const char* kContactsListArr[] = {
        "{\"first\" : \"Alexander\",\"last\" : \"Bell\",\"phone\" : \"+16170000001\"}",
        "{\"first\" : \"Thomas\",\"last\" : \"Watson\",\"phone\" : \"+16170000002\"}",
        "{\"first\" : \"Elisha\",\"last\" : \"Gray\",\"phone\" : \"+18476003599\"}",
        "{\"first\" : \"Antonio\",\"last\" : \"Meucci\",\"phone\" : \"+17188763245\"}",
        "{\"first\" : \"Guglielmo\",\"last\" : \"Marconi\",\"phone\" : \"+39051203222\"}",
        "{\"first\" : \"Thomas\",\"last\" : \"Edison\",\"phone\" : \"+19086575678\"}"

};

std::vector<std::string> Contacts::contactsList(kContactsListArr, std::end(kContactsListArr));

/**
     * API to return Version
     * @return version
     */
std::string contacts::Contacts::getVersion() {
    return kSdkVersion;
}

/**
     * API to return All list of contacts
     * @return contact List
     */
std::string contacts::Contacts::getListContacts() {
    LOGD("Inside Contacts getListContacts");

    return createJsonString();
}

/**
     * API to add new contact in SDK from Java
     */
void contacts::Contacts::addNewContact(std::string newContact) {

    LOGD("Add new Contact %s", newContact.c_str());
    if(newContact.find("first") != std::string::npos) {
        contactsList.push_back(newContact);
        LOGD("call success callback()");
        contacts::jni::callbackContactAddedStatus("SUCCESS");
    } else {
        LOGD("call FAIL callback()");
        contacts::jni::callbackContactAddedStatus("FAIL");
    }
}

/**
     * API to trigger contacts updated to JNI
     * based on timer timeout
     */
void contacts::Contacts::updateContacts() {
    LOGD("update contact");
    contacts::jni::callbackContactUpdated(newContactUpdate, oldContactUpdate);
}
//Helper method to create JsonString from string array
std::string contacts::Contacts::createJsonString() {

    std::string openBracket = "[";
    std::string closedBracket = "]";
    std::string comma = ",";
    std::string s;
    std::vector<std::string>::const_iterator iterator;

    s = s+openBracket;
    for( iterator = contactsList.begin(); iterator != contactsList.end()-1; ++iterator )
    {
        s = s + *iterator + comma;
    }
    s = s+ *iterator;
    return s + closedBracket;
}

/**
     * API exposed internally to start timer
     */
    void contacts::Contacts::startUpdateTimer() {
        LOGD("start Timer:");
        Updatetimer test;
        test.Test();
    }

    contacts::Contacts* contacts::Contacts::getCtx() {
        return this;
    }

}
