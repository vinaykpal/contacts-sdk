#include "contact.h"
#include <utility>

namespace contacts {

Contact::Contact(std::string first_name,
                 std::string last_name,
                 std::string phone_number)
    : first_name_(std::move(first_name)),
      last_name_(std::move(last_name)),
      phone_number_(std::move(phone_number)) {}

}
