package edu.utsa.cs3443.tro893_lab5;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import edu.utsa.cs3443.tro893_lab5.model.User;
import edu.utsa.cs3443.tro893_lab5.model.UserManager;

import java.io.IOException;

public class MainActivity extends AppCompatActivity {

    private EditText editTextUsername;
    private EditText editTextPassword;
    private Button buttonLogin;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        editTextUsername = findViewById(R.id.editTextUsername);
        editTextPassword = findViewById(R.id.editTextPassword);
        buttonLogin = findViewById(R.id.buttonLogin);

        // Load user data
        try {
            UserManager.loadUsers(this, "users.csv");
        } catch (IOException e) {
            e.printStackTrace();
            Toast.makeText(this, "Failed to load user data.", Toast.LENGTH_SHORT).show();
            return; // Exit if users cannot be loaded
        }

        buttonLogin.setOnClickListener(v -> attemptLogin());
    }

    private void attemptLogin() {
        String username = editTextUsername.getText().toString();
        String password = editTextPassword.getText().toString();

        User user = UserManager.getUserByUsername(username);
        if (user != null && user.validate(username, password)) {
            Intent intent = new Intent(MainActivity.this, RoleActivity.class);
            intent.putExtra("username", username);
            startActivity(intent);
            finish();
        } else {
            Toast.makeText(this, "Invalid username or password.", Toast.LENGTH_SHORT).show();
        }
    }
}
