package com.contacts;

import android.util.Log;

/**
 * The Contacts SDK allows users to manage a users contacts. Your submission should include the
 * following features:
 *
 * 1. List all of a users contacts.
 * 2. Add a new contact.
 * 3. Notify user of an updated contact.
 *
 * The class includes a simple {@link #getVersion()} method to demonstrate how to call from a
 * Java class to C++ code.
 */
public class Contacts {

    private static final String LOG_TAG = "contacts-sdk";
    static {
        System.loadLibrary(BuildConfig.CONTACTS_LIBRARY);
    }

    private static Initiater initiaterCtx;
    /**
     * Returns a semantic versioning formatted string.
     */
    public static String getVersion() {
        return nativeGetVersion();
    }

    public static String getListContacts() {
        return nativeGetListContacts();
    }

    public static void addNewCotact(String newContact) {
        nativeAddNewCotact(newContact);
    }

    public static void startUpdateTimer() {
        nativeStartUpdateTimer();
    }

    public static void registerCallback() {
        register();
    }
    private static native String nativeGetListContacts();
    private static native String nativeGetVersion();
    public static native void nativeAddNewCotact(String newContact  );

    public static native void register();
    public static native void nativeStartUpdateTimer();

    /**
     * Event from C++ sdk after contact was added
     * @param retStatus -> SUCCESS /FAIL
     */
    public static void callbackContactAddedStatus(String retStatus) {
        Log.i(LOG_TAG, "from JNI contact added status: " + retStatus);
        //notify to listners
        if(initiaterCtx != null) {
            Log.i(LOG_TAG, "Notify contact added status: " + retStatus);
            initiaterCtx.contactAddedStatus(retStatus);
        }
    }

    /**
     * Event from C++ sdk after contact was updated externally
     * @param newContact, oldContact
     */
    public static void callbackContactUpdated(String newContact, String oldContact) {
        Log.i(LOG_TAG, "from JNI contact updated: newContact: " + newContact +" oldContact: "+ oldContact);
        //notify to listners
        if(initiaterCtx != null) {
            Log.i(LOG_TAG, "Notify contact updated");
            initiaterCtx.contactUpdated(newContact, oldContact);
        }

    }

    public static void setInitiaterCtx(Initiater ctx) {
        initiaterCtx = ctx;
    }
}
