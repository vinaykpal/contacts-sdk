package com.contacts;

import org.junit.Test;

import static org.junit.Assert.*;

public class ContactsUnitTest {
    @Test
    public void nativeLibraryNameShouldBeDefined() {
        assertNotNull(BuildConfig.CONTACTS_LIBRARY);
    }
}