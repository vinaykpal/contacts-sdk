package com.contacts;

public interface ContactListener {
    void onContactAdded(String status);
    void onContactUpdated(String newContact, String oldContact);
}
