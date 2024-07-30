package com.example.gles_cube;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import com.example.gles_cube.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'gles_cube' library on application startup.
    static {
        System.loadLibrary("gles_cube");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        TextView tv = binding.sampleText;
        tv.setText(stringFromJNI());
    }

    /**
     * A native method that is implemented by the 'gles_cube' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}