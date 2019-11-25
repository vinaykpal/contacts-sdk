package com.contacts;

import android.util.Log;

import java.util.ArrayList;
import java.util.List;

public class Initiater {
    private static final String TAG = "contacts-sdk";
    private List<ContactListener> listeners = new ArrayList<>();

    public void addListener(ContactListener toAdd) {
        listeners.add(toAdd);
    }

    public void contactAddedStatus(String status) {
        Log.i(TAG, "contact Added!!");

        // Notify all listener about new contact added status
        for (ContactListener contactListener : listeners)
            contactListener.onContactAdded(status);
    }

    public void contactUpdated(String newContact, String oldContact) {
        Log.i(TAG, "contact Updated!!");

        // Notify all listener about on contact update
        for (ContactListener contactListener : listeners)
            contactListener.onContactUpdated(newContact, oldContact);
    }
}
