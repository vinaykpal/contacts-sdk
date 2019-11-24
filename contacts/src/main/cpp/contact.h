#ifndef CONTACT_H_
#define CONTACT_H_

#include <string>

namespace contacts {

class Contact {

 public:
    Contact(std::string first_name,
            std::string last_name,
            std::string phone_number);

 private:
    const std::string first_name_;
    const std::string last_name_;
    const std::string phone_number_;

};
}

#endif // CONTACT_H_
