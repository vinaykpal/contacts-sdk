package com.contacts.app;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.content.Context;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.RelativeLayout;
import android.widget.Toast;

import com.contacts.ContactListener;
import com.contacts.Contacts;
import com.contacts.Initiater;
import com.contacts.app.R;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;

/**
 * Use this application to demonstrate the capabilities of the Contacts SDK you have implemented.
 * Specifically this app should contain the following features:
 *
 * 1. List all of a user's contacts.
 * 2. Add a contact
 * 3. Update the UI when a contact is updated.
 */
public class ContactsActivity extends AppCompatActivity implements ContactsRecyclerViewAdapter.ItemClickListener, ContactListener {

    private static final String TAG = "contacts-sdk";//ContactsActivity.class.getSimpleName();

    ContactsRecyclerViewAdapter adapter;
    // data to populate the RecyclerView with
    ArrayList<String> firstName = new ArrayList<>();
    ArrayList<String> lastName = new ArrayList<>();
    ArrayList<String> phoneNum = new ArrayList<>();

    ArrayList<ArrayList<String>> dataList = new ArrayList<>();


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_contacts);

        String version = Contacts.getVersion();

        Initiater initiater = new Initiater();
        initiater.addListener(this);
        Contacts.setInitiaterCtx(initiater);

        Contacts.registerCallback();//register to gt callback from native

        getContactLists();
        recyclerViewUpdate();

        Contacts.startUpdateTimer(); //start contact update timer in native
    }

    @Override
    private void onContactAdded(String status) {
        showToast("contact added " + status + " !!");
    }

    @Override
    public void onContactUpdated(String newContact, String oldContact) {
        Log.i(TAG, "onContactUpdated() responder");

        removeOldContact(oldContact);
        addNewContact(newContact);

    }

    private void removeOldContact(String oldContact) {
        int indxFirstName = 0;
        int indxLastName =0 ;
        int indxPhone =0 ;
        boolean update = false;
        try {
            JSONObject jsonObject = new JSONObject(oldContact);

            if (firstName.contains(jsonObject.optString("first"))) {
                indxFirstName = firstName.indexOf(jsonObject.optString("first"));
                update = true;
            }
            if (lastName.contains(jsonObject.optString("last"))) {
                indxLastName = lastName.indexOf(jsonObject.optString("last"));
                update = true;
            }
            if (phoneNum.contains(jsonObject.optString("phone"))) {
                indxPhone = phoneNum.indexOf(jsonObject.optString("phone"));
                update = true;
            }

            if((update == true) &&((indxFirstName == indxLastName) && (indxFirstName == indxPhone)) ){
                firstName.remove(indxFirstName);
                lastName.remove(indxLastName);
                phoneNum.remove(indxPhone);
            } else {
                Log.i(TAG, "old contact is not in the existing list");
            }
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    private void addNewContact (String newContact) {
        try {
            JSONObject jsonObject = new JSONObject(newContact);

            firstName.add(jsonObject.optString("first"));
            lastName.add(jsonObject.optString("last"));
            phoneNum.add(jsonObject.optString("phone"));

        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
    }

    public void recyclerViewUpdate() {
        dataList.clear();

        dataList.add(firstName);
        dataList.add(lastName);
        dataList.add(phoneNum);

        // set up the RecyclerView
        RecyclerView recyclerView = findViewById(R.id.contacts_rv);
        recyclerView.setLayoutManager(new LinearLayoutManager(this));

        adapter = new ContactsRecyclerViewAdapter(this, dataList);
        adapter.setClickListener(this);
        recyclerView.setAdapter(adapter);
    }

    /** Called when the user press Add Good contact the button */
    public void addGoodContact(View view)
    {
        Log.i(TAG, "add new Good Contact");
        String newContact = "{\"first\" : \"Zebra\",\"last\" : \"Dog\",\"phone\" : \"+112343433111\"}";

        //call native api to add new contact
        Contacts.addNewCotact(newContact);
        getContactLists();
        recyclerViewUpdate();
    }

    /** Called when the user press Add Good contact the button */
    public void addBadContact(View view) {
        // Do something in response to button click
        Log.i(TAG, "add new Wrong Contact");

        String newContactWrong = "";
        //call native api to add new contact
        Contacts.addNewCotact(newContactWrong);

    }

    /** Called when the user touches the refresh List button */
    public void getListButton(View view)
    {
        // Do something in response to button click
        Log.i(TAG, "getListButton button");

        getContactLists();
        recyclerViewUpdate();

    }
    /** Called when the user touches the refresh List button */
    public void refreshButton(View view)
    {
        // Do something in response to button click
        Log.i(TAG, "refreshButton button");

        recyclerViewUpdate();

    }

    // TO contacts-SDK cpp
    public void getContactLists() {
        String listContacts = Contacts.getListContacts();
        Log.i(TAG, "#### getListContacts: " + listContacts);
        parseJsonData(listContacts);
    }


    public void parseJsonData(String listContacts) {
        firstName.clear();
        lastName.clear();
        phoneNum.clear();

        try {
            JSONArray contactsArr = new JSONArray(listContacts);

            for (int i = 0; i < contactsArr.length(); i++) {
                JSONObject jsonobject = contactsArr.getJSONObject(i);
                firstName.add(jsonobject.getString("first"));
                lastName.add(jsonobject.getString("last"));
                phoneNum.add(jsonobject.getString("phone"));

            }
        } catch (JSONException e) {
            Log.e(TAG , e.toString());
        }
    }

    @Override
    public void onItemClick(View view, int position) {
        showToast(adapter.getItem(position).get(0) + " " + adapter.getItem(position).get(1) +" number is " + adapter.getItem(position).get(2));
    }

    public void showToast(String msg) {
        Toast.makeText(this,  msg, Toast.LENGTH_SHORT).show();
    }

    @Override
    protected void onStart() {
        super.onStart();
    }

    @Override
    protected void onResume() {
        super.onResume();


    }
}
