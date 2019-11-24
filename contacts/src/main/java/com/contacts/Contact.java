package com.contacts;

import java.util.Objects;

/**
 * Represents a user's contact.
 */
public class Contact {

    public final String firstName;
    public final String lastName;
    public final String phoneNumber;

    public Contact(String firstName, String lastName, String phoneNumber) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.phoneNumber = phoneNumber;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Contact contact = (Contact) o;
        return firstName.equals(contact.firstName) &&
                lastName.equals(contact.lastName) &&
                phoneNumber.equals(contact.phoneNumber);
    }

    @Override
    public int hashCode() {
        return Objects.hash(firstName, lastName, phoneNumber);
    }
}
