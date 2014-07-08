package com.plume.motorcontroler;

import java.util.ArrayList;
import java.util.List;

import android.content.Context;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;



/**
 * A {@link FragmentPagerAdapter} that returns a fragment corresponding to
 * one of the sections/tabs/pages.
 */

public class SectionsPagerAdapter extends FragmentPagerAdapter {
	
	List<String> lFragmentTitles = new ArrayList<String>();
	
	private Context mContext;
	
    public SectionsPagerAdapter(FragmentManager fm, Context context) {
        super(fm);
        
        lFragmentTitles.add(context.getResources().getString(R.string.title_section1));
        lFragmentTitles.add(context.getResources().getString(R.string.title_section2));
        
        mContext = context;
    }

    @Override
    public Fragment getItem(int position) {
    	Fragment fragment = null;
    	if(position == 0){
    		fragment = new ControlSectionFragment();
//    		Bundle args = new Bundle();
//    		args.putInt(lFragmentTitles.get(0), position);
//    		fragment1.setArguments(args);
    	}else if(position == 1){
    		fragment = new SettingsSectionFragment();
//    		Bundle args = new Bundle(); 
//    		args.putInt(lFragmentTitles.get(0), position);
//    		fragment2.setArguments(args);
    	}
    	
    	return fragment;
    }

    @Override
    public int getCount() {
        return 2;
    }

    @Override
    public CharSequence getPageTitle(int position) {
    	return lFragmentTitles.get(position);
    }

}
