#ifndef CONTACTS_H_
#define CONTACTS_H_

#include <string>
#include <vector>
#include "contact.h"

namespace contacts {

class Contacts {
 public:

    Contacts();

    static std::string getVersion();
    static std::string getListContacts();
    static void updateContacts();
    static void addNewContact(std::string);
    static void startUpdateTimer();

    static std::string createJsonString();
    static std::vector<std::string> contactsList;

 private:

    const static std::string kSdkVersion;
    const static std::string kContactsList;
};

}

#endif //CONTACTS_H_
