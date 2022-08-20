package com.example.a18119098_vuongnhatnam;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.core.view.GravityCompat;
import androidx.drawerlayout.widget.DrawerLayout;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;

import android.content.Intent;
import android.os.Bundle;
import android.view.MenuItem;

import com.google.android.material.navigation.NavigationView;

public class MainActivity extends AppCompatActivity {
    private Toolbar toolbar;
    private DrawerLayout mDrawer;
    private NavigationView nvDrawer;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        toolbar = findViewById(R.id.toolbar);
        mDrawer = findViewById(R.id.drawerlayout);
        nvDrawer = findViewById(R.id.nvView);

        setSupportActionBar(toolbar);
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);
        getSupportActionBar().setHomeAsUpIndicator(R.drawable.ic_menu);
        setupDrawerContent(nvDrawer);
        loadFragment(new HomeFragment());
    }

    @Override
    public boolean onOptionsItemSelected(@NonNull MenuItem item) {
        switch (item.getItemId()){
            case android.R.id.home:
                mDrawer.openDrawer(GravityCompat.START);
                return true;
        }
        return super.onOptionsItemSelected(item);
    }
    private void setupDrawerContent(NavigationView navigationView){
        navigationView.setNavigationItemSelectedListener(new NavigationView.OnNavigationItemSelectedListener() {
            @Override
            public boolean onNavigationItemSelected(@NonNull MenuItem item) {
                Fragment fragment;
                switch (item.getItemId()) {
                    case R.id.hcm:
                        fragment = new HCMFragment();
                        loadFragment(fragment);
                        break;
                    case R.id.dalat:
                        fragment = new DaLatFragment();
                        loadFragment(fragment);
                        break;
                    case R.id.hanoi:
                        fragment = new HaNoiFragment();
                        loadFragment(fragment);
                        break;
                    case R.id.setting:
                        fragment = new SettingFragment();
                        loadFragment(fragment);
                        break;
                    case R.id.profile:
                        fragment = new ProfileFragment();
                        loadFragment(fragment);
                        break;
                    default:
                        fragment = new HCMFragment();
                        loadFragment(fragment);
                }
                item.setChecked(true);
                setTitle(item.getTitle());
                mDrawer.closeDrawers();
                return true;
            }
        });
    }
    private void loadFragment(Fragment fragment){
        FragmentManager fragmentManager = getSupportFragmentManager();
        FragmentTransaction transaction = fragmentManager.beginTransaction();
        transaction.replace(R.id.flContent,fragment);
        transaction.addToBackStack(null);
        transaction.commit();
    }
}