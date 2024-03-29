package com.example.smartparkingsystem;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.ImageButton;
import android.widget.ListView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import com.firebase.client.DataSnapshot;
import com.firebase.client.Firebase;
import com.firebase.client.FirebaseError;
import com.firebase.client.ValueEventListener;

import java.util.ArrayList;

public class CommentBoss extends AppCompatActivity {

    private Firebase root;
    private ListView listView;
    private ArrayList<commentObj> list = new ArrayList<>();
    private commentObj temp;

    private class commentObj {
        String key, date, comment, rating, user;

        commentObj() {
            key = date = comment = rating = user = "";
        }

        // setter methods
        public void setKey(String key) {
            this.key = key;
        }

        public void setDate(String date) {
            this.date = date;
        }

        public void setComment(String comment) {
            this.comment = comment;
        }

        public void setRating(String rating) {
            this.rating = rating;
        }

        public void setUser(String user) {
            this.user = user;
        }

        @NonNull
        @Override
        public String toString() {
            return String.format("\nUSER:  %s\t\t\t\t\t\t\t\tDATE:  %s\n\nCOMMENT: %s\nRATING: %s\n", user, date, comment, rating);
        }
    }

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_comment_boss);

        listView = (ListView) findViewById(R.id.list_view2);
        ImageButton home = (ImageButton) findViewById(R.id.homeBB);

        home.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // if home button is pressed, send user to Owner Homepage
                Intent intent = new Intent(CommentBoss.this, OwnerHomepage.class);
                startActivity(intent);
            }
        });

        root = new Firebase("https://smartparkingsystem-6187e.firebaseio.com/Comments");
        final ArrayAdapter<commentObj> arrayAdapter = new ArrayAdapter<>(this, android.R.layout.simple_list_item_1, list);
        listView.setAdapter(arrayAdapter);

        // populate commentObjs with comments and data
        // adding to list for display with array adapter
        root.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {
                for (DataSnapshot child : dataSnapshot.getChildren()) {
                    temp = new commentObj();

                    temp.setKey(child.child("Key").getValue(String.class));
                    temp.setDate(child.child("Date").getValue(String.class));
                    temp.setComment(child.child("Comment").getValue(String.class));
                    temp.setRating(child.child("Rating").getValue(String.class));
                    temp.setUser(child.child("User").getValue(String.class));

                    list.add(temp);
                    arrayAdapter.notifyDataSetChanged();
                }
            }

            @Override
            public void onCancelled(FirebaseError firebaseError) {

            }
        });
    }

    @Override
    protected void onPause() {
        super.onPause();

        SharedPreferences prefs = getSharedPreferences("X", MODE_PRIVATE);
        SharedPreferences.Editor editor = prefs.edit();
        editor.putString("lastActivity", getClass().getName());
        editor.commit();
    }
}
