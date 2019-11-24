package com.contacts;


import androidx.test.ext.junit.runners.AndroidJUnit4;

import com.contacts.Contacts;

import org.junit.Test;
import org.junit.runner.RunWith;

import static junit.framework.TestCase.assertNotNull;
import static org.junit.Assert.assertTrue;

@RunWith(AndroidJUnit4.class)
public class ContactsTest {
    @Test
    public void getVersionReturnsSemVerFormattedVersion() {
        String semVerRegex =
                "^([0-9]+)\\.([0-9]+)\\.([0-9]+)(?:-([0-9A-"
                        + "Za-z-]+(?:\\.[0-9A-Za-z-]+)*))?(?:\\+[0-9A-Za-z-]+)?$";
        String version = Contacts.getVersion();

        assertNotNull(version);
        assertTrue(version.matches(semVerRegex));
    }
}
