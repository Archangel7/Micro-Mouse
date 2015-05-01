package com.example.mousecontroller;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.URL;
import java.util.Set;
import java.util.UUID;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;


public class MainActivity extends Activity {

	private BluetoothAdapter mBluetoothAdapter = null;
    private BluetoothSocket btSocket = null;
    private OutputStream outStream = null;
    private InputStream instream = null;
    TextView tv;
    TextView tv2;
    TextView tv3;
    private static final UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
    private InputStream inStream = null;
    Handler handler = new Handler();
    private String dataToSend;
    byte delimiter = 10;
    boolean stopWorker = false;
    int readBufferPosition = 0;
    byte[] readBuffer = new byte[1024];
	String address = "itead";
	BluetoothDevice mydevice = null;
    Thread workerThread;  
    Handler message;
    
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        tv = (TextView)findViewById(R.id.textView1);
        tv2 = (TextView)findViewById(R.id.textView2);
        tv3 = (TextView)findViewById(R.id.textView3);
        tv.setText("not connected");
        tv2.setText("");
        tv3.setText("");
        mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        enableBluetooth();
    }
       
    public void startBluetooth(View view)
    {
    	connectToMouse();
    }
    
    public void enableBluetooth()
    {    	
    	 if(!mBluetoothAdapter.isEnabled())
    	 {
    	      Intent enableBluetooth = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
    	      startActivityForResult(enableBluetooth, 0);
    	 }
    	 Toast.makeText(MainActivity.this, "Bluetooth Enabled!", Toast.LENGTH_SHORT).show();
    }
    
    public void connectToMouse()
    {
    	Set<BluetoothDevice> pairedDevices = mBluetoothAdapter.getBondedDevices();
    	    	
    	 if (pairedDevices.size() > 0)
    	 {
		 	// Loop through paired devices
             for (BluetoothDevice device : pairedDevices)
             {
            	 if(device.getName().toString().equals("itead"))
                 {  	 
                	mydevice = device;
                 }
                 else
                 {
                	 mydevice = device;
                 }
             }
    	 }
             Log.d("Address", address);
             BluetoothDevice device = mBluetoothAdapter.getRemoteDevice(mydevice.getAddress());
             Log.d("connect", "Connecting to ... " + device);
             mBluetoothAdapter.cancelDiscovery();
             try {
                     btSocket = device.createRfcommSocketToServiceRecord(MY_UUID);
                     btSocket.connect();
                     Log.d("connecting", "Connection made");
                     Toast.makeText(MainActivity.this, "Connected",Toast.LENGTH_SHORT).show();
                     tv.setText("Connected");
                     outStream = btSocket.getOutputStream();
                     instream  = btSocket.getInputStream();
             } 
             catch (IOException e)
             {
                     try
                     {
                          btSocket.close();
                     }
                     catch (IOException e2)
                     {
                             Log.d("Unable", "Unable to end the connection");
                             Toast.makeText(getApplicationContext(), "Impossibile terminare la connessione",Toast.LENGTH_SHORT).show();
                     }
                     Log.d("socket failed", "Socket creation failed");
                     Toast.makeText(getApplicationContext(), "Couldn't connect",Toast.LENGTH_SHORT).show();
                     tv.setText("couldnt connect");
             }
             beginListenForData();
     }
   	
    public void closeConnection(View view)
    {
    	try
    	{
			btSocket.close();
		}
    	catch (IOException e)
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
    	tv.setText("Connection closed");
    	tv2.setText("");
    }
    
    public void backward(View view)
    {
    	write("4");
    	tv2.setText("Reverse");
    }
    public void forward(View view)
    {
    	write("1");
    	tv2.setText("Forward");
    }
    public void turnLeft(View view)
    {
    	write("2");
    	tv2.setText("Turn Left");
    }
    public void turnRight(View view)
    {
    	write("3");
    	tv2.setText("Turn Right");
    }
    public void stop(View view)
    {
    	write("0");
    	tv2.setText("Stop");
    }
    
    public void beginListenForData()
    {
        final Handler handler = new Handler();
        final byte delimiter = 10; //This is the ASCII code for a newline character

        stopWorker = false;
        readBufferPosition = 0;
        readBuffer = new byte[1024];
        
        workerThread = new Thread(new Runnable()
        {
            public void run()
            {      
            	while(true)
            	{
               // while(!Thread.currentThread().isInterrupted() && !stopWorker)
               // {
                    try
                    {
                        int bytesAvailable = instream.available();
                        int bytes = 0;
                        final int s = bytesAvailable;
                        /*
                        runOnUiThread(new Runnable(){
                    		public void run()
                    		{
                    			Toast.makeText(getApplicationContext(),"",Toast.LENGTH_SHORT).show();
                    			tv3.setText(""+s);
                    		}
                    	});
                    	*/   
                        if(bytesAvailable > 0)
                        {
                            final byte[] packetBytes = new byte[bytesAvailable];
                            instream.read(packetBytes);
                            
                            String input = new String(packetBytes, 0, bytes);
                                                
                            runOnUiThread(new Runnable(){
                        		public void run()
                        		{
                        			Toast.makeText(getApplicationContext(), packetBytes.toString(),Toast.LENGTH_SHORT).show();
                        			tv3.setText("input");
                        		}
                        	});   
                            
                            
                            for(int i=0;i<bytesAvailable;i++)
                            {
                                byte b = packetBytes[i];
                                if(b == delimiter)
                                {
                                    byte[] encodedBytes = new byte[readBufferPosition];
                                    System.arraycopy(readBuffer, 0, encodedBytes, 0, encodedBytes.length);
                                    final String data = new String(encodedBytes, "US-ASCII");
                                    readBufferPosition = 0;

                                    
                                    runOnUiThread(new Runnable()
                                    {
                                		public void run()
                                		{
                                			Toast.makeText(getApplicationContext(),data,Toast.LENGTH_SHORT).show();
                                			tv3.setText(data);
                                		}
                                	});
                                    
                                    /*
                                    handler.post(new Runnable()
                                    {
                                        public void run()
                                        {
                                            tv3.setText("derp");
                                        }
                                    });
                                    */
                                }
                                else
                                {
                                    readBuffer[readBufferPosition++] = b;
                                }
                            }
                        }
                    }
                    catch (IOException ex) 
                    {
                        stopWorker = true;
                    }
                }
            }
        });
        workerThread.start();
    }
    	
    public void write(String message) 
    {
        Log.d("sending", "...Data to send: " + message + "...");
        byte[] msgBuffer = message.getBytes();
        try
        {
        	outStream.write(msgBuffer);
        }
        catch (IOException e)
        {
            Log.d("Error", "...Error data send: " + e.getMessage() + "...");
        }
    }
    
    @Override
    public boolean onCreateOptionsMenu(Menu menu) 
    {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }
    
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        if (id == R.id.action_settings) 
        {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }
}
