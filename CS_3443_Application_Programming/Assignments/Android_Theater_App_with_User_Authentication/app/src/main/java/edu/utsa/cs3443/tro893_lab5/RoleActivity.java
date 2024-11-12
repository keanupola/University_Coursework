package edu.utsa.cs3443.tro893_lab5;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;
import java.io.IOException;
import java.util.List;

import androidx.appcompat.app.AppCompatActivity;

import edu.utsa.cs3443.tro893_lab5.model.User;
import edu.utsa.cs3443.tro893_lab5.model.Role;
import edu.utsa.cs3443.tro893_lab5.model.UserManager;


public class RoleActivity extends AppCompatActivity {

    private TextView textViewUserName;
    private TextView textViewRoles;
    private Button buttonActOne;
    private Button buttonActTwo;
    private Button buttonLogout;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_role);

        // Initialize UI components
        textViewUserName = findViewById(R.id.textViewUserName);
        textViewRoles = findViewById(R.id.textViewRoles);
        buttonActOne = findViewById(R.id.buttonActOne);
        buttonActTwo = findViewById(R.id.buttonActTwo);
        buttonLogout = findViewById(R.id.buttonLogout);

        // Retrieve the username from the intent
        String username = getIntent().getStringExtra("username");

        // Fetch the user details from the UserManager
        User user = UserManager.getUserByUsername(username);

        if (user != null) {
            // Display user details
            displayUserDetails(user);
        } else {
            // user not found
            handleUserNotFound();
        }

        setupButtonListeners();
    }

    private void displayUserDetails(User user) {
        textViewUserName.setText(String.format("Name: %s", user.getRealName()));
        StringBuilder rolesBuilder = new StringBuilder("Role(s):\n");
        for (Role role : user.getRoles()) {
            rolesBuilder.append(role.getName()).append("\n");
        }
        textViewRoles.setText(rolesBuilder.toString().trim());
    }

    private void handleUserNotFound() {
        textViewUserName.setText("User not found");
        textViewRoles.setText("");
    }

    private User fetchUserDetails(String username, List<User> users) {
        for (User user : users) {
            if (user.getUsername().equals(username)) {
                return user;
            }
        }
        return null; // User not found
    }

    private void setupButtonListeners() {
        buttonActOne.setOnClickListener(v -> navigateToAct(1));
        buttonActTwo.setOnClickListener(v -> navigateToAct(2));
        buttonLogout.setOnClickListener(v -> logout());
    }

    private void navigateToAct(int actNumber) {
        String username = getIntent().getStringExtra("username");
        Intent intent = new Intent(RoleActivity.this, ActActivity.class);
        intent.putExtra("act_number", actNumber);
        intent.putExtra("username", username); // Pass username to ActActivity
        startActivity(intent);
    }


    private void logout() {
        Intent intent = new Intent(RoleActivity.this, MainActivity.class);
        intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP | Intent.FLAG_ACTIVITY_NEW_TASK);
        startActivity(intent);
        finish();
    }
}
