package com.plume.motorcontroler;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;

import android.support.v4.app.Fragment;
import android.view.View;
import android.view.ViewGroup;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View.OnClickListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.CompoundButton.OnCheckedChangeListener;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.Toast;

public class ControlSectionFragment extends Fragment  implements OnClickListener, OnCheckedChangeListener{
    
	View view = null;
	
    Button btn_ok = null;
    Button btn_cancel = null;
	
    CheckBox cbx_enable = null;
    EditText txt_frqn = null;
    Spinner spn_dir = null;
    
    int frequency = 10;
    boolean enable = true;
    String direction = "F";
    
    public ControlSectionFragment() {
    }


	@Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
            Bundle savedInstanceState) {
        view = inflater.inflate(R.layout.tab_control, container, false); 
        
        btn_ok = (Button) view.findViewById(R.id.app_control_ok_btn);
        btn_ok.setOnClickListener(this);
        btn_cancel = (Button) view.findViewById(R.id.app_control_cancel_btn);
        btn_cancel.setOnClickListener(this);
        
        cbx_enable = (CheckBox) view.findViewById(R.id.app_control_enable_cbx);
        cbx_enable.setOnCheckedChangeListener(this);        
        
        txt_frqn = (EditText) view.findViewById(R.id.app_control_frequency_txt);
        txt_frqn.setText(String.valueOf(frequency));
        
        spn_dir = (Spinner) view.findViewById(R.id.app_control_direction_spnr);
        
        ArrayAdapter adapter2 = 
        		ArrayAdapter.createFromResource(getActivity(), R.array.app_control_dirs_set, android.R.layout.simple_spinner_item);
        adapter2.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        
        spn_dir.setAdapter(adapter2);
        spn_dir.setSelection(0);
        
        cbx_enable.setChecked(true);
        
        return view;
    }


	@Override
	public void onClick(View v) {
		if(((Button)v).getId() == btn_ok.getId()){
			if(MotorControlActivity.socket == null){
				Toast.makeText(v.getContext(), R.string.app_control_msg_not_connected, Toast.LENGTH_SHORT).show();
				return;
			}
			
			String result = null;
			
		    boolean t_Enable = cbx_enable.isChecked();
		    if(!t_Enable){
		    	this.enable = false;
		    	
		    	result = sendAndRecieve("STOP");
		    }
		    else{
			    int t_Frequency = Integer.valueOf(txt_frqn.getText().toString());
			    String t_Ddirection = (spn_dir.getSelectedItemPosition() == 0) ? "F" : "R";
			    
			    if(t_Frequency < 10 || t_Frequency > 1000){
			    	Toast.makeText(v.getContext(), R.string.app_control_frqn_range_error, Toast.LENGTH_SHORT).show();
			    	return;
			    }
			    
			    if(t_Ddirection != "F" && t_Ddirection != "R"){
			    	Toast.makeText(v.getContext(), R.string.app_control_dir_set_error, Toast.LENGTH_SHORT).show();
			    	return;
			    }
			    
			    this.enable = true;
			    this.frequency = t_Frequency;
			    this.direction = t_Ddirection;
			    
			    int f = (int) ((double) t_Frequency) / 10;
			    String cmd = "START " + f + " " + this.direction;
			    
			    result = sendAndRecieve(cmd);
			    if(result != null && result.contains("SUCCESS")){
			    	Toast.makeText(v.getContext(), R.string.app_control_msg_change_sucess, Toast.LENGTH_SHORT).show();
			    }else{
			    	Toast.makeText(v.getContext(), R.string.app_control_msg_change_fail, Toast.LENGTH_SHORT).show();
			    }
		    }
			
		}else if(((Button)v).getId() == btn_cancel.getId()){			
			// restore the values
		    txt_frqn.setText(frequency);
		    spn_dir.setSelection((direction == "F") ? 0 : 1);
		    cbx_enable.setChecked(enable);
		}
	}


	@Override
	public void onCheckedChanged(CompoundButton arg0, boolean isChecked) {
	    txt_frqn.setEnabled(isChecked);
	    spn_dir.setEnabled(isChecked);
	}
	
	private String sendAndRecieve(String cmd){
		String result = null;
		try {
			
			MotorControlActivity.writer.write(cmd, 0 , cmd.length());
			MotorControlActivity.writer.flush();
			result = MotorControlActivity.reader.readLine();
			
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		
		return result;
	}
}
