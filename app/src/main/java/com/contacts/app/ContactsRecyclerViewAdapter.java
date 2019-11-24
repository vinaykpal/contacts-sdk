package com.contacts.app;

import android.content.Context;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.recyclerview.widget.RecyclerView;

import java.util.ArrayList;
import java.util.List;

public class ContactsRecyclerViewAdapter extends RecyclerView.Adapter<ContactsRecyclerViewAdapter.ViewHolder> {

    private static final String TAG = "contacts-sdk";
    private List<String> mData;
    private ArrayList<ArrayList<String>> contactsData;
    private LayoutInflater mInflater;
    private ItemClickListener mClickListener;

    ArrayList<String> firstNameList; //= contactsData.get(0);
    ArrayList<String> lasstNameList ;//= contactsData.get(1);
    ArrayList<String> phoneList;// = contactsData.get(2);

    // data is passed into the constructor
    ContactsRecyclerViewAdapter(Context context,ArrayList<ArrayList<String>> data) {
        this.mInflater = LayoutInflater.from(context);
        //this.mData = data;
        this.contactsData = data;

        firstNameList = contactsData.get(0);
        lasstNameList = contactsData.get(1);
        phoneList = contactsData.get(2);

        Log.i(TAG, "firstName ArrayList " + firstNameList);
        Log.i(TAG, "lastName ArrayList " + lasstNameList);
        Log.i(TAG, "phoneNum ArrayList " + phoneList);

    }

    // inflates the row layout from xml when needed
    @Override
    public ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View view = mInflater.inflate(R.layout.contacts_list_r, parent, false);
        Log.i(TAG, "onCreateViewHolder:  " );
        return new ViewHolder(view);
    }

    // binds the data to the TextView in each row
    @Override
    public void onBindViewHolder(ViewHolder holder, int position) {

        holder.firstTextView.setText(firstNameList.get(position));
        holder.lastTextView.setText(lasstNameList.get(position));
        holder.phoneTextView.setText(phoneList.get(position));
    }

    // total number of rows
    @Override
    public int getItemCount() {

        Log.i(TAG, "getItemCount " +contactsData.get(0).size() );
        return contactsData.get(0).size();
    }

    // stores and recycles views as they are scrolled off screen
    public class ViewHolder extends RecyclerView.ViewHolder implements View.OnClickListener {
        TextView firstTextView;
        TextView lastTextView;
        TextView phoneTextView;

        ViewHolder(View itemView) {
            super(itemView);
            firstTextView = itemView.findViewById(R.id.tv_contactFirstName);
            lastTextView = itemView.findViewById(R.id.tv_contactLastName);
            phoneTextView = itemView.findViewById(R.id.tv_contactPhone);

            itemView.setOnClickListener(this);
        }

        @Override
        public void onClick(View view) {
            if (mClickListener != null) mClickListener.onItemClick(view, getAdapterPosition());
        }
    }

    // convenience method for getting data at click position
    ArrayList<String> getItem(int id) {
        ArrayList<String> contact = new ArrayList<>();
        contact.add(firstNameList.get(id));
        contact.add(lasstNameList.get(id));
        contact.add(phoneList.get(id));

        return contact;
    }

    // allows clicks events to be caught
    void setClickListener(ItemClickListener itemClickListener) {
        this.mClickListener = itemClickListener;
    }

    // parent activity will implement this method to respond to click events
    public interface ItemClickListener {
        void onItemClick(View view, int position);
    }
}
