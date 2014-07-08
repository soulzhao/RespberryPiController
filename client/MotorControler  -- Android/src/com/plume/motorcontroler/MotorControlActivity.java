package com.plume.motorcontroler;

import android.app.ActionBar;
import android.app.FragmentTransaction;
import android.os.Bundle;
import android.support.v4.app.FragmentActivity;
import android.support.v4.view.ViewPager;
import android.view.KeyEvent;
import android.view.Menu;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;
import java.util.Timer;
import java.util.TimerTask;

import android.os.StrictMode;

public class MotorControlActivity extends FragmentActivity implements ActionBar.TabListener {

    /**
     * The {@link android.support.v4.view.PagerAdapter} that will provide
     * fragments for each of the sections. We use a
     * {@link android.support.v4.app.FragmentPagerAdapter} derivative, which
     * will keep every loaded fragment in memory. If this becomes too memory
     * intensive, it may be best to switch to a
     * {@link android.support.v4.app.FragmentStatePagerAdapter}.
     */
    SectionsPagerAdapter mSectionsPagerAdapter;

    /*
     * Define socket things
     */
    public static Socket socket = null;

	public static BufferedWriter writer = null;
	public static BufferedReader reader = null;
	
    
    /**
     * The {@link ViewPager} that will host the section contents.
     */
    ViewPager mViewPager;

    @Override
    protected void onCreate(Bundle savedInstanceState) {     
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_motor_control);

        if (android.os.Build.VERSION.SDK_INT > 9) {
            StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
            StrictMode.setThreadPolicy(policy);
        }
        
        // Set up the action bar.
        final ActionBar actionBar = getActionBar();
        actionBar.setNavigationMode(ActionBar.NAVIGATION_MODE_TABS);
        
        // Create the adapter that will return a fragment for each of the three
        // primary sections of the app.
        mSectionsPagerAdapter = new SectionsPagerAdapter(getSupportFragmentManager(), this);        
        // Set up the ViewPager with the sections adapter.
        mViewPager = (ViewPager) findViewById(R.id.pager);
        mViewPager.setAdapter(mSectionsPagerAdapter);

        // When swiping between different sections, select the corresponding
        // tab. We can also use ActionBar.Tab#select() to do this if we have
        // a reference to the Tab.
        mViewPager.setOnPageChangeListener(new ViewPager.SimpleOnPageChangeListener() {
            @Override
            public void onPageSelected(int position) {
                actionBar.setSelectedNavigationItem(position);
            }
        });

        // For each of the sections in the app, add a tab to the action bar.
        for (int i = 0; i < mSectionsPagerAdapter.getCount(); i++) {
            // Create a tab with text corresponding to the page title defined by
            // the adapter. Also specify this Activity object, which implements
            // the TabListener interface, as the callback (listener) for when
            // this tab is selected.
            actionBar.addTab(
                    actionBar.newTab()
                            .setText(mSectionsPagerAdapter.getPageTitle(i))
                            .setTabListener(this));
        }

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.activity_motor_control, menu);
        return true;
    }
    
    @Override
    public void onTabSelected(ActionBar.Tab tab, FragmentTransaction fragmentTransaction) {
        // When the given tab is selected, switch to the corresponding page in
        // the ViewPager.
        mViewPager.setCurrentItem(tab.getPosition());
    }

    @Override
    public void onTabUnselected(ActionBar.Tab tab, FragmentTransaction fragmentTransaction) {
    }

    @Override
    public void onTabReselected(ActionBar.Tab tab, FragmentTransaction fragmentTransaction) {
    }
    
    private static Boolean isExit = false;
    private static Boolean hasTask = false;
    Timer tExit = new Timer();
    TimerTask task = new TimerTask() {

        @Override
        public void run() {
            isExit = true;
            hasTask = true;
        }
    };
    
    
    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        //System.out.println("TabHost_Index.java onKeyDown");
        if (keyCode == KeyEvent.KEYCODE_BACK) {
            if (isExit == false) {
                isExit = true;
                Toast.makeText(this, R.string.app_exit, Toast.LENGTH_SHORT).show();
                if (!hasTask) {
                    tExit.schedule(task, 2000);
                }
            } else {
            	if(socket != null)
					try {
						if(writer != null) writer.close();
						if(reader != null) reader.close();
						if(socket != null) socket.close();
						
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
                finish();
                System.exit(0);
            }
        }
        return true;

    }

}
