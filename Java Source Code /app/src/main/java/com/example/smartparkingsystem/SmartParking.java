package com.example.smartparkingsystem;

import android.app.Application;

import com.firebase.client.Firebase;

public class SmartParking extends Application {

    @Override
    public void onCreate() {
        super.onCreate();

        Firebase.setAndroidContext(this);
    }
}
