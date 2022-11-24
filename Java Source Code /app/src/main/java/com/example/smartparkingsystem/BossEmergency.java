package com.example.smartparkingsystem;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.ImageButton;
import android.widget.ListView;
import android.widget.PopupWindow;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import com.firebase.client.DataSnapshot;
import com.firebase.client.Firebase;
import com.firebase.client.FirebaseError;
import com.firebase.client.ValueEventListener;

import java.util.ArrayList;

public class BossEmergency extends AppCompatActivity {

    private Firebase root;
    private ListView listView;
    private ArrayList<commentBoss> list = new ArrayList<>();
    private commentBoss temp;
    ImageButton home;

    // inner class used to retrieve data from Firebase for display in the Emergency layout
    class commentBoss {
        String date, emergencyType, parkingSpot, user;

        // constructor
        commentBoss() {
            date = emergencyType = parkingSpot = user = "";
        }

        // setter methods
        public void setDate(String date) {
            this.date = date;
        }

        public void setEmergencyType(String comment) {
            this.emergencyType = comment;
        }

        public void setParkingSpot(String rating) {
            this.parkingSpot = rating;
        }

        public void setUser(String user) {
            this.user = user;
        }

    }

    @Override
    protected void onPause() {
        super.onPause();

        SharedPreferences prefs = getSharedPreferences("X", MODE_PRIVATE);
        SharedPreferences.Editor editor = prefs.edit();
        editor.putString("lastActivity", getClass().getName());
        editor.commit();
    }

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_boss_emergency);

        // reset new emergency messages flag to false
        Firebase resetEmergencyRead = new Firebase("https://smartparkingsystem-6187e.firebaseio.com/OwnerStatus/NewEmergencyMessages");
        resetEmergencyRead.setValue(false);

        home = (ImageButton) findViewById(R.id.homeBBB);
        listView = (ListView) findViewById(R.id.list_view_emergency);
        root = new Firebase("https://smartparkingsystem-6187e.firebaseio.com/EmergencyHistory");
        final ArrayAdapter<commentBoss> arrayAdapter = new ArrayAdapter<>(this, android.R.layout.simple_list_item_1, list);
        listView.setAdapter(arrayAdapter);

        // Display the correct values for Date, EmergenctType, ParkingNumber and User from firebase
        root.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {

                for (DataSnapshot child : dataSnapshot.getChildren()) {
                    temp = new commentBoss();
                    temp.setDate(child.child("Date").getValue(String.class));
                    temp.setEmergencyType(child.child("EmergencyType").getValue(String.class));
                    temp.setParkingSpot(child.child("ParkingNumber").getValue(String.class));
                    temp.setUser(child.child("User").getValue(String.class));

                    list.add(temp);
                    arrayAdapter.notifyDataSetChanged();
                }

            }

            @Override
            public void onCancelled(FirebaseError firebaseError) {

            }
        });

        home.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(BossEmergency.this, OwnerHomepage.class);
                startActivity(intent);
            }
        });
    }
}
