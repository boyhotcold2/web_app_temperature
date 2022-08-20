package com.example.a18119098_vuongnhatnam;

import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class DaLatFragment extends Fragment {

    private TextView tvtemp, tvhumd, tvco2, tvnoise, tvuv, tvwind ;
    private String humi,temp,co2,noise,uv,wind;
    FirebaseDatabase database = FirebaseDatabase.getInstance();
    DatabaseReference myRef = database.getReference("DALAT");

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_da_lat, container, false);
        tvtemp = view.findViewById(R.id.view3);
        tvhumd = view.findViewById(R.id.view6);
        tvco2 = view.findViewById(R.id.view8);
        tvnoise = view.findViewById(R.id.view10);
        tvuv = view.findViewById(R.id.view12);
        tvwind = view.findViewById(R.id.view14);

        myRef.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                humi = snapshot.child("HUMI").getValue().toString();
                temp = snapshot.child("TEMP").getValue().toString();
                co2 = snapshot.child("CO2").getValue().toString();
                noise = snapshot.child("NOISE").getValue().toString();
                uv = snapshot.child("UV").getValue().toString();
                wind = snapshot.child("GIO").getValue().toString();


                tvco2.setText(co2 + "PPM");
                tvhumd.setText(humi + "%");
                tvtemp.setText(temp + "°C");
                tvnoise.setText(noise + "dB");
                tvuv.setText(uv + "");
                tvwind.setText(wind + " km/h");
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });

        return view;
    }
}