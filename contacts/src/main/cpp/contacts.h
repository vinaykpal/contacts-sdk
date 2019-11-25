#ifndef CONTACTS_H_
#define CONTACTS_H_

#include <string>
#include <vector>
#include "contact.h"

namespace contacts {

class Contacts {
 public:
    /**
     * API to return Version
     * @return version
     */
    static std::string getVersion();
    /**
     * API to return All list of contacts
     * @return contact List
     */
    static std::string getListContacts();
    /**
     * API to trigger contacts updated to JNI
     * based on timer timeout
     */
    static void updateContacts();
    /**
     * API to add new contact in SDK from Java
     */
    static void addNewContact(std::string);
    /**
     * API exposed internally to start timer
     */
    static void startUpdateTimer();

    static std::string createJsonString();
    static std::vector<std::string> contactsList;

    contacts::Contacts* getCtx();

 private:

    const static std::string kSdkVersion;
};

}

#endif //CONTACTS_H_
