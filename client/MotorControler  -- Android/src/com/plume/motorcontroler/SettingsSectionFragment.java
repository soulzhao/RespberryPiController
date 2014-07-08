package com.plume.motorcontroler;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;
import java.net.UnknownHostException;

import android.support.v4.app.Fragment;
import android.view.View;
import android.view.ViewGroup;
import android.content.DialogInterface;
import android.content.res.ColorStateList;
import android.view.View.OnClickListener;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class SettingsSectionFragment extends Fragment implements OnClickListener {
   
    Button btn_connect = null;
    Button btn_disconnect = null;
    
    String ipAddr = "192.168.1.104";
    int port = 8989;

    EditText txt_ipaddr = null;
    EditText txt_port = null;
	
    public SettingsSectionFragment() {
    	
    }

	@Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
            Bundle savedInstanceState) {
		View view =  inflater.inflate(R.layout.tab_settings, container, false);
		
        btn_connect = (Button) view.findViewById(R.id.app_settings_connect_btn);
        btn_connect.setOnClickListener(this);
        btn_disconnect = (Button) view.findViewById(R.id.app_settings_disconnect_btn);
        btn_disconnect.setOnClickListener(this);
        
        txt_ipaddr = (EditText) view.findViewById(R.id.app_host_ipaddr_txt);
        txt_port = (EditText) view.findViewById(R.id.app_host_port_txt);
        
        txt_ipaddr.setText(ipAddr);
        txt_port.setText(String.valueOf(port));
        
        setButtonStatus(true);
        return view;
    }

	@Override
	public void onClick(View v) {
		// TODO Auto-generated method stub
		if(((Button)v).getId() == btn_connect.getId()){
		    String t_IpAddr = txt_ipaddr.getText().toString();
		    int t_Port = 0;
		    t_Port = Integer.valueOf(txt_port.getText().toString());
			
		    if(t_IpAddr == null || 0 == t_Port){
		    	Toast.makeText(getActivity().getCurrentFocus().getContext(), 
						R.string.app_setting_params_not_set_correct + "\n", 
						Toast.LENGTH_SHORT).show();
		    	return;
		    }
			if(connect(t_IpAddr, t_Port)){		
				ipAddr = t_IpAddr;
				port = t_Port;
				
				setButtonStatus(false);
			}
		}else if(((Button)v).getId() == btn_disconnect.getId()){
			if(disConnect()){
			    ipAddr = "192.168.1.104";
			    port = 8989;
				
				setButtonStatus(true);
			}
		}
	}
	
	private void setButtonStatus(boolean connect){
		btn_connect.setClickable(connect);
		btn_connect.setBackgroundResource(connect ? R.drawable.btn_blue : R.drawable.btn_gray);
		ColorStateList color = getResources().getColorStateList(connect ? R.color.blue : R.color.gray);
		btn_connect.setTextColor(color);
		
		btn_disconnect.setClickable(!(connect));
		btn_disconnect.setBackgroundResource(connect ? R.drawable.btn_gray : R.drawable.btn_blue);
		color = getResources().getColorStateList(connect ? R.color.gray : R.color.blue);
		btn_disconnect.setTextColor(color);
	}
	
	private boolean connect(String ip, int prt){
		try {
			MotorControlActivity.socket  = new Socket(ip, prt);
			if(MotorControlActivity.reader == null)
				MotorControlActivity.reader = new BufferedReader(new InputStreamReader(MotorControlActivity.socket.getInputStream()));
			if(MotorControlActivity.writer == null)
				MotorControlActivity.writer = new BufferedWriter(new OutputStreamWriter(MotorControlActivity.socket.getOutputStream()));
			
			String readline = MotorControlActivity.reader.readLine();
			
			Toast.makeText(getActivity().getCurrentFocus().getContext(), 
					R.string.app_setting_msg_connect_success + "\n" + "Server say:" + readline, 
					Toast.LENGTH_SHORT).show();
			
			return true;
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			Toast.makeText(getActivity().getCurrentFocus().getContext(), 
					R.string.app_setting_msg_connect_fail + "\n" + "Error msg:" + e.getMessage(), 
					Toast.LENGTH_LONG).show();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			Toast.makeText(getActivity().getCurrentFocus().getContext(), 
					R.string.app_setting_msg_connect_fail + "\n" + "Server say:" + e.getMessage(), 
					Toast.LENGTH_LONG).show();
		}
		return false;
	}
	
	private boolean disConnect(){
		if(MotorControlActivity.socket == null) return false;
		
		try {
			MotorControlActivity.socket.close();
			MotorControlActivity.socket = null;
			
			MotorControlActivity.reader.close();
			MotorControlActivity.reader = null;
			
			MotorControlActivity.writer.close();
			MotorControlActivity.writer = null;
			return true;
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return false;
	}
}
